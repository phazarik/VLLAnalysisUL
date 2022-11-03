
// Signal Cutflow in each channel after various cuts

void VLLAna::SignalCutflow(){
  //FlowChart for signals//
  //ll
  if((int)llep.size()>0){
    n_l++;
    if(llep.at(0).v.Pt()>15){
      n_l15GeV++;
      if((abs(llep[0].id)==13)?llep.at(0).v.Pt()>26:llep.at(0).v.Pt()>32){
	n_trigg++;
	if((int)llep.size()>1){
	  n_2l++;
	}
      }
    }
  }
  
  //lt
  if((int)llep.size()==1){
    if((abs(llep[0].id)==13)?llep.at(0).v.Pt()>26:llep.at(0).v.Pt()>32){//Lepton Pass Trigger
      if((int)taus.size()>0){
	n_1l1t++;h.tauacc[0]->Fill(taus[0].v.Pt());                  //1L1T Base
	if(Tau_idDeepTau2017v2p1VSjet[taus[0].ind]>15){             //Pass Loose DeepCSV
	  n_1l1tloose++;h.tauacc[1]->Fill(taus[0].v.Pt());          
	  if(fabs(taus[0].v.Eta())<2.3){                             //Pass |n|<2.3
	    n_1l1tpassEta++;h.tauacc[2]->Fill(taus[0].v.Pt());
	    if(Tau_idDeepTau2017v2p1VSe[taus[0].ind]>15){           // Loose AntiEle
	      n_1l1tpassAntiEle++;h.tauacc[3]->Fill(taus[0].v.Pt()); 
	      if(Tau_idDeepTau2017v2p1VSmu[taus[0].ind]>3){         // Loose AntiMu
		n_1l1tpassAntiMu++;h.tauacc[4]->Fill(taus[0].v.Pt());
		if(fabs(Tau_dz[taus[0].ind])<0.2){                   // Pass prompt(dz cut)
		  n_1l1tprompt++;h.tauacc[5]->Fill(taus[0].v.Pt());
		  if(taus[0].lepcleaning){                           // LooseLepton Cleaning
		    n_1l1tlepclean++;h.tauacc[6]->Fill(taus[0].v.Pt());
		    if(taus[0].v.Pt()>20){                           // Tau Pt >20 GeV
		      n_1l1tpassPt++;h.tauacc[7]->Fill(taus[0].v.Pt());
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }
      
  
  
  
  //tt
  if((int)taus.size()>0){
    n_t++;
    if((int)taus.size()>1){
      n_2t++;
      if(taus[0].v.Pt()>35){
	n_t35GeV++;
	if(taus[0].v.Pt()>70){
	  n_tautrigg++;
	}
      }
    }
  }  
}


