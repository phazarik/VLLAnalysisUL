void VLLAna::Make2muPlots()
{
  //This function is called in the main VLLAna.C file.
  //It runs for all the 2Mu events.

  //Defining how SS and OS boxes are filled:
  bool samesign = false;
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
  //Finding the closest jet to the muons:
  float dRmin0 = 1000;
  float dRmin1 = 1000;
  float muon0_nearestJet_deepB = 2;
  float muon1_nearestJet_deepB = 2;
  for(int i=0; i<(int)jets.size(); i++){
    float dR_jet = Muon.at(0).v.DeltaR(jets.at(i).v);
    if(dR_jet < dRmin0){
      dRmin0 = dR_jet;
      muon0_nearestJet_deepB = jets.at(i).deepBscore;
    }
  }
  for(int i=0; i<(int)jets.size(); i++){
    float dR_jet = Muon.at(1).v.DeltaR(jets.at(i).v);
    if(dR_jet < dRmin1){
      dRmin1 = dR_jet;
      muon1_nearestJet_deepB = jets.at(i).deepBscore;
    }
  }

  //Further event selections:
  bool masscut = dimuonmass > 50 && dimuonmass < 300;
  bool mT0cut = mu0_mT > 50;
  bool mT1cut = mu1_mT > 50;
  bool dRcut = dR_muon < 3.5;
  bool metcut = metpt > 20;
  bool dEtacut = deta_muon < 3;
  bool vetoBjets =  (int)BTaggedJet.size()==0;

  bool passcuts = true;// masscut && mT0cut && mT1cut && dRcut && metcut && dEtacut;

  //Cutflow for the SS events:
  //bin0 = All the SS events
  //bin1 = SS events with cut 1
  //                 .. etc etc.
  if(samesign)                h.cutflow[0]->Fill(0);
  if(samesign && masscut)     h.cutflow[0]->Fill(1);
  if(samesign && mT0cut)      h.cutflow[0]->Fill(2);
  if(samesign && mT1cut)      h.cutflow[0]->Fill(3);
  if(samesign && dRcut)       h.cutflow[0]->Fill(4);
  if(samesign && metcut)      h.cutflow[0]->Fill(5);
  if(samesign && dEtacut)     h.cutflow[0]->Fill(6);
  if(samesign && vetoBjets)   h.cutflow[0]->Fill(7);
  
  if(passcuts){//Place the cuts here.
    //#####################
    //2mu inclusive events:
    //#####################
    //h.study2L[0]->Fill(0);
    h.study2L[0]->Fill(Muon.at(0).v.Pt());
    h.study2L[1]->Fill(Muon.at(0).v.Eta());
    h.study2L[2]->Fill(Muon.at(0).v.Phi());
    h.study2L[3]->Fill(Muon.at(1).v.Pt());
    h.study2L[4]->Fill(Muon.at(1).v.Eta());
    h.study2L[5]->Fill(Muon.at(1).v.Phi());
    h.study2L[6]->Fill(deta_muon);
    h.study2L[7]->Fill(dphi_muon);
    h.study2L[8]->Fill(dR_muon);
    h.study2L[9]->Fill(dimuonmass);
    h.study2L[10]->Fill(metpt);
    h.study2L[11]->Fill(metphi);
    h.study2L[12]->Fill(mu0_mT);
    h.study2L[13]->Fill(mu1_mT);
    h.study2L[14]->Fill(sumcosdphi);
    h.study2L[15]->Fill(Muon.at(0).sip3d);
    h.study2L[16]->Fill(Muon.at(0).reliso03);
    h.study2L[17]->Fill(Muon.at(0).reliso04);
    h.study2L[18]->Fill(Muon.at(1).sip3d);
    h.study2L[19]->Fill(Muon.at(1).reliso03);
    h.study2L[20]->Fill(Muon.at(1).reliso04);
    h.study2L[21]->Fill(muon0_nearestJet_deepB);
    h.study2L[22]->Fill(muon1_nearestJet_deepB);
    //################
    //Opposite Sign Events:
    //################
    if(!samesign){
      //h.study2L[0]->Fill(1);
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
      h.studyOS[15]->Fill(Muon.at(0).sip3d);
      h.studyOS[16]->Fill(Muon.at(0).reliso03);
      h.studyOS[17]->Fill(Muon.at(0).reliso04);
      h.studyOS[18]->Fill(Muon.at(1).sip3d);
      h.studyOS[19]->Fill(Muon.at(1).reliso03);
      h.studyOS[20]->Fill(Muon.at(1).reliso04);
      h.studyOS[21]->Fill(muon0_nearestJet_deepB);
      h.studyOS[22]->Fill(muon1_nearestJet_deepB);
    }
    if(samesign){
      //h.study2L[0]->Fill(2);
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
      h.studySS[15]->Fill(Muon.at(0).sip3d);
      h.studySS[16]->Fill(Muon.at(0).reliso03);
      h.studySS[17]->Fill(Muon.at(0).reliso04);
      h.studySS[18]->Fill(Muon.at(1).sip3d);
      h.studySS[19]->Fill(Muon.at(1).reliso03);
      h.studySS[20]->Fill(Muon.at(1).reliso04);
      h.studySS[21]->Fill(muon0_nearestJet_deepB);
      h.studySS[22]->Fill(muon1_nearestJet_deepB);
    }
  }
}
