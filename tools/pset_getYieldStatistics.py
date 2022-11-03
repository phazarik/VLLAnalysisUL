#Import Libraries
import ROOT
from ROOT import *
import os,sys
from tabulate import tabulate    

import setup.plotsetup.plot_settings as plotsetting #import plotsetting from setup/plotsetup
import setup.plotsetup.plotmaker as pset            #import plotsetting from setup/plotsetup
import json


## USER DEFINED
LocalTest=True
runOnSkimmedSample=False
CondorJobName ="VLL2018_1L2JAnalysisWJetsEstimation_Sep13_v0"
jsonfilepath="./external/InputFiles/"+CondorJobName+"/"
bkgbundle =["HTbinnedWJets","QCD_MuEnriched","SingleTop","TTBar","DYJetsToLL","WW","WZ","ZZ","SingleMuon"]
YEAR = 2018


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

#IMPORT ROOTPLOTMAKER JSON FILE
with open('./inputs/rootplotmakerConfig.json','r') as infile:
    jsonfile = json.load(infile)
#----------------------------------------------------------
def GetRegionHistoDictSorted(region,var):
    pname = var+"_l2j_"+region+";1"
    histodict= pset.GetGroupHistoDict(runOnSkimmedSample,YEAR,bkgbundle,bkgname,CondorJobName,jsonfilepath,jsonfile,pname)
    histodict= pset.SortDict(histodict,True)
    return histodict

def CalculateWjetYield(Dict):
    totOtherBkg=0
    for index,(histkey,hist) in enumerate(Dict.items()):
        #print(histkey,hist)    
        events=hist[1]
        
        if(histkey != 'SingleMuon' and histkey != 'HTbinnedWJets'):
            totOtherBkg+=events
    return totOtherBkg

def getStatTable(histodict,NAME):
    bkgstat=[]
    bkgname=[]
    bkgstat.append(NAME)
    for bkg in bkgbundle:
        if(bkg!='HTbinnedWJets'):
            bkgstat.append(histodict[bkg][1])
            bkgname.append(histodict[bkg][0])

    n_wjets=histodict['SingleMuon'][1]-CalculateWjetYield(histodict)
    bkgstat.append(n_wjets)
    #print(bkgname)
    #print(bkgstat)
    return bkgstat

##############
###STATS
##############
Region_A= GetRegionHistoDictSorted("regA","dijetmass")
Region_B= GetRegionHistoDictSorted("regB","dijetmass")
Region_C= GetRegionHistoDictSorted("regC","dijetmass")
Region_D= GetRegionHistoDictSorted("regD","dijetmass")


info=[]
reglabel=["CR-B","CR-C","CR-D"]
for ireg,region in enumerate([Region_B, Region_C,Region_D]):
    info.append(getStatTable(region,reglabel[ireg]))

    
from tabulate import tabulate    
colname=['Region','QCD', 'ST', 'ttjets', 'zjets', 'WW', 'WZ', 'ZZ', 'data','wjets']
print(tabulate(info,headers=colname,floatfmt=".0f",tablefmt='github')) 





