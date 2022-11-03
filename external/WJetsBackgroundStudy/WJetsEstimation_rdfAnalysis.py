import ROOT
import ROOT.RDataFrame as rdf

ifpath = "/home/arnab/Arnab/Work/PhD2022/VLLAnalysisUL/external/InputFiles/VLL2018_1L2JAnalysisWJetsEstimation_Sep5_v2/"
ifname = "VLL2018_1L2JAnalysisWJetsEstimation_Sep5_v2_HTbinnedWJets_Inclusive_sample.root"
sigfname="VLL2018_1L2JAnalysisWJetsEstimation_Sep5_v2_VLLM100_sample.root"

df = rdf("TreeS",ifpath+ifname)
sigdf=rdf("TreeS",ifpath+sigfname)

#df=df.Filter("abs(lep0_flavor)==13")
#sigdf=sigdf.Filter("abs(lep0_flavor)==13")
df=df.Filter("abs(lep0_flavor)==13","Muon Flavor Cut")\
     .Filter("deltaR_jet01<10","deltaR cut")
sigdf=sigdf.Filter("abs(lep0_flavor)==13","Muon Flavor Cut")\
           .Filter("deltaR_jet01<10","deltaR cut")
print("\n****************************************************")

wjetslumi=1516.39
siglumi=465811.96
datalumi=59700

print("No of WJets events =",df.Count().GetValue())
print("No of VLLM100 events =",sigdf.Count().GetValue())
print("---")
print("No of WJets events =",df.Count().GetValue()*(datalumi/wjetslumi))
print("No of VLLM100 events =",sigdf.Count().GetValue()*(datalumi/siglumi))
print("***************************************************** ")

##plotting
def plot2D(df,var1,var2,x_low,x_hi,y_low,y_hi,title):
    ROOT.gStyle.SetOptStat(1)
    ROOT.gStyle.SetTextFont(42)
    canvas = ROOT.TCanvas("c", "", 800,700)
    
    #2DHistogram
    histo = df.Histo2D(("h1",title,(x_hi-x_low),x_low,x_hi,(y_hi-y_low),y_low,y_hi),var1,var2)
    histo.GetXaxis().SetTitle(var1)
    histo.GetYaxis().SetTitle(var2)
    histo.GetXaxis().SetTitleSize(0.04)
    histo.GetYaxis().SetTitleSize(0.04)
    histo.Draw("colz")
    canvas.SaveAs("./output/"+title+".pdf")

def plot2DSameCanvas(dfsig,dfbkg,var1,var2,nbinx,x_low,x_hi,nbiny,y_low,y_hi,title):
    #2DHistogram
    histo = dfsig.Histo2D(("h1",title+"_VLLM100",nbinx,x_low,x_hi,nbiny,y_low,y_hi),var1,var2)
    h_bkg = dfbkg.Histo2D(("h1",title+"_WJets",nbinx,x_low,x_hi,nbiny,y_low,y_hi),var1,var2)

    ROOT.gStyle.SetOptStat(1)
    ROOT.gStyle.SetTextFont(42)
    canvas = ROOT.TCanvas("c", "", 600,800)
    pad = ROOT.TPad("p","",0,0,1,1)
    pad.Draw()
    pad.Divide(1,2)

    histo.GetXaxis().SetTitle(var1)
    histo.GetYaxis().SetTitle(var2)
    histo.GetXaxis().SetTitleSize(0.04)
    histo.GetYaxis().SetTitleSize(0.04)

    h_bkg.GetXaxis().SetTitle(var1)
    h_bkg.GetYaxis().SetTitle(var2)
    h_bkg.GetXaxis().SetTitleSize(0.04)
    h_bkg.GetYaxis().SetTitleSize(0.04)

    pad.cd(1)
    histo.Draw("colz")
    canvas.cd(0)
    pad.cd(2)
    h_bkg.Draw("colz")
    canvas.SaveAs("./output/"+title+"VLLM100_WJets_MuonChannel_dRcutApplied.png")
    

