//######################################################################
//                    2016 preVFP ScaleFactors
// Due to some technical error, the 2016 dataset had to be split into
// 'preVPF' and 'postVFP'. That's why these calculations are twice as
// long. Luminosity weights are used to combine the two sets of numbers
//######################################################################

//Electron Reco
double VLLAna::Electron_2016UL_Reco_preVFP(float pt, float eta){
  double scale_factor = 1.0; //default value
  if(10<pt && pt<=20){
    if(-5.0<eta && eta<=-2.1)          scale_factor = 1.0138888359069824;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9903433322906494;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.206501007080078;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 1.0175824165344238;
    else if(-1.0<eta && eta<=0.0)      scale_factor = 1.055690050125122;
    else if(0.0<eta && eta<=1.0)       scale_factor = 1.055690050125122;
    else if(1.0<eta && eta<=1.444)     scale_factor = 1.0175824165344238;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.206501007080078;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9903433322906494;
    else if(2.0<eta && eta<=5.0)       scale_factor = 1.0138888359069824;
  }
  else if(20<pt && pt<=45){
    if(-5.0<eta && eta<=-2.1)          scale_factor = 0.996791422367096;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9927234649658204;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 0.9575971961021424;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 0.9855967164039612;
    else if(-1.0<eta && eta<=-0.5)     scale_factor = 0.9794450402259828;
    else if(-0.5<eta && eta<=0.0)      scale_factor = 0.9752577543258668;
    else if(0.0<eta && eta<=0.5)       scale_factor = 0.9865979552268982;
    else if(0.5<eta && eta<=1.0)       scale_factor = 0.9877049326896667;
    else if(1.0<eta && eta<=1.444)     scale_factor = 0.989722490310669;
    else if(1.444<eta && eta<=1.566)   scale_factor = 0.971563994884491;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9938016533851624;
    else if(2.0<eta && eta<=5.0)       scale_factor = 1.0;
  }
  else if(45<pt && pt<=75){
    if(-5.0<eta && eta<=-2.1)          scale_factor = 0.9915878176689148;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9927685856819152;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 0.9621621370315552;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 0.9867211580276488;
    else if(-1.0<eta && eta<=-0.5)     scale_factor = 0.9816138744354248;
    else if(-0.5<eta && eta<=0.0)      scale_factor = 0.9795291423797609;
    else if(0.0<eta && eta<=0.5)       scale_factor = 0.9877175092697144;
    else if(0.5<eta && eta<=1.0)       scale_factor = 0.9877800345420836;
    else if(1.0<eta && eta<=1.444)     scale_factor = 0.9887754917144777;
    else if(1.444<eta && eta<=1.566)   scale_factor = 0.9751351475715636;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9907597303390504;
    else if(2.0<eta && eta<=5.0)       scale_factor = 0.9925373196601868;
  }
  else if(75<pt && pt<=100){
    if(-5.0<eta && eta<=-2.1)          scale_factor = 0.9883720874786376;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 0.9846311211586;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0121278762817385;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 0.9827761054039;
    else if(-1.0<eta && eta<=-0.5)     scale_factor = 0.9766022562980652;
    else if(-0.5<eta && eta<=0.0)      scale_factor = 0.9877426028251648;
    else if(0.0<eta && eta<=0.5)       scale_factor = 0.9877426028251648;
    else if(0.5<eta && eta<=1.0)       scale_factor = 0.9766022562980652;
    else if(1.0<eta && eta<=1.444)     scale_factor = 0.9827761054039;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0121278762817385;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9846311211586;
    else if(2.0<eta && eta<=5.0)       scale_factor = 0.9883720874786376;
  }
  else if(100<pt && pt<1000){
    if(-5.0<eta && eta<=-2.1)     scale_factor = 1.009584665298462;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 1.0163766145706177;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0143805742263794;
    else if(-1.444<eta && eta<=-1.0)   scale_factor = 0.9798183441162108;
    else if(-1.0<eta && eta<=-0.5)     scale_factor = 0.9848637580871582;
    else if(-0.5<eta && eta<=0.0)      scale_factor = 0.9898682832717896;
    else if(0.0<eta && eta<=0.5)       scale_factor = 0.9898682832717896;
    else if(0.5<eta && eta<=1.0)       scale_factor = 0.9848637580871582;
    else if(1.0<eta && eta<=1.444)     scale_factor = 0.9798183441162108;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0143805742263794;
    else if(1.566<eta && eta<=2.0)     scale_factor = 1.0163766145706177;
    else if(2.0<eta && eta<=5.0)       scale_factor = 1.009584665298462;
  }
  return scale_factor;
}
//Electron IdIso
double VLLAna::Electron_2016UL_IDIso_preVFP(float pt, float eta){
  double scale_factor = 1.0;//default value
  if(10<pt && pt<=20){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 1.0819367170333862;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 1.065743923187256;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 1.038673996925354;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.9839285612106324;
    else if(0.0<eta && eta<=0.8)       scale_factor = 0.9912126660346984;
    else if(0.8<eta && eta<=1.444)     scale_factor = 1.0694184303283691;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor =1.0352113246917725;
    else if(2.0<eta && eta<=2.4)       scale_factor = 1.0833333730697632;
  }
  else if(20<pt && pt<=35){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 1.0307917594909668;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 1.0176870822906494;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 0.9957447052001952;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.9723374843597412;
    else if(0.0<eta && eta<=0.8)       scale_factor = 0.9821428656578064;
    else if(0.8<eta && eta<=1.444)     scale_factor = 1.0028570890426636;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 1.009602189064026;
    else if(2.0<eta && eta<=2.4)       scale_factor = 1.0203487873077393;
  }
  else if(35<pt && pt<=50){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 1.0152283906936646;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 1.0120337009429932;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 0.990407645702362;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.9692671298980712;
    else if(0.0<eta && eta<=0.8)       scale_factor = 0.9799528121948242;
    else if(0.8<eta && eta<=1.444)     scale_factor =0.9927797913551332 ;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 1.0096385478973389;
    else if(2.0<eta && eta<=2.4)       scale_factor = 1.0114504098892212;
  }
  else if(50<pt && pt<=100){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 1.0024067163467407;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 1.004629611968994;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 0.9896193742752076;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.9693182110786438;
    else if(0.0<eta && eta<=0.8)       scale_factor = 0.9773242473602296;
    else if(0.8<eta && eta<=1.444)     scale_factor = 0.9884659647941588;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 1.0092915296554563;
    else if(2.0<eta && eta<=2.4)       scale_factor =1.0048367977142334 ;
  }
  else if(100<pt && pt<=1000){
    if(-2.4<eta && eta<=-2.1)          scale_factor = 1.0160366296768188;
    else if(-2.1<eta && eta<=-1.566)   scale_factor = 1.0245535373687744;
    else if(-1.566<eta && eta<=-1.444) scale_factor = 1.0;
    else if(-1.444<eta && eta<=-0.8)   scale_factor = 1.0022321939468384;
    else if(-0.8<eta && eta<=0.0)      scale_factor = 0.9889135360717772;
    else if(0.0<eta && eta<=0.8)       scale_factor = 1.0011111497879028;
    else if(0.8<eta && eta<=1.444)     scale_factor = 1.011135816574097;
    else if(1.444<eta && eta<=1.566)   scale_factor = 1.0;
    else if(1.566<eta && eta<=2.0)     scale_factor = 0.9911012053489684;
    else if(2.0<eta && eta<=2.4)       scale_factor = 1.0346020460128784;
  }
  return scale_factor;
}

