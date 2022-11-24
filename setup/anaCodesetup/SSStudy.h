void VLLAna::MakeSSPlots()
{
  //This section runs for 2L(incl) events
  //We need 3 boxes - all 2L events, OS events, SS events.
  h.studySS[0]->Fill((int)llep.size());
  h.studySS[1]->Fill(0);
  bool samesign = false;

  /*
  if((int)llep.size() == 2){
    if(llep.at(0).charge == llep.at(1).charge) samesign = true;
  }
  else if((int)llep.size() > 2){
    //If there are three or more leptons, we make same-sign pair of the first three.
    if(llep.at(0).charge == llep.at(1).charge) samesign = true;
    else if(llep.at(0).charge == llep.at(2).charge) samesign = true;
    else if(llep.at(1).charge == llep.at(2).charge) samesign = true;
    }*/

  if(llep.at(0).charge == llep.at(1).charge) samesign = true; 
  if(!samesign) h.studySS[1]->Fill(1);
  if(samesign) h.studySS[1]->Fill(2);

  //Derived variables:
  float dphi_llep = delta_phi(llep.at(0).v.Phi(), llep.at(1).v.Phi());
  float dR_llep = llep.at(0).v.DeltaR(llep.at(1).v);
  float deta_llep = fabs(llep.at(0).v.Eta() - llep.at(1).v.Eta());
  float dilep_mass = (llep.at(0).v+llep.at(1).v).M(); 
  float lep0mT = transv_mass(llep.at(0).v.E(), llep.at(0).v.Phi(), metpt, metphi);
  float lep1mT = transv_mass(llep.at(1).v.E(), llep.at(1).v.Phi(), metpt, metphi);

  //Make plots for the SS events:
  if(samesign){
    h.studySS[2]->Fill(llep.at(0).v.Pt());
    h.studySS[3]->Fill(llep.at(0).v.Eta());
    h.studySS[4]->Fill(llep.at(0).v.Phi());
    h.studySS[5]->Fill(llep.at(1).v.Pt());
    h.studySS[6]->Fill(llep.at(1).v.Eta());
    h.studySS[7]->Fill(llep.at(1).v.Phi());  
    h.studySS[8]->Fill(deta_llep);
    h.studySS[9]->Fill(dphi_llep);
    h.studySS[10]->Fill(dR_llep);
    h.studySS[11]->Fill(dilep_mass);
    h.studySS[12]->Fill(metpt);
    h.studySS[13]->Fill(metphi);
    h.studySS[14]->Fill(lep0mT);
    h.studySS[15]->Fill(lep1mT);
  }
  
  if(!samesign){
    h.studyOS[0]->Fill(llep.at(0).v.Pt());
    h.studyOS[1]->Fill(llep.at(0).v.Eta());
    h.studyOS[2]->Fill(llep.at(0).v.Phi());
    h.studyOS[3]->Fill(llep.at(1).v.Pt());
    h.studyOS[4]->Fill(llep.at(1).v.Eta());
    h.studyOS[5]->Fill(llep.at(1).v.Phi());  
    h.studyOS[6]->Fill(deta_llep);
    h.studyOS[7]->Fill(dphi_llep);
    h.studyOS[8]->Fill(dR_llep);
    h.studyOS[9]->Fill(dilep_mass);
    h.studyOS[10]->Fill(metpt);
    h.studyOS[11]->Fill(metphi);
    h.studyOS[12]->Fill(lep0mT);
    h.studyOS[13]->Fill(lep1mT);
  }
  


}
