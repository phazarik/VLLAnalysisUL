void VLLAna::Make2LPlots()
{
  //This function is called in the main VLLAna.C file.
  //It runs for all the 2L events.

  //Filling out different boxes:
  //bin0 -> n2L
  //bin1 -> OS
  //bin2 -> OSSF
  //bin3 -> OSOF
  //bin4 -> SS
  //bin5 -> SSSF
  //bin6 -> SSOF
  h.study2L[0]->Fill(0);//n2L

  //For opposite signed lepton pairs:
  if(llep.at(0).charge == -llep.at(1).charge){
    n_os++;
    h.study2L[0]->Fill(1);
    //for same flavoured pairs:
    if(fabs(llep.at(0).id) == fabs(llep.at(1).id)){
      n_ossf++;
      h.study2L[0]->Fill(2); //OSSF
    }
    else{
      //for different flavoured pairs:
      n_osof++;
      h.study2L[0]->Fill(3); //OSOF
    }
  }
  
  //For same signed lepton pairs:
  if(llep.at(0).charge == llep.at(1).charge){
    n_ss++;
    h.study2L[0]->Fill(4);//SS
    if(fabs(llep.at(0).id) == fabs(llep.at(1).id)){
      n_sssf++;
      h.study2L[0]->Fill(5); //SSSF
    }
    else{
      n_ssof++;
      h.study2L[0]->Fill(6); //SSOF
    }
  }

  //Kinematic variables for 2L events:
  h.study2L[1]->Fill(llep.at(0).v.Pt());
  h.study2L[2]->Fill(llep.at(0).v.Eta());
  h.study2L[3]->Fill(llep.at(0).v.Phi());
  h.study2L[4]->Fill(llep.at(1).v.Pt());
  h.study2L[5]->Fill(llep.at(1).v.Eta());
  h.study2L[6]->Fill(llep.at(1).v.Phi());

  float dphi_llep = delta_phi(llep.at(0).v.Phi(), llep.at(1).v.Phi());
  float dR_llep = llep.at(0).v.DeltaR(llep.at(1).v);
  float deta_llep = fabs(llep.at(0).v.Eta() - llep.at(1).v.Eta());
  float dilep_mass = (llep.at(0).v+llep.at(1).v).M();
  h.study2L[7]->Fill(deta_llep);
  h.study2L[8]->Fill(dphi_llep);
  h.study2L[9]->Fill(dR_llep);
  h.study2L[10]->Fill(dilep_mass);

  h.study2L[11]->Fill(metpt);
  h.study2L[12]->Fill(metphi);
  float lep0mT = transv_mass(llep.at(0).v.E(), llep.at(0).v.Phi(), metpt, metphi);
  float lep1mT = transv_mass(llep.at(1).v.E(), llep.at(1).v.Phi(), metpt, metphi);
  h.study2L[13]->Fill(lep0mT);
  h.study2L[14]->Fill(lep1mT);

  //To reduce QCD:
  float dphi1 = delta_phi(llep.at(0).v.Phi(), metphi);
  float dphi2 = delta_phi(llep.at(1).v.Phi(), metphi);
  float sumcosdphi = cos(dphi1) + cos(dphi2);
  h.study2L[15]->Fill(sumcosdphi);
}
