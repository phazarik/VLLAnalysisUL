#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
void ana(int sample=0)
{
  const char *hstfilename, *sumfilename;
  
  TChain *chain = new TChain("Events");
  VLLAna m_selec;//declared an instance of our class.
  
  //--------------------------------------------------------------------------//
  //               Choose the sample you want to run over                     //
  //--------------------------------------------------------------------------//

  if(sample==0){
    chain->Add("/home/work/phazarik1/work/VLLanalysis/SkimmedSamples/Skimmed2018/VLLAna_2muSSskimmed_May22/SingleMuon/SingleMuon_A/*.root");
    hstfilename = "outputs/hst_data_test.root";
    sumfilename = "outputs/sum_data_test.txt";
    m_selec.SetData(1); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  if(sample==1){
    chain->Add("/home/work/phazarik1/work/VLLanalysis/SkimmedSamples/Skimmed2018/VLLAna_2muSSskimmed_May22/DYJetsToLL/M50/*.root");
    hstfilename = "outputs/hst_dy_skimmed.root";
    sumfilename = "outputs/sum_dy_skimmed.txt";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }

  //For signal:
  if(sample==100){
    chain->Add("/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/archive/prachu/skimmer/skimmed_signal/VLL100_skimmed.root");
    hstfilename = "outputs/hst_VLL100.root";
    sumfilename = "outputs/sum_VLL100.txt";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  
  std::cout<<"Output files are "<<hstfilename<<" and "<<sumfilename<<std::endl;
  m_selec.SetHstFileName(hstfilename);
  m_selec.SetSumFileName(sumfilename);
  m_selec.SetVerbose(0);//set verbosity level for output.
  
  //this calls the Process function for each event in the chain
  //and runs the m_selec code over it.
  chain->Process(&m_selec);
    
}
