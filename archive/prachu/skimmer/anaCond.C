#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
//#include <boost/lexical_cast.hpp>// for lexical_cast()

void anaCond( TString ifname , TString ofname, TString data, TString year, TString lep, TString era, TString MC)
{
  gROOT->Time();  
  const char *hstfilename,*skimfilename;
  TChain *chain = new TChain("Events");
  VLLAna m_selec;
  //cout<<"Declared chains"<<endl;
  TString input = ifname;
  bool manual = input.EndsWith(".root");
  //bool single = (mode == 4 || mode == 5);//not used anymore
  bool single=false;
  if(!manual) {
    input += "/*.root";
  }
  chain->Add(input);	
  hstfilename = "hst_"+ofname;
  skimfilename= ofname;
  //cout<<"Output files are "<<hstfilename<<endl;
  m_selec.SetHstFileName(hstfilename);
  m_selec.SetSkimFileName(skimfilename);
  if(data=='0'&& MC=="wz")
    m_selec.SetNNFileName("/home/work/alaha/Work/FullRun2/VLLSROpt/wjetsScore_Binary_CombineType3.txt");
  if(data=='0'&& MC=="tt")
    m_selec.SetNNFileName("/home/work/alaha/Work/FullRun2/VLLSROpt/ttjetsScore_Binary_CombineType3.txt");
  if(data=='0'&& MC=="dy")
    m_selec.SetNNFileName("/home/work/alaha/Work/FullRun2/VLLSROpt/zjetsScore_Binary_CombineType3.txt");
  
  m_selec.SetVerbose(1);
  //  m_selec.SetData(boost::lexical_cast<int>(data)); //0 - not running over data, 1 - running over data
  if(data=="0")
    m_selec.SetData(0); //0 - not running over data, 1 - running over data
  if(data=="1")
    m_selec.SetData(1); //0 - not running over data, 1 - running over data
  
  m_selec.SetSample(0); //_sample = 0-WZ, 1-ZZ, 2-TTW, 3-TTZ, 4-TTH, 5-WWW, 6-WWZ, 7-DY, 8-TTDilep, 9-TTSlep, 10-TTBarSlep
  if(year=="2016")
    m_selec.SetYear(2016);
  if(year=="2017")
    m_selec.SetYear(2017);
  if(year=="2018")
    m_selec.SetYear(2018);
  m_selec.SetEra(era);
  if(lep=="el")
    m_selec.SetLep(0);
  if(lep=="mu")
    m_selec.SetLep(1);
  //cout<<"Set the options"<<endl;

  float MC2016_normwt[13] = {1,1.02,1,1.14,1,1,1,1,1,1,1,1,1}; //_sample = 0-WZ, 1-ZZ, 2-TTW, 3-TTZ, 4-TTH, 5-WWW, 6-WWZ, 7-WZZ, 8-ZZZ, 9-signal, 10-DY, 11-TTDilep, 12-rare
  float MC2017_normwt[13] = {1.03,1.00,1,1.40,1,1,1,1,1,1,1,1,1}; //_sample = 0-WZ, 1-ZZ, 2-TTW, 3-TTZ, 4-TTH, 5-WWW, 6-WWZ, 7-WZZ, 8-ZZZ, 9-signal, 10-DY, 11-TTDilep, 12-rare
  float MC2018_normwt[13] = {1.,1.,1,1.,1,1,1,1,1,1,1,1,1}; //_sample = 0-WZ, 1-ZZ, 2-TTW, 3-TTZ, 4-TTH, 5-WWW, 6-WWZ, 7-WZZ, 8-ZZZ, 9-signal, 10-DY, 11-TTDilep, 12-rare

  if(data=="0"){
    int _sample = -1;
    if(MC=="wz")
      _sample = 0;
    if(MC=="zz")
      _sample = 1;
    if(MC=="ttw")
      _sample = 2;
    if(MC=="ttz")
      _sample = 3;
    if(MC=="tth")
      _sample = 4;
    if(MC=="www")
      _sample = 5;
    if(MC=="wwz")
      _sample = 6;
    if(MC=="wzz")
      _sample = 7;
    if(MC=="zzz")
      _sample = 8;
    if(MC=="rhn"){
      _sample = 9;
      m_selec.SetSample(9);
    }
    if(MC=="dy")
      _sample = 10;
    if(MC=="tt")
      _sample = 11;
    if(MC=="rare")
      _sample = 12;
  
    if(year=="2016")
      m_selec.SetMCwt(MC2016_normwt[_sample]);
    if(year=="2017")
      m_selec.SetMCwt(MC2017_normwt[_sample]);
    if(year=="2018")
      m_selec.SetMCwt(MC2018_normwt[_sample]);
  }
  
  chain->Process(&m_selec);
  gROOT->Time();
}
