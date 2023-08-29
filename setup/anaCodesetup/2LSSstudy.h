void VLLAna::Make2LSSPlots(float wt){

  //Picking the samesign pair:
  //The first one is the leading one.
  //The index of the second one is calculated below.
  int ss=-1;
  for(int i=1; i<(int)llep.size(); i++){
    if(llep.at(0).charge == llep.at(i).charge){
      ss = i;
      break;
    }
  }

  //-------------------------
  // Constructing variables:
  //-------------------------
  
  //Leading lepton:
  float mt0 = transv_mass(llep.at(0).v.E(), llep.at(0).v.Phi(), metpt, metphi);

  //Other lepton:
  float mtss = transv_mass(llep.at(ss).v.E(), llep.at(ss).v.Phi(), metpt, metphi);

  //dilepton system:
  TLorentzVector dilep = llep.at(0).v + llep.at(ss).v;
  float dilep_mass = dilep.M();
  float deta_llep = fabs(llep.at(0).v.Eta() - llep.at(ss).v.Eta());
  float dphi_llep = delta_phi(llep.at(0).v.Phi(), llep.at(ss).v.Phi());
  float dR_llep = llep.at(0).v.DeltaR(llep.at(ss).v);
  float ptratio = llep.at(ss).v.Pt() / llep.at(0).v.Pt();
  
  //Event level:
  int nllep = (int)llep.size();
  int njet = (int)jets.size();
  int nbjet = (int)BTaggedJet.size();
  float LT=0; for(int i=0; i<(int)llep.size(); i++) LT = LT + llep.at(i).v.Pt();
  float HT=0; for(int i=0; i<(int)jets.size(); i++) HT = HT + jets.at(i).v.Pt();
  float ST=LT+HT;
  float STfrac = 0; if(ST>0) STfrac = LT/ST;
  float dphi_met0 = delta_phi(llep.at(0).v.Phi(), metphi);
  float dphi_metss = delta_phi(llep.at(ss).v.Phi(), metphi);

  //---------------------
  // Event selections :
  //---------------------

  bool nonIsoEvts = 0.70 < llep.at(0).reliso03 && llep.at(0).reliso03 < 1;
  bool Isollep0 = llep.at(0).reliso03 < 0.10;
  bool additional = (llep.at(0).sip3d < 2.0 &&
		     llep.at(ss).reliso03 < 0.2 &&
		     llep.at(ss).sip3d < 3.0 &&
		     HT < 500 &&
		     50 < LT && LT < 500 &&
		     nbjet < 3 &&
		     llep.at(0).v.Pt() > 30
		     );
  

  bool event_selection = Isollep0 && additional;

  //Cutflow:
  h.cutflow[0]->Fill((int)0, wt); //All pre-selected events
  if(Isollep0){
    h.cutflow[0]->Fill((int)1, wt); //Isolated llep0 in pre-selected events
    if(llep.at(0).sip3d < 2.0){
      h.cutflow[0]->Fill((int)2, wt); //Aggressive
      if(llep.at(ss).reliso03 < 0.2){
	h.cutflow[0]->Fill((int)3, wt); //Aggressive
	if(llep.at(ss).sip3d < 3.0){
	  h.cutflow[0]->Fill((int)4, wt);
	  if(HT < 500){
	    h.cutflow[0]->Fill((int)5, wt);
	    if(50 < LT && LT < 500){
	      h.cutflow[0]->Fill((int)6, wt);
	      if(nbjet < 3){
		h.cutflow[0]->Fill((int)7, wt);
		if(llep.at(0).v.Pt() > 30){
		  h.cutflow[0]->Fill((int)8, wt);
		}
	      }
	    }
	  }
	}
      }
    }
  }
  
  if(nonIsoEvts){//Put selections here
    nEvtPass++;
    
    //leading lepton plots:
    h.studySS[0]->Fill(llep.at(0).v.Pt(),  wt);
    h.studySS[1]->Fill(llep.at(0).v.Eta(), wt);
    h.studySS[2]->Fill(llep.at(0).v.Phi(), wt);
    h.studySS[3]->Fill(mt0, wt);
    h.studySS[4]->Fill(llep.at(0).reliso03, wt);
    h.studySS[5]->Fill(llep.at(0).sip3d,    wt);

    //samesign lepton plots:
    h.studySS[6]->Fill(llep.at(ss).v.Pt(),  wt);
    h.studySS[7]->Fill(llep.at(ss).v.Eta(), wt);
    h.studySS[8]->Fill(llep.at(ss).v.Phi(), wt);
    h.studySS[9]->Fill(mtss, wt);
    h.studySS[10]->Fill(llep.at(ss).reliso03, wt);
    h.studySS[11]->Fill(llep.at(ss).sip3d,    wt);

    //dilepton system plots:
    h.studySS[12]->Fill(dilep_mass, wt);
    h.studySS[13]->Fill(deta_llep, wt);
    h.studySS[14]->Fill(dphi_llep, wt);
    h.studySS[15]->Fill(dR_llep, wt);
    h.studySS[16]->Fill(ptratio, wt);

    //event level plots:
    h.studySS[17]->Fill(nllep, wt);
    h.studySS[18]->Fill(njet,  wt);
    h.studySS[19]->Fill(nbjet, wt);
    h.studySS[20]->Fill(metpt, wt);
    h.studySS[21]->Fill(metphi, wt);
    h.studySS[22]->Fill(LT, wt);
    h.studySS[23]->Fill(HT, wt);
    h.studySS[24]->Fill(ST, wt);
    h.studySS[25]->Fill(STfrac, wt);
    h.studySS[26]->Fill(dphi_met0, wt);
    h.studySS[27]->Fill(dphi_metss, wt);
    h.studySS[28]->Fill(max(dphi_met0, dphi_metss), wt);
    h.studySS[29]->Fill(min(dphi_met0, dphi_metss), wt);
  }

 
}
