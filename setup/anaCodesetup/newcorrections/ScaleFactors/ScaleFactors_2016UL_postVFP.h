//######################################################################
//                      2016 postVFP ScaleFactors
// Due to some technical error, the 2016 dataset had to be split into
// 'preVPF' and 'postVFP'. That's why these calculations are twice as
// long. Luminosity weights are used to combine the two sets of numbers
//######################################################################

//Electron Reco
double VLLAna::Electron_2016UL_Reco_postVFP(float pt, float eta){
  double scale_factor = 1.0; //default value
  if(10<pt && pt<=20){
    if(-5.0<eta && eta<=-2.1)          scale_factor = 1.0152403116226196;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.990312159061432;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.1295620203018188;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 0.9585605263710022;
    else if(-1.0<eta && eta<=0.0)      scale_factor = 1.0240384340286257;
    else if(0.0<eta && eta<=1.0)       scale_factor = 1.0240384340286257;
    else if(1.0<eta && eta<=1.444)     scale_factor = 0.9585605263710022;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.1295620203018188;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.990312159061432;
    else if(2.0<eta && eta<=5.0)       scale_factor = 1.0152403116226196;
  }
  else if(20<pt && pt<=45){
    if(-5.0<eta && eta<=-2.1)          scale_factor = 1.0353591442108154;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9926931262016296;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 0.989461362361908;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 0.9876416325569152;
    else if(-1.0<eta && eta<=-0.5)     scale_factor = 0.9856704473495485;
    else if(-0.5<eta && eta<=0.0)      scale_factor = 0.983589768409729;
    else if(0.0<eta && eta<=0.5)       scale_factor = 0.983589768409729;
    else if(0.5<eta && eta<=1.0)       scale_factor = 0.9856997132301332;
    else if(1.0<eta && eta<=1.444)     scale_factor = 0.9845995903015136;
    else if(1.444<eta && eta<=1.566)   scale_factor = 0.9763872623443604;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.98860102891922;
    else if(2.0<eta && eta<=5.0)       scale_factor = 0.991416335105896;
  }
  else if(45<pt && pt<=75){
    if(-5.0<eta && eta<=-2.1)          scale_factor = 1.020474195480347;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9896265268325806;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 0.9596510529518129;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 0.9867346882820128;
    else if(-1.0<eta && eta<=-0.5)     scale_factor = 0.98578679561615;
    else if(-0.5<eta && eta<=0.0)      scale_factor = 0.9857434034347534;
    else if(0.0<eta && eta<=0.5)       scale_factor = 0.984725058078766;
    else if(0.5<eta && eta<=1.0)       scale_factor = 0.9868020415306092;
    else if(1.0<eta && eta<=1.444)     scale_factor = 0.9857288599014282;
    else if(1.444<eta && eta<=1.566)   scale_factor = 0.9589632749557496;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9886831045150756;
    else if(2.0<eta && eta<=5.0)       scale_factor = 0.9915878176689148;
  }
  else if(75<pt && pt<=100){
    if(-5.0<eta && eta<=-2.1)          scale_factor = 1.0;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9732785224914552;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 0.991256833076477;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 0.9817444086074828;
    else if(-1.0<eta && eta<=-0.5)     scale_factor = 0.9766970872879028;
    else if(-0.5<eta && eta<=0.0)      scale_factor = 0.976673424243927;
    else if(0.0<eta && eta<=0.5)       scale_factor = 0.976673424243927;
    else if(0.5<eta && eta<=1.0)       scale_factor = 0.9766970872879028 ;
    else if(1.0<eta && eta<=1.444)     scale_factor = 0.9817444086074828;
    else if(1.444<eta && eta<=1.566)   scale_factor = 0.991256833076477;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9732785224914552;
    else if(2.0<eta && eta<=5.0)       scale_factor = 1.0;
  }
  else if(100<pt && pt<=1000){
    if(-5.0<eta && eta<=-2.1)          scale_factor = 1.0105262994766235;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9969356656074524;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 0.9988986849784852;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 0.9919354915618896;
    else if(-1.0<eta && eta<=-0.5)     scale_factor = 0.9909273982048036;
    else if(-0.5<eta && eta<=0.0)      scale_factor = 0.986868679523468;
    else if(0.0<eta && eta<=0.5)       scale_factor = 0.986868679523468;
    else if(0.5<eta && eta<=1.0)       scale_factor =0.9909273982048036 ;
    else if(1.0<eta && eta<=1.444)     scale_factor = 0.9919354915618896;
    else if(1.444<eta && eta<=1.566)   scale_factor =0.9988986849784852 ;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9969356656074524;
    else if(2.0<eta && eta<=5.0)       scale_factor = 1.0105262994766235;
  }
  return scale_factor;
}
//Electron IdIso
double VLLAna::Electron_2016UL_IDIso_postVFP(float pt, float eta){
  double scale_factor = 1.0;//default value
  if(10<pt && pt<=20){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 1.0397112369537354;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 1.0204429626464844;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 1.003610134124756;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.9584055542945862;
    else if(0.0<eta && eta<=0.8)       scale_factor = 0.9655172228813172;
    else if(0.8<eta && eta<=1.444)     scale_factor = 1.0;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 1.0242633819580078;
    else if(2.0<eta && eta<=2.4)       scale_factor = 1.022687554359436;
  }
  else if(20<pt && pt<=35){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 1.015895962715149;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9973154067993164;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 0.9831932783126832;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.9647696614265442;
    else if(0.0<eta && eta<=0.8)       scale_factor = 0.98505437374115;
    else if(0.8<eta && eta<=1.444)     scale_factor = 0.9858956336975098;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9878048896789552;
    else if(2.0<eta && eta<=2.4)       scale_factor = 1.0114285945892334;
  }
  else if(35<pt && pt<=50){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 1.008838415145874;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 1.0011975765228271;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 0.982206404209137;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.9731621742248536;
    else if(0.0<eta && eta<=0.8)       scale_factor = 0.9859319925308228;
    else if(0.8<eta && eta<=1.444)     scale_factor = 0.9880383014678956;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9952152967453004;
    else if(2.0<eta && eta<=2.4)       scale_factor = 0.9962406158447266;
  }
  else if(50<pt && pt<=100){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 1.0036144256591797;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 1.0034762620925903;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 0.9828571677207948;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.9719416499137878;
    else if(0.0<eta && eta<=0.8)       scale_factor = 0.9830890893936156;
    else if(0.8<eta && eta<=1.444)     scale_factor = 0.9862385392189026;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.99190753698349;
    else if(2.0<eta && eta<=2.4)       scale_factor = 0.9880810379981996;
  }
  else if(100<pt && pt<=1000){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 1.0270880460739136;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 1.024608492851257;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 1.0011049509048462;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 1.0032930374145508;
    else if(0.0<eta && eta<=0.8)       scale_factor = 1.0099338293075562;
    else if(0.8<eta && eta<=1.444)     scale_factor = 1.0100446939468384;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9945295453071594;
    else if(2.0<eta && eta<=2.4)       scale_factor = 1.0067644119262695;
  }
  return scale_factor;
}

