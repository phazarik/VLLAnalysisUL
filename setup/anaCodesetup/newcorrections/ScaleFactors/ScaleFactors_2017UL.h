//######################################################################
//                         2017 ScaleFactors
//######################################################################

//--------------------------
//        Electrons
//--------------------------

//Electron Reco
double VLLAna::Electron_2017UL_Reco(float pt, float eta){
  double scale_factor = 1.0; //default value
  if(10<pt && pt<=20){
    if(-5.0<eta && eta<=-2.1)          scale_factor = 1.0136841535568235;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 1.0126183032989502;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.092337965965271;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 1.0033222436904907;
    else if(-1.0<eta && eta<=0.0)      scale_factor = 1.047619104385376;
    else if(0.0<eta && eta<=1.0)       scale_factor = 1.047619104385376;
    else if(1.0<eta && eta<=1.444)     scale_factor = 1.0033222436904907;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.092337965965271;
    else if(1.566<eta && eta<=2.0)     scale_factor = 1.0126183032989502;
    else if(2.0<eta && eta<=5.0)       scale_factor = 1.0136841535568235;
  }
  else if(20<pt && pt<=45){
    if(-5.0<eta && eta<=-2.1)          scale_factor = 0.9814624190330504;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.986652970314026;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 0.9261430501937866;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 0.9803516268730164;
    else if(-1.0<eta && eta<=-0.5)     scale_factor = 0.9866666793823242;
    else if(-0.5<eta && eta<=0.0)      scale_factor = 0.9876543283462524;
    else if(0.0<eta && eta<=0.5)       scale_factor = 0.9886481165885924;
    else if(0.5<eta && eta<=1.0)       scale_factor = 0.9917355179786682;
    else if(1.0<eta && eta<=1.444)     scale_factor = 0.98221755027771;
    else if(1.444<eta && eta<=1.566)   scale_factor = 0.978723406791687;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9876543283462524;
    else if(2.0<eta && eta<=5.0)       scale_factor = 0.986652970314026;
  }   
  else if(45<pt && pt<=75){
    if(-5.0<eta && eta<=-2.1)          scale_factor = 0.9836233258247375;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9867346882820128;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 0.9574015140533448;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 0.9825819730758668;
    else if(-1.0<eta && eta<=-0.5)     scale_factor = 0.9887983798980712;
    else if(-0.5<eta && eta<=0.0)      scale_factor = 0.988752543926239;
    else if(0.0<eta && eta<=0.5)       scale_factor = 0.9897540807724;
    else if(0.5<eta && eta<=1.0)       scale_factor = 0.9938398599624634;
    else if(1.0<eta && eta<=1.444)     scale_factor = 0.98343688249588;
    else if(1.444<eta && eta<=1.566)   scale_factor = 0.9817400574684144;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9897750616073608;
    else if(2.0<eta && eta<=5.0)       scale_factor = 0.9867346882820128;
  }
  else if(75<pt && pt<=100){
    if(-5.0<eta && eta<=-2.1)          scale_factor = 0.9764344096183776;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 1.004094123840332;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0240436792373655;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 0.9887640476226808;
    else if(-1.0<eta && eta<=-0.5)     scale_factor = 0.998976469039917;
    else if(-0.5<eta && eta<=0.0)      scale_factor = 0.984725058078766;
    else if(0.0<eta && eta<=0.5)       scale_factor = 0.984725058078766;
    else if(0.5<eta && eta<=1.0)       scale_factor = 0.998976469039917;
    else if(1.0<eta && eta<=1.444)     scale_factor = 0.9887640476226808;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0240436792373655;
    else if(1.566<eta && eta<=2.0)     scale_factor = 1.004094123840332;
    else if(2.0<eta && eta<=5.0)       scale_factor = 0.9764344096183776;
  }
  else if(100<pt && pt<=1000){
    if(-5.0<eta && eta<=-2.1)          scale_factor = 0.978830635547638;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9878296256065368;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.04966139793396;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 0.988752543926239;
    else if(-1.0<eta && eta<=-0.5)     scale_factor = 0.9949341416358948;
    else if(-0.5<eta && eta<=0.0)      scale_factor = 1.0010162591934204;
    else if(0.0<eta && eta<=0.5)       scale_factor = 1.0010162591934204;
    else if(0.5<eta && eta<=1.0)       scale_factor = 0.9949341416358948;
    else if(1.0<eta && eta<=1.444)     scale_factor = 0.988752543926239;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.04966139793396;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9878296256065368;
    else if(2.0<eta && eta<=5.0)       scale_factor = 0.978830635547638;
  }
  return scale_factor;
}
//Electron IdIso
double VLLAna::Electron_2017UL_IDIso(float pt, float eta){
  double scale_factor = 1.0;//default value
  if(10<pt && pt<=20){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 1.0641509294509888;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 1.0369181632995603;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 1.0371747016906738;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.9908088445663452;
    else if(0.0<eta && eta<=0.8)       scale_factor = 1.012635350227356;
    else if(0.8<eta && eta<=1.444)     scale_factor = 1.0055969953536987;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 1.0367279052734375;
    else if(2.0<eta && eta<=2.4)       scale_factor = 1.117424249649048;
  }
  else if(20<pt && pt<=35){
    if(-2.4<eta && eta<=-2.1)     scale_factor = 1.0115773677825928;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9868593811988832;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 0.9860917925834656;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.9647218585014344;
    else if(0.0<eta && eta<=0.8)       scale_factor = 0.973045825958252;
    else if(0.8<eta && eta<=1.444)     scale_factor = 0.9929676651954652;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.990728497505188;
    else if(2.0<eta && eta<=2.4)       scale_factor = 0.9971264600753784;
  }
  else if(35<pt && pt<=50){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 1.0;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9929824471473694;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 0.9799764156341552;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.9698376059532166;
    else if(0.0<eta && eta<=0.8)       scale_factor = 0.9768250584602356;
    else if(0.8<eta && eta<=1.444)     scale_factor = 0.9834123253822328;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9906213283538818;
    else if(2.0<eta && eta<=2.4)       scale_factor = 1.011264085769653;
  }
  else if(50<pt && pt<=100){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 0.9988123774528505;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.993228018283844;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 0.979706883430481;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.9721293449401855;
    else if(0.0<eta && eta<=0.8)       scale_factor = 0.9788418412208556;
    else if(0.8<eta && eta<=1.444)     scale_factor = 0.9830124378204346;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9954648613929749;
    else if(2.0<eta && eta<=2.4)       scale_factor = 1.0035587549209597;
  }
  else if(100<pt && pt<=1000){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 0.9966443181037904;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 1.0044004917144775;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 1.0120482444763184;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.993513524532318;
    else if(0.0<eta && eta<=0.8)       scale_factor = 0.9967532753944396;
    else if(0.8<eta && eta<=1.444)     scale_factor = 1.012061357498169;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 1.0032858848571775;
    else if(2.0<eta && eta<=2.4)       scale_factor = 1.0055803060531616;
  }
  return scale_factor;
}

