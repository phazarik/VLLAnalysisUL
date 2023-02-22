void VLLAna::MakeChargePlots(){
  //This function runs on the 2mu events with whatever cuts applied (2mustudy.h).
  //It runs for MC only
  //h.studyCharge

  //################################
  //GenMatching of the leading muon:
  float dR0_min = 1000;
  int closest0 = -1;
  for(int i=0; i<(int)genMuon.size(); i++){
    float dR = Muon.at(0).v.DeltaR(genMuon.at(i).v);
    if(dR < dR0_min){
      dR0_min = dR;
      closest0 = i;
    }
  }
  if(dR0_min<0.4){
    //genMuon(i) is matching with the leading muon
    h.studyCharge[0]-> Fill(genMuon.at(closest0).charge);
  }

  //####################################
  //GenMatching of the sub-leading muon:
  float dR1_min = 1000;
  int closest1 = -1;
  for(int i=0; i<(int)genMuon.size(); i++){
    float dR = Muon.at(1).v.DeltaR(genMuon.at(i).v);
    if(dR < dR1_min){
      dR1_min = dR;
      closest1 = i;
    }
  }
  if(dR1_min<0.4){
    //GenMuon(i) is matching with the sub-leading muon
    h.studyCharge[1]-> Fill(genMuon.at(closest1).charge);
  }

  if(dR0_min<0.4 && dR1_min<0.4){
    h.studyCharge[2]-> Fill(genMuon.at(closest0).charge * genMuon.at(closest1).charge);
  }
  if((int)genMuon.size()>1){
    h.studyCharge[3]-> Fill(genMuon.at(0).charge * genMuon.at(1).charge);
  }
  h.studyCharge[4]-> Fill(Muon.at(0).charge * Muon.at(1).charge);

}
