//######################################################################
//                         2018 ScaleFactors
//######################################################################

//--------------------------
//        Electrons
//--------------------------

//Electron Reco
double VLLAna::Electron_2018UL_Reco(float pt, float eta){
  double scale_factor = 1.0; //default value
  if(10<pt && pt<=20){
    if(-5.0<eta && eta<-2.1)           scale_factor = 0.99895179271698;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.99895179271698;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.1436463594436646;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 0.9888888597488404;
    else if(-1.0<eta && eta<=0.0)      scale_factor = 1.0768293142318726;
    else if(0.0<eta && eta<=1.0)       scale_factor = 1.0768293142318726;
    else if(1.0<eta && eta<=1.444)     scale_factor = 0.9888888597488404;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.1436463594436646;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.99895179271698;
    else if(2.0<eta && eta<=5.0)       scale_factor = 0.99895179271698;
  }
  else if(20<pt && pt<=45){
    if(-5.0<eta && eta<=-2.1)          scale_factor = 0.98353910446167;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9887179732322692;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 0.9754385948181152;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 0.98238343000412;
    else if(-1.0<eta && eta<=-0.5)     scale_factor = 0.9886831045150756;
    else if(-0.5<eta && eta<=0.0)      scale_factor = 0.9865702390670776;
    else if(0.0<eta && eta<=0.5)       scale_factor = 0.9864583611488342;
    else if(0.5<eta && eta<=1.0)       scale_factor = 0.987525999546051;
    else if(1.0<eta && eta<=1.444)     scale_factor = 0.9791013598442078;
    else if(1.444<eta && eta<=1.566)   scale_factor = 0.9870129823684692;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9877049326896667;
    else if(2.0<eta && eta<=5.0)       scale_factor = 0.9866803288459778;
  }
  else if(45<pt && pt<=75){
    if(-5.0<eta && eta<=-2.1)          scale_factor = 0.98670756816864;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9887869358062744;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 0.96592116355896;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 0.98353910446167;
    else if(-1.0<eta && eta<=-0.5)     scale_factor = 0.9877426028251648;
    else if(-0.5<eta && eta<=0.0)      scale_factor = 0.9876922965049744;
    else if(0.0<eta && eta<=0.5)       scale_factor = 0.9855072498321532;
    else if(0.5<eta && eta<=1.0)       scale_factor = 0.9886128306388856;
    else if(1.0<eta && eta<=1.444)     scale_factor = 0.98031085729599;
    else if(1.444<eta && eta<=1.566)   scale_factor = 0.9741935729980468;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9887869358062744;
    else if(2.0<eta && eta<=5.0)       scale_factor = 0.9887869358062744;
  }
  else if(75<pt && pt<=100){
    if(-5.0<eta && eta<=-2.1)          scale_factor = 0.996926248073578;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9939024448394777;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0338428020477295;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 0.9979296326637268;
    else if(-1.0<eta && eta<=-0.5)     scale_factor = 0.9897330403327942;
    else if(-0.5<eta && eta<=0.0)      scale_factor = 0.9897540807724;
    else if(0.0<eta && eta<=0.5)       scale_factor = 0.9897540807724;
    else if(0.5<eta && eta<=1.0)       scale_factor = 0.9897330403327942;
    else if(1.0<eta && eta<=1.444)     scale_factor = 0.9979296326637268;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0338428020477295;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9939024448394777;
    else if(2.0<eta && eta<=5.0)       scale_factor = 0.996926248073578;
  }
  else if(100<pt && pt<=1000){
    if(-5.0<eta && eta<=-2.1)          scale_factor = 0.9989827275276184;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 1.007128357887268;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.030803084373474;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 0.9938271641731262;
    else if(-1.0<eta && eta<=-0.5)     scale_factor = 0.9959100484848022;
    else if(-0.5<eta && eta<=0.0)      scale_factor = 0.9959058165550232;
    else if(0.0<eta && eta<=0.5)       scale_factor = 0.9959058165550232;
    else if(0.5<eta && eta<=1.0)       scale_factor = 0.9959100484848022;
    else if(1.0<eta && eta<=1.444)     scale_factor = 0.9938271641731262;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.030803084373474;
    else if(1.566<eta && eta<=2.0)     scale_factor = 1.007128357887268;
    else if(2.0<eta && eta<=5.0)       scale_factor = 0.9989827275276184;
  }
  return scale_factor;
}
//Electron IdIso
double VLLAna::Electron_2018UL_IDIso(float pt, float eta){
  double scale_factor = 1.0;//default value
  if(10<pt && pt<=20){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 1.0568181276321411;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 1.0353130102157593;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 1.0157480239868164;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.970703125;
    else if(0.0<eta && eta<=0.8)       scale_factor = 0.9808428883552552;
    else if(0.8<eta && eta<=1.444)     scale_factor = 1.0078431367874146;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 1.0016286373138428;
    else if(2.0<eta && eta<=2.4)       scale_factor = 1.0356472730636597;
  }
  else if(20<pt && pt<=35){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 1.0014164447784424;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9870466589927672;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 0.9584487676620485;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.967346966266632;
    else if(0.0<eta && eta<=0.8)       scale_factor = 0.9728997349739076;
    else if(0.8<eta && eta<=1.444)     scale_factor = 0.9650349617004396;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9750983119010924;
    else if(2.0<eta && eta<=2.4)       scale_factor = 0.9886845946311952;
  }
  else if(35<pt && pt<=50){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 0.9950980544090272;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9861271381378174;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 0.9647887349128724;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.9686775207519532;
    else if(0.0<eta && eta<=0.8)       scale_factor = 0.9732868671417236;
    else if(0.8<eta && eta<=1.444)     scale_factor = 0.9668246507644652;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9802784323692322;
    else if(2.0<eta && eta<=2.4)       scale_factor = 0.9852579832077026;
  }
  else if(50<pt && pt<=100){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 0.9918032884597778;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9865319728851318;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 0.966216206550598;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.9709821343421936;
    else if(0.0<eta && eta<=0.8)       scale_factor = 0.9732142686843872;
    else if(0.8<eta && eta<=1.444)     scale_factor = 0.9693877696990968;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9797979593276978;
    else if(2.0<eta && eta<=2.4)       scale_factor = 0.9801169633865356;
  }
  else if(100<pt && pt<=1000){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 1.0;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9978237152099608;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 1.0021858215332031;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.990217387676239;
    else if(0.0<eta && eta<=0.8)       scale_factor = 1.0054525136947632;
    else if(0.8<eta && eta<=1.444)     scale_factor = 1.0054824352264404;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.99672132730484;
    else if(2.0<eta && eta<=2.4)       scale_factor = 0.9854586124420166;
  }
  return scale_factor;
}

