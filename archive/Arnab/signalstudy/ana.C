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

  //VLLM100 ULegacy
  if(sample==1){
    chain->Add("/home/work/alaha1/public/RunII_ULNanoAODv8Samples/signal/2018/VLL/VLLM100/*");
    hstfilename = "VLLM100_UL.root";
    sumfilename = "VLLM100_UL.txt";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }

  // DYToLL ULegacy
  if(sample==2){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/DYJetsToLL/M50/VLL_DYJetsToLL_M50_9.root");//83 for more events
    hstfilename = "DYJets_UL.root";
    sumfilename = "DYJets_UL.txt";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }


  // W+Jets Inclusive(For Sourabh July 18 2022)
  if(sample==3){
    chain->Add("/home/work/alaha1/work/FullRun2/VLLAnalysis/LocalSamples/*");//83 for more events
    hstfilename = "WJets_UL.root";
    sumfilename = "WJets_UL.txt";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
    //m_selec.SetNNFileName("/home/arnab/Arnab/Work/PhD2021/VLLSingletStudy/MultiClassifier/SignalScore_vllneuron.txt");
  }

  // SingleMu Data UL(For Sourabh July 18 2022)
  if(sample==4){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/QCD_MuEnriched/120to170/VLL_QCDPt120to170MuEnrichedPt5_61.root");//83 for more events
    hstfilename = "QCD_UL.root";
    sumfilename = "QCD_UL.txt";
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
