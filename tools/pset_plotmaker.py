import os,sys
from collections import defaultdict
import json

#----------------------------------------------------
# IMPORT CROSS SECTION DATABASE(/inputs/CrossSection.json)
#----------------------------------------------------
with open('./inputs/CrossSection.json','r') as infile:
    XsecDict = json.load(infile)
#----------------------------------------------------    
#----------------------------------------------------
# IMPORT SAMPLE LUMI DATABASE(/inputs/SampleLumi.json)
#----------------------------------------------------
with open('./inputs/SampleLumi.json','r') as infile:
    LumiDict = json.load(infile)
#----------------------------------------------------    



outputdir ="./CollectOutput/"
CondorJobName ="VLL2018_1L2JAnalysisWJetsEstimation_Sep11_v0"

bkgbundle =["HTbinnedWJets","QCD_MuEnriched","SingleTop","TTBar","DYJetsToLL","WW","WZ","ZZ","SingleMuon"]
DATA=0
YEAR=2018
outfile_json="rootplotmakerConfig.json"

sampledict =defaultdict(dict)
filelist = os.listdir(os.path.join(outputdir,CondorJobName))
#print(filelist)
for item in filelist:
    #print(item)
    #print(item.split(CondorJobName+"_")[1])
    _item = item.split(CondorJobName+"_")[1]
    for bundle in bkgbundle:
        if(_item.lower().startswith(bundle.lower())):
            #print(_item)
            sample=_item.split("_sample")[0]
            #print(sample)
            sampledict[bundle][sample]={}
            sampledict[bundle][sample]["filename"]=_item
            sampledict[bundle][sample]["data"]=DATA
            sampledict[bundle][sample]["year"]=YEAR
            sampledict[bundle][sample]["xsec"]=XsecDict[bundle][sample]
            try:
                sampledict[bundle][sample]["lumi"]=LumiDict[bundle][sample]
            except KeyError:
                if(YEAR==2016):
                    sampledict[bundle][sample]["lumi"]=35.9
                if(YEAR==2017):
                    sampledict[bundle][sample]["lumi"]=41.5
                if(YEAR==2018):    
                    sampledict[bundle][sample]["lumi"]=59.7
#print(dict(sampledict))
#plotmaker_inputDict=dict(sampledict)

# ROOT PLOT MAKER
#import ROOT
#dataAndMCbundle = ['wjets','zjets','ttjets','QCD','SingleTop']





print("\n**********Printing json file final plot making: "+ outfile_json +"...*******\n")
json_object = json.dumps(sampledict,indent=2,sort_keys=True)
with open(outfile_json,'w+') as outfile :
    outfile.write(json_object)


    
