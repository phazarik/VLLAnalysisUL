
// Applying scale factor for ele,mu and tau for 2016,2017,2018 by calling the individual SF function defined later


float VLLAna::LeptonID_SF(int id, float pt, float eta)
{
  float SF = 1.;
  
  //TAU
  if(abs(id)==15){
    float TauPt =pt;
    float TauEta=eta;
    if(_year==2016)
      SF = tauSF2016(TauPt,TauEta);
    if(_year==2017)
      SF = tauSF2017(TauPt,TauEta);
    if(_year==2018)
      SF = tauSF2018(TauPt,TauEta);
  }

  //MUON
  if(abs(id)==13){
    if(_year==2016)
      SF = Muon2016SF(pt,eta);
    if(_year==2017)
      SF = Muon2017SF(pt,eta);
    if(_year==2018)
      SF = Muon2018SF(pt,eta);
  }
  //Electron
  if(abs(id)==11){
    if(_year==2016)
      SF = 1.0;
    if(_year==2017)
      SF = 1.0;
    if(_year==2018)
      SF = electronSF2018(pt,eta)*electronRecoSF2018(pt,eta);
  }
  
  return SF;
}


//TriggerSF
//Functions are in TriggerEfficiencyScaleFactor.h header file

float VLLAna::SingleLepTrigger_SF(int id, float pt, float eta)
{
  float SF = 1.0;
  if(abs(id)==13){
    if(_year==2016)
      SF = TriggEff2016Data_IsoMu24(pt,eta)/TriggEff2016MC_IsoMu24(pt,eta);
    if(_year==2017)
      SF = TriggEff2017Data_IsoMu27(pt,eta)/TriggEff2017MC_IsoMu27(pt,eta);
    if(_year==2018)
      SF = TriggEff2018Data_IsoMu24(pt,eta)/TriggEff2018MC_IsoMu24(pt,eta);
  }
  
  //if(abs(id)==11){
  // if(_year==2016)
  //   eff = TriggEff2016Data_Ele27WPTightGsf(pt,eta);
  // if(_year==2017)
  //   eff = TriggEff2017Data_Ele32WPTightGsf(pt,eta);
  // if(_year==2018)
  //   eff = TriggEff2018Data_Ele32WPTightGsf(pt,eta);
  //}
  
  return SF;
}
float VLLAna::SingleLepTrigger_eff(int id, float pt, float eta)
{
  float eff = 0.0;
  if(abs(id)==13){
    if(_year==2016)
      eff= TriggEff2016Data_IsoMu24(pt,eta);
    if(_year==2017)
      eff= TriggEff2017Data_IsoMu27(pt,eta);
    if(_year==2018)
      eff= TriggEff2018Data_IsoMu24(pt,eta);
  }
  return eff;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