//--------------------------
//        Muons
//--------------------------

//Muon Reco
double VLLAna::Muon_2018UL_Reco(float pt, float eta){
  double scale_factor = 1.0;//default value
  if(fabs(eta)<=0.9){
    if( 15<pt && pt<=20)         scale_factor =  1.04000400946163;
    else if( 20<pt && pt<=25)    scale_factor =  0.989014677272758;
    else if( 25<pt && pt<=30)    scale_factor =  0.9989055590645546;
    else if( 30<pt && pt<=40)    scale_factor =  0.999760853514322;
    else if( 40<pt && pt<=50)    scale_factor =  0.999565467845588;
    else if( 50<pt && pt<=60)    scale_factor =  0.9998204415944014;
    else if( 60<pt && pt<=120)   scale_factor =  0.9975015485587808;
    else if( 120<pt && pt<=3000) scale_factor =  0.9975015485587808;   
  }
  else if(0.9<fabs(eta) && fabs(eta)<=1.2){
    if( 15<pt && pt<=20)         scale_factor =  1.0334239991476872;
    else if( 20<pt && pt<=25)    scale_factor =  0.9832043508246824;
    else if( 25<pt && pt<=30)    scale_factor =  0.9962074764783356;
    else if( 30<pt && pt<=40)    scale_factor =  0.999066550372675;
    else if( 40<pt && pt<=50)    scale_factor =  0.999297799609978;
    else if( 50<pt && pt<=60)    scale_factor =  0.999898284881032;
    else if( 60<pt && pt<=120)   scale_factor =  0.9978985301114488;
    else if( 120<pt && pt<=3000) scale_factor =  0.9978985301114488;
  }
  else if(1.2<fabs(eta) && fabs(eta)<=2.1){
    if( 15<pt && pt<=20)         scale_factor =  0.9052340457842656;
    else if( 20<pt && pt<=25)    scale_factor =  0.9932902480824264;
    else if( 25<pt && pt<=30)    scale_factor =  0.9941744704916416;
    else if( 30<pt && pt<=40)    scale_factor =  0.9981802152409986 ;
    else if( 40<pt && pt<=50)    scale_factor =  0.9992437146078612;
    else if( 50<pt && pt<=60)    scale_factor =  0.9988904857161484;
    else if( 60<pt && pt<=120)   scale_factor =  0.9961937512394232;
    else if( 120<pt && pt<=3000) scale_factor =  0.9961937512394232;
  }
  else if(2.1<fabs(eta) && fabs(eta)<=2.4){
    if( 15<pt && pt<=20)         scale_factor =  0.9606433668106512;
    else if( 20<pt && pt<=25)    scale_factor =  0.9911896930756448;
    else if( 25<pt && pt<=30)    scale_factor =  0.9910856248132396;
    else if( 30<pt && pt<=40)    scale_factor =  0.9907553768818946;
    else if( 40<pt && pt<=50)    scale_factor =  0.9933622417972257;
    else if( 50<pt && pt<=60)    scale_factor =  0.9972680454815808;
    else if( 60<pt && pt<=120)   scale_factor =  0.9665749388673832;
    else if( 120<pt && pt<=3000) scale_factor =  0.9665749388673832;
  }
  return scale_factor;
}

