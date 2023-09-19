//###################################################################################
//                        Trigger Efficiency scale factors
//###################################################################################

//--------------------
// SingleMuon trigger
//--------------------
//__________________________________________

// 2016 preVFP MC
float VLLAna::TrigEff_2016preVFP_IsoMu24_MC(float pt, float eta){
  float eff = 0.0; //default value
  if( pt<10 || eta>2.4 ) return 0.0;
  else if(fabs(eta)<=1.479) eff = 0.5*0.971934*(1.0+TMath::Erf((pt-23.4424)/(2.0*0.178376))); //barrel
  else if(fabs(eta)>1.479)  eff = 0.5*0.966306*(1.0+TMath::Erf((pt-23.9592)/(2.0*0.487943))); //endcap
  return eff;
}
// 2016 preVFP Data
float VLLAna::TrigEff_2016preVFP_IsoMu24_Data(float pt, float eta){
  float eff = 0.0; //default value
  if( pt<10 || eta>2.4 ) return 0.0;
  else if(fabs(eta)<=1.479) eff = 0.5*0.952501*(1.0+TMath::Erf((pt-23.9491)/(2.0*0.405232))); //barrel
  else if(fabs(eta)>1.479){
    if(pt<=100)             eff = 0.5*0.951936*(1.0+TMath::Erf((pt-23.9399)/(2.0*0.533316)));
    else                    eff = 0.774;
  }
  return eff;
}
//__________________________________________

// 2016 postVFP MC
float VLLAna::TrigEff_2016postVFP_IsoMu24_MC(float pt, float eta){
  float eff = 0.0; //default value
  if( pt<10 || eta>2.4 ) return 0.0;
  else if(fabs(eta)<=1.479) eff = 0.5*0.974532*(1.0+TMath::Erf((pt-23.3954)/(2.0*0.151737)));
  else if(fabs(eta)>1.479)  eff = 0.5*0.970343*(1.0+TMath::Erf((pt-23.977)/(2.0*0.445236)));
  return eff;
}
// 2016 postVFP Data
float VLLAna::TrigEff_2016postVFP_IsoMu24_Data(float pt, float eta){
  float eff = 0.0; //default value
  if( pt<10 || eta>2.4 ) return 0.0;
  else if(fabs(eta)<=1.479) eff = 0.5*0.963135*(1.0+TMath::Erf((pt-23.9546)/(2.0*0.363316)));
  else if(fabs(eta)>1.479)  eff = 0.5*0.96043*(1.0+TMath::Erf((pt-23.9677)/(2.0*0.463984)));
  return eff;
}
//__________________________________________

// 2017 MC
float VLLAna::TrigEff_2017_IsoMu27_MC(float pt, float eta){
  float eff = 0.0; //default value
  if( pt<10 || eta>2.4 ) return 0.0;
  else if(fabs(eta)<=1.479) eff = 0.5*0.960212*(1.0+TMath::Erf((pt-26.9652)/(2.0*0.597564))); 
  else if(fabs(eta)>1.479)  eff = 0.5*0.94303*(1.0+TMath::Erf((pt-26.9123)/(2.0*0.747516)));
  return eff;
}
// 2017 Data
float VLLAna::TrigEff_2017_IsoMu27_Data(float pt, float eta){
  float eff = 0.0; //default value
  if( pt<10 || eta>2.4 ) return 0.0;
  else if(fabs(eta)<=1.479){
    if(pt<=100)            eff = 0.5*0.929318*(1.0+TMath::Erf((pt-26.9424)/(2.0*0.612448)));
    else                   eff = 0.958305;
  }
  else if(fabs(eta)>1.479) eff = 0.5*0.94163*(1.0+TMath::Erf((pt-26.9092)/(2.0*0.844543)));
  return eff;
}
//__________________________________________

//2018 MC
float VLLAna::TrigEff_2018_IsoMu24_MC(float pt, float eta){
  float eff = 0.0; //default value
  if( pt<10 || eta>2.4 ) return 0.0;
  else if(fabs(eta)<=1.479) eff = 0.5*0.971878*(1.0+TMath::Erf((pt-23.9589)/(2.0*0.356627)));
  else if(fabs(eta)>1.479)  eff = 0.5*0.958908*(1.0+TMath::Erf((pt-23.9493)/(2.0*0.408312)));
  return eff;
}
//2018 Data
float VLLAna::TrigEff_2018_IsoMu24_Data(float pt, float eta){
  float eff = 0.0; //default value
  if( pt<10 || eta>2.4 ) return 0.0;
  else if(fabs(eta)<=1.479) eff = 0.5*0.950463*(1.0+TMath::Erf((pt-23.9593)/(2.0*0.375996)));
  else if(fabs(eta)>1.479)  eff = 0.5*0.953162*(1.0+TMath::Erf((pt-23.9459)/(2.0*0.457351)));
  return eff;
}

