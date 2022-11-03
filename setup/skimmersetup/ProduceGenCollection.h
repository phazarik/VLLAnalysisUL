//#include "VLLAna.h" 

// CREATE GEN LEPTON COLLECTIONS

//Gen Muon
void VLLAna::GenMuon()
{
  int grandmomid=-1;
  h.genPart[0]->Fill(*nGenPart);
  for(unsigned int i=0; i< (*nGenPart); i++){
    Lepton temp; temp.v.SetPtEtaPhiM(GenPart_pt[i],GenPart_eta[i],GenPart_phi[i],GenPart_mass[i]);temp.status = GenPart_status[i]; temp.ind = i;temp.pdgid = GenPart_pdgId[i];temp.momid=MotherID(i,GenPart_genPartIdxMother[i]);
    
    bool passcutmu= abs(temp.pdgid)==13 && temp.status==1 && temp.v.Pt()>5 && fabs(temp.v.Eta())<2.4;
    bool motherisnotmu= abs(MotherID(i,GenPart_genPartIdxMother[i]))!=13 && GenPart_pdgId[GenPart_genPartIdxMother[i]]!=22;
    bool promptdecay= abs(temp.momid)==15 ||abs(temp.momid)==23||abs(temp.momid)==24||abs(temp.momid)==25||(abs(temp.momid)>0 && abs(temp.momid)<7);
    bool WZbosondecay=false;bool ttzdecay=false;
    if(promptdecay){
      if(abs(temp.momid)==24 || abs(temp.momid)==23|| abs(temp.momid)==15){ttzdecay=true;
	int grandmomid=MotherID(GenPart_genPartIdxMother[i],GenPart_genPartIdxMother[GenPart_genPartIdxMother[i]]);
	//cout<<"GrandMom ID="<<grandmomid<<endl;
	if((abs(grandmomid)>0 && abs(grandmomid)<7))
	  WZbosondecay=true;    //Interested in very specific decay: W->l nu, Z->ll, mother is W or Z and grandmother should be a quark
      }
    }
    passcutmu = passcutmu && motherisnotmu && promptdecay; 
    
    if(passcutmu){     	
      genMuon.push_back(temp);
      genllep.push_back(temp);
      //h.genPart[1]->Fill(genMuon.size());
      h.genpltmu[1]->Fill(temp.v.Pt());
      h.genpltmu[2]->Fill(temp.v.Eta());
      h.genpltmu[3]->Fill(temp.v.Phi());
      h.genpltmu[4]->Fill(MotherID(i,GenPart_genPartIdxMother[i]));
    }
    
    
  }
}

//Gen Electron
void VLLAna::GenElectron()
{
  int grandmomid=-1;
  //h.genPart[0]->Fill(nGenPart);
  for(unsigned int i=0; i< (*nGenPart); i++){
    Lepton temp; temp.v.SetPtEtaPhiM(GenPart_pt[i],GenPart_eta[i],GenPart_phi[i],GenPart_mass[i]);temp.status = GenPart_status[i]; temp.ind = i;temp.pdgid = GenPart_pdgId[i];temp.momid=MotherID(i,GenPart_genPartIdxMother[i]);
    //GenElectron Block
    bool passcutele= abs(temp.pdgid)==11 && temp.status==1 && temp.v.Pt()>5 && fabs(temp.v.Eta())<2.4;
    bool motherisnotele= abs(MotherID(i,GenPart_genPartIdxMother[i]))!=11 && GenPart_pdgId[GenPart_genPartIdxMother[i]]!=22;
    bool promptdecay= abs(temp.momid)==15 ||abs(temp.momid)==23||abs(temp.momid)==24||abs(temp.momid)==25||(abs(temp.momid)>0 && abs(temp.momid)<7);
    bool WZbosondecay=false;bool ttzdecay=false;
    if(promptdecay){
      if(abs(temp.momid)==24 || abs(temp.momid)==23|| abs(temp.momid)==15){ttzdecay=true;
	int grandmomid=MotherID(GenPart_genPartIdxMother[i],GenPart_genPartIdxMother[GenPart_genPartIdxMother[i]]);
	if((abs(grandmomid)>0 && abs(grandmomid)<7))
	  WZbosondecay=true;    //Interested in very specific decay: W->l nu, Z->ll, mother is W or Z and grandmother should be a quark
      }
    }
    
    //Final selection
    passcutele = passcutele && motherisnotele && promptdecay; 
    
    if(passcutele){     	
      genElectron.push_back(temp);
      genllep.push_back(temp);
      h.genpltele[1]->Fill(temp.v.Pt());
      h.genpltele[2]->Fill(temp.v.Eta());
      h.genpltele[3]->Fill(temp.v.Phi());
      h.genpltele[4]->Fill(MotherID(i,GenPart_genPartIdxMother[i]));
    }
  }
}

// Visible Gen Tau
void VLLAna::GenVisTau()
{
  //nGenVisTau Collection
  //h.genhadtau[0]->Fill(nGenVisTau);
  for(unsigned int i=0; i< (*nGenVisTau); i++){
    Lepton temp; temp.v.SetPtEtaPhiM(GenVisTau_pt[i],GenVisTau_eta[i],GenVisTau_phi[i],GenVisTau_mass[i]);temp.status = GenVisTau_status[i]; temp.ind = i;  temp.pdgid = -15*GenVisTau_charge[i];temp.momid=MotherID(i,GenVisTau_genPartIdxMother[i]);
    bool passcut = temp.v.Pt()>5 && fabs(temp.v.Eta())<2.3;
    if(passcut){
      genHadronicTau.push_back(temp);
      h.genplttau[1]->Fill(temp.v.Pt());
      h.genplttau[2]->Fill(temp.v.Eta());
      h.genplttau[3]->Fill(temp.v.Phi());
      h.genplttau[4]->Fill(MotherID(i,GenPart_genPartIdxMother[i]));
    }
  } 
}

//GenJET Collection
void VLLAna::GenJet()
{
  for(unsigned int i=0; i< (*nGenJet); i++){
    Lepton temp; temp.v.SetPtEtaPhiM(GenJet_pt[i],GenJet_eta[i],GenJet_phi[i],GenPart_mass[i]);temp.partonflav=GenJet_partonFlavour[i];temp.hadronflav=GenJet_hadronFlavour[i];temp.bflav=IsbJet(temp.v);
    bool passcut=temp.v.Pt()>30 && temp.v.Eta()<2.4;
    //bool passcut=true;
    
    if(passcut)genjet.push_back(temp);        
  }
}
