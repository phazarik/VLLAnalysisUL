import ROOT
import ROOT.RDataFrame as rdf

ifname_qcd_inclusive="./inputSamples/VLL_QCDPt20MuEnrichedPt15_5.root"
ifname_qcd_20to30="./inputSamples/VLL_QCDPt20to30MuEnrichedPt5_50.root"

df_incl = rdf("Events",ifname_qcd_inclusive)
df_20to30=rdf("Events",ifname_qcd_20to30)

print("\n Summary of Files\n--------------------------")
print("Events in Inclusive QCD File = ",df_incl.Count().GetValue())
print("Events in QCD_PTBinned_20to30 File = ",df_20to30.Count().GetValue())


def plot(df,var,nbins,binlow,binhi,title):
    histo=df.Histo1D(("histo",var+";"+var+";Count",nbins,binlow,binhi),var)
    #plotting
    ROOT.gStyle.SetOptStat(1)
    ROOT.gStyle.SetTextFont(42)
    canvas = ROOT.TCanvas("c", "", 800, 700)
    canvas.SetLogy()

    histo.SetTitle(title)
    histo.GetXaxis().SetTitleSize(0.04)
    histo.GetYaxis().SetTitleSize(0.04)
    histo.SetLineWidth(2)
    histo.Rebin(10)
    histo.Draw("HIST")    
    canvas.SaveAs(title+".pdf")

def plotOverlay(df1,df2,var,nbins,binlow,binhi,title):
    histo1=df1.Histo1D(("h1",var+";"+var+";Count",nbins,binlow,binhi),var)
    histo2=df2.Histo1D(("h2",var+";"+var+";Count",nbins,binlow,binhi),var)
    #plotting
    ROOT.gStyle.SetOptStat(0)
    ROOT.gStyle.SetTextFont(42)
    canvas = ROOT.TCanvas("c", "", 800, 700)
    ROOT.SetOwnership(canvas,False)
    canvas.SetLogy()
    
    #decoration
    histo1.SetTitle(title)
    histo1.GetXaxis().SetTitleSize(0.04)
    histo1.GetYaxis().SetTitleSize(0.04)
    histo1.SetLineWidth(2)
    histo1.SetLineColor(ROOT.kRed)

    histo2.SetLineColor(ROOT.kBlue)
    histo2.SetLineWidth(2)
    
    histo1.Rebin(5)
    histo2.Rebin(5)
    #histo1.Scale(1/histo1.Integral())
    #histo2.Scale(1/histo2.Integral())
    histo1=histo1.DrawCopy("HIST")    
    histo2=histo2.DrawCopy("HIST SAME")

    #Legend
    legend = ROOT.TLegend(0.40,0.55,0.80,0.82)
    legend.SetFillColor(0)
    legend.SetBorderSize(0)
    legend.SetTextSize(0.03)
    legend.AddEntry(histo1,"QCDPt20toInf_MuEnrichedPt15","l")
    legend.AddEntry(histo2, "QCDPt20to30_MuEnrichedPt5","l")
    legend.Draw()
    canvas.Draw()
    canvas.SaveAs(title+"_overlay_notnormalized.png")

    
    
#plot(df_incl,"Muon_pt",1000,0,1000,"MuonPt_QcdInclusive")
#plot(df_20to30,"Muon_pt",1000,0,1000,"MuonPt_Qcd_20to30")

df_incl_pt30=df_incl.Filter("All(Jet_pt<45)")

plotOverlay(df_incl_pt30,df_20to30,"Muon_pt",300,0,300,"MuonPt")
plotOverlay(df_incl_pt30,df_20to30,"Jet_pt",300,0,300,"JetPt")
plotOverlay(df_incl_pt30,df_20to30,"Electron_pt",300,0,300,"ElectronPt")
