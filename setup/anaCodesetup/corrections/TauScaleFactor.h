#include <iostream>
using namespace std;

//--------------------------------------------------------------------------------------------------------------//
//                                      Scale Factors for Taus                                                  //
//                                                                                                              //
//--------------------------------------------------------------------------------------------------------------//

//2016
float VLLAna::tauSF2016(float TauPt, float TauEta)
{  
  float tauSF=1.0;  
  //DeepVsJet VTight WP
  if(TauPt<=20) tauSF=0.;
  else if(TauPt>20 && TauPt<=25) tauSF=0.89125;
  else if(TauPt>25 && TauPt<=30) tauSF=0.89316;
  else if(TauPt>30 && TauPt<=35) tauSF=0.88662;
  else if(TauPt>35 && TauPt<=40) tauSF=0.86494;
  else tauSF=0.88256;
  
  return tauSF;
}

//2017
float VLLAna::tauSF2017(float TauPt, float TauEta)
{  
  float tauSF=1.0;
  
  if(TauPt<=20) tauSF=0.;
  else if(TauPt>20 && TauPt<=25) tauSF=0.85754;
  else if(TauPt>25 && TauPt<=30) tauSF=0.87826;
  else if(TauPt>30 && TauPt<=35) tauSF=0.84281;
  else if(TauPt>35 && TauPt<=40) tauSF=0.82723;
  else tauSF=0.87676;
  
  return tauSF;
}

//2018
float VLLAna::tauSF2018(float TauPt, float TauEta)
{  
  float tauSF=1.0;
  if(TauPt<20) tauSF=0.;
  else if(TauPt>20 && TauPt<=25) tauSF=0.96355;
  else if(TauPt>25 && TauPt<=30) tauSF=0.91565;
  else if(TauPt>30 && TauPt<=35) tauSF=0.92357;
  else if(TauPt>35 && TauPt<=40) tauSF=0.94837;
  else tauSF=0.97749;
  
  return tauSF;
}
