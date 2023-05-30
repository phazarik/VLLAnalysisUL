import os

dumped_dir = "/home/work/phazarik1/work/VLLanalysis/CondorOutput/output"
dirlist=os.listdir(dumped_dir)
#print(dirlist)

#jobname="VLLAna_2muSSskimmed_May23"
bkggroup=["DYJetsToLL", "HTbinnedWJets", "QCD_MuEnriched", "SingleTop", "TTBar", "WW", "WZ", "ZZ"]
#bkggroup=["DYJetsToLL"]

#################
#Dont touch below
#################

import argparse
parser=argparse.ArgumentParser()
parser.add_argument('--dryrun',type=bool,required=False,help='Prints the processlines, no execution.')
parser.add_argument('--jobname',type=str,required=True,help='Give the condor jobname')
args=parser.parse_args()
DRYRUN=args.dryrun
jobname=args.jobname

print("")
list_of_empty_dirs = []


def move_bkgs(jobname, bkggroup, dirlist):
    for bkg in bkggroup:
        samplegroup=bkg
        for item in dirlist:
            if(item.startswith(jobname+"_"+bkg)):
                #print(item)
                subsamplename=item.split(jobname+"_")[1].split("_sample")[0].split(bkg+"_")[1]
                outdir = "hists/"+jobname+"/"+bkg+"/"+subsamplename
                flag = not os.listdir("output/"+item)
                if flag : list_of_empty_dirs.append(item)
                files = "output/"+item+"/*"+subsamplename+"*.root"
                processline= "mv "+files+" "+outdir+"/"
                if flag==False :
                    make_directory = "mkdir -p "+outdir
                    os.system(make_directory)
                    if DRYRUN==True:print(processline)
                    else : os.system(processline)
                else:
                    print("Skipping empty directories")
                
        print(samplegroup+" files have been moved sucessfully.\n")

    print("The following (background) directories were empty.")
    for dirname in list_of_empty_dirs : print(dirname)

def move_data(dataset, datagroup, dirlist):
    for data in datagroup:
        for item in dirlist:
            #print(item)
            #print(jobname+"_"+dataset+"_"+data)
            if(item.startswith(jobname+"_"+dataset+"_"+data)):
                indir = "output/"+item
                flag = not os.listdir(indir)
                files = indir+"/*.root"
                outdir = "hists/"+jobname+"/"+dataset+"/"+data
                if flag==False:
                    make_directory = "mkdir -p "+outdir
                    os.system(make_directory)
                    processline="mv "+files+" "+outdir+"/"
                    if DRYRUN==True : print(processline)
                    else : os.system(processline)
                else:
                    print("Skipping empty directories")

move_bkgs(jobname, bkggroup, dirlist)
datagroup = ["SingleMuon_A", "SingleMuon_B", "SingleMuon_C", "SingleMuon_D"]
#datagroup = ["SingleMuon_A"]
print("\nMoving data files...\n")
move_data("SingleMuon", datagroup, dirlist)

print("\nAll files moved sucessfully!\n")
