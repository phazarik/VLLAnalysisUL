//Prototype of Analysis Code

// llep, jets array are automatically feeded

void VLLAna::Analysis2L(){
  //cout<<"No of light lepton in 2L event="<<lep.size()<<endl;
  float LT =llep[0].v.Pt()+llep[1].v.Pt();
  float MET=metpt;
  float HT=-1.0;
  for(int i=0;i<(int)jets.size();i++)
    HT=HT+jets.at(i).v.Pt();
  float ST=LT+MET+HT;
  float mtlep0=sqrt(2.0*llep[0].v.Pt()*metpt*(1-cos(delta_phi(llep[0].v.Phi(),metphi))));
  float mtlep1=sqrt(2.0*llep[1].v.Pt()*metpt*(1-cos(delta_phi(llep[1].v.Phi(),metphi))));
  float dileppt=(llep[0].v+llep[1].v).Pt();
  float dilepmt=sqrt(2.0*dileppt*metpt*(1-cos(delta_phi((llep[0].v+llep[1].v).Phi(),metphi))));
  float Mass=getInvMass(llep[0].v,llep[1].v);//Invariant Mass
  
  float OSMass=-1.0,SSMass=-1.0;
  if(llep[0].charge != llep[1].charge)OSMass=getInvMass(llep[0].v,llep[1].v);//OS Mass
  if(llep[0].charge == llep[1].charge)SSMass=getInvMass(llep[0].v,llep[1].v);//SS Mass
  
  float OSSFMass=-1.0,SSSFMass=-1.0,OSOFMass=-1.0,SSOFMass=-1.0;
  if(abs(llep[0].id)==abs(llep[1].id)){//SF
    if(llep[0].charge != llep[1].charge)OSSFMass=getInvMass(llep[0].v,llep[1].v);//OSSF
    if(llep[0].charge == llep[1].charge)SSSFMass=getInvMass(llep[0].v,llep[1].v);//SSSF
  }
  else
    {
      if(llep[0].charge != llep[1].charge)OSSFMass=getInvMass(llep[0].v,llep[1].v);//OSOF
      if(llep[0].charge == llep[1].charge)SSSFMass=getInvMass(llep[0].v,llep[1].v);//SSOF
    }
  
  float dPhijet0met=-1.0,dRlep0jet0=-1.0,dRlep1jet0=-1.0;
  if((int)jets.size()>0){
    dPhijet0met=delta_phi(jets.at(0).v.Phi(),metphi);
    dRlep0jet0=llep[0].v.DeltaR(jets.at(0).v);
    dRlep1jet0=llep[1].v.DeltaR(jets.at(0).v);    
  }
  float njet=(int)jets.size();
  float nbjet=(int)BTaggedJet.size();
  
  
  //Selections
  vector<int>channelindex,flavindex;
  bool channel_2L=true;
  bool channel_OS=false;bool channel_SS=false;
  bool flav_ee=false;bool flav_emu=false;bool flav_mumu=false;
  
  if(llep[0].charge != llep[1].charge)channel_OS=true;
  if(llep[0].charge == llep[1].charge)channel_SS=true;
  if(abs(llep[0].id)==11 && abs(llep[1].id)==11)flav_ee=true;
  if(abs(llep[0].id)==13 && abs(llep[1].id)==13)flav_mumu=true;
  if((abs(llep[0].id)==11 && abs(llep[1].id)==13)||(abs(llep[0].id)==13 && abs(llep[1].id)==11))flav_emu=true;
  
  if(channel_2L)channelindex.push_back(0),h.landscape2L->Fill(0);//Inclusive
  if(channel_OS)channelindex.push_back(1),h.landscape2L->Fill(1);//FlavInclusive(OS)
  if(channel_SS)channelindex.push_back(2),h.landscape2L->Fill(2);//FlavInclusive(SS)
  if(flav_ee)channelindex.push_back(3),h.landscape2L->Fill(3);   //ee
  if(flav_emu)channelindex.push_back(4),h.landscape2L->Fill(4);  //emu
  if(flav_mumu)channelindex.push_back(5),h.landscape2L->Fill(5); //mumu
  
  if(channel_OS && flav_ee)channelindex.push_back(6),h.landscape2L->Fill(6);//ee and SS channel
  if(channel_SS && flav_ee)channelindex.push_back(7),h.landscape2L->Fill(7);//ee and OS channel
  if(channel_OS && flav_emu)channelindex.push_back(8),h.landscape2L->Fill(8);//emu and SS channel
  if(channel_SS && flav_emu)channelindex.push_back(9),h.landscape2L->Fill(9);//emu and OS channel
  if(channel_OS && flav_mumu)channelindex.push_back(10),h.landscape2L->Fill(10);//mumu and SS channel
  if(channel_SS && flav_mumu)channelindex.push_back(11),h.landscape2L->Fill(11);//mumu and OS channel
  
  
  //Fill Histograms
  for(vector<int>::iterator iter = channelindex.begin();iter<channelindex.end();iter++){
    h.vllplot2l[0][*iter]->Fill(llep[0].v.Pt(),evtwt);
    h.vllplot2l[1][*iter]->Fill(llep[1].v.Pt(),evtwt);
    h.vllplot2l[2][*iter]->Fill(llep[0].v.Eta(),evtwt);
    h.vllplot2l[3][*iter]->Fill(llep[1].v.Eta(),evtwt);
    h.vllplot2l[4][*iter]->Fill(llep[0].v.Phi(),evtwt);
    h.vllplot2l[5][*iter]->Fill(llep[1].v.Phi(),evtwt);
    h.vllplot2l[6][*iter]->Fill(llep[0].v.DeltaR(llep[1].v),evtwt);
    h.vllplot2l[7][*iter]->Fill(delta_phi(llep[0].v.Phi(),metphi),evtwt);
    h.vllplot2l[8][*iter]->Fill(delta_phi(llep[1].v.Phi(),metphi),evtwt);
    h.vllplot2l[9][*iter]->Fill(Mass,evtwt);
    h.vllplot2l[10][*iter]->Fill(OSMass,evtwt);
    h.vllplot2l[11][*iter]->Fill(SSMass,evtwt);
    h.vllplot2l[12][*iter]->Fill(OSSFMass,evtwt);
    h.vllplot2l[13][*iter]->Fill(OSOFMass,evtwt);
    h.vllplot2l[14][*iter]->Fill(SSSFMass,evtwt);
    h.vllplot2l[15][*iter]->Fill(SSOFMass,evtwt);
    h.vllplot2l[16][*iter]->Fill(mtlep0,evtwt);
    h.vllplot2l[17][*iter]->Fill(mtlep1,evtwt);
    h.vllplot2l[18][*iter]->Fill(dileppt,evtwt);
    h.vllplot2l[19][*iter]->Fill(dilepmt,evtwt);
    h.vllplot2l[20][*iter]->Fill(njet,evtwt);
    h.vllplot2l[21][*iter]->Fill(nbjet,evtwt);
    h.vllplot2l[22][*iter]->Fill(dPhijet0met,evtwt);
    h.vllplot2l[23][*iter]->Fill(dRlep0jet0,evtwt);
    h.vllplot2l[24][*iter]->Fill(dRlep1jet0,evtwt);
    h.vllplot2l[25][*iter]->Fill(LT,evtwt);
    h.vllplot2l[26][*iter]->Fill(MET,evtwt);
    h.vllplot2l[27][*iter]->Fill(HT,evtwt);
    h.vllplot2l[28][*iter]->Fill(ST,evtwt);
    h.vllplot2l[29][*iter]->Fill(*iter,evtwt);
  }
}

