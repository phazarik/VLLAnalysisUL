##Import libraries
import ROOT
from ROOT import *
import copy
import os,sys
import setup.plotsetup.plot_settings as plotsetting
import setup.plotsetup.usefulFunctions as usefunc
import setup.plotsetup.plotmaker as pset
import json
from collections import defaultdict
from tabulate import tabulate

## USER DEFINED
LocalTest=True
CondorJobName ="VLL2018_1L2JAnalysis_Sep2_v0"
jsonfilepath="./external/InputFiles/"+CondorJobName+"/"
bkgbundle =["HTbinnedWJets","QCD_MuEnriched","SingleTop","TTBar","DYJetsToLL","WW","WZ","ZZ"]
sigbundle=["VLLM100","VLLM125","VLLM150","VLLM400"]

plotname = 'dijetmass'+'_l2j_regA;1'
#datalumi = 59.7*1000 #inpb
rebin = 25
##############################################

bkgname={"HTbinnedWJets":"wjets",
         "QCD_MuEnriched":"QCD",
         "SingleTop":"ST",
         "TTBar":"ttjets",
         "DYJetsToLL":"zjets",
         "WW":"WW",
         "WZ":"WZ",
         "ZZ":"ZZ"}
StackingColorScheme={
    'data':kBlack,
    'wjets':kGray+1,
    'zjets':kRed-9,
    'ttjets':kCyan-10,
    'ST':kCyan -9,
    'WZ':kBlue-9,
    'ZZ':kBlue-7,
    'WW':kGreen-4,
    'QCD':kYellow,
    'VLLM100':kMagenta,
    'VLLM125':kGreen,
    'VLLM150':kOrange,
    'VLLM200':kBlue,
    'VLLM400':kRed}
SignalCrossSectionDB={
    'VLLM100':1.17,
    'VLLM125':0.545,
    'VLLM150':0.29,
    'VLLM200':0.105,
    'VLLM250':0.046,
    'VLLM300':0.029,
    'VLLM350':0.0125,
    'VLLM400':0.0072
}

plotsetting.PlotRatioPad=True
plotsetting.year=2018                                                                                                           
plotsetting.publicationStyle=False
plotsetting.WorkInProgress=True


##--------------------------------------------------------------------------------------------------------------------#
##                                      DON'T TOUCH BELOW                                                             #
##--------------------------------------------------------------------------------------------------------------------#
#IMPORT ROOTPLOTMAKER JSON FILE

with open(jsonfilepath+CondorJobName+"_"+'rootplotmaker.json','r') as infile:
    jsonfile = json.load(infile)
#----------------------------------------------------------

## Get Histogram Dict
#pset.CheckGroupHisto(2018,bkgbundle,bkgname,CondorJobName,jsonfilepath,jsonfile,plotname)
##FunctionForSignalHistos
def GetSignalHistoDict(year,signalbundle,ifpath,plotname):
    if(year==2018):datalumi=59.7*1000
    if(year==2017):datalumi=41.5*1000
    if(year==2016):datalumi=35.1*1000
    
    ## READ TFiles
    SigFilesDict={}
    for ifile,filename in enumerate(signalbundle):
        file_ifile=TFile.Open(ifpath+CondorJobName+"_"+filename+'_sample.root','READ')
        SigFilesDict[filename]=file_ifile

    #print(SigFilesDict)

    #Get Histograms
    HistoDict={}
    for index,(filekey,file) in enumerate(SigFilesDict.items()):
        #print(filekey,file)
        #pname =plotname.rstrip(';1')+"_base;1"
        pname =plotname
        #print(pname)
        histo= file.Get(pname)
        histo.SetDirectory(0)
        histoevent=float(pset.Count(histo))

        #LumiCorr-------------------------------
        totEvent=file.nEvents.GetBinContent(2)
        Xsec=SignalCrossSectionDB[filekey]
        sampleLumi=totEvent/Xsec
        if(filekey!='data'): lumi_corr=datalumi/sampleLumi
        else: lumi_corr=1
        #print(filekey,totEvent,Xsec,sampleLumi,lumi_corr)    
        histo.Scale(lumi_corr)
        histoeventAfterCorr=float(pset.Count(histo))
        #---------------------------------------
        #histogram.append([filekey,histoevent,histoeventAfterCorr,OverlayColorScheme[filekey],histo])
        HistoDict[filekey]=[filekey,histoeventAfterCorr,StackingColorScheme[filekey],histo]

        #print(HistoDict)
    return HistoDict

