import os
import sys
import argparse

parser=argparse.ArgumentParser()
parser.add_argument('--jobname',type=str,required=True,help='AnalysisName: Such as VLL2018_Mar1_v0')
#Parse the argument
args=parser.parse_args()
#####################################

CondorJobName=args.jobname
CurrentJobIdentifier=CondorJobName


CurrentFolderPath=os.getcwd()
CondorJobOutputFolder='CondorOutput/output/'
CondorJobOutputFolderPath=os.path.join(CurrentFolderPath,CondorJobOutputFolder)

DumpHaddFileFolder=os.path.join(CurrentFolderPath,"CollectOutput/"+CurrentJobIdentifier)

##Create the folder where you dump all hadded files
if(os.path.isdir(DumpHaddFileFolder)==1):
    print("\nFolder already Exist.......\n")
else:
    os.makedirs(DumpHaddFileFolder)

##Check if the dumping folder is clean
haddfile=os.listdir(DumpHaddFileFolder+"/")
if(len(haddfile)!=0):
    print("DumpingFolder "+DumpHaddFileFolder+" is not clean...The files are below\n")
    for file in (haddfile):
        print(file)        
    sys.exit("\nClean your dumping folder\n")

#### START ACCUMULATING    
OutputFolderJobList=os.listdir(CondorJobOutputFolderPath)
for folder in OutputFolderJobList:
    print(folder)
    if(folder.startswith(CurrentJobIdentifier)):
        #ProcessName
        print(folder)
        SampleName = folder.split(CurrentJobIdentifier+"_")[1].split('__')[0]
        print(SampleName)
        #HaddFileNameCreate
        haddfileName=CurrentJobIdentifier+"_"+SampleName+".root"
        samplefolder=os.path.join(CondorJobOutputFolderPath,folder+"/")
        os.chdir(samplefolder)
        os.system("hadd "+haddfileName+" "+"*.root")
        os.system("cp "+haddfileName+" "+DumpHaddFileFolder+"/")
        os.chdir(CondorJobOutputFolderPath)

os.chdir(CurrentFolderPath)
#################################
##   Summary of the hadd file  ##
#################################
haddfile=os.listdir(DumpHaddFileFolder+"/")
print("###########################################\n")
print("#######  Here is the hadd file list  ######\n")
print("###########################################\n")
for file in haddfile:
    print(file)
    
