//////////////////////////
//                      //
// MVA Variables        //
//                      //
//                      //
/////////////////////////

void VLLAna::InitializeMVATreeBranch(){
  //  _mvaFile = new TFile("skim.root","recreate");
  tree = new TTree("TreeS","SignalTree");
  
  //Branch
  tree->Branch("nEvt",&nEvtTotal);                         //1.Event No
  tree->Branch("lep0_flavor",&lep0_flavor);                //2.Leading Lepton Flavor
  tree->Branch("lep0_pt",&lep0_pt);                        //3.Leading Lepton Pt
  tree->Branch("jet0_pt",&jet0_pt);                        //4.Leading Jet Pt
  tree->Branch("jet1_pt",&jet1_pt);                        //5.Subleading Jet Pt
  tree->Branch("lep0_mt",&lep0_mt);                        //6.Leading Lepton MT
  tree->Branch("jet0_mt",&jet0_mt);                        //7.Leading Jet MT
  tree->Branch("jet1_mt",&jet1_mt);                        //8.Subleading Jet MT
  tree->Branch("dijet_mass",&dijet_mass);                  //9.Dijet Invariant Mass
  tree->Branch("deltaR_jet01",&deltaR_jet01);              //10.deltaR(Leading Jet,Subleading Jet)
  tree->Branch("deltaPhi_metjet0",&deltaPhi_metjet0);      //11.deltaPhi(MET,Leading Jet)
  tree->Branch("deltaPhi_metjet1",&deltaPhi_metjet1);      //12.deltaPhi(MET,Subleading Jet)
  tree->Branch("deltaPhi_metlep0",&deltaPhi_metlep0);      //13.deltaPhi(MET,Leading Lepton)
  tree->Branch("deltaPhi_jet0lep0",&deltaPhi_jet0lep0);    //14.deltaPhi(Leading Jet,Leading Lepton)
  tree->Branch("deltaPhi_jet1lep0",&deltaPhi_jet1lep0);    //15.deltaPhi(Subleading Jet,Leading Lepton)
  tree->Branch("deltaPhi_dijetlep0",&deltaPhi_dijetlep0);  //16.deltaPhi(Dijet System,Leading Lepton)
  tree->Branch("deltaPhi_metdijet",&deltaPhi_metdijet);   //17.deltaPhi(Dijet System,MET)
  tree->Branch("dijet_pt",&dijet_pt);                      //18.Dijet System PT
  tree->Branch("dijet_mt",&dijet_mt);                      //19.Dijet System MT
  tree->Branch("event_MET",&event_MET);                    //20.MET
  tree->Branch("event_HT",&event_HT);                      //21.HT
  tree->Branch("event_ST",&event_ST);                      //22.ST
  tree->Branch("n_Jet",&n_Jet);                            //23.No of Jets
  tree->Branch("n_bJet",&n_bJet);                          //24.No of bjets  
}


// Important Note:
/*
These variables are defined at event level. So, if you think of a dataframe, for each row(i.e. event) there would be these 24 columns as defined above. 
You can directly read this MVATree branches in pandas dataframe/numpy arrays using Uproot. Then manipulate dataframe, train NN etc as usual
*/
