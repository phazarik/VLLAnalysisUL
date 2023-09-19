//####################################################################################################
// Scale factors are often calculated as a funtion of pT and Eta
// For light-leptons, there are 3 types: Reco SF and ID SF and Iso SF (both with different pT-eta bins)
// For taus : antiEle, antiMu and antiJet
// For electrons, ID and Iso are together.
// Final SF = product of the different types of ScaleFactors.
// Sources : ScaleFactors_2016UL.h 
//#####################################################################################################

//Main:
double VLLAna::LeptonID_SF(int id, float pt, float eta){
  double SF = 1.0;//default value
  if(fabs(id)==13){//MUON
    if(_year==2016)      SF = Muon2016SF(pt,eta);
    else if(_year==2017) SF = Muon2017SF(pt,eta);
    else if(_year==2018) SF = Muon2018SF(pt,eta);
  }
  else if(fabs(id)==11){//Electron
    if(_year==2016)      SF = Electron2016SF(pt,eta);
    else if(_year==2017) SF = Electron2017SF(pt,eta);
    else if(_year==2018) SF = Electron2018SF(pt,eta);
  }
  else if(fabs(id)==15){//TAU
    if(_year==2016)      SF = Tau2016SF(pt,eta);
    else if(_year==2017) SF = Tau2017SF(pt,eta);
    else if(_year==2018) SF = Tau2018SF(pt,eta);
  }
  return SF;
}


float VLLAna::SingleLepTrigger_eff(int id, float pt, float eta){
  float eff = 1.0; 
  if(abs(id)==13){ //MuonTrigger
    if(_year==2016)      eff = TrigEff_2016_IsoMu24_Data(pt,eta);
    else if(_year==2017) eff = TrigEff_2017_IsoMu27_Data(pt,eta);
    else if(_year==2018) eff = TrigEff_2018_IsoMu24_Data(pt,eta);
  }
  else if(abs(id)==11){ //ElectronTrigger
    if(_year==2016)      eff = TrigEff_2016_Ele27WPTightGsf_Data(pt,eta);
    else if(_year==2017) eff = TrigEff_2017_Ele32WPTightGsf_Data(pt,eta);
    else if(_year==2018) eff = TrigEff_2018_Ele32WPTightGsf_Data(pt,eta);
  }
  return eff;
}


//__________________________________________________________________________________

//Combining different types of scale factors together:
//__________________________________________________________________________________

//#####
//2016:
//#####

float VLLAna::TrigEff_2016_IsoMu24_MC(float pt, float eta){
  float lumi_preVFP  = 5747.0+2573.0+4242.0+4025.0+3105.0;
  float lumi_postVFP = 7576.0+8651.0;
  float trigeff_preVFP = TrigEff_2016preVFP_IsoMu24_MC(pt,eta);
  float trigeff_postVFP = TrigEff_2016postVFP_IsoMu24_MC(pt,eta);
  float trigeff = (trigeff_preVFP*lumi_preVFP + (trigeff_postVFP*lumi_postVFP))/(lumi_preVFP+lumi_postVFP);
  return trigeff;
}
float VLLAna::TrigEff_2016_IsoMu24_Data(float pt, float eta){
  float lumi_preVFP  = 5747.0+2573.0+4242.0+4025.0+3105.0;
  float lumi_postVFP = 7576.0+8651.0;
  float trigeff_preVFP = TrigEff_2016preVFP_IsoMu24_Data(pt,eta);
  float trigeff_postVFP = TrigEff_2016postVFP_IsoMu24_Data(pt,eta);
  float trigeff = (trigeff_preVFP*lumi_preVFP + (trigeff_postVFP*lumi_postVFP))/(lumi_preVFP+lumi_postVFP);
  return trigeff;
}
float VLLAna::TrigEff_2016_Ele27WPTightGsf_MC(float pt, float eta){
  float lumi_preVFP  = 5747.0+2573.0+4242.0+4025.0+3105.0;
  float lumi_postVFP = 7576.0+8651.0;
  float trigeff_preVFP = TrigEff_2016preVFP_Ele27WPTightGsf_MC(pt,eta);
  float trigeff_postVFP = TrigEff_2016postVFP_Ele27WPTightGsf_MC(pt,eta);
  float trigeff = (trigeff_preVFP*lumi_preVFP + (trigeff_postVFP*lumi_postVFP))/(lumi_preVFP+lumi_postVFP);
  return trigeff;
}
float VLLAna::TrigEff_2016_Ele27WPTightGsf_Data(float pt, float eta){
  float lumi_preVFP  = 5747.0+2573.0+4242.0+4025.0+3105.0;
  float lumi_postVFP = 7576.0+8651.0;
  float trigeff_preVFP = TrigEff_2016preVFP_Ele27WPTightGsf_Data(pt,eta);
  float trigeff_postVFP = TrigEff_2016postVFP_Ele27WPTightGsf_Data(pt,eta);
  float trigeff = (trigeff_preVFP*lumi_preVFP + (trigeff_postVFP*lumi_postVFP))/(lumi_preVFP+lumi_postVFP);
  return trigeff;
}