#plot    
#plot2D(sigdf,"dijet_mass","lep0_mt",0,800,0,600,"dijetMass_Vs_LeptonMT_for_Signal")    
#plot2DSameCanvas(sigdf,df,"dijet_mass","lep0_mt",1000,0,1000,600,0,600,"dijetMass_Vs_LeptonMT")
#plot2DSameCanvas(sigdf,df,"deltaR_jet01","lep0_mt",100,0,10,600,0,600,"drjet01_Vs_LeptonMT")
#plot2DSameCanvas(sigdf,df,"dijet_mass","deltaR_jet01",600,0,600,100,0,10,"dijetMass_Vs_drjet01")
    
### WJETS BACKGROUND(ABCD Checks)
def GetEvents(h,binxlow,binxhi,binylow,binyhi):
    nevt=h.Integral(binxlow,binxhi,binylow,binyhi)
    #print("No of events between X= "+str(binxlow)+"-"+str(binxhi)+" and Y= "+str(binylow)+"-"+str(binyhi)+"= ")
    return nevt

nbinx=70
x_low=0
x_hi=7
nbiny=600
y_low=0
y_hi=600

#RegA=[40,200,40,130]
#RegB=[40,200,130,250]
#RegC=[200,400,20,130]
#RegD=[200,400,130,250]
RegA=[0.4,2.6,40,130]
RegB=[0.4,2.6,130,200]
RegC=[2.7,3.5,50,125]
RegD=[2.7,3.5,125,200]

#2DHistogram
h_1 = df.Histo2D(("h1","deltaR vs lepton mt",nbinx,x_low,x_hi,nbiny,y_low,y_hi),"deltaR_jet01","lep0_mt")

#Region
n_regA=GetEvents(h_1,int(RegA[0]*10),int(RegA[1]*10),RegA[2],RegA[3])    
n_regB=GetEvents(h_1,int(RegB[0]*10),int(RegB[1]*10),RegB[2],RegB[3])
n_regC=GetEvents(h_1,int(RegC[0]*10),int(RegC[1]*10),RegC[2],RegC[3])
n_regD=GetEvents(h_1,int(RegD[0]*10),int(RegD[1]*10),RegD[2],RegD[3])
print("Region A = ",n_regA)
print("Region B = ",n_regB)
print("Region C = ",n_regC)
print("Region D = ",n_regD)
print(" ")
print("----A/B = C/D verification-----\n")
print("A/B =",n_regA/n_regB)
print("C/D =",n_regC/n_regD)
print("Ratio =", (n_regA*n_regD)/(n_regB*n_regC))
print(" ")

ROOT.gStyle.SetOptStat(1)
ROOT.gStyle.SetTextFont(42)
canvas = ROOT.TCanvas("c", "", 800, 700)
#canvas.SetLogy()

#h_mass.SetTitle("Dimuon Invariant Mass")
h_1.GetXaxis().SetTitleSize(0.04)
h_1.GetYaxis().SetTitleSize(0.04)
#h_1.Rebin(1)
h_1.Draw("colz")

def DrawBox(xlow,xhi,ylow,yhi):
    box=ROOT.TBox(xlow,ylow,xhi,yhi)
    box.SetLineColor(ROOT.kBlack)
    box.SetFillStyle(0)
    return box
boxA=DrawBox(RegA[0],RegA[1],RegA[2],RegA[3])
boxA.Draw("SAME")
boxB=DrawBox(RegB[0],RegB[1],RegB[2],RegB[3])
boxB.Draw("SAME")
boxC=DrawBox(RegC[0],RegC[1],RegC[2],RegC[3])
boxC.Draw("SAME")
boxD=DrawBox(RegD[0],RegD[1],RegD[2],RegD[3])
boxD.Draw("SAME")

canvas.SaveAs("./output/deltaR_LeptonMT_Mass_MuonChannel.png")