def SquareRootHisto(histo):
    for i in range(histo.GetNcells()):
        bin=i
        #print(histo.GetBinContent(bin))
        histo.SetBinContent(bin,sqrt(histo.GetBinContent(bin)))
        #print(histo.GetBinContent(bin))
    return histo

def ClearHisto(histo):
    for i in range(histo.GetNcells()):
        bin=i
        #print(histo.GetBinContent(bin))
        histo.SetBinContent(bin,0)
        #print(histo.GetBinContent(bin))
    return histo  


def plotmaker_sigbkgstacker(SigHistoDict,BkgHistoDict,plotname,XaxisName,rebin,SaveOption,outputfilepath,outputPDFName):
        
    #Stacking(ONLY)
    stack=THStack()
    stackinglist=list(BkgHistoDict.keys())
    h_Allbkg=BkgHistoDict[stackinglist[0]][-1].Clone()
    h_Allbkg.Rebin(rebin)

    for imc,mc in reversed(list(enumerate(BkgHistoDict.keys()))):
        histoname=BkgHistoDict[mc][0]
        color=BkgHistoDict[mc][2]
        histo=BkgHistoDict[mc][-1]
        ##SetStyle
        histo.SetLineWidth(0)
        histo.SetLineColor(1)
        histo.SetFillColor(color)
        histo.Rebin(rebin)
        plotsetting.SetOverflowBin(histo)
        stack.Add(histo)
        #Denominotor for ratioPlot
        if(imc>0): h_Allbkg.Add(histo)

    ##Dummy RatioHisto        
    ratioHisto=h_Allbkg.Clone()
    #ratioHisto.Divide(h_Allbkg)
    h_den=copy.deepcopy(ratioHisto)
    h_den=SquareRootHisto(h_den)
    ratioHisto=ClearHisto(ratioHisto)
    print('stacking done...\n')

    ##Legend Settings
    legend = ROOT.TLegend(0.99, 0.45, 0.80,0.86)
    plotsetting.SetLegendStyle(legend)
    legend.SetTextSize(0.025)
    #bkg 
    for imc,mc in (list(enumerate(BkgHistoDict.keys()))):
        histoname=BkgHistoDict[mc][0]
        color=BkgHistoDict[mc][2]
        histo=BkgHistoDict[mc][-1]
        legend.AddEntry(histo,histoname+"["+pset.Count(histo)+"]","lf")
        
    ##Plotting
    cName=plotname
    canvas=TCanvas(cName,cName,700,600)
    pad=plotsetting.CreatePad("pad",0,1.0)
    #pad.SetLogy(0)
    pad.Draw()
    #RatioPad
    if(plotsetting.PlotRatioPad==True):
        ratioPad = plotsetting.CreateRatioPad('ratioPad',0,0.25)
        ratioPad.SetGrid(1)
        ratioPad.Draw()
        
    pad.cd()
    pad.SetFillStyle(4000)
    stack.SetMaximum(1e8)
    stack.SetMinimum(0.1)
    #dataHisto.Draw("ep")
    stack.Draw("HIST")

    for imc,mc in (list(enumerate(SigHistoDict.keys()))):
        histoname=SigHistoDict[mc][0]
        color=SigHistoDict[mc][2]
        histo=SigHistoDict[mc][-1]
            
        histo.SetLineWidth(2)
        histo.SetLineColor(color)
        histo.Rebin(rebin)
        plotsetting.SetOverflowBin(histo)
        histo.Draw("HIST SAME")
        if(mc=='VLLM100'):ratioHisto=histo.Clone()
        legend.AddEntry(histo,histoname+"["+pset.Count(histo)+"]","l")

            
    legend.Draw("SAME")

    ratioHisto.Divide(h_den)
    ##RatioPadDraw                                                                                                                  
    if(plotsetting.PlotRatioPad==True):
        ratioPad.cd()
        plotsetting.SetRatioHistoStyle(ratioHisto,xlabel=XaxisName)
        ratioHisto.SetFillColor(kGray)
        ratioHisto.SetLineWidth(1)
        ratioHisto.GetYaxis().SetTitle('S/#sqrt{B}')
        ratioHisto.GetYaxis().SetTitleOffset(1.6)
        ratioHisto.Draw('hist')
        ratioHisto.GetYaxis().SetRangeUser(-0.5,1.0)
        
    pad.cd()
    plotsetting.CMSLabel(pad)
    pad.SetTickx(1)
    pad.Update()
    plotsetting.SetStackHistoStyle(stack,xlabel="")
    
    #Extra Text
    pad.cd()
    plotsetting.DrawText(0.60,0.84,'2018 1L2J Base')
    
    print("leaving......drawing canvas")
    
    #canvas.Draw()
    
    
    #canvas.Draw()
    if(SaveOption==False):
        canvas.SaveAs("Plots/SigBkgStackPlots/"+plotname.rstrip(';1')+".pdf")
    if(SaveOption==True):
        canvas.Print(outputfilepath+outputPDFName)
        canvas.SaveAs(outputfilepath+plotname+'.pdf')
        
    return canvas,stack,legend,ratioHisto,histo



