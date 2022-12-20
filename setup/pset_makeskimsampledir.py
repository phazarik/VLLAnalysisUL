import os

dumped_dir = "/home/work/phazarik1/work/VLLanalysis/SkimmedSamples/output"
dirlist=os.listdir(dumped_dir)

jobname="VLLAna_2muSkimmed_Dec19"
#bkggroup=["HTbinnedWJets", "QCD_MuEnriched", "SingleTop", "TTBar", "WW", "WZ", "ZZ"]
bkggroup=["DYJetsToLL"]
print("")

for bkg in bkggroup:
    samplegroup=bkg
    for item in dirlist:
        if(item.startswith(jobname+"_"+bkg)):
            #print("moving ..."+item)
            subsamplename=item.split(jobname+"_")[1].split("_sample")[0].split(bkg+"_")[1]
            outdir = "Skimmed2018/"+jobname+"/"+bkg+"/"+subsamplename
            #print(outdir)
            files = "output/"+item+"/*"+subsamplename+"*.root"
            processline= "mv "+files+" "+outdir+"/"
            #moved_files = os.listdir(outdir)
            #print(processline)
            #print(files)
            #example: mv VLLAna_2muSkimmed_Dec15_DYJetsToLL_M50_sample__121522_104436/* Skimmed2018/DYJetsToLL/M50/
            os.makedirs(outdir)
            os.system(processline)
    print(samplegroup+" files have been moved sucessfully.\n")

print("\nAll files moved sucessfully!\n")