//--------------------------
//        Muons
//--------------------------

//Muon Reco
double VLLAna::Muon_2017UL_Reco(float pt, float eta){
  double scale_factor = 1.0;//default value
  if(fabs(eta)<=0.9){
    if( 15<pt && pt<=20)         scale_factor =  1.0371205652692903;
    else if( 20<pt && pt<=25)    scale_factor =  0.9953024686566452;
    else if( 25<pt && pt<=30)    scale_factor =  0.997336963959657;
    else if( 30<pt && pt<=40)    scale_factor =  0.9998589637860762;
    else if( 40<pt && pt<=50)    scale_factor =  0.9996989192141472;
    else if( 50<pt && pt<=60)    scale_factor =  0.9992867403140626;
    else if( 60<pt && pt<=120)   scale_factor =  0.9987532372551404;
    else if( 120<pt && pt<=3000) scale_factor =  0.9987532372551404;    
  }  
  else if(0.9<fabs(eta) && fabs(eta)<=1.2){
    if( 15<pt && pt<=20)         scale_factor =  1.0155193528163595;
    else if( 20<pt && pt<=25)    scale_factor =  0.997835231302182;
    else if( 25<pt && pt<=30)    scale_factor =  0.998108430594894;
    else if( 30<pt && pt<=40)    scale_factor =  0.999698441575575;
    else if( 40<pt && pt<=50)    scale_factor =  0.9996785795794768;
    else if( 50<pt && pt<=60)    scale_factor =  0.9996068337718907;
    else if( 60<pt && pt<=120)   scale_factor =  0.9979892255029518;
    else if( 120<pt && pt<=3000) scale_factor =  0.9979892255029518;
  }
  else if(1.2<fabs(eta) && fabs(eta)<=2.1){
    if( 15<pt && pt<=20)         scale_factor = 0.9425928386608312;
    else if( 20<pt && pt<=25)    scale_factor = 0.9774500349547384 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.9926385124009492 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9990079418864558;
    else if( 40<pt && pt<=50)    scale_factor = 0.999447004850786 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.998832969729422 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.9934707909605992 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.9934707909605992 ;
  }
  
  else if(2.1<fabs(eta) && fabs(eta)<=2.4){
    if( 15<pt && pt<=20)         scale_factor = 0.9804188624012592 ;
    else if( 20<pt && pt<=25)    scale_factor = 0.9346039234654976 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.9947780248422452 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9913476405385134 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9966131458258156 ;
    else if( 50<pt && pt<=60)    scale_factor = 1.000509333359629 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.9872165645210326;
    else if( 120<pt && pt<=3000) scale_factor = 0.9872165645210326 ;
  }
  return scale_factor;
}