//________________________________________________________________________________________

//Muon Reco
double VLLAna::Muon_2016UL_Reco_postVFP(float pt, float eta){
  double scale_factor = 1.0;//default value
  if(fabs(eta)<=0.9){
    if( 15<pt && pt<=20)         scale_factor = 1.056291820381002;
    else if( 20<pt && pt<=25)    scale_factor = 0.9627870246357144 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.987978023401688 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9992000996873548 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9995367348504244 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9980919725414232 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.9853222024574856;
    else if( 120<pt && pt<=3000) scale_factor = 0.9853222024574856 ;   
  }  
  else if(0.9<fabs(eta) && fabs(eta)<=1.2){
    if( 15<pt && pt<=20)         scale_factor = 0.8892388955220546 ;
    else if( 20<pt && pt<=25)    scale_factor = 1.022054581840318 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.9955481975125244 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9991822468718874 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9988601953525188 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9997061366209312 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.9927611463643844 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.9927611463643844 ;
  }  
  else if(1.2<fabs(eta) && fabs(eta)<=2.1){
    if( 15<pt && pt<=20)         scale_factor = 0.9363650483641645 ;
    else if( 20<pt && pt<=25)    scale_factor = 0.9739458317338784 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.9987101660679462 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.997568576306376 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9986652097641068 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9994639649262176 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.9938417669117328 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.9938417669117328 ;
  }  
  else if(2.1<fabs(eta) && fabs(eta)<=2.4){
    if( 15<pt && pt<=20)         scale_factor = 0.945474482343702 ;
    else if( 20<pt && pt<=25)    scale_factor = 1.0090118243659676 ;
    else if( 25<pt && pt<=30)    scale_factor = 1.0047838836783498 ;
    else if( 30<pt && pt<=40)    scale_factor = 1.002353454383219 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9921194306198418 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9890612820855476;
    else if( 60<pt && pt<=120)   scale_factor = 1.008307516945261 ;
    else if( 120<pt && pt<=3000) scale_factor = 1.008307516945261 ;
  }
  return scale_factor;
}

