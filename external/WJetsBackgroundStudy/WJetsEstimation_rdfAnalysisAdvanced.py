import ROOT
import ROOT.RDataFrame as rdf
import plotdef as plot

#InputFile
ifpath = "/home/arnab/Arnab/Work/PhD2022/VLLAnalysisUL/external/InputFiles/VLL2018_1L2JAnalysisWJetsEstimation_Sep5_v2/"
ifname = "VLL2018_1L2JAnalysisWJetsEstimation_Sep5_v2_HTbinnedWJets_Inclusive_sample.root"
sigfname="VLL2018_1L2JAnalysisWJetsEstimation_Sep5_v2_VLLM100_sample.root"

df = rdf("TreeS",ifpath+ifname)
sigdf=rdf("TreeS",ifpath+sigfname)

#HandyFunctions
def ApplyCuts(df):
    df=df.Filter("n_bJet==0","nbjet cut")\
         .Filter("n_Jet<100","njet cut")\
         .Filter("deltaR_jet01<2.7","deltaR cut")\
         .Filter("dijet_mass<120 && dijet_mass>50","dijet mass cut")\
         .Filter("lep0_mt>0 && lep0_mt<125","lepton mt cut")
    return df

def Summary(sigdf,bkgdf):
    ##
    wjetslumi=1516.39
    siglumi=465811.96
    datalumi=59700
    print("\n****************************************************")
    print("No of WJets events =",bkgdf.Count().GetValue())
    print("No of VLLM100 events =",sigdf.Count().GetValue())
    print("---")
    print("No of WJets events =",bkgdf.Count().GetValue()*(datalumi/wjetslumi))
    print("No of VLLM100 events =",sigdf.Count().GetValue()*(datalumi/siglumi))
    print("***************************************************** ")

#################
##  FILTERING  ##
#################
df=df.Filter("abs(lep0_flavor)==13","Muon Flavor Cut")
sigdf=sigdf.Filter("abs(lep0_flavor)==13","Muon Flavor Cut")

#Prepare DataFrame for ABCD Method
df_sig=ApplyCuts(sigdf)
df_bkg=ApplyCuts(df)

#plot2D(sigdf,"dijet_mass","lep0_mt",0,800,0,600,"dijetMass_Vs_LeptonMT_for_Signal")    
#plot2DSameCanvas(sigdf,df,"dijet_mass","lep0_mt",1000,0,1000,600,0,600,"dijetMass_Vs_LeptonMT")
#plot2DSameCanvas(sigdf,df,"deltaR_jet01","lep0_mt",100,0,10,600,0,600,"drjet01_Vs_LeptonMT")
#plot2DSameCanvas(sigdf,df,"dijet_mass","deltaR_jet01",600,0,600,100,0,10,"dijetMass_Vs_drjet01")
    
### WJETS BACKGROUND(ABCD Checks)
def GetEvents(h,binxlow,binxhi,binylow,binyhi):
    nevt=h.Integral(binxlow,binxhi,binylow,binyhi)
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
ofname =""
RegA=[0.4,2.6,0,130]
RegB=[0.4,2.6,130,200]
RegC=[2.7,3.5,40,110]
RegD=[2.7,3.5,120,200]

##ABCD
df_regA=df.Filter("dijet_mass>50 && dijet_mass<110")
df_regB=df.Filter("deltaR_jet01<2.6 && lep0_mt<200 && lep0_mt>130")
df_regC=df.Filter("deltaR_jet01>2.7 && deltaR_jet01<3.5 && lep0_mt<125 && lep0_mt>50")
df_regD=df.Filter("deltaR_jet01>2.7 && deltaR_jet01<3.5 && lep0_mt<200 && lep0_mt>125")
#2DHistogram
h_regA= df_regA.Histo2D(("hA","deltaR vs lepton mt",nbinx,x_low,x_hi,nbiny,y_low,y_hi),"deltaR_jet01","lep0_mt")
h_regB= df_regB.Histo2D(("hB","deltaR vs lepton mt",nbinx,x_low,x_hi,nbiny,y_low,y_hi),"deltaR_jet01","lep0_mt")
h_regC= df_regC.Histo2D(("hC","deltaR vs lepton mt",nbinx,x_low,x_hi,nbiny,y_low,y_hi),"deltaR_jet01","lep0_mt")
h_regD= df_regD.Histo2D(("hD","deltaR vs lepton mt",nbinx,x_low,x_hi,nbiny,y_low,y_hi),"deltaR_jet01","lep0_mt")