//Muon ID
double VLLAna::Muon_2018UL_ID(float pt, float eta){
  double scale_factor = 1.0;//default value
  if(fabs(eta)<=0.9){
    if( 15<pt && pt<=20)         scale_factor =  0.997503630932556;
    else if( 20<pt && pt<=25)    scale_factor =  0.9970098193760408;
    else if( 25<pt && pt<=30)    scale_factor =  0.9967038731014324;
    else if( 30<pt && pt<=40)    scale_factor =  0.9968067958281034;
    else if( 40<pt && pt<=50)    scale_factor =  0.9967508548887346;
    else if( 50<pt && pt<=60)    scale_factor =  0.9966229487883712;
    else if( 60<pt && pt<=120)   scale_factor =  0.9960404563074258;
    else if( 120<pt && pt<=3000) scale_factor =  0.9960404563074258;   
  }
  
  else if(0.9<fabs(eta) && fabs(eta)<=1.2){
    if( 15<pt && pt<=20)         scale_factor =  0.9946687083751804;
    else if( 20<pt && pt<=25)    scale_factor =  0.9945901104821656;
    else if( 25<pt && pt<=30)    scale_factor =  0.9949123046983688;
    else if( 30<pt && pt<=40)    scale_factor =  0.9956851566638726;
    else if( 40<pt && pt<=50)    scale_factor =  0.995312757370098;
    else if( 50<pt && pt<=60)    scale_factor =  0.9953453170396492;
    else if( 60<pt && pt<=120)   scale_factor =  0.9952502092400578;
    else if( 120<pt && pt<=3000) scale_factor =  0.9952502092400578;
  }
  else if(1.2<fabs(eta) && fabs(eta)<=2.1){
    if( 15<pt && pt<=20)         scale_factor =  0.9935059740562387;
    else if( 20<pt && pt<=25)    scale_factor =  0.9938964039703309;
    else if( 25<pt && pt<=30)    scale_factor =  0.9940771317309104;
    else if( 30<pt && pt<=40)    scale_factor =  0.9941876412222066;
    else if( 40<pt && pt<=50)    scale_factor =  0.9947739560711352;
    else if( 50<pt && pt<=60)    scale_factor =  0.9944640815519576;
    else if( 60<pt && pt<=120)   scale_factor =  0.9944321015185944;
    else if( 120<pt && pt<=3000) scale_factor =  0.9944321015185944;
  }
  
  else if(2.1<fabs(eta) && fabs(eta)<=2.4){
    if( 15<pt && pt<=20)         scale_factor =  0.9741187787139896;
    else if( 20<pt && pt<=25)    scale_factor =  0.9727131632621572;
    else if( 25<pt && pt<=30)    scale_factor =  0.9739795198691632;
    else if( 30<pt && pt<=40)    scale_factor =  0.9750724343730348;
    else if( 40<pt && pt<=50)    scale_factor =  0.9747976871311668;
    else if( 50<pt && pt<=60)    scale_factor =  0.9743746068723314;
    else if( 60<pt && pt<=120)   scale_factor =  0.970208378910226;
    else if( 120<pt && pt<=3000) scale_factor =  0.970208378910226;
  }
  return scale_factor;
}

