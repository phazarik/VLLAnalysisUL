import ROOT
from ROOT import *
import setup.plotsetup.plot_settings as plotsetting
import setup.plotsetup.plotmaker as pset
###################################################

inputdir="/home/arnab/Arnab/Work/PhD2022/VLLAnalysisUL/external/InputFiles/BestMassStudy/"

filename1="VLLM100_UL.root"
filename2="WJets_ULIncl.root"

plotname1="dijetmass_l2j_base;1"
plotname2="bestdijetMass;1"


vllfile=TFile.Open(inputdir+filename1,'READ')
wjetfile=TFile.Open(inputdir+filename2,'READ')

def GetHisto(fname,plotname):
    histo=fname.Get(plotname)
    #histo.SetDirectory(0)
    plotsetting.SetOverflowBin(histo)
    histoevent=float(pset.Count(histo))
    return histo

vllhisto_dijetmass=GetHisto(vllfile,plotname2)
vllhisto_bestdijetmass=GetHisto(wjetfile,plotname2)

#Legend
legend=TLegend(0.60,0.55,0.90,0.82)
plotsetting.SetLegendStyle(legend)    

legend.AddEntry(vllhisto_dijetmass,"BestDijetMass_vll","l")
legend.AddEntry(vllhisto_bestdijetmass,"BestDijetMass_wjets","l")

canvas=TCanvas("can","",700,600)
gStyle.SetOptStat(1)

##decoration
vllhisto_dijetmass.SetLineWidth(2)
vllhisto_dijetmass.SetLineColor(kBlue)
vllhisto_bestdijetmass.SetLineWidth(2)
vllhisto_bestdijetmass.SetLineColor(kRed)
vllhisto_bestdijetmass.GetYaxis().SetTitle("Count")
vllhisto_bestdijetmass.GetXaxis().SetTitle("dijetInvMass(GeV)")
vllhisto_bestdijetmass.GetYaxis().CenterTitle()
vllhisto_bestdijetmass.GetXaxis().CenterTitle()

##Normalization
vllhisto_dijetmass.Scale(1/float(pset.Count(vllhisto_dijetmass)))
vllhisto_bestdijetmass.Scale(1/float(pset.Count(vllhisto_bestdijetmass)))

#Draw
vllhisto_bestdijetmass.Draw("HIST")
vllhisto_dijetmass.Draw("HIST SAMES")
legend.Draw()

#Rebin
vllhisto_dijetmass.Rebin(10)
vllhisto_bestdijetmass.Rebin(10)

canvas.Draw()







