void VLLAna::EstimateFakeRate(float wt){
  /*Note:
    This function is called inside the process() of VLLAna.C
    
    Here is my strategy. First, I will create the loose and the tight objects and store them in looseObj and tightObj. (Muons in this case).
    Then, I will select photon+looseObj events and check how many of them pass the Photon+tightObj selection.

    FakeRate = nEvt(Photon+tightObj)/nEvt(Photon+looseObj) 
  */

  //###################
  // Object selection :
  //###################
  looseObj.clear();
  tightObj.clear();
  
  for(unsigned int i=0; i< (*nMuon); i++){
    Lepton temp; temp.v.SetPtEtaPhiM(Muon_pt[i],Muon_eta[i],Muon_phi[i],0.105); 
    temp.id = -13*Muon_charge[i]; temp.ind = i;  temp.charge = Muon_charge[i];
    temp.sip3d = Muon_sip3d[i];
    temp.reliso03 = Muon_pfRelIso03_all[i];
    temp.reliso04 = Muon_pfRelIso04_all[i];
    
    //Making plots to check the variables before object selection:
    h.fakerate[0]->Fill(Muon_pt[i], wt);
    h.fakerate[1]->Fill(Muon_eta[i], wt);
    h.fakerate[2]->Fill(Muon_pfRelIso04_all[i], wt);
    h.fakerate[3]->Fill(Muon_looseId[i], wt);
    h.fakerate[4]->Fill(Muon_mediumId[i], wt);
    h.fakerate[5]->Fill(Muon_dxy[i], wt);
    h.fakerate[6]->Fill(Muon_dz[i], wt);

    bool ptetacut = temp.v.Pt()>10 && fabs(temp.v.Eta())<2.4;
    bool prompt = fabs(Muon_dxy[i])<0.05 && fabs(Muon_dz[i])<0.1;
    
    bool passcut_loosemuon =  Muon_pfRelIso04_all[i]<0.30 && Muon_looseId[i];
    bool passcut_tightmuon =  Muon_pfRelIso04_all[i]<0.25 && Muon_mediumId[i] && prompt;

    if(ptetacut && passcut_loosemuon) looseObj.push_back(temp);
    if(ptetacut && passcut_tightmuon) tightObj.push_back(temp);
  }//end of object selection


  //Kinematics of the loose and the tight objects:
  h.fakerate[7]->Fill((int)Photon.size(), wt);
  h.fakerate[8]->Fill((int)looseObj.size(), wt);
  h.fakerate[9]->Fill((int)tightObj.size(), wt);
  
  
  //#################
  // Event selection:
  //#################
  bool isPhoNLooseEvt = false;
  bool isPhoNTightEvt = false;
  if((int)Photon.size() == 1 && (int)looseObj.size()==1){
    isPhoNLooseEvt = true;
    n_pho_loose_evt ++;
  }
  if((int)Photon.size() == 1 && (int)tightObj.size()==1){
    isPhoNTightEvt = true;
    n_pho_tight_evt ++;
  }

  

  //##################
  // Filling up plots:
  //##################

  
  
  
}//end of function
