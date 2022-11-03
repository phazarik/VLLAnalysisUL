
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
  
  if((int)llep.size()>0){ //Atleast one lepton
    bool passTrigger=false;
    if(abs(llep.at(0).id)==13 && llep.at(0).v.Pt()>26)
      passTrigger=true;
    if(abs(llep.at(0).id)==11 && llep.at(0).v.Pt()>32)
      passTrigger=true;

    if(passTrigger){
      if((int)llep.size()>1){is_ll_event=true,n_ll++;}              // >=2L events
      else if((int)llep.size()==1 && (int)taus.size()>0){           // 1L+>=1T events
	is_lt_event=true;n_lt++;
      }
      else if((int)llep.size()==1 && (int)jets.size()>1){           // 1L + >=2Jets events
	is_l2j_event=true;n_l2j++;	
      }
      else if((int)taus.size()>1){                                  // >2T events
	is_tt_event=true;n_tt++;
      }
    }
  }
}

//#####################################################