//________________________________________________________________________________________

//Muon Reco
double VLLAna::Muon_2016UL_Reco_preVFP(float pt, float eta){
  double scale_factor = 1.0;//default value
  if(fabs(eta)<=0.9){
    if( 15<pt && pt<=20)         scale_factor = 1.0446273708660905;
    else if( 20<pt && pt<=25)    scale_factor = 0.9405655555018376;
    else if( 25<pt && pt<=30)    scale_factor = 0.9998939867138692 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9995277742731352;
    else if( 40<pt && pt<=50)    scale_factor = 0.9999352681323206;
    else if( 50<pt && pt<=60)    scale_factor = 0.9995078992862044 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.99375897804621 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.99375897804621 ;    
  }
  else if(0.9<fabs(eta) && fabs(eta)<=1.2){
    if( 15<pt && pt<=20)         scale_factor = 1.0361175046804814;
    else if( 20<pt && pt<=25)    scale_factor = 0.9923137867078856;
    else if( 25<pt && pt<=30)    scale_factor = 0.9983364124577536 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.998972512114526 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9997915677286272 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9988593796096642 ;
    else if( 60<pt && pt<=120)   scale_factor = 1.0007144177738287 ;
    else if( 120<pt && pt<=3000) scale_factor = 1.0007144177738287 ;
  }
  else if(1.2<fabs(eta) && fabs(eta)<=2.1){
    if( 15<pt && pt<=20)         scale_factor = 0.9129515796253396 ;
    else if( 20<pt && pt<=25)    scale_factor = 0.9658955236931815 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.9936254866774044 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9979681231700336 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9993470103425014 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9989902374832634;
    else if( 60<pt && pt<=120)   scale_factor = 0.983545090393948 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.983545090393948 ;
  }
  else if(2.1<fabs(eta) && fabs(eta)<=2.4){
    if( 15<pt && pt<=20)         scale_factor = 0.9477240389808844 ;
    else if( 20<pt && pt<=25)    scale_factor = 0.92859269411554 ;
    else if( 25<pt && pt<=30)    scale_factor = 1.0055252510399186 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.996450420248231 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.992818592569064 ;
    else if( 50<pt && pt<=60)    scale_factor = 1.002406180326867 ;
    else if( 60<pt && pt<=120)   scale_factor =  0.9956175157367412;
    else if( 120<pt && pt<=3000) scale_factor =  0.9956175157367412;
  }
  return scale_factor;
}

