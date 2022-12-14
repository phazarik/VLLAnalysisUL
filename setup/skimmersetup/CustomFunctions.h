

// CUSTOM FUNCTIONS


float VLLAna::delta_phi(float phi1, float phi2)
{
  //Calculate the correct deltaPhi=phi1-phi2
  phi1 = TVector2::Phi_0_2pi(phi1);
  phi2 = TVector2::Phi_0_2pi(phi2);
  float dphi = fabs(phi1 - phi2);
  if(dphi>TMath::Pi()) dphi = 2*TMath::Pi() - dphi;
  return dphi;
}

int VLLAna::MotherID(int partindex, int momindex)
{
  int parid =GenPart_pdgId[partindex];
  int momid = GenPart_pdgId[momindex];
  while(parid==momid){
    partindex=momindex;
    momindex=GenPart_genPartIdxMother[momindex];
    parid =GenPart_pdgId[partindex];
    momid = GenPart_pdgId[momindex];
  }
  return momid;
}
int VLLAna::IsGenMatched(int id, TLorentzVector t)
{
  int genmatch=0;
  
  //Light Lepton Matching//
  for(int i=0;i<(int)genllep.size();i++){    
    if(t.DeltaR(genllep.at(i).v)<0.2 && abs(id)==abs(genllep.at(i).pdgid)){
      genmatch=1;break;
    }
  }
  return genmatch;
}

int VLLAna::GenMatchedLepIndex(int id, TLorentzVector t)
{
  int genmatch=0,lepindex=-1.0; float dr=0.0,drmin=999.0;
  
  //Light Lepton Matching//
  for(int i=0;i<(int)genllep.size();i++){
    
    if(abs(id)==abs(genllep.at(i).pdgid)){
      dr=t.DeltaR(genllep.at(i).v);
      if(dr<drmin)drmin=dr;
      if(drmin<0.4){	
	genmatch=1;lepindex=i;break;	
      }
    }
  }
  //cout<<"LepIndex="<<lepindex<<endl;
  return lepindex;
}


bool VLLAna::LeptonIsbFake(TLorentzVector t, int opt)
{//t is the four vector for lepton
 //Find the recojet
 //SKIM 2: lepton-->RecoJet-->Find b quark nearby
 //SKIM 1: lepton-->RecoJet-->Matched genJet-->Find a bquark nearby
  
  bool result=false;int jetind=-1.0,genjetind=-1.0;
  if(opt==1){
    jetind=getMatchedJetIndex(t,1); //opt==1: matched recoJet Collection
    //cout<<"JetIndex="<<jetind<<endl;
    if(jetind >-1)
      genjetind=getMatchedJetIndex(jets.at(jetind).v,2);
    //cout<<"genJetIndex="<<genjetind<<endl;
    Lepton temp;
    if(genjetind>-1)
      temp= genjet.at(genjetind);
    bool isbjet= IsbJet(temp.v); //Manual Matching
    bool isbjet_partflav=abs(temp.partonflav)==5; //By partonFlav
    bool isbjet_hadflav=temp.hadronflav==5; //By JetHadronFlav
    
    if(isbjet)result=true;
  }
  
  if(opt==2){
    jetind=getMatchedJetIndex(t,1); //opt==1: matched recoJet Collection
    //cout<<"JetIndex="<<jetind<<endl;
    Lepton temp;
    if(jetind >-1)
      temp=jets.at(jetind);
    bool isbjet=IsbJet(temp.v);
    if(isbjet)result=true;
  }

  if(opt==3){
    jetind=GenMatchedLepIndex(13,t); //opt==1: matched recoJet Collection
    //cout<<"JetIndex="<<jetind<<endl;
    Lepton temp;
    if(jetind >-1)
      temp=genllep.at(jetind);
    bool isbjet=IsbJet(temp.v);
    if(isbjet)result=true;
  }
  return result;
}

