##############################################################################
# FileName: pset_stackplotmaker.py 
# Task    : Produce stacked plots with data overlaid
# Author  : Arnab Laha(laha.arnab@students.iiserpune.ac.in)**ask me for help #
# ----------------------------------------------------
# This is a configuration file which actually use functions defined in setup/plotsetup/plotmaker.py file
# It uses two functions,
# 1. GetGroupHistoDict(**Args): to produce a dictionary containing,
#     {
#      'SampleGroup': ['AliasBackgroundName',Total Events, Stack Color, histogram]                  
#     }    
#    So, For example,
#     {"SingleMuon":['data',88907654,kBlack,<data histogram pointer>]}
#
# 2. PlotMaker(**Args): to produce the plot by manipulating the histograms available from the available
#                       dictionary     
##############################################################################

#Import Libraries
import ROOT
from ROOT import *
import os,sys

import setup.plotsetup.plot_settings as plotsetting #import plotsetting from setup/plotsetup
import setup.plotsetup.plotmaker as pset            #import plotsetting from setup/plotsetup
import json

## USER DEFINED
LocalTest=False
runOnSkimmedSample=False
CondorJobName ="VLL2018_1L2JAnalysisWJetsEstimation_Sep13_v0"
inputfilepath ="external/InputFiles/"+CondorJobName+"/"
bkgbundle =["HTbinnedWJets","QCD_MuEnriched","SingleTop","TTBar","DYJetsToLL","WW","WZ","ZZ","SingleMuon"]
YEAR = 2018

## TEST LOCALLY ON A VARIABLE
plotname   ="drjet01"+"_l2j_regD;1"
#plotname = "avgbscore;1"
XaxisLabel = "deltaR(jet0,jet1)"
BinWidth   = 5

## CREATE ALIAS LABEL
bkgname={"HTbinnedWJets":"wjets",
         "QCD_MuEnriched":"QCD",
         "SingleTop":"ST",
         "TTBar":"ttjets",                 ## These are aliases Name
         "DYJetsToLL":"zjets",             ## These Names will be shown in Legend
         "WW":"WW",                        ## HTbinnedWJets will be named as wjets in Legend
         "WZ":"WZ",
         "ZZ":"ZZ",
         "SingleMuon":"data"}


## CMS LEVEL PLOT SETTINGS
plotsetting.PlotRatioPad=True
plotsetting.year=YEAR
plotsetting.publicationStyle=False
plotsetting.WorkInProgress=True


##--------------------------------------------------------------------------------------------------------------------#
##                                      DON'T TOUCH BELOW                                                             #
##--------------------------------------------------------------------------------------------------------------------#
#IMPORT ROOTPLOTMAKER JSON FILE

with open("./inputs/rootplotmakerConfig.json",'r') as infile:
    jsonfile = json.load(infile)
#----------------------------------------------------------    

# LOCAL TEST
if(LocalTest==True):
    #check one sample group histo using CheckGroupHisto function
    #defined in setup/plotsetup/plotmaker.py package
    pset.CheckGroupHisto(runOnSkimmedSample,2018,bkgbundle,bkgname,CondorJobName,inputfilepath,jsonfile,plotname)
    
    #Make a histogram directory
    HistoDict=pset.GetGroupHistoDict(runOnSkimmedSample,YEAR,bkgbundle,bkgname,CondorJobName,inputfilepath,jsonfile,plotname)
    HistoDict=pset.SortDict(HistoDict,True) #Sorting based on yield[Descending, Flag=False ascending order]
    
    print(HistoDict)
    
    #Plotting: MC stacked and Data Overlaid
    canvas,stack,legend,ratioHisto,ratioleg=pset.PlotMaker(HistoDict,plotname,XaxisLabel,BinWidth,False,"Plots/plots_Sep13v0","")
    canvas.Draw()
    #dataHisto.Draw("ep")
    #stack.Draw("HIST SAME")
    #dataHisto.Draw("ep same")
    #legend.Draw("SAME")
    #ratioHisto.Draw("ep")
    #ratioleg.Draw("ep")


    
#############################################################################
##                   PLOT ALL THE VARIABLES                                ##
#############################################################################

if(LocalTest==False):
    ### MAKE PLOTS FOR ALL VARIABLES
    import time
    timex=time.ctime()
    print('_'.join(timex.split()))
    timestamp= '_'.join(timex.split())

    outputdir=CondorJobName+'_'+timestamp
    print(outputdir)
    os.makedirs("Plots/"+outputdir)
    outputfilepath= "Plots/"+outputdir+"/"


    ## Plots
    VariableName=["ptlep0","ptjet0","ptjet1","mtlep0","mtjet0","mtjet1","dijetmass","drjet01",
                  "dijetPT","dijetMT","MET","HT","ST","njet","nbjet","dphimetjet0","dphimetjet1",
                  "dphimetlep0","dphijet0lep0","dphijet1lep0","dphidijetlep0","dphimetdijet"]

    #RegionName=["_base_mjj","_primaryCuts_mjj","_base_wjetbkg_mjj","_base_qcdbkg_mjj",
    #            "_primaryCuts_wjetbkg_mjj","_primaryCuts_qcdbkg_mjj","_regA","_regB","_regC","_regD"]

    RegionName=["_base_mjj","_regA","_regB","_regC","_regD"]

    
    LabelName=["Lepton PT","Leading jet Pt","SubLeading jet pt","Lepton MT","Leading Jet MT",
               "Subleading Jet MT","Dijet Inv Mass","deltaR(jet0,jet1)","Dijet System PT",
               "Dijet System MT","MET","HT","ST","No of jets","No of b-jets","dphi(met,leading jet)",
               "dphi(met,subleading jet)","dphi(met,lepton)","dphi(jet0,lepton)","dphi(jet1,lepton)",
               "dphi(dijet system,lepton)","dphi(dijet system,met)"]


    binning=[20,20,20,25,25,25,25,5,25,25,25,25,25,1,1,5,5,5,5,5,5,5]

    outputPDFName='WjetCRPlot.pdf'
    c=TCanvas()
    c.Print(outputfilepath+outputPDFName+"[")
    for ireg,reg in enumerate(RegionName):
        for ivar,var in enumerate(VariableName):
            plotname=var+'_l2j'+reg
            
            TempoDict=pset.GetGroupHistoDict(runOnSkimmedSample,2018,bkgbundle,bkgname,CondorJobName,inputfilepath,jsonfile,plotname)
        
            XaxisName=LabelName[ivar]+reg
            rebin=binning[ivar]
            pset.PlotMaker(TempoDict,plotname,XaxisName,rebin,True,outputfilepath,outputPDFName)
            TempoDict.clear()
    c.Print(outputfilepath+outputPDFName+"]")
