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
  
  if(sample==1){
    chain->Add("/home/work/alaha1/work/skimmedTrees/1L2JSkim/2018/HTbinnedWJets/100to200/83676_VLL_WJetsHT100to200_54_data.root");
    hstfilename = "wjets_skimUL.root";
    sumfilename = "wjets_skimUL.txt";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }

  // DYToLL ULegacy
  if(sample==2){
    chain->Add("/home/work/alaha1/work/skimmedTrees/2LSkim/2018/DYJetsToLL/M50/83675_VLL_DYJetsToLL_M50_83_data.root");//83 for more events
    hstfilename = "DYJets_UL.root";
    sumfilename = "DYJets_UL.txt";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  
  //VLLM100 ULegacy
  if(sample==3){
    chain->Add("/home/work/alaha1/public/RunII_ULNanoAODv8Samples/signal/2018/VLL/VLLM100/*");
    hstfilename = "VLL2018_M100.root";
    sumfilename = "VLLM100_UL.txt";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }

  
  //WJetsULInclusive
  if(sample==4){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/HTbinnedWJets/Inclusive/VLL_WJetsToLNu_Inclusive_89.root");//83 for more events
    hstfilename = "WJets_ULIncl.root";
    sumfilename = "Data_UL.txt";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }

  //WJetsTesting(29Aug2022)
  if(sample==5){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/HTbinnedWJets/1200to2500/VLL_WJetsHT1200to2500_3.root");//83 for more events
    hstfilename = "WJets_UL1200to2500test.root";
    sumfilename = "Data_UL.txt";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }

  //Data(29Aug2022)
  if(sample==6){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/UL2018Data/SingleMuon/SingleMuon_A/SingleMuon_2018A_92.root");//83 for more events
    hstfilename = "SingleMuonData_UL.root";
    sumfilename = "Data_UL.txt";
    m_selec.SetData(1); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }
  
  //SkimmedData(29Aug2022)
  if(sample==7){
    chain->Add("/home/work/alaha1/work/skimmedTrees/1L2JSkim/2018/SingleMuon/SingleMuon_A/*SingleMuon_2018A_88_data.root");//
    hstfilename = "SingleMuonData_ULSkimmed.root";
    sumfilename = "Data_UL.txt";
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

  //m_select.SetAnalysis1L2J_HstFileName;
  //this calls the Process function for each event in the chain
  //and runs the m_selec code over it.
  chain->Process(&m_selec);
    
}
