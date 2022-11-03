import ROOT
from ROOT import *


#############################################################
# Some Global Variable
#############################################################

doRatio=0.25  ## RatioPad/Pad, applied when PlotRatioPad==True

#############################################################

def CreatePad(padName,padYlow,padYhigh):
    pad = ROOT.TPad(padName, padName, 0, padYlow, 1.0, padYhigh);
    pad.SetLogy(1)
    gStyle.SetOptStat(0)
    pad.SetLeftMargin(0.15)
    pad.SetRightMargin(0.20)
    pad.SetTopMargin(0.09)
    pad.SetBottomMargin(0.12)
    pad.SetTickx(1)
    pad.SetTicky(1)
    
    if(PlotRatioPad==True):
        pad = ROOT.TPad(padName, padName, 0, padYlow+doRatio,1.0, padYhigh);
        pad.SetLogy(1)
        gStyle.SetOptStat(0)
        pad.SetLeftMargin(0.15)
        pad.SetRightMargin(0.20)
        pad.SetTopMargin(0.09)
        pad.SetBottomMargin(0.01)
        pad.SetTickx(1)
        pad.SetTicky(1)
    
    return pad

def CreateRatioPad(padName,padYlow,padYhigh):
    padYhigh=doRatio
    pad = ROOT.TPad(padName, padName, 0, padYlow, 1,doRatio);
    gStyle.SetOptStat(0)
    pad.SetLeftMargin(0.15)
    pad.SetRightMargin(0.20)
    pad.SetTopMargin(0.05)
    pad.SetBottomMargin(0.40)
    pad.SetTickx(1)
    pad.SetTicky(1)
    return pad
    #return ratiopad


def SetHistoStyle(histo,xlabel=""):
    histo.SetLineColor(kBlack)
    histo.SetLineWidth(2)
    histo.SetMarkerStyle(20)
    histo.SetMarkerSize(1.2)
    histo.SetTitle("")
    
    #Y-axis
    histo.GetYaxis().SetTitle("Count")
    histo.GetYaxis().SetTitleFont(43)
    histo.GetYaxis().SetTitleSize(20)
    histo.GetYaxis().SetTitleOffset(1.6)
    histo.GetYaxis().SetLabelFont(43)
    histo.GetYaxis().SetLabelSize(20)
    histo.GetYaxis().CenterTitle()

    #X-axis
    histo.GetXaxis().SetTitle(xlabel)
    histo.GetXaxis().SetTitleFont(43)
    histo.GetXaxis().SetTitleSize(20)
    histo.GetXaxis().SetTitleOffset(1.5)
    histo.GetXaxis().SetLabelFont(43)
    histo.GetXaxis().SetLabelSize(20)    
    histo.GetXaxis().CenterTitle()

    
    #height adjustment
    maxbin=histo.GetMaximumBin()
    maxheight=histo.GetBinContent(maxbin)
    #histo.GetYaxis().SetRangeUser(0.1,maxheight*10)
    #return histo


def SetOverlayHistoStyle(histo,linecolor,linewidth,xlabel=""):
    histo.SetLineColor(linecolor)
    histo.SetLineWidth(linewidth)
    #histo.SetMarkerStyle(20)
    #histo.SetMarkerSize(1.2)
    histo.SetTitle(xlabel)
    
    #Y-axis
    histo.GetYaxis().SetTitle("Normalized Count")
    histo.GetYaxis().SetTitleFont(43)
    histo.GetYaxis().SetTitleSize(20)
    histo.GetYaxis().SetTitleOffset(1.2)
    histo.GetYaxis().SetLabelFont(43)
    histo.GetYaxis().SetLabelSize(20)
    histo.GetYaxis().CenterTitle()

    #X-axis
    histo.GetXaxis().SetTitle(xlabel)
    histo.GetXaxis().SetTitleFont(43)
    histo.GetXaxis().SetTitleSize(20)
    histo.GetXaxis().SetTitleOffset(1.5)
    histo.GetXaxis().SetLabelFont(43)
    histo.GetXaxis().SetLabelSize(20)    
    histo.GetXaxis().CenterTitle()

    
    #height adjustment
    maxbin=histo.GetMaximumBin()
    maxheight=histo.GetBinContent(maxbin)
    #histo.GetYaxis().SetRangeUser(0.1,maxheight*10)
    #return histo


    
