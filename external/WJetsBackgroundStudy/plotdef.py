import ROOT

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
    canvas.SaveAs("./output/"+title+"VLLM100_WJets.pdf")

### WJETS BACKGROUND(ABCD Checks)
def GetEvents(h,binxlow,binxhi,binylow,binyhi):
    nevt=h.Integral(binxlow,binxhi,binylow,binyhi)
    #print("No of events between X= "+str(binxlow)+"-"+str(binxhi)+" and Y= "+str(binylow)+"-"+str(binyhi)+"= ")
    return nevt
    
