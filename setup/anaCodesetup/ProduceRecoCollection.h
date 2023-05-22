/*===================================
   Producing Reco Collections

=====================================
        Documentation
       ~~~~~~~~~~~~~~~
This header file has functions that should create

1.Muon Array
2.Electron Array
3.Tau Array
4.Jets Array
5.BTaggedJet Array
  
*/

//Code Starts
int nmu = 0, nel = 0, nph=0, n4l=0;

//MUONS
void VLLAna::RecoLightLepton(){
  //h.nlep[0]->Fill(*nMuon);
  for(unsigned int i=0; i< (*nMuon); i++){
    Lepton temp; temp.v.SetPtEtaPhiM(Muon_pt[i],Muon_eta[i],Muon_phi[i],0.105); 
    temp.id = -13*Muon_charge[i]; temp.ind = i;  temp.charge = Muon_charge[i];
    temp.sip3d = Muon_sip3d[i];
    temp.reliso03 = Muon_pfRelIso03_all[i];
    temp.reliso04 = Muon_pfRelIso04_all[i];
    
    //h.ptlep[0]->Fill(temp.v.Pt());
    //h.mucut->Fill(9);
	
    bool passcut_loosemuon = temp.v.Pt()>10 && fabs(temp.v.Eta())<2.4 && Muon_pfRelIso04_all[i]<0.30 && Muon_looseId[i];
    if(passcut_loosemuon)
      LooseLep.push_back(temp),loosemuon.push_back(temp);
      
    bool is_promptmuon= fabs(Muon_dxy[i])<0.05 && fabs(Muon_dz[i])<0.1;
    bool passcutmu = temp.v.Pt()>10 && fabs(temp.v.Eta())<2.4 && Muon_mediumId[i];
    //&& Muon_pfRelIso04_all[i]<0.25;
    //bool sipCut = Muon_sip3d[i]<30.0;
    //Isolation on the muon is removed.
    
    bool analysisCut= passcutmu && is_promptmuon;
	
    if(analysisCut){
      nmu++;
      //h.mucut->Fill(7);
      //h.ptlep[1]->Fill(temp.v.Pt());		
      Muon.push_back(temp);
      llep.push_back(temp);      
    }

    /*
    //cutflow(Debugging)
    if(temp.v.Pt()>10){//pt
      h.mucut->Fill(0);
      if(fabs(temp.v.Eta())<2.4){//eta
	h.mucut->Fill(1);
	if(fabs(Muon_dxy[i])<0.05 && fabs(Muon_dz[i])<0.1){//dxydz
	  h.mucut->Fill(2);
	  if(Muon_pfRelIso04_all[i]<0.30 && Muon_looseId[i]){//loose
	    h.mucut->Fill(3);
	    if(Muon_mediumId[i]){//medium
	      h.mucut->Fill(4);
	      if(Muon_pfRelIso04_all[i]<0.15){//PFIso
		h.mucut->Fill(5);
	      }
	    }	    
	  }
	}
      }
    }
    */
	
  }//End of Muon Loop
  //h.nlep[1]->Fill(nmu);

  //ELECTRONS      
  //h.nlep[2]->Fill(*nElectron);
  for(unsigned int i=0; i< (*nElectron); i++){
    Lepton temp; temp.v.SetPtEtaPhiM(Electron_pt[i],Electron_eta[i],Electron_phi[i],0.000511); 
    temp.id = -11*Electron_charge[i]; temp.ind = i; temp.charge = Electron_charge[i];temp.muoncleaning=MuonCleaning(temp.v,0);//0=loosemuon,1=muon
    bool isprompt = false;
    if(fabs(temp.v.Eta())<=1.479){
      if(fabs(Electron_dxy[i])<0.05 && fabs(Electron_dz[i])<0.1)
	isprompt = true;
    }
    if(fabs(temp.v.Eta())>1.479){
      if(fabs(Electron_dxy[i])<0.1 && fabs(Electron_dz[i])<0.2)
	isprompt = true;
    }
    //h.ptlep[2]->Fill(temp.v.Pt());
    //h.elcut->Fill(9);
    
    bool passcut_looseele = temp.v.Pt()>10 && fabs(temp.v.Eta())<2.4 && Electron_cutBased[i]>1; //Loose electron
    if(passcut_looseele)
      LooseLep.push_back(temp);
    
    
    bool passcut_ele_cutbased = temp.v.Pt()>10 && fabs(temp.v.Eta())<2.4 && Electron_cutBased[i]>2;//medium cutbased ID ele
    bool sipCut = Electron_sip3d[i]<30.0; 
    bool analysisCut= passcut_ele_cutbased && isprompt && temp.muoncleaning; //Not using SIP Cut right now
    
    if(analysisCut){
      nel++;
      //h.ptlep[3]->Fill(temp.v.Pt());
      Electron.push_back(temp);
      llep.push_back(temp);
    }
    
    
    //cutflow(Debugging)
    /*
    if(temp.v.Pt()>10){//pt
      h.elcut->Fill(0);
      if(fabs(temp.v.Eta())<2.4){//eta
	h.elcut->Fill(1);
	if(isprompt){//dxydz
	  h.elcut->Fill(2);
	  if(Electron_cutBased[i]>1){//looseID
	    h.elcut->Fill(3);
	    if(Electron_cutBased[i]>2){//mediumID
	      h.elcut->Fill(4);
	      if(temp.muoncleaning){//loosemuon cleaning[dr(ele,loosemuon)>0.05]
		h.elcut->Fill(5);
		//llep.push_back(temp);
	      }
	    }	    
	  }
	}
      }
    }
    */
  } //electron loop ends
  //h.nlep[3]->Fill(nel);
}      
      

