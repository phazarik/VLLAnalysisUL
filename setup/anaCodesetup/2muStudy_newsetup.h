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
  h.cutflow[0]->Fill((int)0, wt);
  h.cutflow[1]->Fill((int)0, wt);
  h.cutflow[2]->Fill((int)0, wt);
  h.cutflow[3]->Fill((int)0, wt);

  //Object level cuts:
  vector<bool> cut_obj =
    {
     Muon.at(0).reliso03 < 0.05,
     Muon.at(0).reliso04 < 0.05,
     Muon.at(0).sip3d < 1.5,
     mT0 > 40,
     Muon.at(1).reliso03 < 1,
     Muon.at(1).reliso04 < 1,
     Muon.at(1).sip3d < 5,
     mTss > 40
    };
  for(int i=0; i<(int)cut_obj.size(); i++){if(cut_obj[i] == true) h.cutflow[0]->Fill(i+1, wt);}
  
  //dimuon (ss) level cuts:
  vector<bool> cut_ss =
    {
     deta_ss_muons < 2,
     dR_ss_muons < 3,
     dphi_ss_muons < 2.5
    };
  for(int i=0; i<(int)cut_ss.size(); i++){if(cut_ss[i] == true) h.cutflow[1]->Fill(i+1, wt);}

  //event level cuts:
  vector<bool> cut_evt =
    {
     njet < 4,
     nbjet == 0,
     HT < 100,
     LT < 50
    };
  for(int i=0; i<(int)cut_evt.size(); i++){if(cut_evt[i] == true) h.cutflow[2]->Fill(i+1, wt);}

  //Combined cuts:
  //Isolation on the leading muon:
  bool cut_iso_mu0 = cut_obj[0] && cut_obj[1] && cut_obj[2];
  bool cut_iso_mu1 = cut_obj[4] && cut_obj[5] && cut_obj[6];
  bool cut_iso_mu = cut_iso_mu0 && cut_iso_mu1;
  //Cuts on nbjet and HT:
  bool cut_evt_jets = cut_evt[0] && cut_evt[1];
  bool cut_evt_E = cut_evt[2] && cut_evt[3];
  bool cut_evts = cut_evt_jets && cut_evt_E;

  bool cut_all = cut_iso_mu && cut_evt_E && cut_ss[1] && cut_ss[2]; 

  if(cut_iso_mu0)                h.cutflow[3]->Fill((int)1, wt);
  if(cut_iso_mu1)                h.cutflow[3]->Fill((int)2, wt);
  if(cut_iso_mu)                 h.cutflow[3]->Fill((int)3, wt);
  if(cut_evt_jets)               h.cutflow[3]->Fill((int)4, wt);
  if(cut_evt_E)                  h.cutflow[3]->Fill((int)5, wt);
  if(cut_evts)                   h.cutflow[3]->Fill((int)6, wt);
  if(cut_ss[1] && cut_ss[2])     h.cutflow[3]->Fill((int)7, wt);
  if(cut_iso_mu && cut_evt_jets) h.cutflow[3]->Fill((int)8, wt);
  if(cut_iso_mu && cut_evt_E)    h.cutflow[3]->Fill((int)9, wt);
  if(cut_iso_mu && cut_evts)     h.cutflow[3]->Fill((int)10, wt);
  if(cut_all)                    h.cutflow[3]->Fill((int)11, wt);
  
  if(cut_iso_mu){//Put selections here.
    //Object level plots:    
    h.studySS[0]->Fill(Muon.at(0).v.Pt(), wt);
    h.studySS[1]->Fill(Muon.at(0).v.Eta(), wt);
    h.studySS[2]->Fill(Muon.at(0).v.Phi(), wt);
    h.studySS[3]->Fill(mT0, wt);
    h.studySS[4]->Fill(Muon.at(0).reliso03, wt);
    h.studySS[5]->Fill(Muon.at(0).reliso04, wt);
    h.studySS[6]->Fill(Muon.at(0).sip3d, wt);
    h.studySS[7]->Fill(Muon.at(ss_ind).v.Pt(), wt);
    h.studySS[8]->Fill(Muon.at(ss_ind).v.Eta(), wt);
    h.studySS[9]->Fill(Muon.at(ss_ind).v.Phi(), wt);
    h.studySS[10]->Fill(mTss, wt);
    h.studySS[11]->Fill(Muon.at(ss_ind).reliso03, wt);
    h.studySS[12]->Fill(Muon.at(ss_ind).reliso04, wt);
    h.studySS[13]->Fill(Muon.at(ss_ind).sip3d, wt);
    
    //The dimuon (samesign) system::    
    h.studySS[14]->Fill(dimuon_ss_mass, wt);
    h.studySS[15]->Fill(deta_ss_muons, wt);
    h.studySS[16]->Fill(dphi_ss_muons, wt);
    h.studySS[17]->Fill(dR_ss_muons, wt);
    h.studySS[18]->Fill(ptratio, wt);
        
    //Event level plots:   
    h.studySS[19]->Fill(metpt, wt);
    h.studySS[20]->Fill(metphi, wt);
    h.studySS[21]->Fill(LT, wt);
    h.studySS[22]->Fill(HT, wt);
    h.studySS[23]->Fill(njet, wt);
    h.studySS[24]->Fill(nbjet, wt);
  }

}