//Muon ID
double VLLAna::Muon_2017UL_ID(float pt, float eta){
  double scale_factor = 1.0;//default value
  if(fabs(eta)<=0.9){
    if( 15<pt && pt<=20)         scale_factor = 0.9924863614579832;
    else if( 20<pt && pt<=25)    scale_factor = 0.9954816932715648;
    else if( 25<pt && pt<=30)    scale_factor = 0.9955697844976936 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9951603878132708 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9951105073375844;
    else if( 50<pt && pt<=60)    scale_factor = 0.9951976038330612 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.994666968105307 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.994666968105307 ;  
  } 
  else if(0.9<fabs(eta) && fabs(eta)<=1.2){
    if( 15<pt && pt<=20)         scale_factor = 0.9956696921512976 ;
    else if( 20<pt && pt<=25)    scale_factor = 0.9939450305313444 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.9947276454652628 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.995398905706962 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9957428336764376 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9955082832064152 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.9955641990427432 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.9955641990427432 ;
  }
  else if(1.2<fabs(eta) && fabs(eta)<=2.1){
    if( 15<pt && pt<=20)         scale_factor = 0.9933986091392504;
    else if( 20<pt && pt<=25)    scale_factor = 0.9927132381475516 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.9941829604829172 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9944960514832868 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9949584995961004 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9944590661336324;
    else if( 60<pt && pt<=120)   scale_factor = 0.994652812538256 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.994652812538256 ;
  }
  else if(2.1<fabs(eta) && fabs(eta)<=2.4){
    if( 15<pt && pt<=20)         scale_factor = 0.9693846291868856;
    else if( 20<pt && pt<=25)    scale_factor = 0.9747230928008838;
    else if( 25<pt && pt<=30)    scale_factor = 0.9759171153765592 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9764452514984272 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9758862144605156 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9742452980764128;
    else if( 60<pt && pt<=120)   scale_factor = 0.974770219850666 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.974770219850666;
  }
  return scale_factor;
}

