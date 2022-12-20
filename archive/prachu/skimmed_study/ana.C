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

  if(sample==0){
    chain->Add("/home/work/phazarik1/work/VLLanalysis/SkimmedSamples/Skimmed2018/VLLAna_2muSkimmed_Dec19/DYJetsToLL/M50/86264_VLL_DYJetsToLL_M50_100_data.root");
    hstfilename = "outputs/hst_dy_skimmed.root";
    sumfilename = "outputs/sum_dy_skimmed.txt";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  if(sample==1){
    chain->Add("/home/work/phazarik1/work/VLLanalysis/SkimmedSamples/Skimmed2018/VLLAna_2muSkimmed_Dec19/QCD_MuEnriched/170to300/86245_VLL_QCDPt170to300MuEnrichedPt5_10_data.root");
    hstfilename = "outputs/hst_qcd_skimmed.root";
    sumfilename = "outputs/sum_qcd_skimmed.txt";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  if(sample==-1){
    chain->Add("/home/work/phazarik1/work/VLLanalysis/SkimmedSamples/Skimmed2018/VLLAna_2muSkimmed_Dec19/UL2018Data/SingleMuon/SingleMuon_A/86281_SingleMuon_2018A_10_data.root");
    hstfilename = "outputs/hst_data_skimmed.root";
    sumfilename = "outputs/sum_data_skimmed.txt";
    m_selec.SetData(1); //0 - running over MC, 1 - running over Data
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
