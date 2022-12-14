//#include <string>
using namespace std;
void VLLAna::ActivateBranch(TTree *t){
  //char activeBranch[] = {"run","luminosityBlock","event","HLT_IsoMu18","HLT_IsoMu20","HLT_IsoMu24","HLT_IsoMu27","HLT_IsoTkMu18","HLT_IsoTkMu20","HLT_IsoTkMu22","HLT_IsoTkMu24","HLT_IsoTkMu27","HLT_Ele32_WPTight_Gsf","HLT_Ele27_WPTight_Gsf","Flag_*","nMuon","Muon_*","nElectron","Electron_*","nTau","Tau_*","nJet","Jet_*","nGenPart","GenPart_*","nGenJet","GenJet_*","nGenVisTau","GenVisTau_*","MET_*","PuppiMET_*","btagWeight_DeepCSVB","GenMET_phi","GenMET_pt","nTrigObj","TrigObj_*"};
  
  //cout<<"No of branches="<<activeBranch.size()<<endl;
  //for(auto activeBranchName : activeBranch){t->SetBranchStatus(activeBranchName, 1);}
  for(auto activeBranchName : {"nMuon","Muon_*"})
    t->SetBranchStatus(activeBranchName, 1);

  //Other things that I am using:
  for(auto activeBranchName : {"Flag_*", "HLT_*"})
    t->SetBranchStatus(activeBranchName, 1);
  
  //Activate ONLY FOR MC
  /*
  if(_data==0){
    for(auto activeBranchName : {"nGenPart","GenPart_*","nGenJet","GenJet_*","nGenVisTau","GenVisTau_*","btagWeight_DeepCSVB","GenMET_phi","GenMET_pt"})
      t->SetBranchStatus(activeBranchName, 1);
      }*/
}



void VLLAna::ReadBranch(){
  //ONLY READ
  //Muon,Electron,Jets,Taus,MET,PuppiMET,GenJet,GenPart,GenVisTau,nTrigObj,Flags,HLT_Path
  // Rules:
  // TTreeReaderValue branch: *variable
  // TTreeReaderArray branch: variable[i] where i is looping over no of that object
  
  *run;
  *luminosityBlock;
  *event;
  
  //Muon Branches
  *nMuon;
  for(unsigned int i=0;i<(*nMuon);i++){
    Muon_dxy[i];
    Muon_dxyErr[i];
    Muon_dxybs[i];
    Muon_dz[i];
    Muon_dzErr[i];
    Muon_eta[i];
    Muon_ip3d[i];
    Muon_jetPtRelv2[i];
    Muon_jetRelIso[i];
    Muon_mass[i];
    Muon_miniPFRelIso_all[i];
    Muon_miniPFRelIso_chg[i];
    Muon_pfRelIso03_all[i];
    Muon_pfRelIso03_chg[i];
    Muon_pfRelIso04_all[i];
    Muon_phi[i];
    Muon_pt[i];
    Muon_ptErr[i];
    Muon_segmentComp[i];
    Muon_sip3d[i];
    Muon_softMva[i];
    Muon_tkRelIso[i];
    Muon_tunepRelPt[i];
    Muon_mvaLowPt[i];
    Muon_mvaTTH[i];
    Muon_charge[i];
    Muon_jetIdx[i];
    Muon_nStations[i];
    Muon_nTrackerLayers[i];
    Muon_pdgId[i];
    Muon_tightCharge[i];
    Muon_fsrPhotonIdx[i];
    Muon_highPtId[i];
    Muon_highPurity[i];
    Muon_inTimeMuon[i];
    Muon_isGlobal[i];
    Muon_isPFcand[i];
    Muon_isStandalone[i];
    Muon_isTracker[i];
    Muon_jetNDauCharged[i];
    Muon_looseId[i];
    Muon_mediumId[i];
    Muon_mediumPromptId[i];
    Muon_miniIsoId[i];
    Muon_multiIsoId[i];
    Muon_mvaId[i];
    Muon_mvaLowPtId[i];
    Muon_pfIsoId[i];
    Muon_puppiIsoId[i];
    Muon_softId[i];
    Muon_softMvaId[i];
    Muon_tightId[i];
    Muon_tkIsoId[i];
    Muon_triggerIdLoose[i];
    if(_data==0){
      Muon_genPartIdx[i];
      Muon_genPartFlav[i];
    }
    Muon_cleanmask[i];    
  }
}