//Muon ID
double VLLAna::Muon_2016UL_ID_preVFP(float pt, float eta){
  double scale_factor = 1.0;//default value
  if(fabs(eta)<=0.9){
    if( 15<pt && pt<=20)    scale_factor = 0.9958995777819518 ;
    else if( 20<pt && pt<=25)    scale_factor = 0.997407446293603 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.9966900133732628 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9963886027389632 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9963339691909062 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9958585208059144 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.995911293220199 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.995911293220199 ;
  }
  else if(0.9<fabs(eta) && fabs(eta)<=1.2){
    if( 15<pt && pt<=20)         scale_factor = 0.9943616457833304 ;
    else if( 20<pt && pt<=25)    scale_factor = 0.9942061202269802 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.99363947046918 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9942575420308007 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9947647951586552 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9943155135270608;
    else if( 60<pt && pt<=120)   scale_factor = 0.9933211462795392 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.9933211462795392;
  }
  else if(1.2<fabs(eta) && fabs(eta)<=2.1){
    if( 15<pt && pt<=20)         scale_factor = 0.9944285295926252 ;
    else if( 20<pt && pt<=25)    scale_factor = 0.9939925358291593 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.994002465208057 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9947471249733232 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9954753870789153 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.995042227697235 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.995414618581377 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.995414618581377 ;
  }
  else if(2.1<fabs(eta) && fabs(eta)<2.4){
    if( 15<pt && pt<=20)         scale_factor = 0.974452901727927 ;
    else if( 20<pt && pt<=25)    scale_factor = 0.9741967439553206 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.9745366426282696 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9748921822166626 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9749005301709184 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9748468540075824 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.9741452452429542;
    else if( 120<pt && pt<=3000) scale_factor = 0.9741452452429542 ;
  }
  return scale_factor;
}

