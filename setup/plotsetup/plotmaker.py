import setup.plotsetup.plot_settings as plotsetting
from tabulate import tabulate
import os,copy
import ROOT
from ROOT import *


def Count(histo):
    n_count="{:.3f}".format(histo.Integral())
    return str(n_count)


def SortDict(dic,opt):
    return dict(sorted(dic.items(),key=lambda x:x[1][1],reverse=opt))

StackingColorScheme={
    'data':kBlack,
    'wjets':kGray+1,
    'zjets':kRed-9,
    'ttjets':kCyan-10,
    'ST':kCyan -9,
    'WZ':kBlue-9,
    'ZZ':kBlue-7,
    'WW':kGreen-4,
    'QCD':kYellow    
}                 

def GetGroupHistoDict(runOnSkimmedSamples,year,bkgbundle,bkgname,condorjobname,ifpath,FilesList,var):    
    if(runOnSkimmedSamples):
        print("******YOU ARE RUNNING ON SKIMMED TREES\n LUMIS ARE SET BASED ON INPUT JSON FILE****** ")
    else:
        print("*******YOU ARE RUNNING ON UNSKIMMED FULL SAMPLES************")
    if(year==2018):datalumi=59.7*1000
    if(year==2017):datalumi=41.5*1000
    if(year==2016):datalumi=35.1*1000

    HistoDict={}
    for bundle in bkgbundle:
        samplehist=[]
        for index,(fkey,fname) in enumerate(FilesList[bundle].items()):
            file_= TFile.Open(ifpath+condorjobname+"_"+fname["filename"],'READ')
            #print("filename= ",file_)
            #print("\nplotname= ",var)
            histo = file_.Get(var)
            histo.SetDirectory(0)
            plotsetting.SetOverflowBin(histo)
            histoevent= float(Count(histo))
            totEvent  = file_.nEvents.GetBinContent(2)
            #getsamplelumi
            if(runOnSkimmedSamples==False):
                Xsec      = fname["xsec"]
                if(fname["data"]==0):
                    samplelumi= totEvent/Xsec
                else:
                    samplelumi=datalumi
            else:
                samplelumi=fname['lumi']

            #Scale
            histo.Scale(datalumi/samplelumi)
            #nevent(afterscale)
            histoevent_scale = float(Count(histo))

            #append all histos in a list to manipulate
            samplehist.append([index,histo,histoevent_scale,fkey])
            
            #print(samplehist[0])
        addhisto=samplehist[0][1] #FirstHistogram
        for listitem in samplehist:
            #print(listitem[0])
            if(listitem[0]>0):
                addhisto.Add(listitem[1]) #Add others to the first histo
        #print(addhisto)        
        #print(bundle+"("+bkgname[bundle]+") =  "+ Count(addhisto))
        ## Return a single added histogram for every sample Group
        ## HistoDictionary of histograms of a bkg group
        HistoDict[bundle]=[bkgname[bundle],float(Count(addhisto)),StackingColorScheme[bkgname[bundle]],addhisto]       

    return HistoDict

# CHECK ONE SAMPLEGROUP HISTOGRAMS IN A PRETTY TABLE
# [SAMPLENAME,NEVENTS(AFTER SELECTION),TOTAL_EVENTS,XSEC,LUMI,NEVENTS(AFTER LUMI WEIGHT APPLIED)]
def CheckGroupHisto(runOnSkimmedSamples,year,bkgbundle,bkgname,condorjobname,ifpath,FilesList,var):
    if(runOnSkimmedSamples):
        print("******YOU ARE RUNNING ON SKIMMED TREES\n LUMIS ARE SET BASED ON INPUT JSON FILE****** ")
    else:
        print("*******YOU ARE RUNNING ON UNSKIMMED FULL SAMPLES************")
    if(year==2018):datalumi=59.7*1000
    if(year==2017):datalumi=41.5*1000
    if(year==2016):datalumi=35.1*1000
    
    colname =["SampleName","Nevent","TotEvent","Xsec","Lumi(pb)","nEvents(scaled)"]
    HistoDict={}
    SampleGroup=[]
    for bundle in bkgbundle:
        samplehist=[]
        for index,(fkey,fname) in enumerate(FilesList[bundle].items()):
            file_= TFile.Open(ifpath+condorjobname+"_"+fname["filename"],'READ')
            histo = file_.Get(var)
            histo.SetDirectory(0)
            plotsetting.SetOverflowBin(histo)
            histoevent= float(Count(histo))
            totEvent  = file_.nEvents.GetBinContent(2)
            Xsec      = fname["xsec"]
            #getsamplelumi
            if(runOnSkimmedSamples==False):
                if(fname["data"]==0):
                    samplelumi= totEvent/Xsec
                else:
                    samplelumi=datalumi
            else:
                samplelumi=fname['lumi']
            #Scale
            histo.Scale(datalumi/samplelumi)
            #nevent(afterscale)
            histoevent_scale = float(Count(histo))
            ##Print in pretty table
            SampleGroup.append([fkey,histoevent,totEvent,Xsec,samplelumi,histoevent_scale])

    #Print all the sample info of a bundle
    print(tabulate(SampleGroup,headers=colname,tablefmt='fancy_grid',numalign='left',floatfmt=".2f"))    
    
    return 1


