#-------------------------------------------------
# Make Background(or Sample) List: July 21,2022
#-------------------------------------------------
# We save sample information in the /inputs/sample.json file
# The structure should be:
#         
#   'SampleGroup':{
#        'SampleName':{
#                     'samplepath': XYZ
#                     'xsec':       XYZ
#                     'data':       XYZ
#                     'year':       XYZ
#                     }
#               }
#  Easy to access later on!  Just read the json file as a python
#  dict and do,
#              $dict["SampleGroup"]["SampleName"]["samplepath"]
#
#  to access the particular sample path.
#
#  For example dict["HTBinnedWJets"][HTBinnedWJets_100to200]["samplepath"]
#---------------------------------------------------

import os,sys
from collections import defaultdict
import json

#----------------------------------------------------
# IMPORT CROSS SECTION DATABASE(/inputs/CrossSection.json)
#----------------------------------------------------
#with open('../inputs/CrossSection.json','r') as infile:                                                                                   XsecDict = json.load(infile)
#----------------------------------------------------    


# User Defined
YEAR = 2018

ISDATA = 0

sampledir_UL = "/home/work/alaha1/public/RunII_ULSamples"

outfile_json = "sample_SingleMuonData.json"

#-------------------------------------------------------
#                 DON'T TOUCH BELOW                    #
#-------------------------------------------------------

samplepath = os.path.join(os.path.join(sampledir_UL,str(YEAR)),"UL2018Data")
samplelist = os.listdir(samplepath)

sampledict=defaultdict(dict)
#print(samplelist)

for folder in samplelist[:]:
    subfolderpath=os.path.join(samplepath,folder)
    subfolderlist=os.listdir(subfolderpath)
    #print(os.listdir(subfolderpath))

    for subfolder in subfolderlist[:]:
        sample=folder+"_"+subfolder
        sampledict[folder][sample]={}
        
        sampledict[folder][sample]['samplepath']=os.path.join(subfolderpath,subfolder)
        sampledict[folder][sample]['data']=1
        sampledict[folder][sample]['year']=2018
        sampledict[folder][sample]['xsec']=1
        

######

#print(sampledict)
print("\n**********Printing Sample Config file: "+ outfile_json +"...*******\n")
json_object = json.dumps(sampledict,indent=2,sort_keys=True)
with open(outfile_json,'w+') as outfile :
    outfile.write(json_object)
    