bool VLLAna::IsbJet(TLorentzVector t)
{
  bool result=false;
  for(unsigned int i=0; i< (*nGenPart); i++){
    Lepton temp; temp.v.SetPtEtaPhiM(GenPart_pt[i],GenPart_eta[i],GenPart_phi[i],GenPart_mass[i]); 
    temp.status = GenPart_status[i]; temp.ind = i;  temp.pdgid = GenPart_pdgId[i];
    temp.momid=MotherID(i,GenPart_genPartIdxMother[i]);
    bool MotherIsNotb=abs(GenPart_pdgId[GenPart_genPartIdxMother[i]])!=5;
    bool HeavyFlav=(abs(temp.pdgid)>400 && abs(temp.pdgid)<600)||(abs(temp.pdgid)>4000 && abs(temp.pdgid)<6000);
    // bool selection = abs(temp.pdgid)==5 && abs(temp.momid)!=5 && MotherIsNotb;
    bool selection = HeavyFlav;
    
    if(selection){
      if(t.DeltaR(temp.v)<0.4){
	result=true;
	//cout<<"Lep Pt="<<t.Pt()<<endl;
	//cout<<"b-quark Pt="<<temp.v.Pt()<<endl;
	h.fracpt->Fill(t.Pt()/temp.v.Pt());
      }
    }
  }
  return result;
}
//B-taggedJet Match//
int VLLAna::IsbjetMatched(TLorentzVector t,int opt)
{
  int genmatch=0,jetindex=1.0;  
  vector<Lepton> tempjet;
  if(opt==1)tempjet=BTaggedJet;
  if(opt==2)tempjet=genjet;           //genjet= collection of gen bjet
  //Light Lepton Matching//
  for(int i=0;i<(int)tempjet.size();i++){
    if(t.DeltaR(tempjet.at(i).v)<0.4){
      genmatch=1;jetindex=tempjet[i].ind;break;
    }
  }
  return genmatch;
}
void VLLAna::TruthbJet()
{
  int genbindex=-1.0;
  for(unsigned int i=0; i< (*nGenPart); i++){
    Lepton temp; temp.v.SetPtEtaPhiM(GenPart_pt[i],GenPart_eta[i],GenPart_phi[i],GenPart_mass[i]); 
    temp.status = GenPart_status[i]; temp.ind = i;  temp.pdgid = GenPart_pdgId[i];
    temp.momid=MotherID(i,GenPart_genPartIdxMother[i]);
    
    if(abs(GenPart_pdgId[GenPart_genPartIdxMother[i]])==5)genbindex=GenPart_genPartIdxMother[i];
    //std::vector<int>::iterator it=std::find(bIndex.begin(),bIndex.end(),genbindex);
    // if(it!=bIndex.end())
    //  continue;
    //else{
    bIndex.push_back(genbindex);
  }
  //}
  
  int ndau,truthbind=-1,motherInd=-1;
  TLorentzVector mc,truthb;
  if(!_data){
    for(int i=0;i<(int)bIndex.size();i++){
      truthbind=bIndex.at(i);
      truthb.SetPtEtaPhiM(0,0,0,0);
      ndau=0;
      for(unsigned int j=0; j<(*nGenPart); j++){
        motherInd = GenPart_genPartIdxMother[j];
        if(GenPart_pdgId[motherInd]==GenPart_pdgId[truthbind] && motherInd==truthbind && GenPart_pdgId[j]!=22){
          ndau++;
          mc.SetPtEtaPhiM(GenPart_pt[j],GenPart_eta[j],GenPart_phi[j],GenPart_mass[j]);
          truthb += mc;
	}  
      }
      Lepton temp; temp.v.SetPtEtaPhiM(truthb.Pt(),truthb.Eta(),truthb.Phi(),truthb.M());
      temp.momid = MotherID(truthbind,GenPart_genPartIdxMother[truthbind]);
      truthbjet.push_back(temp);     
    }
    
  }
}

