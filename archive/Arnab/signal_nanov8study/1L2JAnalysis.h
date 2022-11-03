//Prototype of Analysis Code

// llep, jets array are automatically feeded

void VLLAna::Analysis(){
  //cout<<"No of light lepton in 1L2J event="<<lep.size()<<endl;
  
  //Properties
  float HT=-1.0;
  for(int i=0;i<(int)jets.size();i++)
    HT=HT+jets.at(i).v.Pt();
  
  float mtlep0=sqrt(2.0*llep[0].v.Pt()*metpt*(1-cos(delta_phi(llep[0].v.Phi(),metphi))));
  float mtjet0=sqrt(2.0*jets[0].v.Pt()*metpt*(1-cos(delta_phi(jets[0].v.Phi(),metphi))));
  float mtjet1=sqrt(2.0*jets[1].v.Pt()*metpt*(1-cos(delta_phi(jets[1].v.Phi(),metphi))));
  float MET=metpt;
  float ST=llep[0].v.Pt()+MET+HT;
  float dijetMass=getInvMass(jets[0].v,jets[1].v);
  float drjet01=jets[0].v.DeltaR(jets[1].v);
  float dijetMT=sqrt(2.0*(jets[0].v+jets[1].v).Pt()*metpt*(1-cos(delta_phi((jets[0].v+jets[1].v).Phi(),metphi))));
  float dijetPT=(jets[0].v+jets[1].v).Pt();
  int njet=jets.size();
  int nbjet=BTaggedJet.size();
  float dphimetjet0=delta_phi(jets[0].v.Phi(),metphi);
  float dphimetjet1=delta_phi(jets[1].v.Phi(),metphi);
  float dphimetlep0=delta_phi(llep[0].v.Phi(),metphi);
  float dphijet0lep0=delta_phi(llep[0].v.Phi(),jets[0].v.Phi());
  float dphijet1lep0=delta_phi(llep[0].v.Phi(),jets[1].v.Phi());
  float dphidijetlep0=delta_phi(llep[0].v.Phi(),(jets[0].v+jets[1].v).Phi());
  float dphimetdijet=delta_phi(metphi,(jets[0].v+jets[1].v).Phi());
  float LeadingJetPt=jets[0].v.Pt();
  float drjet0lep0=llep[0].v.DeltaR(jets[0].v);
  float drjet1lep0=llep[0].v.DeltaR(jets[1].v);
  

  //Selections
  vector<int>index; // Needed For 2D Histogram booking
  //bool l2jSelection=BTaggedJet.size()==0 && (LooseLep.size()==1);//No medium b-jets in events, No 2nd loose lepton
  bool l2jSelection=true;
  bool l2jSelection_global=jets.at(0).v.Pt()>30 && drjet01>0.4 && drjet0lep0>0.4 && drjet1lep0>0.4;
  bool l2jSelection_dijetmasscut=(dijetMass<110) && (dijetMass>60);
  bool l2jSelection_drjetcut= (drjet01<1.5);
  bool wjet_bkg=(mtlep0>50)&&(mtlep0<150) && nbjet==0 &&l2jSelection_drjetcut;
  bool l2jSelection_wjet_bkg=l2jSelection_global && wjet_bkg;
  
  
  if(l2jSelection)index.push_back(0); //base
  if(l2jSelection_wjet_bkg)index.push_back(1);//wjetbkg
  //ABCD Method
  bool regA=l2jSelection_wjet_bkg && dijetMass>50 && (mtlep0>50)&&(mtlep0<100); 
  bool regB=l2jSelection_wjet_bkg && dijetMass<50 && (mtlep0>50)&&(mtlep0<100);
  bool regC=l2jSelection_wjet_bkg && dijetMass>50 && (mtlep0>100)&&(mtlep0<150); 
  bool regD=l2jSelection_wjet_bkg && dijetMass<50 && (mtlep0>100)&&(mtlep0<150);
  
  //Save Index to Produce Histos
  if(regA)index.push_back(2);
  if(regB)index.push_back(3);
  if(regC)index.push_back(4);
  if(regD)index.push_back(5);
  
  
  //HISTOGRAMS
  for(vector<int>::iterator iter = index.begin();iter<index.end();iter++){
    //cout<<"index vector is:"<<*_index<<endl;
    h.vllplotl2j[0][*iter]->Fill(llep[0].v.Pt(),evtwt);
    h.vllplotl2j[1][*iter]->Fill(jets[0].v.Pt(),evtwt);
    h.vllplotl2j[2][*iter]->Fill(jets[1].v.Pt(),evtwt);
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
  jet0_pt=jets[0].v.Pt();
  jet1_pt=jets[1].v.Pt();
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
  tree->Fill();  
}

void VLLAna::Book1L2JAnalysisHistograms(){
  //l2j events histos
  
  TString l2jplot[22]={"ptlep0","ptjet0","ptjet1","mtlep0","mtjet0","mtjet1","dijetmass","drjet01","dijetPT","dijetMT","MET","HT","ST","njet","nbjet","dphimetjet0","dphimetjet1","dphimetlep0","dphijet0lep0","dphijet1lep0","dphidijetlep0","dphimetdijet"};
  TString l2jfancyname[22]={"Lepton PT","Leading Jet PT","SubLeading Jet PT","Lepton MT","Leading Jet MT","SubLeading Jet MT","Dijet Inv Mass","DR(jet0,jet1)","Dijet System PT","Dijet System MT","MET in 1L2J events","HT in 1L2J events","ST in 1L2J events","No of Jets","No of b-jets","dphimetjet0","dphimetjet1","dphimetlep0","dphijet0lep0","dphijet1lep0","dphidijetlep0","dphimetdijet"};
  TString type[6]={"_base","_wjetbkg","_regA","_regB","_regC","_regD"};
  float l2jbin[22]={1000,1000,1000,1000,1000,1000,1000,100,1000,1000,1000,1000,1000,10,10,100,100,100,100,100,100,100};
  float l2jbinlow[22]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  float l2jbinhi[22]={1000,1000,1000,1000,1000,1000,1000,10,1000,1000,1000,1000,1000,10,10,10,10,10,10,10,10,10};  
  
  for(int i=0;i<22;i++){
    for(int j=0;j<6;j++){
      TString plottitle= l2jplot[i]+"_l2j"+type[j];
      TString title= l2jfancyname[i]+type[j];
      h.vllplotl2j[i][j]=new TH1F(plottitle,title,l2jbin[i],l2jbinlow[i],l2jbinhi[i]);h.vllplotl2j[i][j]->Sumw2();
    }
  }
}

