import os

dirlist=os.listdir()
#print(dirlist)

jobname="VLL2018_1L2JSkimmer_Aug4_v1_"
bkggroup=["TTBar","WW","WZ","ZZ"]

for bkg in bkggroup[1:]:
    samplegroup=bkg
    for item in dirlist:
        #print(item)
        if(item.startswith(jobname+bkg)):
            #samplegroup=item.split("VLL2018_1L2JSkimmer_Aug4_v1_")[1].split("sample")[0]
            subsamplename=item.split("VLL2018_1L2JSkimmer_Aug4_v1_")[1].split("_sample")[0].split(bkg+"_")[1]
            #print(samplegroup)
            #print(subsamplename)
            os.makedirs(samplegroup+"/"+subsamplename)
            #fname="VLL2018_1L2JSkimmer_Aug4_v1"+"_"+samplegroup+"_"+subsamplename+"_sample"
    
            #if(item.startswith(fname)):
            #print(item)
            processline= "mv "+item+"/* "+samplegroup+"/"+subsamplename+"/"
            
            print(processline)

            os.system(processline)
            print("\ncopying complete.....\n")
            print(samplegroup+"and"+subsamplename+"\n.........................")
            
            os.system("ls "+samplegroup+"/"+subsamplename+"/")