//------------------------
// SingleElectron trigger
//------------------------
//__________________________________________

// 2016 preVFP MC
float VLLAna::TrigEff_2016preVFP_Ele27WPTightGsf_MC(float pt, float eta){
  float eff = 0.0; //default value
  if( pt<10 || eta>2.4 ) return 0.0;
  else if(fabs(eta)<=1.479) eff = 0.5*0.984513*(1.0+TMath::Erf((pt-27.5914)/(2.0*1.0585)));
  else if(fabs(eta)>1.479)  eff = 0.5*0.989446*(1.0+TMath::Erf((pt-26.0586)/(2.0*1.85888)));
  return eff;
}
// 2016 preVFP Data
float VLLAna::TrigEff_2016preVFP_Ele27WPTightGsf_Data(float pt, float eta){
  float eff = 0.0; //default value
  if( pt<10 || eta>2.4 ) return 0.0;
  else if(fabs(eta)<=1.479) eff = 0.5*0.980431*(1.0+TMath::Erf((pt-26.6311)/(2.0*0.977291)));
  else if(fabs(eta)>1.479)  eff = 0.5*0.984774*(1.0+TMath::Erf((pt-27.5187)/(2.0*1.33533)));
  return eff;
}

//__________________________________________

// 2016 postVFP MC
float VLLAna::TrigEff_2016postVFP_Ele27WPTightGsf_MC(float pt, float eta){
  float eff = 0.0; //default value
  if( pt<10 || eta>2.4 ) return 0.0;
  else if(fabs(eta)<=1.479) eff = 0.5*0.983934*(1.0+TMath::Erf((pt-27.5947)/(2.0*1.06344)));
  else if(fabs(eta)>1.479)  eff = 0.5*0.988555*(1.0+TMath::Erf((pt-26.0556)/(2.0*1.85987)));
  return eff;
}
// 2016 postVFP Data
float VLLAna::TrigEff_2016postVFP_Ele27WPTightGsf_Data(float pt, float eta){
  float eff = 0.0; //default value
  if( pt<10 || eta>2.4 ) return 0.0;
  else if(fabs(eta)<=1.479) eff = 0.5*0.975241*(1.0+TMath::Erf((pt-26.6834)/(2.0*1.08336)));
  else if(fabs(eta)>1.479)  eff = 0.5*0.981091*(1.0+TMath::Erf((pt-27.7339)/(2.0*1.44615)));
  return eff;
}

//__________________________________________

// 2017 MC
float VLLAna::TrigEff_2017_Ele32WPTightGsf_MC(float pt, float eta){
  float eff = 0.0; //default value
  if( pt<10 || eta>2.4 ) return 0.0;
  else if(fabs(eta)<=1.479) eff = 0.5*0.96683*(1.0+TMath::Erf((pt-31.6521)/(2.0*1.16952)));
  else if(fabs(eta)>1.479)  eff = 0.5*0.977357*(1.0+TMath::Erf((pt-32.7302)/(2.0*1.98741)));
  return eff;
}
// 2017 Data
float VLLAna::TrigEff_2017_Ele32WPTightGsf_Data(float pt, float eta){
  float eff = 0.0; //default value
  if( pt<10 || eta>2.4 ) return 0.0;
  else if(fabs(eta)<=1.479) eff = 0.5*0.955945*(1.0+TMath::Erf((pt-33.0345)/(2.0*0.885676)));
  else if(fabs(eta)>1.479)  eff = 0.5*0.962208*(1.0+TMath::Erf((pt-33.9927)/(2.0*1.55814)));
  return eff;
}

//__________________________________________

// 2018 MC
float VLLAna::TrigEff_2018_Ele32WPTightGsf_MC(float pt, float eta){
  float eff = 0.0; //default value
  if( pt<10 || eta>2.4 ) return 0.0;
  else if(fabs(eta)<=1.479) eff = 0.5*0.971841*(1.0+TMath::Erf((pt-33.0664)/(2.0*0.830281)));
  else if(fabs(eta)>1.479)  eff = 0.5*0.981582*(1.0+TMath::Erf((pt-33.9066)/(2.0*1.55882)));
  return eff;
}
// 2018 Data
float VLLAna::TrigEff_2018_Ele32WPTightGsf_Data(float pt, float eta){
  float eff = 0.0; //default value
  if( pt<10 || eta>2.4 ) return 0.0;
  else if(fabs(eta)<=1.479) eff = 0.5*0.962897*(1.0+TMath::Erf((pt-33.1188)/(2.0*0.844886)));
  else if(fabs(eta)>1.479)  eff = 0.5*0.975043*(1.0+TMath::Erf((pt-32.9805)/(2.0*1.18094)));
  return eff;
}
