//Prototype of Analysis Code

// llep, jets array are automatically feeded

void VLLAna::Analysis(){
  //cout<<"No of light lepton in 1L2J event="<<lep.size()<<endl;
  
  //Properties
  float HT=-1.0;
  for(int i=0;i<(int)jets.size();i++)
    HT=HT+jets.at(i).v.Pt();
  
  //Best Jet Pairs coming from W
  int jet0index=999,jet1index=999;
  vector<int>jetindex=BestJetPairFinder(jets); //This function returns a vector array of indices
  jet0index=jetindex[0];
  jet1index=jetindex[1];
  
  //USE THIS INDEX IN JETS  
  float mtlep0=sqrt(2.0*llep[0].v.Pt()*metpt*(1-cos(delta_phi(llep[0].v.Phi(),metphi))));
  float mtjet0=sqrt(2.0*jets[jet0index].v.Pt()*metpt*(1-cos(delta_phi(jets[jet0index].v.Phi(),metphi))));
  float mtjet1=sqrt(2.0*jets[jet1index].v.Pt()*metpt*(1-cos(delta_phi(jets[jet1index].v.Phi(),metphi))));
  float MET=metpt;
  float ST=llep[0].v.Pt()+MET+HT;
  float dijetMass=getInvMass(jets[jet0index].v,jets[jet1index].v);
  float drjet01=jets[jet0index].v.DeltaR(jets[jet1index].v);
  float dijetMT=sqrt(2.0*(jets[jet0index].v+jets[jet1index].v).Pt()*metpt*(1-cos(delta_phi((jets[jet0index].v+jets[jet1index].v).Phi(),metphi))));
  float dijetPT=(jets[jet0index].v+jets[jet1index].v).Pt();
  int njet=jets.size();
  int nbjet=BTaggedJet.size();
  float dphimetjet0=delta_phi(jets[jet0index].v.Phi(),metphi);
  float dphimetjet1=delta_phi(jets[jet1index].v.Phi(),metphi);
  float dphimetlep0=delta_phi(llep[0].v.Phi(),metphi);
  float dphijet0lep0=delta_phi(llep[0].v.Phi(),jets[jet0index].v.Phi());
  float dphijet1lep0=delta_phi(llep[0].v.Phi(),jets[jet1index].v.Phi());
  float dphidijetlep0=delta_phi(llep[0].v.Phi(),(jets[jet0index].v+jets[jet1index].v).Phi());
  float dphimetdijet=delta_phi(metphi,(jets[jet0index].v+jets[jet1index].v).Phi());
  float LeadingJetPt=jets[jet0index].v.Pt();
  float drjet0lep0=llep[0].v.DeltaR(jets[jet0index].v);
  float drjet1lep0=llep[0].v.DeltaR(jets[jet1index].v);
  
  
  //Selections
  vector<int>index; // Needed For 2D Histogram booking
  
  //CUT STARTS
  bool l2jSelection_global=jets.at(jet0index).v.Pt()>30 && jets.at(jet1index).v.Pt()>30 && drjet01>0.4 && drjet0lep0>0.4 && drjet1lep0>0.4;
  //bool l2jSelection_primaryCut= (nbjet==0 && njet<=3 && l2jSelection_global); // This phase space is unnecessary
  
  //Sep11,2022[decided to not cut on njets]
  bool l2jSelection_primaryCut= (nbjet==0 && l2jSelection_global); // This phase space is unnecessary
  //SignalRegion
  bool l2jSelection_signalCut= (dijetMass>50)&&(dijetMass<110)&&(mtlep0>0)&&(mtlep0<130)&& drjet01<2.6;
  bool l2jSelection_SR=l2jSelection_primaryCut && l2jSelection_signalCut;
  //ControlRegion
  bool l2jSelection_wjet_bkg= (l2jSelection_global)&&(dijetMass>200)&& mtjet0>75 && (mtlep0>40);
  bool l2jSelection_qcd_bkg = (l2jSelection_global)&&(dijetMass<40) && (mtlep0<40); //dijetMass<40 is AntiSignal Cuts
  bool MuonChannel = abs(llep[0].id)==13;
  bool EleChannel = abs(llep[0].id)==11;
  
  if(l2jSelection_global)index.push_back(0); //base//LeptonInclusive
  if(l2jSelection_global && MuonChannel)index.push_back(1); // mujj channel
  if(l2jSelection_primaryCut && MuonChannel)index.push_back(2); // mujj channel + primary Cuts applied
  
  if(MuonChannel){
    if(l2jSelection_wjet_bkg)index.push_back(3); //WJets bkg CR
    if(l2jSelection_qcd_bkg)index.push_back(4);  //QCD bkg CR
    if(l2jSelection_wjet_bkg && l2jSelection_primaryCut)index.push_back(5); //WJets bkg CR with primaryCuts
    if(l2jSelection_qcd_bkg && l2jSelection_primaryCut)index.push_back(6);  //QCD bkg CR with primaryCuts
    
    //ABCD Method(Predicting WJets in SR)
    //bool regA=l2jSelection_primaryCut && l2jSelection_signalCut;//SR
    //bool regB=l2jSelection_primaryCut && (dijetMass>40) && (dijetMass<200) && (mtlep0>150);    //Region B
    //bool regC=l2jSelection_primaryCut && (dijetMass>200) && (mtlep0>40) && (mtlep0<150);       //Region C 
    //bool regD=l2jSelection_primaryCut && (dijetMass>200) && (mtlep0>150);                      //Region D
    
    bool regA=l2jSelection_primaryCut && l2jSelection_signalCut;//SR(dR<2.6 + 0<LepMT<130 + 50<dijetMass<110)
    bool regB=l2jSelection_primaryCut && (drjet01<2.6) && (mtlep0>130 && mtlep0<200);                  //Region B
    bool regC=l2jSelection_primaryCut && (drjet01>2.7 && drjet01<3.5) && (mtlep0>40) && (mtlep0<110); //Region C 
    bool regD=l2jSelection_primaryCut && (drjet01>2.7 && drjet01<3.5) && (mtlep0>120) && (mtlep0<200); //Region D
    
    //Save Index to Produce Histos
    if(regA)index.push_back(7);
    if(regB)index.push_back(8);
    if(regC)index.push_back(9);
    if(regD)index.push_back(10);
  }
  
  //SIGNAL REGION
  if(l2jSelection_SR)index.push_back(11);                 //ljj
  if(l2jSelection_SR && MuonChannel)index.push_back(12);  //mjj
  if(l2jSelection_SR && EleChannel)index.push_back(13);   //ejj
  //HISTOGRAMS
  for(vector<int>::iterator iter = index.begin();iter<index.end();iter++){
    //cout<<"index vector is:"<<*_index<<endl;
    h.vllplotl2j[0][*iter]->Fill(llep[0].v.Pt(),evtwt);
    h.vllplotl2j[1][*iter]->Fill(jets[jet0index].v.Pt(),evtwt);
    h.vllplotl2j[2][*iter]->Fill(jets[jet1index].v.Pt(),evtwt);
    h.vllplotl2j[3][*iter]->Fill(mtlep0,evtwt);
    h.vllplotl2j[4][*iter]->Fill(mtjet0,evtwt);
    h.vllplotl2j[5][*iter]->Fill(mtjet1,evtwt);
    h.vllplotl2j[6][*iter]->Fill(dijetMass,evtwt);
    h.vllplotl2j[7][*iter]->Fill(drjet01,evtwt);
    h.vllplotl2j[8][*iter]->Fill(dijetPT,evtwt);
    h.vllplotl2j[9][*iter]->Fill(dijetMT,evtwt);
    h.vllplotl2j[10][*iter]->Fill(MET,evtwt);
    h.vllplotl2j[11][*iter]->Fill(HT,evtwt);
    h.vllplotl2j[12][*iter]->Fill(ST,evtwt);
    h.vllplotl2j[13][*iter]->Fill(njet,evtwt);
    h.vllplotl2j[14][*iter]->Fill(nbjet,evtwt);
    h.vllplotl2j[15][*iter]->Fill(dphimetjet0,evtwt);
    h.vllplotl2j[16][*iter]->Fill(dphimetjet1,evtwt);
    h.vllplotl2j[17][*iter]->Fill(dphimetlep0,evtwt);
    h.vllplotl2j[18][*iter]->Fill(dphijet0lep0,evtwt);
    h.vllplotl2j[19][*iter]->Fill(dphijet1lep0,evtwt);
    h.vllplotl2j[20][*iter]->Fill(dphidijetlep0,evtwt);
    h.vllplotl2j[21][*iter]->Fill(dphimetdijet,evtwt);
  }
  
  //MVA Variables//
  //Fill the MVA Variables
  nEvt = nEvtTotal;
  lep0_flavor=llep[0].id; 
  lep0_pt=llep[0].v.Pt();
  jet0_pt=jets[jet0index].v.Pt();
  jet1_pt=jets[jet1index].v.Pt();
  lep0_mt = mtlep0;
  jet0_mt =mtjet0;
  jet1_mt =mtjet1;
  dijet_mass = dijetMass;
  deltaR_jet01 = drjet01;
  deltaPhi_metjet0 = dphimetjet0;
  deltaPhi_metjet1 = dphimetjet1;
  deltaPhi_metlep0 = dphimetlep0;
  deltaPhi_jet0lep0 = dphijet0lep0;
  deltaPhi_jet1lep0 = dphijet1lep0;
  deltaPhi_dijetlep0 = dphidijetlep0;
  deltaPhi_metdijet = dphimetdijet;
  dijet_pt = dijetPT;
  dijet_mt = dijetMT;
  event_MET = MET;
  event_HT = HT;
  event_ST = ST;
  n_Jet = njet;
  n_bJet = nbjet;
  
  //Fill MVA Tree
  //if(l2jSelection_global)tree->Fill();
  
  if(l2jSelection_global && MuonChannel){ //hists after base cuts in mjj channel 
    //End of best Jet Pair Study
    h.testplotl2j[0]->Fill(dijetMass,evtwt);
    h.testplotl2j[1]->Fill(abs(dijetMass));
  
    h.test2Dplotl2j[0]->Fill(dijetMass,drjet01,evtwt);
    h.test2Dplotl2j[1]->Fill(dijetMass,drjet01,evtwt);  
    
    //WJetsEstimation(ABCD check based on WJetsMC)
    if(dijetMass>40 && mtlep0>40)
      h.test2Dplotl2j[2]->Fill(dijetMass,mtlep0,evtwt);
  
    //Adding DeepCSV score of each jet
    h.testplotl2j[2]->Fill(Jet_btagDeepB[jets[0].ind],evtwt); //First Jet btag score
    h.testplotl2j[3]->Fill(Jet_btagDeepB[jets[1].ind],evtwt); //Second Jet btag score
  
    float btagscore=0;
    for(int i=0;i<(int)jets.size();i++){
      btagscore = btagscore + Jet_btagDeepB[jets[i].ind];
    }
    h.testplotl2j[4]->Fill((btagscore/jets.size()),evtwt); //avg btagscore of the event
    
    //SignalRegionCutFlowPlots
    h.testplotl2j[5]->Fill(1,evtwt);            //basecut
    if(nbjet==0){
      h.testplotl2j[5]->Fill(2,evtwt);//nbjet==0
      if(drjet01<2.6){
	h.testplotl2j[5]->Fill(3,evtwt);//dRjet01<2.6
	if(mtlep0<130){
	  h.testplotl2j[5]->Fill(4,evtwt);//0<mtlep0<130
	  if(dijetMass>50){
	    h.testplotl2j[5]->Fill(5,evtwt);//dijetMass>50
	    if(dijetMass<110)h.testplotl2j[5]->Fill(6,evtwt);//dijetMass<110
	  }
	}
      }
    }
  }
}

