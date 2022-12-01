void VLLAna::Make2muPlots()
{
  //This function is called in the main VLLAna.C file.
  //It runs for all the 2Mu events.

  //Filling out different boxes:
  //bin0 -> n2L
  //bin1 -> OS
  //bin2 -> OSSF
  //bin3 -> OSOF
  //bin4 -> SS
  //bin5 -> SSSF
  //bin6 -> SSOF
  /*
  h.study2mu[0]->Fill(0);//n2L

  //For opposite signed lepton pairs:
  if(Muon.at(0).charge == -Muon.at(1).charge){
    n_os++;
    h.study2mu[0]->Fill(1);
    //for same flavoured pairs:
    if(fabs(Muon.at(0).id) == fabs(Muon.at(1).id)){
      n_ossf++;
      h.study2mu[0]->Fill(2); //OSSF
    }
    else{
      //for different flavoured pairs:
      n_osof++;
      h.study2mu[0]->Fill(3); //OSOF
    }
  }
  
  //For same signed lepton pairs:
  if(Muon.at(0).charge == Muon.at(1).charge){
    n_ss++;
    h.study2mu[0]->Fill(4);//SS
    if(fabs(Muon.at(0).id) == fabs(Muon.at(1).id)){
      n_sssf++;
      h.study2mu[0]->Fill(5); //SSSF
    }
    else{
      n_ssof++;
      h.study2mu[0]->Fill(6); //SSOF
    }
  }

  //Kinematic variables for 2L events:
  h.study2mu[1]->Fill(Muon.at(0).v.Pt());
  h.study2mu[2]->Fill(Muon.at(0).v.Eta());
  h.study2mu[3]->Fill(Muon.at(0).v.Phi());
  h.study2mu[4]->Fill(Muon.at(1).v.Pt());
  h.study2mu[5]->Fill(Muon.at(1).v.Eta());
  h.study2mu[6]->Fill(Muon.at(1).v.Phi());

  float dphi_muon = delta_phi(Muon.at(0).v.Phi(), Muon.at(1).v.Phi());
  float dR_muon = Muon.at(0).v.DeltaR(Muon.at(1).v);
  float deta_muon = fabs(Muon.at(0).v.Eta() - Muon.at(1).v.Eta());
  float dimuonmass = (Muon.at(0).v+Muon.at(1).v).M();
  h.study2mu[7]->Fill(deta_muon);
  h.study2mu[8]->Fill(dphi_muon);
  h.study2mu[9]->Fill(dR_muon);
  h.study2mu[10]->Fill(dimuonmass);

  h.study2mu[11]->Fill(metpt);
  h.study2mu[12]->Fill(metphi);
  float mu0_mT = transv_mass(Muon.at(0).v.E(), Muon.at(0).v.Phi(), metpt, metphi);
  float mu1_mT = transv_mass(Muon.at(1).v.E(), Muon.at(1).v.Phi(), metpt, metphi);
  h.study2mu[13]->Fill(mu0_mT);
  h.study2mu[14]->Fill(mu1_mT);

  //Dimuon mass zoomed in:
  if(60<dimuonmass && dimuonmass<120)
    h.study2mu[15]->Fill(dimuonmass);

  //To reduce QCD:
  float dphi1 = delta_phi(Muon.at(0).v.Phi(), metphi);
  float dphi2 = delta_phi(Muon.at(1).v.Phi(), metphi);
  float sumcosdphi = cos(dphi1) + cos(dphi2);
  h.study2mu[16]->Fill(sumcosdphi);*/

  //#######################################
  //Dedicated 2mu study.

  //Defining how SS and OS boxes are filled:
  bool samesign = false;
  /*;
  for(int i=0; i<(int)Muon.size(); i++){
    if(i!=0 && Muon.at(0).charge == Muon.at(i).charge) samesign = true;
    else if(i!=1 && Muon.at(1).charge == Muon.at(i).charge) samesign = true;
    }*/
  for(int i=0; i<(int)Muon.size(); i++){
    for(int j=0; j<(int)Muon.size(); j++){
      if(i!=j && Muon.at(i).charge == Muon.at(j).charge) samesign = true;
    }
  }

  //Derived quantities:
  float dphi_muon = delta_phi(Muon.at(0).v.Phi(), Muon.at(1).v.Phi());
  float dR_muon = Muon.at(0).v.DeltaR(Muon.at(1).v);
  float deta_muon = fabs(Muon.at(0).v.Eta() - Muon.at(1).v.Eta());
  float dimuonmass = (Muon.at(0).v+Muon.at(1).v).M();
  float mu0_mT = transv_mass(Muon.at(0).v.E(), Muon.at(0).v.Phi(), metpt, metphi);
  float mu1_mT = transv_mass(Muon.at(1).v.E(), Muon.at(1).v.Phi(), metpt, metphi);
  //To reduce QCD:
  float dphi1 = delta_phi(Muon.at(0).v.Phi(), metphi);
  float dphi2 = delta_phi(Muon.at(1).v.Phi(), metphi);
  float sumcosdphi = cos(dphi1) + cos(dphi2);

  //#####################
  //2mu inclusive events:
  //#####################
  h.study2L[0]->Fill(0);
  h.study2L[1]->Fill(Muon.at(0).v.Pt());
  h.study2L[2]->Fill(Muon.at(0).v.Eta());
  h.study2L[3]->Fill(Muon.at(0).v.Phi());
  h.study2L[4]->Fill(Muon.at(1).v.Pt());
  h.study2L[5]->Fill(Muon.at(1).v.Eta());
  h.study2L[6]->Fill(Muon.at(1).v.Phi());
  h.study2L[7]->Fill(deta_muon);
  h.study2L[8]->Fill(dphi_muon);
  h.study2L[9]->Fill(dR_muon);
  h.study2L[10]->Fill(dimuonmass);
  h.study2L[11]->Fill(metpt);
  h.study2L[12]->Fill(metphi);
  h.study2L[13]->Fill(mu0_mT);
  h.study2L[14]->Fill(mu1_mT);
  h.study2L[15]->Fill(sumcosdphi);

  //################
  //Opposite Sign Events:
  //################
  if(!samesign){
    h.study2L[0]->Fill(1);
    h.studyOS[0]->Fill(Muon.at(0).v.Pt());
    h.studyOS[1]->Fill(Muon.at(0).v.Eta());
    h.studyOS[2]->Fill(Muon.at(0).v.Phi());
    h.studyOS[3]->Fill(Muon.at(1).v.Pt());
    h.studyOS[4]->Fill(Muon.at(1).v.Eta());
    h.studyOS[5]->Fill(Muon.at(1).v.Phi());
    h.studyOS[6]->Fill(deta_muon);
    h.studyOS[7]->Fill(dphi_muon);
    h.studyOS[8]->Fill(dR_muon);
    h.studyOS[9]->Fill(dimuonmass);
    h.studyOS[10]->Fill(metpt);
    h.studyOS[11]->Fill(metphi);
    h.studyOS[12]->Fill(mu0_mT);
    h.studyOS[13]->Fill(mu1_mT);
    h.studyOS[14]->Fill(sumcosdphi);
  }
  if(samesign){
    h.study2L[0]->Fill(2);
    h.studySS[0]->Fill(Muon.at(0).v.Pt());
    h.studySS[1]->Fill(Muon.at(0).v.Eta());
    h.studySS[2]->Fill(Muon.at(0).v.Phi());
    h.studySS[3]->Fill(Muon.at(1).v.Pt());
    h.studySS[4]->Fill(Muon.at(1).v.Eta());
    h.studySS[5]->Fill(Muon.at(1).v.Phi());
    h.studySS[6]->Fill(deta_muon);
    h.studySS[7]->Fill(dphi_muon);
    h.studySS[8]->Fill(dR_muon);
    h.studySS[9]->Fill(dimuonmass);
    h.studySS[10]->Fill(metpt);
    h.studySS[11]->Fill(metphi);
    h.studySS[12]->Fill(mu0_mT);
    h.studySS[13]->Fill(mu1_mT);
    h.studySS[14]->Fill(sumcosdphi);    
  }
}
