#------------------------------------
# Make Cross Section Template : July 21,2022
#------------------------------------
#
#   This code should produce a template json
#   with the **EXACT STRUCTURE** as sample.json
#   file has. Order doesn't matter. But structure
#   should be same. Then you can manually write
#   ther cross section as a values to the keys.
#   ( Any issue? ask me!!)
#---------------------------------------------------

import os,sys
import json
from collections import defaultdict

# User Defined

YEAR = 2018

sampledir_UL = "/home/work/alaha1/public/RunII_ULSamples/"


#--------------------------------------------------------
#                   DON'T TOUCH BELOW                   #
#--------------------------------------------------------

samplepath = os.path.join(sampledir_UL,str(YEAR))
samplelist = os.listdir(os.path.join(sampledir_UL,str(YEAR)))

sampledict=defaultdict(dict)
#print(samplelist)
for folder in samplelist[:]:
    subfolderpath=os.path.join(samplepath,folder)
    subfolderlist=os.listdir(subfolderpath)
    #print(os.listdir(subfolderpath))
    for subfolder in subfolderlist[:]:
        sample=folder+"_"+subfolder
        sampledict[folder][sample]=1                              ## default template Xsec to all sample is set to 1

##############

print(sampledict)

json_object = json.dumps(sampledict,indent=4)
with open("CrossSection.json",'w+') as outfile :
    outfile.write(json_object)
    
#print(json_object)