double VLLAna::Electron2016SF(float pt, float eta){
  //For 2016, the scale factors are calculated differently for preVFP and postVFP.
  //Later they are combined with luminosity as the weight.
  double lumi_preVFP  = 5747.0+2573.0+4242.0+4025.0+3105.0;
  double lumi_postVFP = 7576.0+8651.0;
  double sf_preVFP    = Electron_2016UL_Reco_preVFP(pt, eta) * Electron_2016UL_IDIso_preVFP(pt, eta);
  double sf_postVFP   = Electron_2016UL_Reco_postVFP(pt, eta) * Electron_2016UL_IDIso_postVFP(pt, eta);
  double sf_combined = (sf_preVFP*lumi_preVFP + (sf_postVFP*lumi_postVFP))/(lumi_preVFP+lumi_postVFP); //using luminosity as weight.
  return sf_combined;
}

double VLLAna::Muon2016SF(float pt, float eta){
  //For 2016, the scale factors are calculated differently for preVFP and postVFP.
  //Later they are combined with luminosity as the weight.
  double lumi_preVFP  = 5747.0+2573.0+4242.0+4025.0+3105.0;
  double lumi_postVFP = 7576.0+8651.0;
  double sf_preVFP    = Muon_2016UL_Reco_preVFP(pt, eta) * Muon_2016UL_ID_preVFP(pt, eta) * Muon_2016UL_Iso_preVFP(pt, eta);
  double sf_postVFP   = Muon_2016UL_Reco_postVFP(pt, eta) * Muon_2016UL_ID_postVFP(pt, eta) * Muon_2016UL_Iso_postVFP(pt, eta);
  double sf_combined = (sf_preVFP*lumi_preVFP + (sf_postVFP*lumi_postVFP))/(lumi_preVFP+lumi_postVFP); //using luminosity as weight.
  return sf_combined;
}

double VLLAna::Tau2016SF(float pt, float eta){
  //For 2016, the scale factors are calculated differently for preVFP and postVFP.
  //Later they are combined with luminosity as the weight.
  double lumi_preVFP  = 5747.0+2573.0+4242.0+4025.0+3105.0;
  double lumi_postVFP = 7576.0+8651.0;
  double sf_preVFP    = Tau_2016UL_AntiJet_preVFP(pt) * Tau_2016UL_AntiEle_preVFP(eta) * Tau_2016UL_AntiMu_preVFP(eta);
  double sf_postVFP   = Tau_2016UL_AntiJet_postVFP(pt) * Tau_2016UL_AntiEle_postVFP(eta) * Tau_2016UL_AntiMu_postVFP(eta);
  double sf_combined = (sf_preVFP*lumi_preVFP + (sf_postVFP*lumi_postVFP))/(lumi_preVFP+lumi_postVFP); //using luminosity as weight.
  return sf_combined;
}

//#####
//2017:
//#####

double VLLAna::Electron2017SF(float pt, float eta){
  double sf_combined = Electron_2017UL_Reco(pt, eta) * Electron_2017UL_IDIso(pt, eta);
  return sf_combined;
}
double VLLAna::Muon2017SF(float pt, float eta){
  double sf_combined = Muon_2017UL_Reco(pt, eta) * Muon_2017UL_ID(pt, eta) * Muon_2017UL_Iso(pt, eta);
  return sf_combined;
}
double VLLAna::Tau2017SF(float pt, float eta){
  double sf_combined = Tau_2017UL_AntiJet(pt) * Tau_2017UL_AntiEle(eta) * Tau_2017UL_AntiMu(eta);
  return sf_combined;
}

//#####
//2018:
//#####
double VLLAna::Electron2018SF(float pt, float eta){
  double sf_combined = Electron_2018UL_Reco(pt, eta) * Electron_2018UL_IDIso(pt, eta);
  return sf_combined;
}
double VLLAna::Muon2018SF(float pt, float eta){
  double sf_combined = Muon_2018UL_Reco(pt, eta) * Muon_2018UL_ID(pt, eta) * Muon_2018UL_Iso(pt, eta);
  return sf_combined;
}
double VLLAna::Tau2018SF(float pt, float eta){
  double sf_combined = Tau_2018UL_AntiJet(pt) * Tau_2018UL_AntiEle(eta) * Tau_2018UL_AntiMu(eta);
  return sf_combined;
}

