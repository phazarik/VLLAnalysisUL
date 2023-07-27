#####################################################################
# This script hadds the skimmed nanaoAOD files from the same samples
#####################################################################

import os
import argparse
parser=argparse.ArgumentParser()
parser.add_argument('--dryrun',type=bool,required=False,help='Check If everything is correct before submitting')
parser.add_argument('--jobname',type=str,required=True,help='Give the condor jobname')
args=parser.parse_args()
dryrun= args.dryrun
jobname= args.jobname

#Samples that I want to move:
samples =["DYJetsToLL", "HTbinnedWJets", "QCD_MuEnriched", "SingleTop", "TTBar", "WW", "WZ", "ZZ", "TTW"]

#dumped_dir = '/home/work/phazarik1/work/VLLanalysis/CondorOutput/hists'
dumped_dir = '/home/work/phazarik1/work/VLLanalysis/CondorOutput/output/'+jobname

#output directory:
outpath = '/home/work/phazarik1/work/VLLanalysis/CondorOutput/hists_hadded/'+jobname

#----------------------------------------------------------------------------------------
#Don't touch below:
empty_folders = []

dirlist = os.listdir(dumped_dir)
for sample in samples:
    for item in dirlist:
        if item.startswith(sample):
            #defining names
            subsample = item.split('_')[1]
            if sample == 'QCD_MuEnriched' : subsample = item.split('_')[2]
            elif sample == 'SingleTop' : subsample = item.split('_')[1]+item.split('_')[2]

            #handling inputs:
            indir = dumped_dir+'/'+item
            allfiles = indir+'/*'
            flag = not os.listdir(indir)
            if flag : empty_folders.append(indir)

            #handling outputs
            outdir = outpath+'/'+sample
            outfile = outdir+'/hst_'+sample+'_'+subsample+'.root'

            processline = 'hadd '+outfile+' '+allfiles
            if flag == False:
                if dryrun == True : print(processline)
                else:
                    os.makedirs(outdir, exist_ok=True)
                    os.system(processline)

    print('\033[93m'+sample+' samples have been h-added.\033[0m')

if len(empty_folders) !=0 :
    print('')
    print('-'*100)
    print('\033[93mThe following folders were empty:\033[0m')
    for item in empty_folders: print(item)
    print('-'*100)
    
print('\033[93m\nDone!\033[0m')
print('\033[93moutdir = '+outpath+'\033[0m')