//Muon Iso
double VLLAna::Muon_2017UL_Iso(float pt, float eta){
  double scale_factor = 1.0;//default value
  if(fabs(eta)<=0.9){
    if( 15<pt && pt<=20)         scale_factor = 0.9947823718048496;
    else if( 20<pt && pt<=25)    scale_factor = 1.0016942717758164 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.9971703762914856 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9973609608464306 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.997806350070658;
    else if( 50<pt && pt<=60)    scale_factor = 0.9978293376015096 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.998652869099414 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.998652869099414 ;
  }  
  else if(0.9<fabs(eta) && fabs(eta)<=1.2){
    if( 15<pt && pt<=20)         scale_factor = 1.0183992947285718;
    else if( 20<pt && pt<=25)    scale_factor = 1.0038832134794526 ;
    else if( 25<pt && pt<=30)    scale_factor = 1.0075445153230558;
    else if( 30<pt && pt<=40)    scale_factor = 1.0020084794113078;
    else if( 40<pt && pt<=50)    scale_factor = 0.9992002400422144;
    else if( 50<pt && pt<=60)    scale_factor = 0.998833434134476 ;
    else if( 60<pt && pt<=120)   scale_factor = 1.000293946420109;
    else if( 120<pt && pt<=3000) scale_factor = 1.000293946420109;
  }
  else if(1.2<fabs(eta) && fabs(eta)<=2.1){
    if( 15<pt && pt<=20)         scale_factor = 1.0284365276526;
    else if( 20<pt && pt<=25)    scale_factor = 1.0231949144028831 ;
    else if( 25<pt && pt<=30)    scale_factor = 1.0139222529965777;
    else if( 30<pt && pt<=40)    scale_factor = 1.006437043406326 ;
    else if( 40<pt && pt<=50)    scale_factor = 1.0024938664942575 ;
    else if( 50<pt && pt<=60)    scale_factor = 1.0010470387044712 ;
    else if( 60<pt && pt<=120)   scale_factor = 1.0004498131972417;
    else if( 120<pt && pt<=3000) scale_factor = 1.0004498131972417;
  }
  
  else if(2.1<fabs(eta) && fabs(eta)<=2.4){
    if( 15<pt && pt<=20)         scale_factor = 1.0300218449052083;
    else if( 20<pt && pt<=25)    scale_factor = 1.024066132761046;
    else if( 25<pt && pt<=30)    scale_factor = 1.0156122873346385;
    else if( 30<pt && pt<=40)    scale_factor = 1.0060772873232575 ;
    else if( 40<pt && pt<=50)    scale_factor = 1.002661144530422;
    else if( 50<pt && pt<=60)    scale_factor = 1.0005458111900405 ;
    else if( 60<pt && pt<=120)   scale_factor = 1.0005556400044369;
    else if( 120<pt && pt<=3000) scale_factor = 1.0005556400044369;
  }
  return scale_factor;
}

//--------------------------
//        Taus
//--------------------------
//Tau AntiJet SF
double VLLAna::Tau_2017UL_AntiJet(float pt){
  double scale_factor = 1.0;//default value
  if( 20<pt && pt<=25)          scale_factor = 0.88092090;
  else if( 25<pt && pt<=30)     scale_factor = 0.90134870;
  else if( 30<pt && pt<=35)     scale_factor = 0.88215320;
  else if( 35<pt && pt<=40)     scale_factor = 0.83283400;
  else if( 40<pt && pt<=500)    scale_factor = 0.84416670;
  else if( 500<pt && pt<=1000)  scale_factor = 0.84416670;
  else if( 1000<pt && pt<=2000) scale_factor = 0.84416670;
  return scale_factor;
}
double VLLAna::Tau_2017UL_AntiEle(float eta){
  double scale_factor = 1.0;//default value
  if( 0.0<fabs(eta) && fabs(eta)<=1.46)        scale_factor = 0.97000;
  else if( 1.46<fabs(eta) && fabs(eta)<=1.558) scale_factor = 0.97000;
  else if( 1.558<fabs(eta) && fabs(eta)<=2.3)  scale_factor = 0.85000;
  return scale_factor;
}
double VLLAna::Tau_2017UL_AntiMu(float eta){
  double scale_factor = 1.0;//default value
  if( 0.0<fabs(eta) && fabs(eta)<=0.4)      scale_factor = 1.27455;
  else if( 0.4<fabs(eta) && fabs(eta)<=0.8) scale_factor = 1.19579;
  else if( 0.8<fabs(eta) && fabs(eta)<=1.2) scale_factor = 1.00426;
  else if( 1.2<fabs(eta) && fabs(eta)<=1.7) scale_factor = 0.80720;
  else if( 1.7<fabs(eta) && fabs(eta)<=2.3) scale_factor = 3.63652;
  return scale_factor;
}