void VLLAna:: RecoPhoton(){
  //h.nlep[6]->Fill(*nPhoton);
  for(unsigned int i=0; i< (*nPhoton); i++){ 
    Lepton temp; temp.v.SetPtEtaPhiM(Photon_pt[i],Photon_eta[i],Photon_phi[i],0); 
    temp.id = 22*Photon_charge[i]; temp.ind = i;
    //h.ptlep[7]->Fill(temp.v.Pt());
    
    bool ptetacuts = temp.v.Pt()>50 && temp.v.Eta()<2.4;
    bool passcuts = ptetacuts && Photon_pfRelIso03_all[i]<0.15;
    if(passcuts) Photon.push_back(temp);
  
    //CutFlow
    //h.phocut->Fill(9);
    if(temp.v.Pt()>10){
      //h.phocut->Fill(0);
      if(fabs(temp.v.Eta())<2.4){
	//h.phocut->Fill(1);
	if(Photon_pfRelIso03_all[i]<0.15){
	  //h.phocut->Fill(3);
	  //Photon.push_back(temp);
	  if(Photon_mvaID[i]){
	    nph++;
	    //h.phocut->Fill(4);
	    //h.ptlep[8]->Fill(temp.v.Pt());
	    //Photon.push_back(temp);
	  }
	}	    
      }
    }
  }
}