//Muon Iso
double VLLAna::Muon_2018UL_Iso(float pt, float eta){
  double scale_factor = 1.0;//default value
  if(fabs(eta)<=0.9){
    if( 15<pt && pt<=20)         scale_factor =  0.9855709248030112;
    else if( 20<pt && pt<=25)    scale_factor =  0.9915374149428736;
    else if( 25<pt && pt<=30)    scale_factor =  0.9892802138927208;
    else if( 30<pt && pt<=40)    scale_factor =  0.99429319088059;
    else if( 40<pt && pt<=50)    scale_factor =  0.9960381793609222;
    else if( 50<pt && pt<60)     scale_factor =  0.9966122162214248;
    else if( 60<pt && pt<=120)   scale_factor =  0.9982512434902386;
    else if( 120<pt && pt<=3000) scale_factor =  0.9982512434902386;
  }
  else if(0.9<fabs(eta) && fabs(eta)<=1.2){
    if( 15<pt && pt<=20)         scale_factor =  0.9704305474456316;
    else if( 20<pt && pt<=25)    scale_factor =  0.979495631900224;
    else if( 25<pt && pt<=30)    scale_factor =  0.986109906870666;
    else if( 30<pt && pt<=40)    scale_factor =  0.9882799134496284;
    else if( 40<pt && pt<=50)    scale_factor =  0.9920317410868984;
    else if( 50<pt && pt<=60)    scale_factor =  0.9944502663616424;
    else if( 60<pt && pt<=120)   scale_factor =  0.9964834155289044;
    else if( 120<pt && pt<=3000) scale_factor =  0.9964834155289044;
  }
  else if(1.2<fabs(eta) && fabs(eta)<=2.1){
    if( 15<pt && pt<=20)         scale_factor =  1.0033355765204894;
    else if( 20<pt && pt<=25)    scale_factor =  1.0015352730781717;
    else if( 25<pt && pt<=30)    scale_factor =  0.999623464660824;
    else if( 30<pt && pt<=40)    scale_factor =  0.9994357007740622;
    else if( 40<pt && pt<=50)    scale_factor =  0.99882097063955;
    else if( 50<pt && pt<=60)    scale_factor =  0.999185450924234;
    else if( 60<pt && pt<=120)   scale_factor =  0.9995171516432572;
    else if( 120<pt && pt<=3000) scale_factor =  0.9995171516432572;
  }
  else if(2.1<fabs(eta) && fabs(eta)<=2.4){
    if( 15<pt && pt<=20)         scale_factor =  1.0252542402601108;
    else if( 20<pt && pt<=25)    scale_factor =  1.0198418523288777;
    else if( 25<pt && pt<30)     scale_factor =  1.012454313839175;
    else if( 30<pt && pt<=40)    scale_factor =  1.008064837308479;
    else if( 40<pt && pt<=50)    scale_factor =  1.0037288955534218;
    else if( 50<pt && pt<=60)    scale_factor =  1.0028456983691447;
    else if( 60<pt && pt<=120)   scale_factor =  1.0029888816740478;
    else if( 120<pt && pt<=3000) scale_factor =  1.0029888816740478;
  }
  return scale_factor;
}

//--------------------------
//        Taus
//--------------------------
//Tau AntiJet SF
double VLLAna::Tau_2018UL_AntiJet(float pt){
  double scale_factor = 1.0;//default value
  if( 20<pt && pt<=25)          scale_factor = 0.92814490;
  else if( 25<pt && pt<=30)     scale_factor = 0.86074460;
  else if( 30<pt && pt<=35)     scale_factor = 0.89813290;
  else if( 35<pt && pt<=40)     scale_factor = 0.89707170;
  else if( 40<pt && pt<=500)    scale_factor = 0.89079360;
  else if( 500<pt && pt<=1000)  scale_factor = 0.89079360;
  else if( 1000<pt && pt<=2000) scale_factor = 0.89079360;
  return scale_factor;
}
double VLLAna::Tau_2018UL_AntiEle(float eta){
  double scale_factor = 1.0;//default value
  if( 0.0<fabs(eta) && fabs(eta)<=1.46)        scale_factor = 0.92;
  else if( 1.46<fabs(eta) && fabs(eta)<=1.558) scale_factor = 1.0;
  else if( 1.558<fabs(eta) && fabs(eta)<=2.3)  scale_factor = 0.94;
  return scale_factor;
}
double VLLAna::Tau_2018UL_AntiMu(float eta){
  double scale_factor = 1.0;//default value
  if( 0.0<fabs(eta) && fabs(eta)<=0.4)      scale_factor = 1.31325;
  else if( 0.4<fabs(eta) && fabs(eta)<=0.8) scale_factor = 1.20266;
  else if( 0.8<fabs(eta) && fabs(eta)<=1.2) scale_factor = 0.95748;
  else if( 1.2<fabs(eta) && fabs(eta)<=1.7) scale_factor = 1.13798;
  else if( 1.7<fabs(eta) && fabs(eta)<=2.3) scale_factor = 6.01864;
  return scale_factor;
}