void VLLAna::Book2LAnalysisHistograms(){
  //2L events histos
  TString plotname[30]={"ptlep0","ptlep1","etalep0","etalep1","philep0","philep1","dRlep01","dphimetlep0","dphimetlep1","mass","OSmass","SSmass","OSSFmass","OSOFmass","SSSFmass","SSOFmass","mtlep0","mtlep1","dileppt","dilepmt","njet","nbjet","dphijet0met","dRlep0jet0","dRlep1jet0","LT","MET","HT","ST","N_channel"};
  TString fancyname[30]={"First Lepton PT","Second Lepton PT","First Lepton Eta","Second Lepton Eta","First Lepton Phi","Second Lepton Phi","dR(first lepton, second lepton)","dPhi(met,first lepton)","dphi(met,second lepton)","Invariant Mass","OSMass","SSMass","M_OSSF","M_OSSF","M_SSOF","M_SSSF","First Lepton MT","Second Lepton MT","Dilepton system PT","Dilepton system MT","No of Jets","No of medium bjets","dphi(met,leading jet)","dphi(leading jet, first lepton)","dphi(leading jet, second lepton)","LT","MET","HT","ST","nEvt_channel"};
  
  TString channel[12]={"2L","2L_OS","2L_SS","ee","emu","mumu","ee_OS","ee_SS","emu_OS","emu_SS","mumu_OS","mumu_SS"};
  
  float bin_2l[30]={1000,1000,100,100,100,100,100,100,100,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,10,10,100,100,100,1000,1000,1000,1000,15};
  float binlow_2l[30]={0,0,-5,-5,-5,-5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  float binhi_2l[30]={1000,1000,5,5,5,5,5,5,5,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,10,10,5,5,5,1000,1000,1000,1000,15};
  
  //book histograms
  for(int ichan=0;ichan<12;ichan++){
    for(int iplot=0;iplot<30;iplot++){
      TString title=plotname[iplot]+"_"+channel[ichan];
      TString label=fancyname[iplot]+"_"+channel[ichan];
      
      h.vllplot2l[iplot][ichan]=new TH1F(title,label,bin_2l[iplot],binlow_2l[iplot],binhi_2l[iplot]);
      h.vllplot2l[iplot][ichan]->Sumw2();
    }
  }//end of for loop


  //2L Landscape
  TString title="0:2L,1:2LOS,2:2LSS,3:ee,4:emu+mue,5.mumu,6:eeOS,7:eeSS,8:emu+mue_OS,9:emu+mue_SS,10:mumuOS,11:mumuSS";
  h.landscape2L = new TH1F("Landscape2L",title,15,0,15);h.landscape2L->Sumw2();
}

