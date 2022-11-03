import ROOT
import ROOT.RDataFrame as rdf
import plotdef as plot
from tabulate import tabulate
import operator
ifpath = "/home/arnab/Arnab/Work/PhD2022/VLLAnalysisUL/external/InputFiles/VLL2018_1L2JAnalysisWJetsEstimation_Sep5_v2/"
ifname = "VLL2018_1L2JAnalysisWJetsEstimation_Sep5_v2_HTbinnedWJets_Inclusive_sample.root"
sigfname="VLL2018_1L2JAnalysisWJetsEstimation_Sep5_v2_VLLM100_sample.root"

df = rdf("TreeS",ifpath+ifname)
sigdf=rdf("TreeS",ifpath+sigfname)

print("\n****************************************************")

wjetslumi=1516.39
siglumi=465811.96
datalumi=59700

print("No of WJets events =",df.Count().GetValue())
print("No of VLLM100 events =",sigdf.Count().GetValue())
print("\n--After Lumi Correction--\n")
print("No of WJets events =",df.Count().GetValue()*(datalumi/wjetslumi))
print("No of VLLM100 events =",sigdf.Count().GetValue()*(datalumi/siglumi))
print("***************************************************** ")

#df_mjj=df.Filter("abs(lep0_flavor)==13","Muon Flavor Cut")
#sigdf_mjj=sigdf.Filter("abs(lep0_flavor)==13","Muon Flavor Cut")
##################################################################

def ApplyCuts(df):
    df=df.Filter("n_bJet==0","nbjet cut")\
         .Filter("n_Jet<100","njet cut")\
         .Filter("deltaR_jet01<2.7","deltaR cut")\
         .Filter("dijet_mass<120 && dijet_mass>50","dijet mass cut")

    return df

def ApplyCuts_v1(df):
    df=df.Filter("n_bJet==0","nbjet cut")\
         .Filter("n_Jet<100","njet cut")\
         .Filter("deltaR_jet01<2.6","deltaR cut")\
         .Filter("lep0_mt>0 && lep0_mt<130","lepton mt cut")

    return df

def ApplyCuts_v2(df):
    df=df.Filter("n_bJet==0","nbjet cut")\
         .Filter("n_Jet<100","njet cut")\
         .Filter("deltaR_jet01<2.7","deltaR cut")\
         .Filter("dijet_mass<120 && dijet_mass>50","dijet mass cut")\
         .Filter("lep0_mt>0 && lep0_mt<125","lepton mt cut")
    return df


df_mjj=ApplyCuts_v2(df)
sigdf_mjj=ApplyCuts_v2(sigdf)

print("\n**mujj channel\n==================")
print("No of WJets events =",df_mjj.Count().GetValue())
print("No of VLLM100 events =",sigdf_mjj.Count().GetValue())
print("\n--After Lumi Correction--\n")
print("No of WJets events =",df_mjj.Count().GetValue()*(datalumi/wjetslumi))
print("No of VLLM100 events =",sigdf_mjj.Count().GetValue()*(datalumi/siglumi))
print("***************************************************** ")

df_mjj.Report().Print()
print("---")
sigdf_mjj.Report().Print()


##SOME 2D Plots
plot.plot2DSameCanvas(sigdf_mjj,df_mjj,"deltaR_jet01","lep0_mt",70,0,7,600,0,600,"dRvsLepMT_afterCut2_")





#####
import numpy as np
def plotROC(sigdf,bkgdf):
    sigeff=[]
    bkgeff=[]
    #info=[]
    n_sigtot=sigdf.Count().GetValue()
    n_bkgtot=bkgdf.Count().GetValue()
    cutString=[]
    signi=[]
    #print("Total sig= ",n_sigtot)
    #print("Total bkg= ",n_bkgtot)
    for drcut in range(150,300,10):
        for lowmasscut in range(30,80,10):
            for masscut in range(90,160,10):

                cuts="deltaR_jet01<"+str(drcut/100)+"&& deltaR_jet01>"+str(lowmasscut)+ " && dijet_mass<"+str(masscut)
                print(cuts)
                sigdf_drcut=sigdf.Filter("deltaR_jet01<"+str(drcut/100))
                bkgdf_drcut=bkgdf.Filter("deltaR_jet01<"+str(drcut/100))
                sigdf_masscut=sigdf_drcut.Filter("dijet_mass>"+str(lowmasscut)+"&& dijet_mass<"+str(masscut))
                bkgdf_masscut=bkgdf_drcut.Filter("dijet_mass>"+str(lowmasscut)+"&& dijet_mass<"+str(masscut))

                n_sig=sigdf_masscut.Count().GetValue()
                n_bkg=bkgdf_masscut.Count().GetValue()
            
                #print("sig after cuts= ",n_sig)
                #print("bkg after cuts= ",n_bkg)
                #print('------')
                #print(type(n_sig))
            
                sigeff.append(n_sig/n_sigtot)
                bkgeff.append(n_bkg/n_bkgtot)
                cutString.append(cuts)
                signi.append(n_sig/np.sqrt(n_bkgtot))
                #info.append(["deltaR_jet01<"+str(drcut/100),"dijet_mass>"+str(lowmasscut)+"&& dijet_mass<"+str(masscut),n_sig/n_sigtot,n_bkg/n_bkgtot])
    #PlotROC       
    #print(sigeff)
    #print("")
    #print(bkgeff)
    #colname=["dRcut","Masscut","sigeff","bkgeff"]
    #print(tabulate(info,headers=colname,tablefmt='fancy_grid',numalign='left',floatfmt="0.3f"))
    return signi,sigeff,bkgeff,cutString
"""
signi,sigeff,bkgeff,cutString=plotROC(sigdf,df)

bkgeff,signi,sigeff,cutString = (list(t) for t in zip(*sorted(zip(bkgeff,signi,sigeff,cutString))))
info=[]
for i in range(len(sigeff)):
    ratio=sigeff[i]-bkgeff[i]
    if(sigeff[i]>0.6):
        info.append([cutString[i],sigeff[i],bkgeff[i],signi[i],ratio])

info.sort(key = operator.itemgetter(4,1))    
colname=["Cuts","sigeff","bkgeff","S/rootB","ratio"]
print(tabulate(info,headers=colname,tablefmt='fancy_grid',numalign='left',floatfmt="0.3f"))
    
import matplotlib.pyplot as plt
plt.figure(figsize=(8,6))
plt.plot(bkgeff,sigeff,color="xkcd:denim blue",marker='o',markersize=3)
plt.xlabel("Background Efficiency",fontsize=16)
plt.ylabel("Signal Efficiency",fontsize=16)
plt.title("ROC plot based on deltaR_jet01_Vs_dijetMass plane",fontsize=14)
plt.grid("--")
#plt.show()
plt.savefig("ROC_finerbinning_v2.png",dpi=250,facecolor="white",bbox_inches='tight')
"""
     