//Muon ID
double VLLAna::Muon_2016UL_ID_postVFP(float pt, float eta){
  double scale_factor = 1.0;//default value
  if(fabs(eta)<=0.9){
    if( 15<pt && pt<=20)         scale_factor = 1.0000041738158354 ;
    else if( 20<pt && pt<=25)    scale_factor = 0.9990199540731494 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.999548660646305 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9992690049961372 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9992537131247722 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9987772239305884 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.9988329307945766 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.9988329307945766 ;    
  }  
  else if(0.9<fabs(eta) && fabs(eta)<=1.2){
    if( 15<pt && pt<=20)         scale_factor = 0.9935125772523964 ;
    else if( 20<pt && pt<=25)    scale_factor = 0.9945582990388512 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.9963131040992652 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.995557465152997 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.995849044136711 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9960145401876056;
    else if( 60<pt && pt<=120)   scale_factor = 0.9955682146213594 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.9955682146213594 ;
  }  
  else if(1.2<fabs(eta) && fabs(eta)<=2.1){
    if( 15<pt && pt<=20)         scale_factor = 0.9952467407300474 ;
    else if( 20<pt && pt<=25)    scale_factor = 0.9956863884750184 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.9963280270258894 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9963540789044504;
    else if( 40<pt && pt<=50)    scale_factor = 0.997101761840005  ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9967922838866176 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.9967515371285344;
    else if( 120<pt && pt<=3000) scale_factor = 0.9967515371285344 ;
  }  
  else if(2.1<fabs(eta) && fabs(eta)<=2.4){
    if( 15<pt && pt<=20)         scale_factor = 0.9785830351419386 ;
    else if( 20<pt && pt<=25)    scale_factor = 0.9768825062950852 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.9771488876540624 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.978591269895218 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9775049786244718;
    else if( 50<pt && pt<=60)    scale_factor = 0.978501128153901 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.9759579114670028 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.9759579114670028 ;
  }
  return scale_factor;
}

