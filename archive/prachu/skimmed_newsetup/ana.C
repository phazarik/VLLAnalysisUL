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
  TString jobname = "VLLAna_2muSSskimmed_Apr18";
  TString inputdir = "/home/work/phazarik1/work/VLLanalysis/SkimmedSamples/Skimmed2018/"+jobname;
  cout<<"inputdir = "<<inputdir<<endl;

  if(sample==-1){
    chain->Add(inputdir+"/SingleMuon/SingleMuon_A/88926_SingleMuon_2018A_10_data.root");
    hstfilename = "outputs/hst_data.root";
    sumfilename = "outputs/sum_data.txt";
    m_selec.SetData(1); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
  }
  
  if(sample==0){
    chain->Add(inputdir+"/QCD_MuEnriched/800to1000/*.root");
    hstfilename = "outputs/hst_qcd.root";
    sumfilename = "outputs/sum_qcd.txt";
    m_selec.SetData(0); //0 - running over MC, 1 - running over Data
    m_selec.SetYear(2018);
    m_selec.SetMCwt(1);
    m_selec.SetLep(1); //0-electron dataset, 1-muon dataset
  }

  if(sample==1){
    chain->Add(inputdir+"/TTBar/TTToSemiLeptonic/*.root");
    hstfilename = "outputs/hst_ttbar.root";
    sumfilename = "outputs/sum_ttbar.txt";
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
