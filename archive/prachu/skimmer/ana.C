#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
void ana(int sample=0)
{
  const char *hstfilename, *sumfilename, *skimfilename;
  
  TChain *chain = new TChain("Events");
  VLLAna m_selec;//declared an instance of our class.
  
  //--------------------------------------------------------------------------//
  //               Choose the sample you want to run over                     //
  //--------------------------------------------------------------------------//

  if(sample==0){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/QCD_MuEnriched/120to170/VLL_QCDPt120to170MuEnrichedPt5_10.root");
    hstfilename = "outputs/hst_qcd.root";
    sumfilename = "outputs/sum_qcd.txt";
    skimfilename = "outputs/QCD_skimmed.root";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  if(sample==1){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/DYJetsToLL/M50/VLL_DYJetsToLL_M50_9.root");
    hstfilename = "outputs/hst_dy.root";
    sumfilename = "outputs/sum_dy.txt";
    skimfilename = "outputs/DY_skimmed.root";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  if(sample==2){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/UL2018Data/SingleMuon/SingleMuon_A/SingleMuon_2018A_37.root");
    hstfilename = "outputs/hst_data.root";
    sumfilename = "outputs/sum_data.txt";
    skimfilename = "outputs/data_skimmed.root";
    m_selec.SetData(1); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }

  //Signal:
  if(sample==100){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/VLL/M100/*.root");
    hstfilename = "outputs/hst_vll100.root";
    sumfilename = "outputs/sum_vll100.txt";
    skimfilename = "skimmed_signal/VLL100_skimmed.root";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  if(sample==150){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/VLL/M150/*.root");
    hstfilename = "outputs/hst_vll150.root";
    sumfilename = "outputs/sum_vll150.txt";
    skimfilename = "skimmed_signal/VLL150_skimmed.root";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  if(sample==200){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/VLL/M200/*.root");
    hstfilename = "outputs/hst_vll200.root";
    sumfilename = "outputs/sum_vll200.txt";
    skimfilename = "skimmed_signal/VLL200_skimmed.root";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  if(sample==250){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/VLL/M250/*.root");
    hstfilename = "outputs/hst_vll250.root";
    sumfilename = "outputs/sum_vll250.txt";
    skimfilename = "skimmed_signal/VLL250_skimmed.root";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  if(sample==300){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/VLL/M300/*.root");
    hstfilename = "outputs/hst_vll300.root";
    sumfilename = "outputs/sum_vll300.txt";
    skimfilename = "skimmed_signal/VLL300_skimmed.root";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  if(sample==350){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/VLL/M350/*.root");
    hstfilename = "outputs/hst_vll350.root";
    sumfilename = "outputs/sum_vll350.txt";
    skimfilename = "skimmed_signal/VLL350_skimmed.root";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  if(sample==400){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/VLL/M400/*.root");
    hstfilename = "outputs/hst_vll400.root";
    sumfilename = "outputs/sum_vll400.txt";
    skimfilename = "skimmed_signal/VLL400_skimmed.root";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  
  std::cout<<"Output files are "<<hstfilename<<" and "<<sumfilename<<std::endl;
  m_selec.SetHstFileName(hstfilename);
  m_selec.SetSumFileName(sumfilename);
  m_selec.SetSkimFileName(skimfilename);
  m_selec.SetVerbose(0);//set verbosity level for output.
  
  //this calls the Process function for each event in the chain
  //and runs the m_selec code over it.
  chain->Process(&m_selec);
    
}
