void VLLAna::Make2muPlots(float wt)
{
  //This function is called in the main VLLAna.C file.
  //It runs for all the 2Mu events.

  //Defining how SS and OS boxes are filled:
  bool samesign = false;
  for(int i=0; i<(int)Muon.size(); i++){
    for(int j=0; j<(int)Muon.size(); j++){
      if(i!=j && Muon.at(i).charge == Muon.at(j).charge){
	samesign = true;
	//MakeChargePlots();
      }
    }
  }
  //if((int)Muon.size()>1 && Muon.at(0).charge == Muon.at(1).charge) samesign = true;
  
  //Derived quantities:
  float dphi_muon = delta_phi(Muon.at(0).v.Phi(), Muon.at(1).v.Phi());
  float dR_muon = Muon.at(0).v.DeltaR(Muon.at(1).v);
  float deta_muon = fabs(Muon.at(0).v.Eta() - Muon.at(1).v.Eta());
  float dimuonmass = (Muon.at(0).v+Muon.at(1).v).M();
  float mu0_mT = transv_mass(Muon.at(0).v.E(), Muon.at(0).v.Phi(), metpt, metphi);
  float mu1_mT = transv_mass(Muon.at(1).v.E(), Muon.at(1).v.Phi(), metpt, metphi);
  float ptratio =  Muon.at(1).v.Pt()/Muon.at(0).v.Pt();
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
  float ST=0; for(int i=0; i<(int)Muon.size(); i++) ST = ST + Muon.at(i).v.Pt();
  float HT=0; for(int i=0; i<(int)jets.size(); i++) HT = HT + jets.at(i).v.Pt();
  

  //Exploring cuts on the skimmed samples:
  //cuts on the first lepton:
  bool iso03cut_llep0 = Muon.at(0).reliso03 < 0.15;
  bool iso04cut_llep0 = Muon.at(0).reliso04 < 0.15;
  bool sip3dcut_llep0 = Muon.at(0).sip3d < 5;
  bool mT0cut = mu0_mT > 50;
  //cuts on the second lepton:
  bool iso03cut_llep1 = Muon.at(1).reliso03 < 0.25;
  bool iso04cut_llep1 = Muon.at(1).reliso04 < 0.25;
  bool sip3dcut_llep1 = Muon.at(1).sip3d < 5;
  bool mT1cut = mu1_mT > 50;
  //cuts on the dilepton system:
  bool dEtacut = deta_muon < 2.5;
  bool dRcut = dR_muon < 3.2;
  bool ratiocut = ptratio > 0.5;
  bool STcut = ST > 50;
  //Combined cuts
  bool iso0cut = iso03cut_llep0 && iso04cut_llep0 && sip3dcut_llep0;
  bool iso0mTcut = iso0cut && mT1cut && mT0cut;
  bool iso0mTratiocut = iso0mTcut && ratiocut;
  bool iso0mTSTcut = iso0mTcut && STcut;
  
  
  //Additional cuts after looking in the 20-120 mass region:
  bool ismasswindow = 20<dimuonmass && dimuonmass<120;
  bool metcut = metpt > 40;
  bool allcut = iso0mTSTcut && ratiocut && metcut;
  //if(ismasswindow){
   
  //}
    
  
  bool eventselection = allcut;

  //Cutflow for the SS events:
  //bin0 = All the SS events
  //bin1 = SS events with cut 1
  //                 .. etc etc.
  if(samesign){
    //No cuts, just basic selection:
    h.cutflow[0]->Fill(0);
    //cuts on the first lepton:
    if(iso03cut_llep0)     h.cutflow[0]->Fill(1, wt);
    if(iso04cut_llep0)     h.cutflow[0]->Fill(2, wt);
    if(sip3dcut_llep0)     h.cutflow[0]->Fill(3, wt);
    if(mT0cut)             h.cutflow[0]->Fill(4, wt);
    //cuts on the second lepton:
    if(iso03cut_llep1)     h.cutflow[0]->Fill(5, wt);
    if(iso04cut_llep1)     h.cutflow[0]->Fill(6, wt);
    if(sip3dcut_llep1)     h.cutflow[0]->Fill(7, wt);
    if(mT1cut)             h.cutflow[0]->Fill(8, wt);
    //cuts on the dilepton system:
    if(dEtacut)            h.cutflow[0]->Fill(9, wt);
    if(dRcut)              h.cutflow[0]->Fill(10, wt);
    if(ratiocut)           h.cutflow[0]->Fill(11, wt);
    if(STcut)              h.cutflow[0]->Fill(12, wt);
    //event level variable:
    if(metcut)             h.cutflow[0]->Fill(13, wt);
    //combined cuts:
    if(iso0cut)            h.cutflow[0]->Fill(14, wt);
    if(iso0mTcut)          h.cutflow[0]->Fill(15, wt);
    if(iso0mTratiocut)     h.cutflow[0]->Fill(16, wt);
    if(iso0mTSTcut)        h.cutflow[0]->Fill(17, wt);
    if(allcut)             h.cutflow[0]->Fill(18, wt);
  }
  
  if(!samesign){
    //No cuts, just basic selection:
    h.cutflow[1]->Fill(0); // 0.37
    //cuts on the first lepton:
    if(iso03cut_llep0)     h.cutflow[1]->Fill(1, wt);
    if(iso04cut_llep0)     h.cutflow[1]->Fill(2, wt);
    if(sip3dcut_llep0)     h.cutflow[1]->Fill(3, wt);
    if(mT0cut)             h.cutflow[1]->Fill(4, wt);
    //cuts on the second lepton:
    if(iso03cut_llep1)     h.cutflow[1]->Fill(5, wt);
    if(iso04cut_llep1)     h.cutflow[1]->Fill(6, wt);
    if(sip3dcut_llep1)     h.cutflow[1]->Fill(7, wt);
    if(mT1cut)             h.cutflow[1]->Fill(8, wt);
    //cuts on the dilepton system:
    if(dEtacut)            h.cutflow[1]->Fill(9, wt);
    if(dRcut)              h.cutflow[1]->Fill(10, wt);
    if(ratiocut)           h.cutflow[1]->Fill(11, wt);
    if(STcut)              h.cutflow[1]->Fill(12, wt);
    //event level variable:
    if(metcut)             h.cutflow[1]->Fill(13, wt);
    //combined cuts:
    if(iso0cut)            h.cutflow[1]->Fill(14, wt);
    if(iso0mTcut)          h.cutflow[1]->Fill(15, wt);
    if(iso0mTratiocut)     h.cutflow[1]->Fill(16, wt);
    if(iso0mTSTcut)        h.cutflow[1]->Fill(17, wt);
    if(allcut)             h.cutflow[1]->Fill(18, wt);
  }

  
  if(eventselection){//Place the cuts here.
    //#####################
    //2mu inclusive events:
    //#####################
    //h.study2L[0]->Fill(0);
    h.study2L[0]->Fill(Muon.at(0).v.Pt(), wt);
    h.study2L[1]->Fill(Muon.at(0).v.Eta(), wt);
    h.study2L[2]->Fill(Muon.at(0).v.Phi(), wt);
    h.study2L[3]->Fill(Muon.at(1).v.Pt(), wt);
    h.study2L[4]->Fill(Muon.at(1).v.Eta(), wt);
    h.study2L[5]->Fill(Muon.at(1).v.Phi(), wt);
    h.study2L[6]->Fill(deta_muon, wt);
    h.study2L[7]->Fill(dphi_muon, wt);
    h.study2L[8]->Fill(dR_muon, wt);
    h.study2L[9]->Fill(dimuonmass, wt);
    h.study2L[10]->Fill(metpt, wt);
    h.study2L[11]->Fill(metphi, wt);
    h.study2L[12]->Fill(mu0_mT, wt);
    h.study2L[13]->Fill(mu1_mT, wt);
    h.study2L[14]->Fill(sumcosdphi, wt);
    h.study2L[15]->Fill(Muon.at(0).sip3d, wt);
    h.study2L[16]->Fill(Muon.at(0).reliso03, wt);
    h.study2L[17]->Fill(Muon.at(0).reliso04, wt);
    h.study2L[18]->Fill(Muon.at(1).sip3d, wt);
    h.study2L[19]->Fill(Muon.at(1).reliso03, wt);
    h.study2L[20]->Fill(Muon.at(1).reliso04, wt);
    h.study2L[21]->Fill(muon0_nearestJet_deepB, wt);
    h.study2L[22]->Fill(muon1_nearestJet_deepB, wt);
    h.study2L[23]->Fill(ptratio, wt);
    h.study2L[24]->Fill(ST, wt);
    h.study2L[25]->Fill(HT, wt);
    //################
    //Opposite Sign Events:
    //################
    if(!samesign){
      //h.study2L[0]->Fill(1);
      h.studyOS[0]->Fill(Muon.at(0).v.Pt(), wt);
      h.studyOS[1]->Fill(Muon.at(0).v.Eta(), wt);
      h.studyOS[2]->Fill(Muon.at(0).v.Phi(), wt);
      h.studyOS[3]->Fill(Muon.at(1).v.Pt(), wt);
      h.studyOS[4]->Fill(Muon.at(1).v.Eta(), wt);
      h.studyOS[5]->Fill(Muon.at(1).v.Phi(), wt);
      h.studyOS[6]->Fill(deta_muon, wt);
      h.studyOS[7]->Fill(dphi_muon, wt);
      h.studyOS[8]->Fill(dR_muon, wt);
      h.studyOS[9]->Fill(dimuonmass, wt);
      h.studyOS[10]->Fill(metpt, wt);
      h.studyOS[11]->Fill(metphi, wt);
      h.studyOS[12]->Fill(mu0_mT, wt);
      h.studyOS[13]->Fill(mu1_mT, wt);
      h.studyOS[14]->Fill(sumcosdphi, wt);
      h.studyOS[15]->Fill(Muon.at(0).sip3d, wt);
      h.studyOS[16]->Fill(Muon.at(0).reliso03, wt);
      h.studyOS[17]->Fill(Muon.at(0).reliso04, wt);
      h.studyOS[18]->Fill(Muon.at(1).sip3d, wt);
      h.studyOS[19]->Fill(Muon.at(1).reliso03, wt);
      h.studyOS[20]->Fill(Muon.at(1).reliso04, wt);
      h.studyOS[21]->Fill(muon0_nearestJet_deepB, wt);
      h.studyOS[22]->Fill(muon1_nearestJet_deepB, wt);
      h.studyOS[23]->Fill(ptratio, wt);
      h.studyOS[24]->Fill(ST, wt);
      h.studyOS[25]->Fill(HT, wt);
    }
    if(samesign){
      //h.study2L[0]->Fill(2);
      h.studySS[0]->Fill(Muon.at(0).v.Pt(), wt);
      h.studySS[1]->Fill(Muon.at(0).v.Eta(), wt);
      h.studySS[2]->Fill(Muon.at(0).v.Phi(), wt);
      h.studySS[3]->Fill(Muon.at(1).v.Pt(), wt);
      h.studySS[4]->Fill(Muon.at(1).v.Eta(), wt);
      h.studySS[5]->Fill(Muon.at(1).v.Phi(), wt);
      h.studySS[6]->Fill(deta_muon, wt);
      h.studySS[7]->Fill(dphi_muon, wt);
      h.studySS[8]->Fill(dR_muon, wt);
      h.studySS[9]->Fill(dimuonmass, wt);
      h.studySS[10]->Fill(metpt, wt);
      h.studySS[11]->Fill(metphi, wt);
      h.studySS[12]->Fill(mu0_mT, wt);
      h.studySS[13]->Fill(mu1_mT, wt);
      h.studySS[14]->Fill(sumcosdphi, wt);
      h.studySS[15]->Fill(Muon.at(0).sip3d, wt);
      h.studySS[16]->Fill(Muon.at(0).reliso03, wt);
      h.studySS[17]->Fill(Muon.at(0).reliso04, wt);
      h.studySS[18]->Fill(Muon.at(1).sip3d, wt);
      h.studySS[19]->Fill(Muon.at(1).reliso03, wt);
      h.studySS[20]->Fill(Muon.at(1).reliso04, wt);
      h.studySS[21]->Fill(muon0_nearestJet_deepB, wt);
      h.studySS[22]->Fill(muon1_nearestJet_deepB, wt);
      h.studySS[23]->Fill(ptratio, wt);
      h.studySS[24]->Fill(ST, wt);
      h.studySS[25]->Fill(HT, wt);

      //plots for measuring charge misID:
      if(_data==0 && 76<dimuonmass && dimuonmass<106) MakeChargePlots();
      
    }//samesign
  }
}
