#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
void ana(int sample=2)
{
  const char *hstfilename, *sumfilename;
  
  TChain *chain = new TChain("Events");
  VLLAna m_selec;//declared an instance of our class.
  
  //--------------------------------------------------------------------------//
  //               Choose the sample you want to run over                     //
  //--------------------------------------------------------------------------//
  if(sample==-1){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/UL2018Data/EGamma/EGamma_A/EGamma_2018A_101.root");
    hstfilename = "outputs/hst_data_EGamma.root";
    sumfilename = "outputs/sum_data_EGamma.txt";
    m_selec.SetData(1); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(0); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  if(sample==0){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/UL2018Data/SingleMuon/SingleMuon_A/SingleMuon_2018A_78.root");
    hstfilename = "outputs/hst_data_SingleMuon.root";
    sumfilename = "outputs/sum_data_SingleMuon.txt";
    m_selec.SetData(1); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  if(sample==1){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/QCD_MuEnriched/120to170/VLL_QCDPt120to170MuEnrichedPt5_10.root");
    hstfilename = "outputs/hst_qcd.root";
    sumfilename = "outputs/sum_qcd.txt";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  if(sample==2){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/DYJetsToLL/M50/VLL_DYJetsToLL_M50_9.root");
    hstfilename = "outputs/hst_dy.root";
    sumfilename = "outputs/sum_dy.txt";
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
