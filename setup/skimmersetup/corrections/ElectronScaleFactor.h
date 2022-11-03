
//.........................................................//
//                                                         //
//        Electron Scale Factor                            //
//                                                         //
//.........................................................//

#include <iostream>
using namespace std;

//Electron SF = MediumID SF * ElectronRecoSF
float VLLAna:: electronSF2018( float Pt, float Eta ){
  // Reference:
  // https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2#Efficiencies_and_scale_factors
  // https://twiki.cern.ch/twiki/pub/CMS/EgammaIDRecipesRun2/2018_ElectronMedium_2D.pdf
  if( Pt<5 || Eta>2.5 ) return 0.0;;
  //
  //....................................SF = (Medium Cut Based ID SF)
  float SF=1.;
  if(Pt>10&& Pt<=20){
    if(Eta>-2.5&& Eta<=-2)SF=1.218;
    else if(Eta>-2&& Eta<=-1.566)SF=1.060;
    else if(Eta>-1.566&& Eta<=-1.444)SF=1.000;
    else if(Eta>-1.444&& Eta<=-0.8)SF=1.033;
    else if(Eta>-0.8&& Eta<=0)SF=0.981;
    else if(Eta>0&& Eta<=0.8)SF=1.000;
    else if(Eta>0.8&& Eta<=1.444)SF=1.020;
    else if(Eta>1.444&& Eta<=1.566)SF=1.000;
    else if(Eta>1.566&& Eta<=2)SF=1.017;
    else if(Eta>2&& Eta<=2.5)SF=1.197;
  }
  else if(Pt>20&& Pt<=35){
    if(Eta>-2.5&& Eta<=-2)SF=1.108;
    else if(Eta>-2&& Eta<=-1.566)SF=1.013;
    else if(Eta>-1.566&& Eta<=-1.444)SF=1.000;
    else if(Eta>-1.444&& Eta<=-0.8)SF=0.961;
    else if(Eta>-0.8&& Eta<=0)SF=0.955;
    else if(Eta>0&& Eta<=0.8)SF=0.960;
    else if(Eta>0.8&& Eta<=1.444)SF=0.957;
    else if(Eta>1.444&& Eta<=1.566)SF=1.000;
    else if(Eta>1.566&& Eta<=2)SF=1.016;
    else if(Eta>2&& Eta<=2.5)SF=1.092;
  }
  else if(Pt>35&& Pt<=50){
    if(Eta>-2.5&& Eta<=-2)SF=1.053;
    else if(Eta>-2&& Eta<=-1.566)SF=1.004;
    else if(Eta>-1.566&& Eta<=-1.444)SF=1.000;
    else if(Eta>-1.444&& Eta<=-0.8)SF=0.965;
    else if(Eta>-0.8&& Eta<=0)SF=0.965;
    else if(Eta>0&& Eta<=0.8)SF=0.969;
    else if(Eta>0.8&& Eta<=1.444)SF=0.969;
    else if(Eta>1.444&& Eta<=1.566)SF=1.000;
    else if(Eta>1.566&& Eta<=2)SF=1.000;
    else if(Eta>2&& Eta<=2.5)SF=1.048;
  }
  else if(Pt>50&& Pt<=100){
    if(Eta>-2.5&& Eta<=-2)SF=1.034;
    else if(Eta>-2&& Eta<=-1.566)SF=1.000;
    else if(Eta>-1.566&& Eta<=-1.444)SF=1.000;
    else if(Eta>-1.444&& Eta<=-0.8)SF=0.966;
    else if(Eta>-0.8&& Eta<=0)SF=0.968;
    else if(Eta>0&& Eta<=0.8)SF=0.967;
    else if(Eta>0.8&& Eta<=1.444)SF=0.971;
    else if(Eta>1.444&& Eta<=1.566)SF=1.000;
    else if(Eta>1.566&& Eta<=2)SF=0.997;
    else if(Eta>2&& Eta<=2.5)SF=1.009;
  }
  else if(Pt>100&& Pt<=200){
    if(Eta>-2.5&& Eta<=-2)SF=1.012;
    else if(Eta>-2&& Eta<=-1.566)SF=1.007;
    else if(Eta>-1.566&& Eta<=-1.444)SF=1.000;
    else if(Eta>-1.444&& Eta<=-0.8)SF=0.984;
    else if(Eta>-0.8&& Eta<=0)SF=0.972;
    else if(Eta>0&& Eta<=0.8)SF=0.987;
    else if(Eta>0.8&& Eta<=1.444)SF=0.987;
    else if(Eta>1.444&& Eta<=1.566)SF=1.000;
    else if(Eta>1.566&& Eta<=2)SF=0.988;
    else if(Eta>2&& Eta<=2.5)SF=0.992;
  }
  else if(Pt>200){
    if(Eta>-2.5&& Eta<=-2)SF=1.006;
    else if(Eta>-2&& Eta<=-1.566)SF=0.984;
    else if(Eta>-1.566&& Eta<=-1.444)SF=1.000;
    else if(Eta>-1.444&& Eta<=-0.8)SF=0.976;
    else if(Eta>-0.8&& Eta<=0)SF=1.010;
    else if(Eta>0&& Eta<=0.8)SF=0.985;
    else if(Eta>0.8&& Eta<=1.444)SF=0.979;
    else if(Eta>1.444&& Eta<=1.566)SF=1.000;
    else if(Eta>1.566&& Eta<=2)SF=0.999;
    else if(Eta>2&& Eta<=2.5)SF=1.024;
  }
  return SF;
}


