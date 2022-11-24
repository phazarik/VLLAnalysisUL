#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
void runana(TString ifname="input_file" , TString ofname="outputfile" , TString data="data", TString year="year", TString lep="lep", TString era="era", TString MC="mc" )
{
TString anastring =".x /home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/archive/prachu/sig_study/anaCond.C(\""+ifname+"\",\""+ofname+"\",\""+data+"\",\""+year+"\",\""+lep+"\",\""+era+"\",\""+MC+"\")";
gSystem->Load("/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/archive/prachu/sig_study/VLLAna_C.so");
gROOT->ProcessLine(anastring);
}