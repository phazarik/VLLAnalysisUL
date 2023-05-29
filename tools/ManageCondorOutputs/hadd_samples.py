#####################################################################
# This script hadds the skimmed nanaoAOD files from the same samples
#####################################################################

import os
import argparse
parser=argparse.ArgumentParser()
parser.add_argument('--dryrun',type=bool,required=False,help='Check If everything is correct before submitting')
parser.add_argument('--jobname',type=str,required=True,help='Give the condor jobname')
args=parser.parse_args()
DRYRUN= args.dryrun
jobname= args.jobname
#jobname = 'VLLAna_2muSSskimmed_May23'

dumped_dir = '/home/work/phazarik1/work/VLLanalysis/CondorOutput/hists'
dirlist = os.listdir(dumped_dir)
#samplegroups = ["QCD_MuEnriched"]
#samplegroups = ["SingleMuon"]
samplegroups =["DYJetsToLL", "HTbinnedWJets", "QCD_MuEnriched", "SingleTop", "TTBar", "WW", "WZ", "ZZ", "SingleMuon"]

outpath = '/home/work/phazarik1/work/VLLanalysis/CondorOutput/hists_hadded/'+jobname

for group in samplegroups:
    path_to_samplegroup = dumped_dir+'/'+jobname+'/'+group
    subfolder = os.listdir(path_to_samplegroup)
    print('\nhadding '+group+' files ...')
    
    for sample in subfolder:
        indir = path_to_samplegroup+'/'+sample
        outdir = outpath+'/'+group
        outfile = outdir+'/'+group+'_'+sample+'.root'
        infiles = indir+'/*.root'

        #Special case for SingleMuon:
        if group=='SingleMuon':
            outdir = outpath+'/'+group
            outfile = outdir+'/'+sample+'.root'

        make_outdir='mkdir -p '+outdir
        add_all = 'hadd -f '+outfile+' '+infiles

        flag = not os.listdir(indir)
        if flag == False:
            if DRYRUN == True:
                print('processline : '+add_all)
            else :
                os.system(make_outdir)
                os.system(add_all)
        else:
            print('Skipping empty directory : '+indir)

    print('done.')

print('hadding success for all.')
