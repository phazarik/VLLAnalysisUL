import os

jobname = 'VLLAna_2muSSskimmed_Apr12'
dumped_dir = '/home/work/phazarik1/work/VLLanalysis/SkimmedSamples/Skimmed2018'
dirlist = os.listdir(dumped_dir)
#samplegroups = ["QCD_MuEnriched"]
samplegroups = ["SingleMuon"]
#samplegroups =["DYJetsToLL", "HTbinnedWJets", "QCD_MuEnriched", "SingleTop", "TTBar", "WW", "WZ", "ZZ", "SingleMuon"]

os.system('mkdir -p outputs/bulk/')

for group in samplegroups:
    path_to_samplegroup = dumped_dir+'/'+jobname+'/'+group
    subfolder = os.listdir(path_to_samplegroup)

    #Set parameters:
    data = 0
    if group == 'SingleMuon' : data = '1'
    year = '2018'
    lep=1 #for muons
    era=1
    mcwt=1

    '''
    for sample in subfolder:
        iterate = 0
        indir = path_to_samplegroup+'/'+sample
        ifnames = os.listdir(indir)
        #print(filepath)
        flag = not os.listdir(indir)

        outdir = 'outputs/bulk/'+group+'/'+sample
        make_outdir = 'mkdir -p '+outdir
        os.system(make_outdir)

        if flag == False:
            #anascript = 'ana_python.C("'+indir+'","'+outdir+'","'+outname+'",'+data+','+year+')'
            #processline='root -q -l -b '+"'"+anascript+"'"
            #print(len(ifnames))
            for ifname in ifnames:
                iterate = iterate +1
                ifname = indir+'/'+ifname
                ofname = outdir+'/'+group+'_'+sample+'_'+str(iterate)+'.root'
                anaCond_script = 'runana.C("'+ifname+'","'+ofname+'","'+data+','+year+','+lep+','+era+','+mcwt+')'
                print(anaCond_script)
                #print(processline)
                #os.system(processline)
                break
    '''

    for sample in subfolder:

        #hadding the same samples together.
        indir = path_to_samplegroup+'/'+sample
        infile = path_to_samplegroup+'/'+group+'_'+sample+'.root'
        infiles = indir+'/*.root'
        add_all = 'hadd -f '+infile+' '+infiles

        flag = not os.listdir(indir)
        if flag == False:
            print(add_all)
            #os.system(add_all)


        #Assigning inputs and output locations.
        ifname = infile
        outdir='outputs/bulk/'+group
        make_outdir = 'mkdir -p '+outdir
        os.system(make_outdir)
        ofname = outdir+'/hst_'+group+'_'+sample+'.root'
        #print(ifname)
        #print(ofname)

        if flag == False:
            runana_script = 'runana.C("'+ifname+'","'+ofname+'",'+str(data)+','+str(year)+','+str(lep)+','+str(era)+','+str(mcwt)+')'
            processline = "root -q -l -b '"+runana_script+"'"
            print(processline)
            os.system(processline)
        break