int VLLAna::getMatchedJetIndex(TLorentzVector t,int opt)
{
  int genmatch=0,jetindex=-1.0; float dr=0.0,drmin=999.0;  
  vector<Lepton> tempjet;
  if(opt==1)tempjet=jets;
  if(opt==2)tempjet=genjet;
  //Light Lepton Matching//
  for(int i=0;i<(int)tempjet.size();i++){
    dr=t.DeltaR(tempjet.at(i).v);
    if(dr<drmin)drmin=dr;
    if(drmin<0.4){
      genmatch=1;jetindex=i;break;
    }
  }
  return jetindex;
}



//DISTINCT OSSFN PAIR//
int VLLAna::getOSSFN()
{
  if((int)llep.size()==3){
    Lepton lep0=llep.at(0), lep1=llep.at(1),lep2=llep.at(2); 
    {
      if(abs(lep0.id)==abs(lep1.id) && lep0.charge != lep1.charge ) return 1;  
      if(abs(lep0.id)==abs(lep2.id) && lep0.charge != lep2.charge) return 1;
      if(abs(lep1.id)==abs(lep2.id) && lep1.charge != lep2.charge) return 1;
      else return 0;
    }
  }
  else return 0;
}

float VLLAna::getInvMass(TLorentzVector a,TLorentzVector b)
{
  return (a+b).M();
}
//is OSSF?
bool VLLAna::isOSSF(int i, int j)
{
  bool result= false;
  Lepton lep_i=llep.at(i),lep_j=llep.at(j);
  if(abs(lep_i.id)==abs(lep_j.id) && lep_i.charge != lep_j.charge ){
    result=true;
  }
  return result;
}

float VLLAna::OSSFMass(int i, int j)
{
  float mass=-1.0;
  Lepton lep_i=llep.at(i),lep_j=llep.at(j);
  if(abs(lep_i.id)==abs(lep_j.id) && lep_i.charge != lep_j.charge ){
    mass=getInvMass(lep_i.v,lep_j.v);
  }
  return mass;
}

//BEST OSSF PAIR
float VLLAna::getMOSSF()
{
  float bestMOSSF=-1.0, ZMass=91.0, dmMin=999.0;
  for(int i=0; i<(int)llep.size(); i++){
    for(int j=0; j<(int)llep.size();j++){
      if(j!=i && j>i){
	if(abs(llep.at(j).id)==abs(llep.at(i).id) && llep.at(j).charge!=llep.at(i).charge){
	  bool onZpair=getInvMass(llep.at(i).v,llep.at(j).v)>76 && getInvMass(llep.at(i).v,llep.at(j).v)<106;
	  if(onZpair){
	    if(abs(ZMass-getInvMass(llep.at(i).v,llep.at(j).v))<=dmMin){
	      bestMOSSF=getInvMass(llep.at(i).v,llep.at(j).v);
	      dmMin=abs(ZMass-getInvMass(llep.at(i).v,llep.at(j).v));
	    }
	  }
	}
      }
    }
  }
  return bestMOSSF;
}

//Non best on Z lepton index//
int VLLAna::NonBestOnZLeptonIndex()
{
  if((int)llep.size()==3){
    float LightLeptonBestMOSSF=getMOSSF();
    Lepton lep0=llep.at(0),lep1=llep.at(1),lep2=llep.at(2);
    float pair01mass=-1.0,pair02mass=-1.0,pair12mass=-1.0;
    if(isOSSF(0,1))  pair01mass=getInvMass(lep0.v,lep1.v);
    if(isOSSF(0,2))  pair02mass=getInvMass(lep0.v,lep2.v);
    if(isOSSF(1,2))  pair12mass=getInvMass(lep1.v,lep2.v);
    
    //NON Z LEPTON INDEX//
    if(pair01mass==LightLeptonBestMOSSF) return 2;
    if(pair02mass==LightLeptonBestMOSSF) return 1;
    if(pair12mass==LightLeptonBestMOSSF) return 0;
    else return 0;
  }
  else return 0;
}


float VLLAna::transv_mass(float lepE, float lepphi, float met, float metphi)
{
  float dphi = fabs(lepphi - metphi);
  if(dphi>TMath::Pi()) dphi = 2*TMath::Pi() - dphi;
  float mT = sqrt(2* lepE * met *(1-cos(dphi)));
  return mT;
}
