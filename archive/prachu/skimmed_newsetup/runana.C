#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
void runana(TString ifname="input_file" , TString ofname="outputfile" , TString data="data", TString year="year", TString lep="lep", TString era="era", TString MC="mc" )
{
  TString path_to_anaCond = "/home/phazarik/work/VLLAnalysis/new_setup/archive/prachu/skimmed_study/";
  TString path_to_so= "/home/phazarik/work/VLLAnalysis/new_setup/archive/prachu/skimmed_study/";
  TString anastring =".x "+path_to_anaCond+"anaCond.C(\""+ifname+"\",\""+ofname+"\",\""+data+"\",\""+year+"\",\""+lep+"\",\""+era+"\",\""+MC+"\")";
  gSystem->Load(path_to_so+"VLLAna_C.so");
  gROOT->ProcessLine(anastring);
}
