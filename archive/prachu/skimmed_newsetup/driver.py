import os

jobname = 'VLLAna_2muSSskimmed_Apr12'
dumped_dir = '/home/phazarik/work/VLLAnalysis/new_setup/input_files/'+jobname
dirlist = os.listdir(dumped_dir)
path_to_code='/home/phazarik/work/VLLAnalysis/new_setup/archive/prachu/skimmed_study'

print(dirlist)

#samplegroups = ["QCD_MuEnriched"]
#samplegroups = ["SingleMuon"]
samplegroups =["DYJetsToLL", "HTbinnedWJets", "QCD_MuEnriched", "SingleTop", "TTBar", "WW", "WZ", "ZZ", "SingleMuon"]

for group in samplegroups:
    path_to_samplegroup = dumped_dir+'/'+group
    input_files = os.listdir(path_to_samplegroup)

    #Set parameters:
    data = 0
    if group == 'SingleMuon' : data = '1'
    year = '2018'
    lep=1 #for muons
    era=1
    mcwt=1

    print('\n###################################################')
    print(f'ana code running on {group} files...')
    print(f'Parameters for {group} are = {data}, {year}, {lep}, {era}, {mcwt}')
    
    for filename in input_files:
        codename='runana.C'
        ifname = path_to_samplegroup+'/'+filename
        outdir='/home/phazarik/work/VLLAnalysis/new_setup/output_files/'+group
        make_outdir='mkdir -p '+outdir
        os.system(make_outdir)
        ofname=outdir+'/hst_'+filename
        sfname=outdir+'/sum_'+filename+'.txt'

        runana_script = f'{codename}("{ifname}", "{ofname}", TString("{data}"), TString("{year}"), TString("{lep}"), TString("{era}"), TString("{mcwt}"))'
        
        processline = "root -q -l -b '"+runana_script+"'"
        #print(processline)

        #break
        os.system(processline)
