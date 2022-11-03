import uproot

events = uproot.open("VLL_DYJetsToLL_M50_9.root:Events")

#events.show()

branchlist=events.keys()

#print(branchlist)

branch_prefix=["Flag_"]  #Muon,Electron,Jet

for item in branchlist:
    bname_matched=any(map(item.startswith,branch_prefix))
    if(bname_matched):
        print("*"+item+";")

        
    