void VLLAna:: RecoTau(){
  //h.nlep[4]->Fill(*nTau);
  for(unsigned int i=0; i< (*nTau); i++){
    //h.taucut->Fill(0);
    if(Tau_decayMode[i]&&(Tau_decayMode[i]<3||Tau_decayMode[i]>9)){
      //Tau energy scale correction
      float tlv_corr = 1.;
      if(_year==2016){
	if(Tau_decayMode[i]==0)
	  tlv_corr = 0.994;
	if(Tau_decayMode[i]==1)
	  tlv_corr = 0.995;
	if(Tau_decayMode[i]>9)
	  tlv_corr = 1;
      }
      if(_year==2017){
	if(Tau_decayMode[i]==0)
	  tlv_corr = 1.007;
	if(Tau_decayMode[i]==1)
	  tlv_corr = 0.998;
	if(Tau_decayMode[i]==10)
	  tlv_corr = 1.001;
	if(Tau_decayMode[i]==11)
	  tlv_corr = 0.999;
      }
      if(_year==2018){
	if(Tau_decayMode[i]==0)
	  tlv_corr = 0.987;
	if(Tau_decayMode[i]==1)
	  tlv_corr = 0.995;
	if(Tau_decayMode[i]==10)
	  tlv_corr = 0.998;
	if(Tau_decayMode[i]==11)
	  tlv_corr = 1;
      }
      Lepton temp; temp.v.SetPtEtaPhiM(Tau_pt[i],Tau_eta[i],Tau_phi[i],1.77);
      //h.ptlep[4]->Fill(temp.v.Pt());
      temp.v *= tlv_corr; //energy correction
      temp.id = -15*Tau_charge[i]; temp.ind = i; temp.charge = Tau_charge[i];
      temp.lepcleaning = TaulepCleaning(temp.v); //haven't found any lepton in the direction of Tau
      //h.ptlep[5]->Fill(temp.v.Pt());
      //h.taucut->Fill(9);
	  
      bool passcut=temp.v.Pt()>20 && fabs(temp.v.Eta())<2.3;
      passcut = passcut && temp.lepcleaning && fabs(Tau_dz[i]<0.2);
      bool DeepTauID= Tau_idDeepTau2017v2p1VSe[i]>15 && Tau_idDeepTau2017v2p1VSmu[i]>3 && Tau_idDeepTau2017v2p1VSjet[i]>127;
	  
      //bool passcut=true;
      //bool DeepTauID=true;
      //bool DeepTauID=Tau_idDeepTau2017v2p1VSjet[i]>15;//Just Loose DeepCSVAntiJet
      bool analysisCut= passcut && DeepTauID;
	  
      // bool analysisCut= true;
      //taus.push_back(temp);
      if(analysisCut){
	taus.push_back(temp);
	//h.ptlep[6]->Fill(temp.v.Pt());
      }
	  
	  
      //Tau FlowChart
      //Start With New DM finding Taus
      /* 
      h.taucut->Fill(1);//Tau Satisfying New DecayMode
      if(Tau_idDeepTau2017v2p1VSjet[i]>15){//Loose DeepCSV
	h.taucut->Fill(2);
	if(Tau_idDeepTau2017v2p1VSe[i]>15){//Loose AntiEle
	  h.taucut->Fill(3);
	  if(Tau_idDeepTau2017v2p1VSmu[i]>3){//Loose AntiMu
	    h.taucut->Fill(4);
	    if(fabs(Tau_dz[i]<0.2)){//Prompt Cut
	      h.taucut->Fill(5);
	      if(temp.lepcleaning){//LooseLepton Cleaning
		h.taucut->Fill(6);
		if(fabs(temp.v.Eta())<2.3){// |n|<2.3 Cut
		  h.taucut->Fill(7);
		  if(temp.v.Pt()>20){//PT>20GeV Cut
		    h.taucut->Fill(8);
		  }
		}
	      }
	    }
	  }
	}
      }
      */
    }
  }
  //h.nlep[5]->Fill((int)taus.size());
   
}

void VLLAna::RecoJetandBJets(){
  // h.njet[0]->Fill(nJet);
  for(unsigned int i=0; i< (*nJet); i++){
    Lepton temp; temp.v.SetPtEtaPhiM(Jet_pt[i],Jet_eta[i],Jet_phi[i],Jet_mass[i]);
    temp.ind = i;temp.taucleaning=TaujetCleaning(temp.v);temp.lepcleaning=LepjetCleaning(temp.v); // No jet in the direction of tau
    //h.ptjet[0]->Fill(temp.v.Pt());
    temp.deepBscore = Jet_btagDeepB[i];
    bool passcut =temp.v.Pt()>20 && fabs(temp.v.Eta())<2.4 && temp.taucleaning && temp.lepcleaning; //PF Tight Jet ID: bit 2
    //if(passcut)
    //jets.push_back(temp);
    if(passcut){
      if(_year == 2016 ? Jet_jetId[i]>=1 : Jet_jetId[i]>=2){
	jets.push_back(temp);
	if(Jet_btagDeepB[i]>0.4184)   //B tag discriminator medium working point(float variable)
	  {
	    BTaggedJet.push_back(temp);
	  }
      }
    }
  }

}



