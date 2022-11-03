branchname=["run",
            "luminosityBlock",
            "event",
            "HLT_IsoMu20",
            "HLT_IsoMu24",
            "HLT_IsoMu27",
            "HLT_Ele32_WPTight_Gsf",
            "HLT_Ele27_WPTight_Gsf",
            "Flag_HBHENoiseFilter",
            "Flag_HBHENoiseIsoFilter",
            "Flag_CSCTightHaloFilter",            
            "Flag_CSCTightHaloTrkMuUnvetoFilter",
            "Flag_CSCTightHalo2015Filter",            
            "Flag_globalTightHalo2016Filter",
            "Flag_globalSuperTightHalo2016Filter",
            "Flag_HcalStripHaloFilter",
            "Flag_hcalLaserEventFilter",
            "Flag_EcalDeadCellTriggerPrimitiveFilter",
            "Flag_EcalDeadCellBoundaryEnergyFilter",
            "Flag_ecalBadCalibFilter",
            "Flag_goodVertices",
            "Flag_eeBadScFilter",
            "Flag_ecalLaserCorrFilter",
            "Flag_trkPOGFilters",
            "Flag_chargedHadronTrackResolutionFilter",
            "Flag_muonBadTrackFilter",
            "Flag_BadChargedCandidateFilter",
            "Flag_BadPFMuonFilter",
            "Flag_BadPFMuonDzFilter",
            "Flag_hfNoisyHitsFilter",
            "Flag_BadChargedCandidateSummer16Filter",
            "Flag_BadPFMuonSummer16Filter",
            "Flag_trkPOG_manystripclus53X",
            "Flag_trkPOG_toomanystripclus53X",
            "Flag_trkPOG_logErrorTooManyClusters",
            "Flag_METFilters",
            "btagWeight_DeepCSVB",
            "MET_phi",
            "MET_pt",
            "MET_significance",
            "MET_sumEt",
            "PuppiMET_phi",
            "PuppiMET_phiJERDown",
            "PuppiMET_phiJERUp",
            "PuppiMET_phiJESDown",
            "PuppiMET_phiJESUp",
            "PuppiMET_pt",
            "PuppiMET_ptJERDown",
            "PuppiMET_ptJERUp",
            "PuppiMET_ptJESDown",
            "PuppiMET_ptJESUp",
            "PuppiMET_sumEt",
            "GenMET_phi",
            "GenMET_pt",
            "nMuon",
            "Muon_dxy",
            "Muon_dxyErr",
            "Muon_dxybs",
            "Muon_dz",
            "Muon_dzErr",
            "Muon_eta",
            "Muon_ip3d",
            "Muon_jetPtRelv2",
            "Muon_jetRelIso",
            "Muon_mass",
            "Muon_pfRelIso04_all",
            "Muon_phi",
            "Muon_pt",
            "Muon_sip3d",
            "Muon_charge",
            "Muon_jetIdx",
            "Muon_pdgId",
            "Muon_jetNDauCharged",
            "Muon_looseId",
            "Muon_mediumId",
            "Muon_tightId",
            "Muon_genPartIdx",
            "Muon_genPartFlav",
            "nElectron",
            "Electron_dxy",
            "Electron_dxyErr",
            "Electron_dz",
            "Electron_dzErr",
            "Electron_eta",
            "Electron_ip3d",
            "Electron_jetPtRelv2",
            "Electron_jetRelIso",
            "Electron_mass",
            "Electron_pfRelIso03_all",
            "Electron_pfRelIso03_chg",
            "Electron_phi",
            "Electron_pt",
            "Electron_sip3d",
            "Electron_charge",
            "Electron_cutBased",
            "Electron_jetIdx",
            "Electron_pdgId",
            "Electron_vidNestedWPBitmap",
            "Electron_jetNDauCharged",
            "Electron_genPartIdx",
            "Electron_genPartFlav",            
            "nTau",
            "Tau_dxy",
            "Tau_dz",
            "Tau_eta",
            "Tau_mass",
            "Tau_phi",
            "Tau_pt",
            "Tau_puCorr",
            "Tau_charge",
            "Tau_decayMode",
            "Tau_jetIdx",
            "Tau_idDeepTau2017v2p1VSe",
            "Tau_idDeepTau2017v2p1VSjet",
            "Tau_idDeepTau2017v2p1VSmu",
            "Tau_genPartIdx",
            "Tau_genPartFlav",
            "nJet",
            "Jet_btagDeepB",
            "Jet_btagDeepCvB",
            "Jet_btagDeepCvL",
            "Jet_btagDeepFlavB",
            "Jet_btagDeepFlavCvB",
            "Jet_btagDeepFlavCvL",
            "Jet_btagDeepFlavQG",
            "Jet_eta",
            "Jet_mass",
            "Jet_phi",
            "Jet_pt",
            "Jet_jetId",
            "Jet_puId",
            "Jet_genJetIdx",
            "Jet_hadronFlavour",
            "Jet_partonFlavour",
            "nGenJet",
            "GenJet_eta",
            "GenJet_mass",
            "GenJet_phi",
            "GenJet_pt",
            "GenJet_partonFlavour",
            "GenJet_hadronFlavour",
            "nGenPart",
            "GenPart_eta",
            "GenPart_mass",
            "GenPart_phi",
            "GenPart_pt",
            "GenPart_genPartIdxMother",
            "GenPart_pdgId",
            "GenPart_status",
            "GenPart_statusFlags",
            "nGenVisTau",
            "GenVisTau_eta",
            "GenVisTau_mass",
            "GenVisTau_phi",
            "GenVisTau_pt",
            "GenVisTau_charge",
            "GenVisTau_genPartIdxMother",
            "GenVisTau_status",
            "nTrigObj",
            "TrigObj_pt",
            "TrigObj_eta",
            "TrigObj_phi",
            "TrigObj_id",
            "TrigObj_filterBits"
]

#print
for item in branchname:
    print('t->SetBranchStatus("'+item+'",1);')
    #if(item.startswith("Muon")):
    #print(item+"[i]")