def SetRatioHistoStyle(ratiohist,xlabel=""):

    ratiohist.SetLineColor(kBlack)
    ratiohist.SetLineWidth(2)
    ratiohist.SetMarkerStyle(20)
    ratiohist.SetMarkerSize(1.2)
    ratiohist.SetTitle("")


    ##X-axis
    ratiohist.GetXaxis().SetTitle(xlabel)
    ratiohist.GetXaxis().SetTitleSize(20)
    ratiohist.GetXaxis().SetTitleFont(43)
    ratiohist.GetXaxis().SetTitleOffset(1.15)
    ratiohist.GetXaxis().SetLabelFont(43)
    ratiohist.GetXaxis().SetLabelSize(20)
    ratiohist.GetXaxis().CenterTitle()

    ##Y-axis
    ratiohist.GetYaxis().SetTitle("Obs/Exp")
    ratiohist.GetYaxis().SetTitleFont(43)
    ratiohist.GetYaxis().SetTitleSize(16)
    ratiohist.GetYaxis().SetTitleOffset(1.25)
    ratiohist.GetYaxis().SetLabelFont(43)
    ratiohist.GetYaxis().SetLabelSize(20)
    ratiohist.GetYaxis().SetNdivisions(503);
    ratiohist.GetYaxis().CenterTitle()
    ratiohist.GetYaxis().SetRangeUser(0,2);


def SetStackHistoStyle(stackhist,xlabel=""):
    ##X-axis
    #ratiohist.GetXaxis().SetTitle(xlabel)
    #ratiohist.GetXaxis().SetTitleSize(20)
    #ratiohist.GetXaxis().SetTitleFont(43)
    #ratiohist.GetXaxis().SetTitleOffset(1.15)
    #ratiohist.GetXaxis().SetLabelFont(43)
    #ratiohist.GetXaxis().SetLabelSize(20)
    #ratiohist.GetXaxis().CenterTitle()

    ##Y-axis
    #Y-axis
    stackhist.GetYaxis().SetTitle("Count")
    stackhist.GetYaxis().SetTitleFont(43)
    stackhist.GetYaxis().SetTitleSize(20)
    stackhist.GetYaxis().SetTitleOffset(1.6)
    stackhist.GetYaxis().SetLabelFont(43)
    stackhist.GetYaxis().SetLabelSize(20)
    stackhist.GetYaxis().CenterTitle()

    
    

def SetLegendStyle(legend):
    legend.SetTextFont(62)
    legend.SetFillStyle(0)
    legend.SetBorderSize(0)
    legend.SetTextSize(0.03)
    #legend.SetTextAlign(32)

    #return legend


def CMSLabel(pad):
    ##Text Cosmetics
    CMSLabelName1=''
    CMSLabelName2=''
    
    if(publicationStyle==True):
        CMSLabelName1='CMS'
        CMSLabelName2='Internal'
    if((WorkInProgress==True) and (publicationStyle==False)):
        CMSLabelName1='CMS'
        CMSLabelName2='Work in progress'
    else: pass
        
    text = ROOT.TLatex()
    text.SetNDC(True)
    text.SetTextFont(42)
    text.SetTextSize(0.05)
    text.DrawLatex(0.15, 0.92, CMSLabelName1)

    TakeLegendOutside=True    
    if(TakeLegendOutside==True):
        if(year==2018):
            text.DrawLatex(pad.GetUxmax()-0.47, 0.92, "#sqrt{{s}} = 13 TeV, {:.1f} fb^{{-1}}".format(59.7))
    else:
        if(year==2016):
            text.DrawLatex(pad.GetUxmax()-0.42, 0.92, "#sqrt{{s}} = 13 TeV, {:.1f} fb^{{-1}}".format(35.9))
        if(year==2017):
            text.DrawLatex(pad.GetUxmax()-0.42, 0.92, "#sqrt{{s}} = 13 TeV, {:.1f} fb^{{-1}}".format(41.9))
        if(year==2018):
            text.DrawLatex(pad.GetUxmax()-0.42, 0.92, "#sqrt{{s}} = 13 TeV, {:.1f} fb^{{-1}}".format(59.7))    

    ##Italic
    text.SetTextFont(72)
    text.SetTextSize(0.04)
    text.DrawLatex(0.15 + 0.07, 0.92, CMSLabelName2)

            
        
    text.Draw("SAME")


def DrawText(X,Y,txt):
    text = ROOT.TLatex()
    text.SetNDC(True)
    text.SetTextFont(42)
    text.SetTextSize(0.04)
    text.DrawLatex(X,Y,txt)

    text.Draw("SAME")
########################################################
#               Handy Function on Histogram
########################################################
     
def Count(histo):
    n_count="{:.2f}".format(histo.Integral())
    return str(n_count)

def SetOverflowBin(histo):
    nbins = histo.GetNbinsX()
    histo.SetBinContent(nbins, histo.GetBinContent(nbins) + histo.GetBinContent(nbins+100)); ## Overflow
    histo.SetBinContent(1, histo.GetBinContent(1)+ histo.GetBinContent(-100));               ## Underflow

    
