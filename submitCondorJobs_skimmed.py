import sys
import os,argparse
import setup.condorsetup.condorjobsetup as cset
import json


##--------------------------------------------------------------------------------------------------#
#                                     USER DEFINED                                                  #
##--------------------------------------------------------------------------------------------------#
jsonfilename ="inputs/sample_skimmed.json"
#bkgbundle =["SingleMuon"]
#bkgbundle =["DYJetsToLL"]
bkgbundle =["QCD_MuEnriched","HTbinnedWJets","DYJetsToLL","SingleTop","TTBar","WW","WZ","ZZ"]

##--------------------------------------------------------------------------------------------------#
#                                  DON'T TOUCH BELOW                                                #
##--------------------------------------------------------------------------------------------------#
parser=argparse.ArgumentParser()
parser.add_argument('--jobname',type=str,required=True,help='AnalysisName: Such as VLL2018_Mar1_v0')
parser.add_argument('--dryrun',type=bool,required=False,help='Check If everything is correct before submitting')
parser.add_argument('--test',type=bool,required=False,help='Check one job')

args=parser.parse_args()
DRYRUN= args.dryrun
########################

newjob = cset.CondorJob()     
newjob.dataset='mu'
newjob.era ='Z'
newjob.codedir = "archive/prachu/skimmed_study/"
newjob.currentdir = os.getcwd()
newjob.anaConddir = os.getcwd()
newjob.setup()

runanaString = os.path.join(os.path.abspath(newjob.codedir),"runana.C")
print(runanaString)
print("")
# Copy anaCond.C and runana.C to codedirectory
os.system("cp -f runana.C "+newjob.codedir)
os.system("cp -f "+newjob.anaConddir+"/"+"anaCond.C "+newjob.codedir)


### Print Out the inputs
def printInfo():
    print("\n***********************************************************************************************")
    print("*       Jobname is    : ",newjob.jobname)
    print("*       Code dir      : ",newjob.codedir+"VLLAna.C")
    print("*       Sample dir    : ",newjob.sampleinputdir)
    print("*       DATA          : ",newjob.data)
    print("*       YEAR          : ",newjob.year)
    print("*       DATASET       : ",newjob.dataset)
    print("*       Sample Group  : ",samplegroup)
    print("*************************************************************************************************")
    return processLine+"\n"


with open(jsonfilename,'r') as infile:
    bkglist = json.load(infile)

#Path to input files:
skimmed_dir = "/home/work/phazarik1/work/VLLanalysis/SkimmedSamples/Skimmed2018/VLLAna_2muSkimmed_Dec19/"

## Run over samples
samplesummary=[]
for background in bkgbundle:
    for samplegroup,groupvalue in bkglist.items():
        if(samplegroup.lower() == background.lower()):
            #print(samplegroup)
            samplesummary.append(samplegroup)
            for samplename,samplevalue in groupvalue.items():
                samplename_list = samplename.split(samplegroup+"_")
                samplename = samplename_list[1]

                newjob.jobname=args.jobname+"_"+samplegroup+"_"+samplename+"_sample"
                newjob.sampleinputdir= skimmed_dir+samplegroup+"/"+samplename
                newjob.sampletag="wz"
                newjob.data =str(samplevalue["data"])
                newjob.year =str(samplevalue["year"])

                processLine = './createJobsToCondor.sh'+' '+runanaString+' '+newjob.jobname+' '+newjob.sampleinputdir+' '+str(newjob.data)+' '+str(newjob.year)+' '+newjob.dataset+' '+newjob.era+' '+newjob.sampletag

                #print(newjob.jobname)
                #print("")
                
                if(DRYRUN==True):
                    print(printInfo())
                    if(args.test==True):
                        break
                else:
                    os.system(processLine)
                    if(args.test==True):
                        break

#Printing out reports:
for item in samplesummary:
    print("\nYou submit jobs for.....:|"+item)
print(" \n")

if(DRYRUN==None):
    os.system("mv -f submitJobsCondor* CondorJobsLog/")
    print("\n *****SubmitJobsCondor*.sh files are moved to CondorJobs directory******\n")
