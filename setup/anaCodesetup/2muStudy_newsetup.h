void VLLAna::Make2muPlots(float wt)
{
  //This function is called in the main VLLAna.C file.
  //It runs for all the 2Mu same-sign events.

  //Picking the samesign pair:
  //The first one is the leading one.
  //The index of the second one is calculated below.
  int ss_ind=-1;
  for(int i=1; i<(int)Muon.size(); i++){
    if(Muon.at(0).charge == Muon.at(i).charge){
      ss_ind = i;
      break;
    }
  }

  //Variables to be used later:
  //Object level:
  float mT0 = transv_mass(Muon.at(0).v.E(), Muon.at(0).v.Phi(), metpt, metphi);
  float mTss = transv_mass(Muon.at(ss_ind).v.E(), Muon.at(ss_ind).v.Phi(), metpt, metphi);

  //dimuon (ss) system:
  float dimuon_ss_mass = (Muon.at(0).v + Muon.at(ss_ind).v).M();
  float dR_ss_muons = Muon.at(0).v.DeltaR(Muon.at(ss_ind).v);
  float deta_ss_muons = fabs(Muon.at(0).v.Eta()-Muon.at(ss_ind).v.Eta());
  float dphi_ss_muons = delta_phi(Muon.at(0).v.Phi(), Muon.at(ss_ind).v.Phi());
  float ptratio = Muon.at(ss_ind).v.Pt()/Muon.at(0).v.Pt();

  //event level:
  float LT=0; for(int i=0; i<(int)Muon.size(); i++) LT = LT + Muon.at(i).v.Pt();
  float HT=0; for(int i=0; i<(int)jets.size(); i++) HT = HT + jets.at(i).v.Pt();
  int njet = (int)jets.size();
  int nbjet = (int)BTaggedJet.size();

  //QCD HT-binned_scaling:
  bool isQCDsample = false;
  float qcdsf= 1;
  float globalsf = 0.0242004;
  /*
    Calculating HT binned sf for QCD ...
    bin     range   nqcd    ndata   nothers sf
    1       0-100   535473  36008   3165    0.0672452
    2       100-200 1563348 57866   13590   0.0370141
    3       200-300 611866  24947   19942   0.040772
    4       300-400 210541  11219   13601   0.0532865
    5       400-500 75370   5110    7311    0.0677984
    6       500-600 31615   2568    3847    0.0812271
    7       600-700 14247   1462    2179    0.102612
    8       700-800 7156    777     1265    0.108568
    9       800-900 3850    493     774     0.128028
    10      900-1000        5154    882     1632    0.171124
    11      overflow        3140    584     1117    0.185978
  */
  /*
  if(HT<100) qcdsf = 0.031921;
  else if(100<HT && HT<200) qcdsf = 0.0122274;
  else if(200<HT && HT<300) qcdsf = 0.0124822;
  else if(300<HT && HT<400) qcdsf = 0.016445;
  else if(400<HT && HT<500) qcdsf = 0.019735;
  else if(500<HT && HT<600) qcdsf = 0.0242182;
  else if(600<HT && HT<700) qcdsf = 0.0269579;
  else if(700<HT && HT<800) qcdsf = 0.0286833;
  else if(800<HT && HT<900) qcdsf = 0.0302548;
  else if(900<HT && HT<1000)qcdsf = 0.0381407;
  else qcdsf = 0.0391593; //overflow*/

  if(isQCDsample) wt=wt*globalsf;

  /*
  //Cutflow:
  //The first bin contains the original number of events with basic selections:
  h.cutflow[0]->Fill((int)0, wt);
  h.cutflow[1]->Fill((int)0, wt);
  h.cutflow[2]->Fill((int)0, wt);
  h.cutflow[3]->Fill((int)0, wt);

  //Object level cuts:
  vector<bool> cut_obj =
    {
     Muon.at(0).v.Pt() > 30,
     Muon.at(0).reliso03 < 0.2,
     Muon.at(ss_ind).v.Pt() > 20,
     Muon.at(0).sip3d < 2.5
    };
  for(int i=0; i<(int)cut_obj.size(); i++){if(cut_obj[i] == true) h.cutflow[0]->Fill(i+1, wt);}

  //event level cuts:
  vector<bool> cut_evt =
    {
     LT > 40
    };
  for(int i=0; i<(int)cut_evt.size(); i++){if(cut_evt[i] == true) h.cutflow[2]->Fill(i+1, wt);}

  bool noniso = 0.25<Muon.at(0).reliso04 && Muon.at(0).reliso04<1;
  bool iso = Muon.at(0).reliso04<0.15 && Muon.at(0).sip3d < 2.5;
  bool ptcuts = cut_obj[0] && cut_obj[2];

  if(iso)                    h.cutflow[3]->Fill((int)1, wt);
  if(ptcuts)                 h.cutflow[3]->Fill((int)2, wt);
  if(iso && ptcuts)          h.cutflow[3]->Fill((int)3, wt);
  if(iso && ptcuts && LT>40) h.cutflow[3]->Fill((int)4, wt);*/

  //-------------------------------------------------------------------------
  //Selecting good events:
  bool isolated_muons =
    Muon.at(0).reliso04      < 0.15 && Muon.at(0).sip3d      < 2.5 &&
    Muon.at(ss_ind).reliso04 < 0.20 && Muon.at(ss_ind).sip3d < 3.0;

  bool ptcuts =
    Muon.at(0).v.Pt()      > 30 &&
    Muon.at(ss_ind).v.Pt() > 15; 
  
  //-------------------------------------------------------------------------
  
  if(isolated_muons && ptcuts){//Put selections here.
    //Object level plots:    
    h.studySS[0]->Fill(Muon.at(0).v.Pt(), wt);
    h.studySS[1]->Fill(Muon.at(0).v.Eta(), wt);
    h.studySS[2]->Fill(Muon.at(0).v.Phi(), wt);
    h.studySS[3]->Fill(mT0, wt);
    h.studySS[4]->Fill(Muon.at(0).reliso03, wt);
    h.studySS[5]->Fill(Muon.at(0).reliso04, wt);
    h.studySS[6]->Fill(Muon.at(0).sip3d, wt);
    h.studySS[7]->Fill(Muon.at(ss_ind).v.Pt(), wt);
    h.studySS[8]->Fill(Muon.at(ss_ind).v.Eta(), wt);
    h.studySS[9]->Fill(Muon.at(ss_ind).v.Phi(), wt);
    h.studySS[10]->Fill(mTss, wt);
    h.studySS[11]->Fill(Muon.at(ss_ind).reliso03, wt);
    h.studySS[12]->Fill(Muon.at(ss_ind).reliso04, wt);
    h.studySS[13]->Fill(Muon.at(ss_ind).sip3d, wt);
    
    //The dimuon (samesign) system::    
    h.studySS[14]->Fill(dimuon_ss_mass, wt);
    h.studySS[15]->Fill(deta_ss_muons, wt);
    h.studySS[16]->Fill(dphi_ss_muons, wt);
    h.studySS[17]->Fill(dR_ss_muons, wt);
    h.studySS[18]->Fill(ptratio, wt);
        
    //Event level plots:   
    h.studySS[19]->Fill(metpt, wt);
    h.studySS[20]->Fill(metphi, wt);
    h.studySS[21]->Fill(LT, wt);
    h.studySS[22]->Fill(HT, wt);
    h.studySS[23]->Fill(njet, wt);
    h.studySS[24]->Fill(nbjet, wt);
  }

}