//Muon Iso
double VLLAna::Muon_2016UL_Iso_preVFP(float pt, float eta){
  double scale_factor = 1.0;//default value
  if(fabs(eta)<=0.9){
    if( 15<pt && pt<=20)         scale_factor = 0.9854219941983452 ;
    else if( 20<pt && pt<=25)    scale_factor = 0.9873274510709348 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.9857570348249912 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9930490361264857 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.996406871349816;
    else if( 50<pt && pt<=60)    scale_factor = 0.996876679315402 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.9986788196912988 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.9986788196912988 ; 
  }
  else if(0.9<fabs(eta) && fabs(eta)<=1.2){
    if( 15<pt && pt<=20)         scale_factor = 0.9801483018547148 ;
    else if( 20<pt && pt<=25)    scale_factor = 0.987034038637174 ;
    else if( 25<pt && pt<=30)    scale_factor = 0.9961324150426912 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9963549633414416 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.9970368902923656 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9971575821289996 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.9988473955529408 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.9988473955529408 ;
  }
  else if(1.2<fabs(eta) && fabs(eta)<=2.1){
    if( 15<pt && pt<=20)         scale_factor = 0.9972440980735284 ;
    else if( 20<pt && pt<=25)    scale_factor = 0.996750888945838 ;
    else if( 25<pt && pt<=30)    scale_factor = 1.001137262338288 ;
    else if( 30<pt && pt<=40)    scale_factor = 0.9988626071423738 ;
    else if( 40<pt && pt<=50)    scale_factor = 0.998769936879404 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.998384760194074 ;
    else if( 60<pt && pt<=120)   scale_factor = 0.9995753755081986 ;
    else if( 120<pt && pt<=3000) scale_factor = 0.9995753755081986 ;
  }
  else if(2.1<fabs(eta) && fabs(eta)<=2.4){
    if( 15<pt && pt<=20)         scale_factor = 1.0073108674943814 ;
    else if( 20<pt && pt<=25)    scale_factor = 1.0036700117457582 ;
    else if( 25<pt && pt<=30)    scale_factor = 1.0050586818252794 ;
    else if( 30<pt && pt<=40)    scale_factor = 1.0003546800592864 ;
    else if( 40<pt && pt<=50)    scale_factor = 1.0009520269922647 ;
    else if( 50<pt && pt<=60)    scale_factor = 0.9998076464435772 ;
    else if( 60<pt && pt<=120)   scale_factor = 1.0005662186130682 ;
    else if( 120<pt && pt<=3000) scale_factor = 1.0005662186130682 ;
  }
  return scale_factor;
}

//________________________________________________________________________________________

//Taus AntiJet
double VLLAna::Tau_2016UL_AntiJet_preVFP(float pt){
  double scale_factor = 1.0;//default value
  if( 20<pt && pt<=25)        scale_factor = 1.02564100;
  else if( 25<pt && pt<=30)   scale_factor = 1.00438100;
  else if( 30<pt && pt<=35)   scale_factor = 0.96119740;
  else if( 35<pt && pt<=40)   scale_factor = 0.97300020;
  else if( 40<pt && pt<=2000) scale_factor = 0.87672800;
  return scale_factor;
}
//Taus AntiEle
double VLLAna::Tau_2016UL_AntiEle_preVFP(float eta){
  double scale_factor = 1.0;//default value
  if( 0.0<fabs(eta) && fabs(eta)<=1.46)        scale_factor = 1.00000;
  else if( 1.46<fabs(eta) && fabs(eta)<=1.558) scale_factor = 1.00000;
  else if( 1.558<fabs(eta) && fabs(eta)<=2.3)  scale_factor = 1.04000;
  return scale_factor;
}

//Taus AntiMu
double VLLAna::Tau_2016UL_AntiMu_preVFP(float eta){
  double scale_factor = 1.0;//default value
  if( 0.0<fabs(eta) && fabs(eta)<=0.4)      scale_factor = 1.14824;
  else if( 0.4<fabs(eta) && fabs(eta)<=0.8) scale_factor = 1.23390;
  else if( 0.8<fabs(eta) && fabs(eta)<=1.2) scale_factor = 1.33607;
  else if( 1.2<fabs(eta) && fabs(eta)<=1.7) scale_factor = 1.06373;
  else if( 1.7<fabs(eta) && fabs(eta)<=2.3) scale_factor = 4.76128;
  return scale_factor;
}








