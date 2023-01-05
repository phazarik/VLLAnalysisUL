
/*
=======================================
  VLL Event Selection
=======================================
Arnab Laha, July 8, 2022
=======================================
Select >=2L, 1L + >=1T and 1L + >=2J

Medium Lepton, VT Tau, Tight Jets
=======================================
*/

void VLLAna::EventSelection(){
  //ll event
  if((int)llep.size()>1){
    bool passTrigger=false,lightlepdrmin=false;
    if(abs(llep.at(0).id)==13 && llep.at(0).v.Pt()>26)
      passTrigger=true;
    if(abs(llep.at(0).id)==11 && llep.at(0).v.Pt()>32)
      passTrigger=true;
    if(llep.at(0).v.DeltaR(llep.at(1).v)>0.2)lightlepdrmin=true;
    if(passTrigger && lightlepdrmin)is_ll_event=true, n_ll++;
  }
  
  //lt
  else if((int)llep.size()==1 && (int)taus.size()>0){
    bool passTrigger=false,ltdrmin=false;
    if(abs(llep.at(0).id)==13 && llep.at(0).v.Pt()>26)
      passTrigger=true;
    if(abs(llep.at(0).id)==11 && llep.at(0).v.Pt()>32)
      passTrigger=true;
    if(llep.at(0).v.DeltaR(taus.at(0).v)>0.2)ltdrmin=true;
    if(passTrigger && ltdrmin)is_lt_event=true, n_lt++;
  }
  //l+2j
  else if((int)llep.size()==1 && (int)jets.size()>1){
    bool passTrigger=false;//ltdrmin=false;
    if(abs(llep.at(0).id)==13 && llep.at(0).v.Pt()>26)
      passTrigger=true;
    if(abs(llep.at(0).id)==11 && llep.at(0).v.Pt()>32)
      passTrigger=true;
    //if(llep.at(0).v.DeltaR(taus.at(0).v)>0.2)ltdrmin=true;
    if(passTrigger)is_l2j_event=true,n_l2j++;
  }
  
  //tt		
  else if((int)taus.size()>1){
    bool passTrigger=false,ttdrmin=false;
    if(taus.at(0).v.Pt()>35)
      passTrigger=true;
    if(taus.at(0).v.DeltaR(taus.at(1).v)>0.2)ttdrmin=true;
    if(passTrigger && ttdrmin)is_tt_event=true,n_tt++;
  }
}
