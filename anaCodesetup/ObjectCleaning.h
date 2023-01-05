/*
======================================
   Object Cleaning Function

======================================
        Documentation
       ----------------
Describe what is done  

*/

// FUNCTION STARTS

//Muon cleaning: Clean an electron against Muon
bool VLLAna::MuonCleaning(TLorentzVector t, int opt)
{
  bool result1=false;
  vector<Lepton> lepton;
  if(opt==0)lepton=loosemuon;
  if(opt==1)lepton=Muon;
  
  if((int)lepton.size()==0)
    result1=true;
  if((int)lepton.size()>0){
    for(int i=0; i<(int)lepton.size(); i++){
      if(t.DeltaR(lepton[i].v)>0.5)
        result1=true;
      else{
        result1=false;
        break;
      }
    }
  }
  return result1;
}


// Clean a tau against light lepton
bool VLLAna::TaulepCleaning(TLorentzVector t)
{
  bool result1=false;
  if((int)LooseLep.size()==0)
    result1=true;
  if((int)LooseLep.size()>0){
    for(int i=0; i<(int)LooseLep.size(); i++){
      if(t.DeltaR(LooseLep[i].v)>0.5)
        result1=true;
      else{
        result1=false;
        break;
      }
    }
  }
  return result1;
}

// Clean a jet against tau
bool VLLAna::TaujetCleaning(TLorentzVector t)
{
  bool result1=false;
  if((int)taus.size()==0)
    result1=true;
  if((int)taus.size()>0){
    for(int i=0; i<(int)taus.size(); i++){
      if(t.DeltaR(taus[i].v)>0.4)
        result1=true;
      else{
        result1=false;
        break;
      }
    }
  }
  return result1;
}

//Clean a jet against light lepton
bool VLLAna::LepjetCleaning(TLorentzVector t)
{
  bool result1=false;
  if((int)LooseLep.size()==0)
    result1=true;
  if((int)LooseLep.size()>0){
    for(int i=0; i<(int)LooseLep.size(); i++){
      if(t.DeltaR(LooseLep[i].v)>0.4)
        result1=true;
      else{
        result1=false;
        break;
      }
    }
  }
  return result1;
}

// END


