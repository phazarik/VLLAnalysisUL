#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
void ana(int sample=2)
{
  const char *hstfilename, *sumfilename, *skimfilename;
  
  TChain *chain = new TChain("Events");
  VLLAna m_selec;//declared an instance of our class.
  
  //--------------------------------------------------------------------------//
  //               Choose the sample you want to run over                     //
  //--------------------------------------------------------------------------//
  // DYToLL ULegacy
  if(sample==1){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/DYJetsToLL/M50/VLL_DYJetsToLL_M50_9.root");//83 for more events
    hstfilename = "DYJets_UL.root";
    sumfilename = "DYJets_UL.txt";
    skimfilename = "DYJetsUL_Skimmed.root";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
  }
  

  //SingleMuon UL Data
  if(sample==2){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/UL2018Data/SingleMuon/SingleMuon_A/SingleMuon_2018A_92.root");
    hstfilename = "SingleMuonData_UL.root";
    sumfilename = "SingleMuonData_UL.txt";
    skimfilename = "SingleMuonData_UL_skimmed.root";
    m_selec.SetData(1); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
  }
  
  //QCD
  if(sample==3){
    chain->Add("/home/work/alaha1/public/RunII_ULSamples/2018/QCD_MuEnriched/120to170/VLL_QCDPt120to170MuEnrichedPt5_61.root");
    hstfilename = "QCD_UL.root";
    sumfilename = "QCD_UL.txt";
    skimfilename = "QCDUL_skimmed.root";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
  }
  
  std::cout<<"Output files are "<<hstfilename<<" and "<<sumfilename<<" and "<<skimfilename<<std::endl;
  m_selec.SetHstFileName(hstfilename);
  m_selec.SetSumFileName(sumfilename);
  m_selec.SetSkimFileName(skimfilename);
  m_selec.SetVerbose(0);//set verbosity level for output.
  
  //this calls the Process function for each event in the chain
  //and runs the m_selec code over it.
  chain->Process(&m_selec);
  
}