//Muon Iso
double VLLAna::Muon_2016UL_Iso_postVFP(float pt, float eta){
  double scale_factor = 1.0;//default value
  if(fabs(eta)<=0.9){
    if( 15<pt && pt<=20)         scale_factor =  0.9896638155504588;
    else if( 20<pt && pt<=25)    scale_factor =  0.9948288271080996;
    else if( 25<pt && pt<=30)    scale_factor = 0.991510525326622 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9956044247397018 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.996982924553536 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9971974780479392 ;
    else if( 60<pt && pt<=120)   scale_factor =  0.9990199324137672;
    else if( 120<pt && pt<=3000) scale_factor =  0.9990199324137672; 
  }  
  else if(0.9<fabs(eta) && fabs(eta)<=1.2){
    if( 15<pt && pt<=20)         scale_factor =  1.0019934719330423;
    else if( 20<pt && pt<=25)    scale_factor =  1.0003741848922898;
    else if( 25<pt && pt<=30)    scale_factor =  1.003365985645747;
    else if( 30<pt && pt<=40)    scale_factor = 1.0005506260825516 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9979449902609792 ;
    else if( 50<pt && pt<=60)    scale_factor =  0.9996145084763732;
    else if( 60<pt && pt<=120)   scale_factor = 1.0000428280021068 ;
    else if( 120<pt && pt<=3000) scale_factor = 1.0000428280021068 ;
  }
  else if(1.2<fabs(eta) && fabs(eta)<=2.1){
    if( 15<pt && pt<=20)         scale_factor = 1.0033017968451217 ;
    else if( 20<pt && pt<=25)    scale_factor = 1.0070463673112666 ;
    else if( 25<pt && pt<=30)    scale_factor = 1.0051735075912909 ;
    else if( 30<pt && pt<=40)    scale_factor = 1.0015919713475052 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9998315341668478 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9988739251057712 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.9998786688203968 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.9998786688203968 ;
  }
  else if(2.1<fabs(eta) && fabs(eta)<=2.4){
    if( 15<pt && pt<=20)         scale_factor = 1.0137764681943071 ;
    else if( 20<pt && pt<=25)    scale_factor = 1.010785849114932 ;
    else if( 25<pt && pt<=30)    scale_factor = 1.0042843905385197 ;
    else if( 30<pt && pt<=40)    scale_factor = 1.003150058119613 ;
    else if( 40<pt && pt<=50)    scale_factor = 1.001092172040312 ;
    else if( 50<pt && pt<=60)    scale_factor = 1.0010712993352038 ;
    else if( 60<pt && pt<=120)   scale_factor = 1.000794927481125 ;
    else if( 120<pt && pt<=3000) scale_factor = 1.000794927481125 ;
  }
  return scale_factor;
}

//________________________________________________________________________________________

//Taus AntiJet
double VLLAna::Tau_2016UL_AntiJet_postVFP(float pt){
  double scale_factor = 1.0;//default value
  if( 20<pt && pt<=25)          scale_factor = 0.97192130;
  else if( 25<pt && pt<=30)     scale_factor = 0.95513300;
  else if( 30<pt && pt<=35)     scale_factor =0.95673700 ;
  else if( 35<pt && pt<=40)     scale_factor = 0.97832910;
  else if( 40<pt && pt<=500)    scale_factor = 0.80529240;
  else if( 500<pt && pt<=1000)  scale_factor = 0.80529240;
  else if( 1000<pt && pt<=2000) scale_factor = 0.80529240;
  return scale_factor;
}
//Taus AntiEle
double VLLAna::Tau_2016UL_AntiEle_postVFP(float eta){
  double scale_factor = 1.0;//default value
  if( 0.0<fabs(eta) && fabs(eta)<=1.46)        scale_factor = 1.13000;
  else if( 1.46<fabs(eta) && fabs(eta)<=1.558) scale_factor = 1.00000;
  else if( 1.558<fabs(eta) && fabs(eta)<=2.3)  scale_factor = 0.83000;
  return scale_factor;
}

//Taus AntiMu
double VLLAna::Tau_2016UL_AntiMu_postVFP(float eta){
  double scale_factor = 1.0;//default value
  if( 0.0<fabs(eta) && fabs(eta)<=0.4)      scale_factor = 1.02901;
  else if( 0.4<fabs(eta) && fabs(eta)<=0.8) scale_factor = 1.25450;
  else if( 0.8<fabs(eta) && fabs(eta)<=1.2) scale_factor = 0.89939;
  else if( 1.2<fabs(eta) && fabs(eta)<=1.7) scale_factor = 1.24125;
  else if( 1.7<fabs(eta) && fabs(eta)<=2.3) scale_factor = 4.33843;
  return scale_factor;
}