## ONLY MC STACK PLOTTING
def StackPlotter(Dictionary,plotname,Xaxislabel,rebin,SaveOption,outputfilepath,outputPDFName):
    Dict=copy.deepcopy(Dictionary)
    Dict=dict(sorted(Dict.items(),key=lambda x:x[1][1],reverse=True))

    ##Legend Settings
    legend = ROOT.TLegend(0.99, 0.45, 0.80,0.86)
    plotsetting.SetLegendStyle(legend)
    #legend.AddEntry(dataHisto,"Data ["+plotsetting.Count(dataHisto)+"]","ep")                                                           
    for imc,mc in (list(enumerate(Dict.keys()))):
        histoname=Dict[mc][0]
        color=Dict[mc][2]
        histo=Dict[mc][-1]
        legend.AddEntry(histo,histoname+"["+Count(histo)+"]","lf")


    #Stacking(ONLY)
    stack=THStack()
    for imc,mc in reversed(list(enumerate(Dict.keys()))):
        histoname=Dict[mc][0]
        color=Dict[mc][2]
        histo=Dict[mc][-1]
        ##SetStyle
        histo.SetLineWidth(0)
        histo.SetLineColor(1)
        histo.SetFillColor(color)
        histo.Rebin(rebin)
        plotsetting.SetOverflowBin(histo)
        stack.Add(histo)

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
    stack.Draw("HIST")
    legend.Draw("SAME")
    plotsetting.CMSLabel(pad)
    pad.SetTickx(1)
    pad.Update()

    #Extra Text
    pad.cd()
    plotsetting.DrawText(0.60,0.84,'2018 1L2J Base')

    #canvas.Draw()
    if(SaveOption==True):
        canvas.Print(outputfilepath+outputPDFName)
        canvas.SaveAs(outputfilepath+plotname+'.pdf')
       
    return canvas,stack,legend    


## MC STACK + DATA OVERLAID PLOTTING
def PlotMaker(Dictionary,plotname,Xaxislabel,rebin,SaveOption,outputfilepath,outputPDFName):
    
    plotsetting.PlotRatioPad=True
    
    Dict=copy.deepcopy(Dictionary)
    Dict=dict(sorted(Dict.items(),key=lambda x:x[1][1],reverse=True))
    
    ##DataHisto
    dataHisto=Dict['SingleMuon'][-1]
    dataHisto.Rebin(rebin)
    plotsetting.SetOverflowBin(dataHisto)
        
    ##Legend Settings
    legend = ROOT.TLegend(0.99, 0.45, 0.80,0.86) 
    plotsetting.SetLegendStyle(legend)
    legend.AddEntry(dataHisto,"Data ["+str(int(float(plotsetting.Count(dataHisto))))+"]","ep")
    
    #Remove data from stacking
    stackinglist=list(Dict.keys())
    while ('SingleMuon' in stackinglist):stackinglist.remove('SingleMuon')
    for imc,mc in (list(enumerate(stackinglist))):
        histoname=Dict[mc][0]
        color=Dict[mc][2]
        histo=Dict[mc][-1]
        legend.AddEntry(histo,histoname+" ["+str(int(float(Count(histo))))+"]","lf")
    

    #Stacking(ONLY)
    stack=THStack()
    ratioHisto=dataHisto.Clone()
    #print(stackinglist)
    h_Allbkg=Dict[stackinglist[-1]][-1].Clone()
    h_Allbkg.Rebin(rebin)
    
    for imc,mc in reversed(list(enumerate(stackinglist))):
        histoname=Dict[mc][0]
        color=Dict[mc][2]
        histo=Dict[mc][-1]
        ##SetStyle                                                                                                                  
        histo.SetLineWidth(0)
        histo.SetLineColor(1)
        histo.SetFillColor(color)
        histo.Rebin(rebin)
        plotsetting.SetOverflowBin(histo)
        stack.Add(histo)
        #Denominotor for ratioPlot
        if(mc != stackinglist[-1]): h_Allbkg.Add(histo)
    ratioHisto.Divide(h_Allbkg)
   
    ##Obs/Exp Legend
    obs=float(Count(dataHisto))
    exp=float(Count(h_Allbkg))
    ratioleg = ROOT.TLegend(0.99, 0.90, 0.81,0.87)
    plotsetting.SetLegendStyle(ratioleg)
    ratioleg.SetTextSize(0.03)
    ratioleg.SetHeader("obs/exp="+(str(obs/exp)[:5]))

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
    plotsetting.SetHistoStyle(dataHisto,xlabel="")
    #dataHisto.GetYaxis().SetRangeUser(0.1,1e8)
    stack.SetMaximum(1e8)
    stack.SetMinimum(0.1)
    #dataHisto.Draw("ep")
    stack.Draw("HIST")
    dataHisto.Draw("ep same")
    legend.Draw("SAME")
    ratioleg.Draw("SAME")
    plotsetting.CMSLabel(pad)
    pad.SetTickx(1)
    pad.Update()
    plotsetting.SetStackHistoStyle(stack,xlabel="")
    ##RatioPadDraw
    if(plotsetting.PlotRatioPad==True):
        ratioPad.cd()
        plotsetting.SetRatioHistoStyle(ratioHisto,xlabel=Xaxislabel) #xlabel=Xaxislabel
        #ratioHisto.GetXaxis().SetTitle("")
        ratioHisto.Draw('ep')

    
    #Extra Text
    pad.cd()
    plotsetting.DrawText(0.60,0.84,'2018 1L2J Base')
    
    #canvas.Draw()
    if(SaveOption==False):
        outdir=""
        if(outputfilepath==""):
            outdir=os.path.join("Plots","")
        else:
            outdir=os.path.join(outputfilepath,"")
        canvas.SaveAs(outdir+plotname+".pdf")
        canvas.SaveAs(outdir+plotname+".eps")
    if(SaveOption==True):
        canvas.Print(outputfilepath+outputPDFName)
        canvas.SaveAs(outputfilepath+plotname+'.eps')
       
    return canvas,stack,legend,ratioHisto,ratioleg
