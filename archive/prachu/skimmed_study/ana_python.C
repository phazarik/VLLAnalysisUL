#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

//#############################################
// Run this ana script using the python module.
//#############################################

void ana(TString indir, TString outdir, TString outname, int data, int year)
{
  const char *hstfilename, *sumfilename;
  
  TChain *chain = new TChain("Events");
  VLLAna m_selec;//declared an instance of our class.

  TString files = "/*.root";
  TString infiles = indir + files; 

  chain->Add(infiles);
  hstfilename = outdir+"/hst_"+outname+".root";
  sumfilename = outdir+"/sum_"+outname+".txt";
  m_selec.SetData(data); //0 - running over MC, 1 - running over Data
  m_selec.SetYear(year);
  m_selec.SetMCwt(1);
  m_selec.SetLep(1);
  
  std::cout<<"Output files are "<<hstfilename<<" and "<<sumfilename<<std::endl;
  m_selec.SetHstFileName(hstfilename);
  m_selec.SetSumFileName(sumfilename);
  m_selec.SetVerbose(0);//set verbosity level for output.
  
  //this calls the Process function for each event in the chain
  //and runs the m_selec code over it.
  chain->Process(&m_selec);
    
}