h_1 = df.Histo2D(("h1","deltaR vs lepton mt",nbinx,x_low,x_hi,nbiny,y_low,y_hi),"deltaR_jet01","lep0_mt")

#Region
n_regA=GetEvents(h_regA,int(RegA[0]*10),int(RegA[1]*10),RegA[2],RegA[3])    
n_regB=GetEvents(h_1,int(RegB[0]*10),int(RegB[1]*10),RegB[2],RegB[3])
n_regC=GetEvents(h_1,int(RegC[0]*10),int(RegC[1]*10),RegC[2],RegC[3])
n_regD=GetEvents(h_1,int(RegD[0]*10),int(RegD[1]*10),RegD[2],RegD[3])

print("\n Channel Description\n============================")
print("Region A ="+str(RegA[0])+"<deltaR<"+str(RegA[1])+" && "+str(RegA[2])+"<LeptonMT<"+str(RegA[3]))
print("Region B ="+str(RegB[0])+"<deltaR<"+str(RegB[1])+" && "+str(RegB[2])+"<LeptonMT<"+str(RegB[3]))
print("Region C ="+str(RegC[0])+"<deltaR<"+str(RegC[1])+" && "+str(RegC[2])+"<LeptonMT<"+str(RegC[3]))
print("Region D ="+str(RegD[0])+"<deltaR<"+str(RegD[1])+" && "+str(RegD[2])+"<LeptonMT<"+str(RegD[3]))
print("----------------------\n")
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
h_1.GetXaxis().SetTitle("deltaR(Jet0,Jet1)")
h_1.GetYaxis().SetTitle("LeptonMT")
h_1.GetXaxis().CenterTitle()
h_1.GetYaxis().CenterTitle()
h_1.GetYaxis().SetTitleOffset(1.15)
#h_1.Rebin(1)
h_1.Draw("colz")

def DrawBox(xlow,xhi,ylow,yhi):
    box=ROOT.TBox(xlow,ylow,xhi,yhi)
    box.SetLineColor(ROOT.kRed)
    box.SetLineWidth(2)
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

text=ROOT.TLatex()
text.SetNDC(True)
text.SetTextFont(42)
text.SetTextSize(0.03)
txtstringA= "Region A= "+str(n_regA)
txtstringB= "Region B= "+str(n_regB)
txtstringC= "Region C= "+str(n_regC)
txtstringD= "Region D= "+str(n_regD)
txtABratio= "A/B     = {:.2f}".format(n_regA/n_regB)
txtCDratio= "C/D     = {:.2f}".format(n_regC/n_regD)
txtRatio  = "Ratio   = {:.2f}".format((n_regA*n_regD)/(n_regB*n_regC))
#txtstring="ABCD Method"
x=0.40;y=0.84
text.DrawLatex(x,y,txtstringA)
text.DrawLatex(x,y-0.04,txtstringB)
text.DrawLatex(x,y-0.08,txtstringC)
text.DrawLatex(x,y-0.12,txtstringD)
text.DrawLatex(x,y-0.16,txtABratio)
text.DrawLatex(x,y-0.2,txtCDratio)
text.DrawLatex(x,y-0.24,txtRatio)
##
text.DrawLatex(0.30,y,"B | D")
text.DrawLatex(0.30,y-0.02,"--------")
text.DrawLatex(0.30,y-0.04,"A | C")
text.Draw("SAME")
#canvas.Draw()


canvas.SaveAs("./output_sep92022/deltaR_LeptonMT_Mass_MuonChannel_advanced"+ofname+".png")

##plotIndividually
plot.plot2DSameCanvas(sigdf,df_regA,"deltaR_jet01","lep0_mt",100,0,10,600,0,600,"deltaRvsLepMT_advanced")





