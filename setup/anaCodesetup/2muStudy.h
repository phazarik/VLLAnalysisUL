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
}
