void VLLAna::Make2muPlots(float wt)
{
  //This function is called in the main VLLAna.C file.
  //It runs for all the 2Mu same-sign events.

  //Picking the samesign pair:
  //The first one is the leading one.
  //The index of the second one is calculated below.
  int ss_ind=-1;
  for(int i=1; i<(int)Muon.size(); i++){
    if(Muon.at(0).charge == Muon.at(i).charge){
      ss_ind = i;
      break;
    }
  }

  //Variables to be used later:
  //Object level:
  float mT0 = transv_mass(Muon.at(0).v.E(), Muon.at(0).v.Phi(), metpt, metphi);
  float mTss = transv_mass(Muon.at(ss_ind).v.E(), Muon.at(ss_ind).v.Phi(), metpt, metphi);

  //dimuon (ss) system:
  float dimuon_ss_mass = (Muon.at(0).v + Muon.at(ss_ind).v).M();
  float dR_ss_muons = Muon.at(0).v.DeltaR(Muon.at(ss_ind).v);
  float deta_ss_muons = fabs(Muon.at(0).v.Eta()-Muon.at(ss_ind).v.Eta());
  float dphi_ss_muons = delta_phi(Muon.at(0).v.Phi(), Muon.at(ss_ind).v.Phi());
  float ptratio = Muon.at(ss_ind).v.Pt()/Muon.at(0).v.Pt();

  //event level:
  float LT=0; for(int i=0; i<(int)Muon.size(); i++) LT = LT + Muon.at(i).v.Pt();
  float HT=0; for(int i=0; i<(int)jets.size(); i++) HT = HT + jets.at(i).v.Pt();
  int njet = (int)jets.size();
  int nbjet = (int)BTaggedJet.size();

  //Cutflow:
  //The first bin contains the original number of events with basic selections:
  h.cutflow[0]->Fill(0); h.cutflow[1]->Fill(0); h.cutflow[2]->Fill(0);

  //Object level cuts:
  vector<bool> cut_obj =
    {
     Muon.at(0).reliso03 < 2,
     Muon.at(0).reliso04 < 2,
     Muon.at(0).sip3d < 10,
     mT0 < 500,
     Muon.at(1).reliso03 < 5,
     Muon.at(1).reliso04 < 5,
     Muon.at(1).sip3d < 20,
     mTss < 300
    };
  for(int i=0; i<(int)cut_obj.size(); i++){if(cut_obj[i] == true) h.cutflow[0]->Fill(i+1);}
  
  //dimuon (ss) level cuts:
  vector<bool> cut_ss =
    {
     deta_ss_muons < 3,
     dR_ss_muons < 4
    };
  for(int i=0; i<(int)cut_ss.size(); i++){if(cut_ss[i] == true) h.cutflow[1]->Fill(i+1);}

  //event level cuts:
  vector<bool> cut_evt =
    {
     njet < 6,
     nbjet < 3,
     LT < 400,
     HT < 400
    };
  for(int i=0; i<(int)cut_evt.size(); i++){if(cut_evt[i] == true) h.cutflow[2]->Fill(i+1);}
  
  if(true){//Put selections here.
    //Object level plots:    
    h.studySS[0]->Fill(Muon.at(0).v.Pt());
    h.studySS[1]->Fill(Muon.at(0).v.Eta());
    h.studySS[2]->Fill(Muon.at(0).v.Phi());
    h.studySS[3]->Fill(mT0);
    h.studySS[4]->Fill(Muon.at(0).reliso03);
    h.studySS[5]->Fill(Muon.at(0).reliso04);
    h.studySS[6]->Fill(Muon.at(0).sip3d);
    h.studySS[7]->Fill(Muon.at(ss_ind).v.Pt());
    h.studySS[8]->Fill(Muon.at(ss_ind).v.Eta());
    h.studySS[9]->Fill(Muon.at(ss_ind).v.Phi());
    h.studySS[10]->Fill(mTss);
    h.studySS[11]->Fill(Muon.at(ss_ind).reliso03);
    h.studySS[12]->Fill(Muon.at(ss_ind).reliso04);
    h.studySS[13]->Fill(Muon.at(ss_ind).sip3d);
    
    //The dimuon (samesign) system::    
    h.studySS[14]->Fill(dimuon_ss_mass);
    h.studySS[15]->Fill(deta_ss_muons);
    h.studySS[16]->Fill(dphi_ss_muons);
    h.studySS[17]->Fill(dR_ss_muons);
    h.studySS[18]->Fill(ptratio);
        
    //Event level plots:   
    h.studySS[19]->Fill(metpt);
    h.studySS[20]->Fill(metphi);
    h.studySS[21]->Fill(LT);
    h.studySS[22]->Fill(HT);
    h.studySS[23]->Fill(njet);
    h.studySS[24]->Fill(nbjet);
  }

}
