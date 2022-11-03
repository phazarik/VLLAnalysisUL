def Summary(HistoDict):
    ###Sorting based on lumi corrected weight
    #HistoDict=dict(sorted(HistoDict.items(),key=lambda x:x[1][2],reverse=False))
    print("         Summary Report                ")
    print("_________________________________________")
    print("   ")
    print( "  Name"+"     "+"    No of Events ")
    print("--------"+"    "+"-------------------")
    exp=0
    for key in HistoDict.keys():
        if(key!='data'): exp=exp+HistoDict[key][2]
        print(" "+ key+"          " +str(HistoDict[key][2]))
    print("_________________________________________")
    print("    ")
    print("obs="+str(HistoDict['data'][2])+", "+"exp="+str(exp))
    print("obs/exp=",str((HistoDict['data'][2]/exp))[:5])
    print("_________________________________________")
    print("                                         ")
    obs=HistoDict['data'][2]
    bkgBundle=list(HistoDict.keys())[:-1]
    print("Background Bundle=",bkgBundle)


def SortDict(dic,opt):
    return dict(sorted(dic.items(),key=lambda x:x[1][1],reverse=opt))    
    