SigHistoDict=GetSignalHistoDict(2018,sigbundle,jsonfilepath,plotname)
SigHistoDict=pset.SortDict(SigHistoDict,True)
#print(SigHistoDict)    
BkgHistoDict=pset.GetGroupHistoDict(2018,bkgbundle,bkgname,CondorJobName,jsonfilepath,jsonfile,plotname)
BkgHistoDict=pset.SortDict(BkgHistoDict,True)
#print(BkgHistoDict)

canvas,stack,legend,ratioHisto,histo=plotmaker_sigbkgstacker(SigHistoDict,BkgHistoDict,plotname,plotname,25,False,'','')    
canvas.Draw()    




#############################################################################
##                   PLOT ALL THE VARIABLES                                ##
#############################################################################

if(LocalTest==False):
    ### MAKE PLOTS FOR ALL VARIABLES
    import time
    timex=time.ctime()
    print('_'.join(timex.split()))
    timestamp= '_'.join(timex.split())

    outputdir=CondorJobName+'_SigBkgStackPlots'+timestamp
    print(outputdir)
    os.makedirs("Plots/"+outputdir)
    outputfilepath= "Plots/"+outputdir+"/"


    ## Plots
    VariableName=["ptlep0","ptjet0","ptjet1","mtlep0","mtjet0","mtjet1","dijetmass","drjet01",
                  "dijetPT","dijetMT","MET","HT","ST","njet","nbjet","dphimetjet0","dphimetjet1",
                  "dphimetlep0","dphijet0lep0","dphijet1lep0","dphidijetlep0","dphimetdijet"]

    #RegionName=["_base"]#,"_regA","_regB","_regC","_regD"]
    RegionName=["_base","_base_mjj","_primaryCuts_mjj","_base_wjetbkg_mjj","_base_qcdbkg_mjj","_primaryCuts_wjetbkg_mjj",
                "_primaryCuts_qcdbkg_mjj","_regA","_regB","_regC","_regD","_ljjSR","_mjjSR","_ejjSR"]
    
    LabelName=["Lepton PT","Leading jet Pt","SubLeading jet pt","Lepton MT","Leading Jet MT",
               "Subleading Jet MT","Dijet Inv Mass","deltaR(jet0,jet1)","Dijet System Inv Mass",
               "Dijet System MT","MET","HT","ST","No of jets","No of b-jets","dphi(met,leading jet)",
               "dphi(met,subleading jet)","dphi(met,lepton)","dphi(jet0,lepton)","dphi(jet1,lepton)",
               "dphi(dijet system,lepton)","dphi(dijet system,met)"]


    binning=[20,20,20,25,25,25,25,5,25,25,25,25,25,1,1,5,5,5,5,5,5,5]

    outputPDFName='SigBkgOverlay_BasicSelection.pdf'
    c=TCanvas() 
    c.Print(outputfilepath+outputPDFName+"[")
    for ireg,reg in enumerate(RegionName):
        for ivar,var in enumerate(VariableName):
            plotname=var+'_l2j'+reg

            SigHistoDict=GetSignalHistoDict(2018,sigbundle,jsonfilepath,plotname)
            SigHistoDict=pset.SortDict(SigHistoDict,True)
            BkgHistoDict=pset.GetGroupHistoDict(2018,bkgbundle,bkgname,CondorJobName,jsonfilepath,jsonfile,plotname)
            BkgHistoDict=pset.SortDict(BkgHistoDict,True)

            XaxisName=LabelName[ivar]+reg
            rebin=binning[ivar]

            #Plotting in PDF
            plotmaker_sigbkgstacker(SigHistoDict,BkgHistoDict,plotname,XaxisName,rebin,True,outputfilepath,outputPDFName)

            SigHistoDict.clear()
            BkgHistoDict.clear()
    c.Print(outputfilepath+outputPDFName+"]")