float VLLAna:: electronRecoSF2018(float Pt, float Eta){
  // Pt>20: https://twiki.cern.ch/twiki/pub/CMS/EgammaIDRecipesRun2/egammaEffi.txt_egammaPlots.pdf
  // Pt<20: https://twiki.cern.ch/twiki/pub/CMS/EgammaIDRecipesRun2/egammaEffi.txt_egammaPlots_low.pdf
  if( Pt<5 || Eta>2.5 ) return 0.0;;
  float SF=1.;
  if(Pt>10&& Pt<=20){
    if(Eta>-2.5&& Eta<=-2)SF=1.012;
    else if(Eta>-2&& Eta<=-1.566)SF=0.972;
    else if(Eta>-1.566&& Eta<=-1.444)SF=1.416;
    else if(Eta>-1.444&& Eta<=-1)SF=1.016;
    else if(Eta>-1&& Eta<=-0.5)SF=0.909;
    else if(Eta>-0.5&& Eta<=0)SF=1.000;
    else if(Eta>0&& Eta<=0.5)SF=1.000;
    else if(Eta>0.5&& Eta<=1)SF=0.909;
    else if(Eta>1&& Eta<=1.444)SF=1.016;
    else if(Eta>1.444&& Eta<=1.566)SF=1.416;
    else if(Eta>1.566&& Eta<=2)SF=0.972;
    else if(Eta>2&& Eta<=2.5)SF=1.012;
  }
  else if(Pt>20&& Pt<=45){
    if(Eta>-2.5&& Eta<=-2)SF=0.989;
    else if(Eta>-2&& Eta<=-1.566)SF=0.991;
    else if(Eta>-1.566&& Eta<=-1.444)SF=0.982;
    else if(Eta>-1.444&& Eta<=-1)SF=0.988;
    else if(Eta>-1&& Eta<=-0.5)SF=0.990;
    else if(Eta>-0.5&& Eta<=0)SF=0.986;
    else if(Eta>0&& Eta<=0.5)SF=0.983;
    else if(Eta>0.5&& Eta<=1)SF=0.987;
    else if(Eta>1&& Eta<=1.444)SF=0.984;
    else if(Eta>1.444&& Eta<=1.566)SF=0.985;
    else if(Eta>1.566&& Eta<=2)SF=0.989;
    else if(Eta>2&& Eta<=2.5)SF=0.992;
  }
  else if(Pt>45&& Pt<=75){
    if(Eta>-2.5&& Eta<=-2)SF=0.985;
    else if(Eta>-2&& Eta<=-1.566)SF=0.991;
    else if(Eta>-1.566&& Eta<=-1.444)SF=0.959;
    else if(Eta>-1.444&& Eta<=-1)SF=0.989;
    else if(Eta>-1&& Eta<=-0.5)SF=0.991;
    else if(Eta>-0.5&& Eta<=0)SF=0.989;
    else if(Eta>0&& Eta<=0.5)SF=0.987;
    else if(Eta>0.5&& Eta<=1)SF=0.989;
    else if(Eta>1&& Eta<=1.444)SF=0.982;
    else if(Eta>1.444&& Eta<=1.566)SF=0.973;
    else if(Eta>1.566&& Eta<=2)SF=0.991;
    else if(Eta>2&& Eta<=2.5)SF=0.986;
  }
  else if(Pt>75&& Pt<=100){
    if(Eta>-2.5&& Eta<=-2)SF=1.001;
    else if(Eta>-2&& Eta<=-1.566)SF=1.006;
    else if(Eta>-1.566&& Eta<=-1.444)SF=1.047;
    else if(Eta>-1.444&& Eta<=-1)SF=1.005;
    else if(Eta>-1&& Eta<=-0.5)SF=1.002;
    else if(Eta>-0.5&& Eta<=0)SF=1.006;
    else if(Eta>0&& Eta<=0.5)SF=1.006;
    else if(Eta>0.5&& Eta<=1)SF=1.002;
    else if(Eta>1&& Eta<=1.444)SF=1.005;
    else if(Eta>1.444&& Eta<=1.566)SF=1.047;
    else if(Eta>1.566&& Eta<=2)SF=1.006;
    else if(Eta>2&& Eta<=2.5)SF=1.001;
  }
  else if(Pt>100){
    if(Eta>-2.5&& Eta<=-2)SF=1.007;
    else if(Eta>-2&& Eta<=-1.566)SF=0.992;
    else if(Eta>-1.566&& Eta<=-1.444)SF=0.984;
    else if(Eta>-1.444&& Eta<=-1)SF=1.001;
    else if(Eta>-1&& Eta<=-0.5)SF=1.001;
    else if(Eta>-0.5&& Eta<=0)SF=0.987;
    else if(Eta>0&& Eta<=0.5)SF=0.987;
    else if(Eta>0.5&& Eta<=1)SF=1.001;
    else if(Eta>1&& Eta<=1.444)SF=1.001;
    else if(Eta>1.444&& Eta<=1.566)SF=0.984;
    else if(Eta>1.566&& Eta<=2)SF=0.992;
    else if(Eta>2&& Eta<=2.5)SF=1.007;
  }
  //  
  return SF;
}

