import os

currentdir = os.getcwd()
samdir = os.listdir(currentdir)

print(samdir[:-2])
maindir=os.getcwd()
for item in samdir[:-2]:
    os.chdir(maindir+"/"+item)
    print("You are in.... "+os.getcwd())
    haddcommand = "hadd "+"VLL_QCD_"+item+"_skimtree.root"+" *.root"
    print(haddcommand)
    
    #os.system(haddcommand)
    os.system("rm -rf 8*")
    os.chdir(maindir)
    
    
