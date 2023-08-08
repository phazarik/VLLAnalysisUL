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
  float globalsf = 0.0242004; //Not needed. I am doing it in the stack-maker

  if(isQCDsample) wt=wt*globalsf;

  //-------------------------------------------------------------------------
  //Selecting good events:
  bool isolated_muons =
    Muon.at(0).reliso04      < 0.15 && Muon.at(0).sip3d      < 2.5 &&
    Muon.at(ss_ind).reliso04 < 0.20 && Muon.at(ss_ind).sip3d < 3.0;

  bool ptcuts =
    Muon.at(0).v.Pt()      > 30 &&
    Muon.at(ss_ind).v.Pt() > 15;

  bool working_region = isolated_muons && ptcuts && nbjet==0;
  bool signal_region = deta_ss_muons<2.5 && HT<300; //bottom-left box in the HT-dEta plane
  bool control_region = deta_ss_muons>2.5 || HT>300;
  bool cr1 = deta_ss_muons > 2.5 && HT < 300; //top-left box in the HT-dEta plane
  bool cr2 = deta_ss_muons > 2.5 && HT > 300; //top-right box in the HT-dEta plane
  bool cr3 = deta_ss_muons < 2.5 && HT > 300; //bottom-right box in the HT dEta plan
  
  //-------------------------------------------------------------------------
  
  if(working_region && signal_region){//Put selections here.

    nEvtPass ++; //no of events that pass my selections
    
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

    h.regions[0]->Fill(HT, metpt);
    h.regions[1]->Fill(HT, deta_ss_muons);
    h.regions[2]->Fill(HT, njet);
  }

  //Cutflow:
  h.cutflow[0]->Fill((int)0, wt); //for all events passing basic event selections.
  h.cutflow[1]->Fill((int)0, wt); //for all events passing basic event selections.
  h.cutflow[2]->Fill((int)0, wt); //for all events passing basic event selections.

  //Overall event selection:
  if(nbjet==0){
    h.cutflow[0]->Fill((int)1, wt);
    if(Muon.at(0).v.Pt() > 30){
      h.cutflow[0]->Fill((int)2, wt);
      if(Muon.at(0).reliso04 < 0.15){
	h.cutflow[0]->Fill((int)3, wt);
	if(Muon.at(0).sip3d < 2.5){
	  h.cutflow[0]->Fill((int)4, wt);
	  if(Muon.at(ss_ind).v.Pt() > 15){
	    h.cutflow[0]->Fill((int)5, wt);
	    if(Muon.at(ss_ind).reliso04 < 0.20){
	      h.cutflow[0]->Fill((int)6, wt);
	      if(Muon.at(ss_ind).sip3d < 3.0){
		h.cutflow[0]->Fill((int)7, wt);
	      }
	    }
	  }
	}
      }
    }
  }
  
  //Investigating cuts on the leading muon:
  if(Muon.at(0).v.Pt() > 5)           h.cutflow[1]->Fill((int)1, wt);
  if(Muon.at(0).v.Pt() > 10)     h.cutflow[1]->Fill((int)2, wt);
  if(Muon.at(0).v.Pt() > 15)     h.cutflow[1]->Fill((int)3, wt);
  if(Muon.at(0).v.Pt() > 20)     h.cutflow[1]->Fill((int)4, wt);
  
  if(Muon.at(0).reliso04 < 0.50)      h.cutflow[1]->Fill((int)5, wt);
  if(Muon.at(0).reliso04 < 0.30) h.cutflow[1]->Fill((int)6, wt);
  if(Muon.at(0).reliso04 < 0.20) h.cutflow[1]->Fill((int)7, wt);
  if(Muon.at(0).reliso04 < 0.15) h.cutflow[1]->Fill((int)8, wt);

  if(Muon.at(0).sip3d < 10)           h.cutflow[1]->Fill((int)9, wt);
  if(Muon.at(0).sip3d < 5.0)     h.cutflow[1]->Fill((int)10, wt);
  if(Muon.at(0).sip3d < 3.0)     h.cutflow[1]->Fill((int)11, wt);
  if(Muon.at(0).sip3d < 2.5)     h.cutflow[1]->Fill((int)12, wt);

  //Investigating cuts on the ss muon:
  if(Muon.at(ss_ind).v.Pt() > 5)           h.cutflow[2]->Fill((int)1, wt);
  if(Muon.at(ss_ind).v.Pt() > 10)     h.cutflow[2]->Fill((int)2, wt);
  if(Muon.at(ss_ind).v.Pt() > 15)     h.cutflow[2]->Fill((int)3, wt);
  if(Muon.at(ss_ind).v.Pt() > 20)     h.cutflow[2]->Fill((int)4, wt);
  
  if(Muon.at(ss_ind).reliso04 < 0.50)      h.cutflow[2]->Fill((int)5, wt);
  if(Muon.at(ss_ind).reliso04 < 0.30) h.cutflow[2]->Fill((int)6, wt);
  if(Muon.at(ss_ind).reliso04 < 0.20) h.cutflow[2]->Fill((int)7, wt);
  if(Muon.at(ss_ind).reliso04 < 0.15) h.cutflow[2]->Fill((int)8, wt);

  if(Muon.at(ss_ind).sip3d < 10)           h.cutflow[2]->Fill((int)9, wt);
  if(Muon.at(ss_ind).sip3d < 5.0)     h.cutflow[2]->Fill((int)10, wt);
  if(Muon.at(ss_ind).sip3d < 3.0)     h.cutflow[2]->Fill((int)11, wt);
  if(Muon.at(ss_ind).sip3d < 2.5)     h.cutflow[2]->Fill((int)12, wt);
}