//Functions
vector<int>VLLAna::BestJetPairFinder(vector<Lepton>jetarray){
  float invmass=-1.0;float dMmin=999999.0;
  float Wmass=80.3;float bestMass=-1.0;
  float dRjets=999.0;
  
  vector<int>jetindex;
  //jetindex.clear();
  if(jetarray.size()>2){
    for(int i=0;i<(int)jetarray.size();i++){
      for(int j=0;j<(int)jetarray.size();j++){
	if(i!=j && j>i){
	  jetindex.clear();
	  invmass=getInvMass(jetarray[i].v,jetarray[j].v);
	  //cout<<"Pair("<<i<<","<<j<<"), mass is = "<<invmass<<endl;	
	  //Find Out the closest one to W Mass
	  //bool onWpair = invmass>60 && invmass<100;
	  bool onWpair=true;
	  if(onWpair){
	    if(abs(Wmass-invmass)<=dMmin){
	      bestMass=invmass;
	      dMmin=abs(Wmass-invmass);
	      jetindex.push_back(i);
	      jetindex.push_back(j);
	    }
	  }
	}
      }
    }
  }
  else jetindex.push_back(0),jetindex.push_back(1); // If only two jets found return 0 & 1;
  
  return jetindex;
}


void VLLAna::Book1L2JAnalysisHistograms(){
  //l2j events histos
  
  TString l2jplot[22]={"ptlep0","ptjet0","ptjet1","mtlep0","mtjet0","mtjet1","dijetmass","drjet01","dijetPT","dijetMT","MET","HT","ST","njet","nbjet","dphimetjet0","dphimetjet1","dphimetlep0","dphijet0lep0","dphijet1lep0","dphidijetlep0","dphimetdijet"};
  TString l2jfancyname[22]={"Lepton PT","Leading Jet PT","SubLeading Jet PT","Lepton MT","Leading Jet MT","SubLeading Jet MT","Dijet Inv Mass","DR(jet0,jet1)","Dijet System PT","Dijet System MT","MET in 1L2J events","HT in 1L2J events","ST in 1L2J events","No of Jets","No of b-jets","dphimetjet0","dphimetjet1","dphimetlep0","dphijet0lep0","dphijet1lep0","dphidijetlep0","dphimetdijet"};
  
  TString type[14]={"_base","_base_mjj","_primaryCuts_mjj","_base_wjetbkg_mjj","_base_qcdbkg_mjj","_primaryCuts_wjetbkg_mjj","_primaryCuts_qcdbkg_mjj","_regA","_regB","_regC","_regD","_ljjSR","_mjjSR","_ejjSR"};
  float l2jbin[22]={1000,1000,1000,1000,1000,1000,1000,100,1000,1000,1000,1000,1000,10,10,100,100,100,100,100,100,100};
  float l2jbinlow[22]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  float l2jbinhi[22]={1000,1000,1000,1000,1000,1000,1000,10,1000,1000,1000,1000,1000,10,10,10,10,10,10,10,10,10};  
  
  for(int i=0;i<22;i++){
    for(int j=0;j<14;j++){
      TString plottitle= l2jplot[i]+"_l2j"+type[j];
      TString title= l2jfancyname[i]+type[j];
      h.vllplotl2j[i][j]=new TH1F(plottitle,title,l2jbin[i],l2jbinlow[i],l2jbinhi[i]);h.vllplotl2j[i][j]->Sumw2();
    }
  }
  
  //NewStudy
  h.testplotl2j[0]= new TH1F("bestdijetMass","Best DiJet Mass",1000,0,1000);
  h.testplotl2j[1]= new TH1F("deltadijetMass","BestDijetMass - leading abnd subleading jet diJetMass",500,0,500);
  h.testplotl2j[2]= new TH1F("bscore_firstjet","First Jet btag score",100,0,1);
  h.testplotl2j[3]= new TH1F("bscore_secondjet","Second Jet btag score",100,0,1);
  h.testplotl2j[4]= new TH1F("avgbscore","Avg btag score of the event",100,0,1);
  h.testplotl2j[5]= new TH1F("SRCutFlow","1=basecut,2=nbjetcut,3=dRJet01<2.6,4=lepMT<130,5=dijetmass>50,6=dijetmass<110",10,0,10);
  for(int i=0;i<6;i++){h.testplotl2j[i]->Sumw2();}
  
  //2Dplot(bestMass vs dRjets)
  h.test2Dplotl2j[0] = new TH2F("bestMass_dRjets","BestMass vs dRjets",500,0,500,50,0,5);
  h.test2Dplotl2j[1] = new TH2F("dijetMass_dRjet01","dijetMass01 vs dRjet01",500,0,500,50,0,5);
  h.test2Dplotl2j[2] = new TH2F("dijetMass_mtlep0","dijetMass vs lepton mt",1000,0,1000,1000,0,1000);
}

