#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <string>
using namespace std;

void ana(int sample=0)
{
  const char *hstfilename, *sumfilename;
  
  TChain *chain = new TChain("Events");
  VLLAna m_selec;//declared an instance of our class.
  
  //--------------------------------------------------------------------------//
  //               Choose the sample you want to run over                     //
  //--------------------------------------------------------------------------//

  if(sample==0){
    chain->Add("/home/work/phazarik1/work/VLLanalysis/SkimmedSamples/Skimmed2018/VLLAna_2LSSskimmed_Aug16/SingleMuon/SingleMuon_A/*.root");
    hstfilename = "outputs/hst_data.root";
    sumfilename = "outputs/sum_data.txt";
    m_selec.SetData(1); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  else if(sample==1){
    chain->Add("/home/work/phazarik1/work/VLLanalysis/SkimmedSamples/Skimmed2018/VLLAna_2LSSskimmed_Aug16/DYJetsToLL/M50/*.root");
    hstfilename = "outputs/hst_dy.root";
    sumfilename = "outputs/sum_dy.txt";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }

  else if(sample==2){
    chain->Add("/home/work/phazarik1/work/VLLanalysis/SkimmedSamples/Skimmed2018/VLLAna_2LSSskimmed_Aug16/QCD_MuEnriched/470to600/*.root");
    hstfilename = "outputs/hst_qcd.root";
    sumfilename = "outputs/sum_qcd.txt";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }


  //---------------------------------------------------------------------------------------------------------------------------------------
  //For signal:
  else if (sample==100) {
    chain->Add("/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/archive/prachu/skimmer/skimmed_signal/VLL100_skimmed.root");    
    hstfilename = "outputs/hst_VLL100.root";
    sumfilename = "outputs/sum_VLL100.txt";;
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
  }
  else if (sample==150) {
    chain->Add("/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/archive/prachu/skimmer/skimmed_signal/VLL150_skimmed.root");    
    hstfilename = "outputs/hst_VLL150.root";
    sumfilename = "outputs/sum_VLL150.txt";;
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
  }
  else if (sample==200) {
    chain->Add("/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/archive/prachu/skimmer/skimmed_signal/VLL200_skimmed.root");    
    hstfilename = "outputs/hst_VLL200.root";
    sumfilename = "outputs/sum_VLL200.txt";;
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
  }
  else if (sample==250) {
    chain->Add("/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/archive/prachu/skimmer/skimmed_signal/VLL250_skimmed.root");    
    hstfilename = "outputs/hst_VLL250.root";
    sumfilename = "outputs/sum_VLL250.txt";;
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
  }
  else if (sample==300) {
    chain->Add("/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/archive/prachu/skimmer/skimmed_signal/VLL300_skimmed.root");    
    hstfilename = "outputs/hst_VLL300.root";
    sumfilename = "outputs/sum_VLL300.txt";;
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
  }
  else if (sample==350) {
    chain->Add("/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/archive/prachu/skimmer/skimmed_signal/VLL350_skimmed.root");    
    hstfilename = "outputs/hst_VLL350.root";
    sumfilename = "outputs/sum_VLL350.txt";;
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
  }
  else if (sample==400) {
    chain->Add("/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/archive/prachu/skimmer/skimmed_signal/VLL400_skimmed.root");    
    hstfilename = "outputs/hst_VLL400.root";
    sumfilename = "outputs/sum_VLL400.txt";;
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
  }
  
  std::cout<<"Output files are "<<hstfilename<<" and "<<sumfilename<<std::endl;
  m_selec.SetHstFileName(hstfilename);
  m_selec.SetSumFileName(sumfilename);
  m_selec.SetVerbose(0);//set verbosity level for output.
  
  //this calls the Process function for each event in the chain
  //and runs the m_selec code over it.
  chain->Process(&m_selec);
    
}
