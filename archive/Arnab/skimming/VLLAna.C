#define VLLAna_cxx
#include "VLLAna.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
//Include SF correction header files
#include "/home/work/alaha1/work/FullRun2/VLLAnalysisUL/setup/skimmersetup/IISERLogo.h"
#include "/home/work/alaha1/work/FullRun2/VLLAnalysisUL/setup/skimmersetup/corrections/MuonScaleFactor.h"
#include "/home/work/alaha1/work/FullRun2/VLLAnalysisUL/setup/skimmersetup/corrections/ElectronScaleFactor.h"
#include "/home/work/alaha1/work/FullRun2/VLLAnalysisUL/setup/skimmersetup/corrections/TauScaleFactor.h"
#include "/home/work/alaha1/work/FullRun2/VLLAnalysisUL/setup/skimmersetup/corrections/TriggerEfficiencyScaleFactor.h"
#include "/home/work/alaha1/work/FullRun2/VLLAnalysisUL/setup/skimmersetup/corrections/ApplyScaleFactors.h"
  
#include "/home/work/alaha1/work/FullRun2/VLLAnalysisUL/setup/skimmersetup/ProduceGenCollection.h"
#include "/home/work/alaha1/work/FullRun2/VLLAnalysisUL/setup/skimmersetup/ObjectCleaning.h"
#include "/home/work/alaha1/work/FullRun2/VLLAnalysisUL/setup/skimmersetup/ProduceRecoCollection.h"

#include "/home/work/alaha1/work/FullRun2/VLLAnalysisUL/setup/skimmersetup/EventSelection.h"
#include "/home/work/alaha1/work/FullRun2/VLLAnalysisUL/setup/skimmersetup/SignalCutflow.h"
#include "/home/work/alaha1/work/FullRun2/VLLAnalysisUL/setup/skimmersetup/CustomFunctions.h"

#include "skimmerHelper.h"  


void VLLAna::Begin(TTree * /*tree*/)
{
  iiserlogo();
  //cout<<"Inside Begin()"<<endl;
  TString option = GetOption();
  ReadNNWeights();
}

void VLLAna::SlaveBegin(TTree *tree /*tree*/)
{
  time(&start);
  //Init(tree);
  //cout<<"Inside SlaveBegin()"<<endl;
  TString option = GetOption();
  nEvtTotal = 0;
  nEvtRan = 0;
  nEvtTrigger=0;
  nEvtSkim=0;
  
  n3L=0; n3LonZ=0; n_mu_anlys=0;      n_mu_NNScore=0;
  n_mu_bfake=0;    n_mu_bfake_flav=0; n_mu_prompt=0;
  n_bfake_matching=0;n_ttbarcr=0;n_ttbar2Lplus1Fake=0;
  
  n_ll=0,n_lt=0,n_tt=0,n_l2j=0;
  n_l=0,n_l15GeV=0,n_trigg=0,n_2l=0,n_1l1t=0;
  n_t=0,n_2t=0,n_t35GeV=0,n_tautrigg=0;
  n_ll_OSSF=0,n_ll_OSOF=0,n_ll_SSSF=0,n_ll_OSOF=0;
  
  n_1l1tloose=0,n_1l1tpassEta=0,n_1l1tpassAntiEle=0,n_1l1tpassAntiMu=0;
  n_1l1tprompt=0,n_1l1tlepclean=0,n_1l1tpassPt=0;
  
  //Create the histogram file
  _HstFile = new TFile(_HstFileName,"recreate");
  BookHistograms();
  
  //Deactivate Branches
  tree->SetBranchStatus("*",0);
  //Activate Branches
  ActivateBranch(tree);   //Look at skimmerHelper.h file
  
  //Add nTotEvent branch to the SkimTree : Look at Init() in VLLAna.h to check how we create skimTree and SkimFile
  
  //skimTree->Branch("nEvtTotal",&nEvtTotal);
}
void VLLAna::SlaveTerminate()
{
  //cout<<"Inside SlaveTerminate()"<<endl;
  //Write histograms and close histogram file
  //_mvaFile->Write();
  //_mvaFile->Close();
  _HstFile->Write();
  _HstFile->Close();
  
  cout<<"Writing Skim File....";
  //skimTree->Print();
  //_SkimFile->Write();
  skimTree->Write();
  _SkimFile->Close();
  cout<<"   Done!  "<<endl;
  //skimTree->Print();
  //Output to screen.
  cout<<"Total Triggered events = "<< nEvtTrigger <<endl;
  cout<<"Total events ran       = "<<nEvtRan<<endl;
  cout<<"Total events           = "<<nEvtTotal<<endl;
  cout<<"Total events skimmed   = "<<nEvtSkim<<endl;
  cout<<"-----------------------------------------------"<<endl;
  cout<<"               Event Selection                 "<<endl;
  cout<<"-----------------------------------------------"<<endl;
  cout<<"No of 2L Events        = "<<n_ll<<endl;
  cout<<"No of 1L1T Events      = "<<n_lt<<endl;
  cout<<"No of 1L2J Events      = "<<n_l2j<<endl;
  cout<<"No of 2T Events        = "<<n_tt<<endl;
  cout<<"_______________________________________________"<<endl;
  
  //Open the text output file
  ofstream fout(_SumFileName);
  //Put text output in the summary file.
  fout<<"Total events  = "<<nEvtTotal<<endl;
  fout<<"Total events ran = "<<nEvtRan<<endl;
  fout<<"Total events skimmed  = "<<nEvtSkim<<endl;
  
  //TIME KEEPING
  time(&end);
  double time_taken = double(end-start);
  cout<<"Time taken by the program is= "<<fixed<<time_taken<<setprecision(5);
  cout<<"sec"<<endl;
}


void VLLAna::Terminate()
{
  //   cout<<"Inside Terminate()"<<endl;
}

Bool_t VLLAna::Process(Long64_t entry)
{
  fReader.SetLocalEntry(entry);
  if(_data == 0)
    fReader_MC  .SetLocalEntry(entry);
  if(_data == 1)
    fReader_Data.SetLocalEntry(entry);
  
  //Verbosity determines the number of processed events after which the root prompt is supposed to display a status update.
  if(_verbosity==0 && nEvtTotal%10000==0)cout<<"Processed "<<nEvtTotal<<" event..."<<endl;      
  else if(_verbosity>0 && nEvtTotal%10000==0)cout<<"Processed "<<nEvtTotal<<" event..."<<endl;
  nEvtTotal++;
  h.nevt->Fill(0);
  
  ReadBranch();
  //skimTree->Fill(); //WITHOUT ANY SELECTIONS
  
  h.metfilter[0]->Fill(*Flag_goodVertices);
  h.metfilter[1]->Fill(*Flag_globalSuperTightHalo2016Filter);
  h.metfilter[2]->Fill(*Flag_HBHENoiseFilter);
  h.metfilter[3]->Fill(*Flag_HBHENoiseIsoFilter);
  h.metfilter[4]->Fill(*Flag_EcalDeadCellTriggerPrimitiveFilter);
  h.metfilter[5]->Fill(*Flag_BadPFMuonFilter);
  h.metfilter[6]->Fill(*Flag_eeBadScFilter);
  
  GoodEvt2018 = (_year==2018 ? *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter && *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter && (_data ? *Flag_eeBadScFilter : 1) : 1);
  GoodEvt2017 = (_year==2017 ? *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter && *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter && (_data ? *Flag_eeBadScFilter : 1) : 1);
  GoodEvt2016 = (_year==2016 ? *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter && *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter && (_data ? *Flag_eeBadScFilter : 1) : 1);
  
  h.metfilter[7]->Fill(GoodEvt2016);
  h.metfilter[8]->Fill(GoodEvt2017);
  h.metfilter[9]->Fill(GoodEvt2018);
  
  GoodEvt = GoodEvt2018 && GoodEvt2017 && GoodEvt2016;
  
  h.metfilter[10]->Fill(GoodEvt);
  
  if(GoodEvt){
    
    nEvtRan++; //only good events
    h.nevt->Fill(1);
    
    
    triggerRes=true; //Always true for MC
    if(_data==1){
      trigger2018 = (_year==2018 ? (_lep==1 ? *HLT_IsoMu24==1 : _lep==0 && *HLT_Ele32_WPTight_Gsf) : 1);
      //trigger2017 = (_year==2017 ? (_lep==1 ? *HLT_IsoMu27==1 : _lep==0 && (*HLT_Ele32_WPTight_Gsf||*HLT_Ele32_WPTight_Gsf_L1DoubleEG)) : 1);
      trigger2017 = (_year==2017 ? (_lep==1 ? *HLT_IsoMu27==1 : _lep==0 && (*HLT_Ele32_WPTight_Gsf)) : 1);
      trigger2016 = (_year==2016 ? (_lep==1 ? (*HLT_IsoMu24==1) : _lep==0 && *HLT_Ele27_WPTight_Gsf) : 1);
      
      
      triggerRes = trigger2018 && trigger2017 && trigger2016;
      
    }
    if(triggerRes){
      nEvtTrigger++; //only triggered events
      h.nevt->Fill(2);
      
      
      //-----------------------------------------------------------------------------------------------------------------------
      //                                              GEN OBJECTS BLOCK BEGINS                                                |
      //-----------------------------------------------------------------------------------------------------------------------
      
      if(_data==0){
	//TruthLevelInfo();
	genMuon.clear(),genElectron.clear(),genPart.clear();
	genTau.clear(),truthtaus.clear(),genHadronicTau.clear(),genllep.clear();
	genjet.clear(),bIndex.clear(),truthbjet.clear();
	
	//CALL THE DEDICATED FUNCTION TO CREATE GENMU AND GENELE ARRAY
	GenMuon();
	GenElectron();
	GenJet();
	//GenVisTau();
	Sort(0);//sort all genarray
	
	//NO OF GEN OBJECTS 
	h.genpltmu[0]->Fill((int)genMuon.size());
	h.genpltele[0]->Fill((int)genElectron.size());
	h.genplttau[0]->Fill((int)genHadronicTau.size());
	h.genPart[1]->Fill((int)genllep.size());
	//cout<<"Object are accessible outside functions.GenMuon Size="<<genMuon.size()<<endl;
	


	// SOME GEN LEVEL STUDY (remove this later)
	for(int i=0;i<(int)genllep.size();i++)
	  h.genPart[2]->Fill(genllep.at(i).pdgid);	
	
	//GenJet investigation
	int nbgenjet_partflav=0,nbgenjet_hadflav=0,nbgenjet_bflav=0;
	for(int i=0;i<(int)genjet.size();i++){
	  if(abs(genjet.at(i).partonflav)==5)nbgenjet_partflav++;
	  if(genjet.at(i).hadronflav==5)nbgenjet_hadflav++;
	  if(genjet.at(i).bflav)nbgenjet_bflav++;
	}
	h.genjet[0]->Fill(nbgenjet_partflav);
	h.genjet[1]->Fill(nbgenjet_hadflav);
	h.genjet[2]->Fill(nbgenjet_bflav);
	
	
	
      }
      //-----------------------------------------------------------------------------------------------------------------------
      //                                              RECO OBJECTS BLOCK BEGINS                                               |
      //-----------------------------------------------------------------------------------------------------------------------
      
      llep.clear(); //clear array from previous event
      Muon.clear();Electron.clear();Photon.clear();loosemuon.clear();
      LooseLep.clear();BTaggedJet.clear();jets.clear();taus.clear();
      
      //Call Functions that produce Reco Collections
      RecoLightLepton(); //ele,mu and llep: Muon(),Electron(),llep();
      RecoTau();         //hadronictaus : taus()
      RecoJetandBJets(); // jets and bjets : jets(),BTaggedJet();
      
      h.nlep[1]->Fill(Muon.size());
      
      
      //Sorting Function
      //0=All gen array, 1= llep,2=muon,3=electron,4=taus,5=jets,6=bjet,7=photon;
      //9=LooseLepton;
      //Sort llep,Muon,Electron 
      Sort(1);
      Sort(2);
      Sort(3);
      Sort(4);
      Sort(5);
      Sort(6);//5=jets,6=BtaggedJet
      
      
      //Some jets plots
      h.nJet[0]->Fill((int)jets.size());
      h.nJet[1]->Fill((int)BTaggedJet.size());
      
      /*==========================
	       MET
       ===========================*/
      metpt = *MET_pt;
      metphi = *MET_phi;
      
      h.etmiss->Fill(metpt);//fill a histogram with the missing Et of the event.
      
      //  cout<<"jet & met stored"<<endl;
      
      //-----------------------------------------------------------------------------------------------------------------------
      //                                              RECO OBJECTS BLOCK ENDS                                                 |
      //-----------------------------------------------------------------------------------------------------------------------


      //-----------------------------------------------------------------------------------------------------------------------
      //                                        EVENT SELECTION                                                               |
      //-----------------------------------------------------------------------------------------------------------------------
      
      is_ll_event=false,is_lt_event=false,is_tt_event=false,is_l2j_event=false;//Global variable
      if((int)llep.size()>0){ //Atleast one lepton
	bool passTrigger=false;
	if(abs(llep.at(0).id)==13 && llep.at(0).v.Pt()>26)              // Muon PT>26 GeV
	  passTrigger=true;
	if(abs(llep.at(0).id)==11 && llep.at(0).v.Pt()>35)              // Ele PT >32 GeV
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
      
      //EventSelection();      
      // cout<<"IS LL event?====>"<<is_ll_event<<endl;
      
      //-----------------------------------------------------------------------------------------------------------------------
      //                                        SKIMMING STARTS                                                               |
      //-----------------------------------------------------------------------------------------------------------------------
      
      bool keepThisEvent=false;
      
      //if(is_ll_event) keepThisEvent=true;   //Skim >=2L
      //if(is_lt_event) keepThisEvent=true; //Skim 1L>=1T
      if(is_l2j_event)keepThisEvent=true; //Skim 1L>=2J
      //cout<<"light lepton="<<llep.size()<<endl;
      if(keepThisEvent){
	nEvtSkim++;
	skimTree->Fill();
      }
      
      //END
      
    } //Trigger
  }   //GoodEvt
  return kTRUE;
}     //EventLoop


void VLLAna::Sort(int opt)
{
  //Sort selected objects by pT (always descending).
  //option 1 sorts the gooMu array
  vector<Lepton> lep;  
  if(opt==0){
    //general
    for(int i=0; i<(int)genMuon.size()-1; i++){
      for(int j=i+1; j<(int)genMuon.size(); j++){
	if( genMuon[i].v.Pt() < genMuon[j].v.Pt() ) swap(genMuon.at(i),genMuon.at(j)); }}
    //genElectron
    for(int i=0; i<(int)genElectron.size()-1; i++){
      for(int j=i+1; j<(int)genElectron.size(); j++){
	if( genElectron[i].v.Pt() < genElectron[j].v.Pt() ) swap(genElectron.at(i),genElectron.at(j)); }}
    //genJet
    for(int i=0; i<(int)genjet.size()-1; i++){
      for(int j=i+1; j<(int)genjet.size(); j++){
	if( genjet[i].v.Pt() < genjet[j].v.Pt() ) swap(genjet.at(i),genjet.at(j)); }}
    //genTau
    for(int i=0; i<(int)genTau.size()-1; i++){
      for(int j=i+1; j<(int)genTau.size(); j++){
	if( genTau[i].v.Pt() < genTau[j].v.Pt() ) swap(genTau.at(i),genTau.at(j)); }}
    //genHadronicTau
    for(int i=0; i<(int)genHadronicTau.size()-1; i++){
      for(int j=i+1; j<(int)genHadronicTau.size(); j++){
	if( genHadronicTau[i].v.Pt() < genHadronicTau[j].v.Pt() ) swap(genHadronicTau.at(i),genHadronicTau.at(j)); }}
    //genllep
    for(int i=0; i<(int)genllep.size()-1; i++){
      for(int j=i+1; j<(int)genllep.size(); j++){
	if( genllep[i].v.Pt() < genllep[j].v.Pt() ) swap(genllep.at(i),genllep.at(j)); }}
  }
  
  //if(opt==1)lep=llep;
  // if(opt==2)lep=Muon;
  //if(opt==3)lep=Electron;
  //if(opt==4)lep=taus;
  //if(opt==5)lep=jets;
  //if(opt==6)lep=BTaggedJet;
  //if(opt==7)lep=Photon;
  //if(opt==8)lep=LooseLep;
  
  //The Sorting Loop
  if(opt==1){
    for(int i=0; i<(int)llep.size()-1; i++){
      for(int j=i+1; j<(int)llep.size(); j++){
	if( llep[i].v.Pt() < llep[j].v.Pt() ) swap(llep.at(i),llep.at(j)); }}
  }
  if(opt==2){
    for(int i=0; i<(int)Muon.size()-1; i++){
      for(int j=i+1; j<(int)Muon.size(); j++){
	if( Muon[i].v.Pt() < Muon[j].v.Pt() ) swap(Muon.at(i),Muon.at(j)); }}
  }
  if(opt==3){
    for(int i=0; i<(int)Electron.size()-1; i++){
      for(int j=i+1; j<(int)Electron.size(); j++){
	if( Electron[i].v.Pt() < Electron[j].v.Pt() ) swap(Electron.at(i),Electron.at(j)); }}
  }
  if(opt==4){
    for(int i=0; i<(int)taus.size()-1; i++){
      for(int j=i+1; j<(int)taus.size(); j++){
	if( taus[i].v.Pt() < taus[j].v.Pt() ) swap(taus.at(i),taus.at(j)); }}
  }
  if(opt==5){
    for(int i=0; i<(int)jets.size()-1; i++){
      for(int j=i+1; j<(int)jets.size(); j++){
	if( jets[i].v.Pt() < jets[j].v.Pt() ) swap(jets.at(i),jets.at(j)); }}
  }
  if(opt==6){
    for(int i=0; i<(int)BTaggedJet.size()-1; i++){
      for(int j=i+1; j<(int)BTaggedJet.size(); j++){
	if( BTaggedJet[i].v.Pt() < BTaggedJet[j].v.Pt() ) swap(BTaggedJet.at(i),BTaggedJet.at(j)); }}
  }
  if(opt==8){
    for(int i=0; i<(int)LooseLep.size()-1; i++){
      for(int j=i+1; j<(int)LooseLep.size(); j++){
	if( LooseLep[i].v.Pt() < LooseLep[j].v.Pt() ) swap(LooseLep.at(i),LooseLep.at(j)); }}
  }
}

//DebugMC Function
void VLLAna::TruthLevelInfo()
{
  if(nEvtTotal>20000 && nEvtTotal<20010){
    for(unsigned int i=0; i< (*nGenPart); i++){
      Lepton temp; temp.v.SetPtEtaPhiM(GenPart_pt[i],GenPart_eta[i],GenPart_phi[i],GenPart_mass[i]);temp.status = GenPart_status[i]; temp.ind = i;temp.pdgid = GenPart_pdgId[i];temp.momid=MotherID(i,GenPart_genPartIdxMother[i]);
      if(abs(temp.pdgid)<100 && abs(temp.momid)<100 && temp.status==1){
	cout<<i<<"|"<<temp.pdgid<<"|"<<temp.momid<<"|"<<endl;
	cout<<"===========Event="<<nEvtTotal<<"==========="<<endl;
      }
    }
  }
}

void VLLAna::ReadNNWeights()
{
  ifstream fin(NNFileName);
  
  vector<string> row; string line, word;
  long int event=-1.0,index=-1.0;float prob=1.0;float prob1=1.0;//nnop.clear();
  
  //READ THE LINES//
  while (getline(fin,line)){
    row.clear();
    stringstream s(line);
    while (getline(s, word, ' ')){
      // cout<< word << endl;
      row.push_back(word);      
    }
    
    long int event = stol(row[0]);
    //long int index = stol(row[1]);
    float prob = stof(row[1]);
    float prob1= stof(row[2]);
    //cout<<"event="<<event<<" "<<"nnscore="<<prob<<endl;
    //Store the map
    nnop.insert({event,prob});
    nnop1.insert({event,prob1});
  }
}

void VLLAna::BookHistograms()
{
  //cout<<"Inside BookHist()"<<endl;
  h.nevt = new TH1F("nEvents","0-Total events, 1-Total events ran, 2-Total events with trigger applied",5,-1,4);
  h.metfilter[0] = new TH1F("METfilter_goodVertices","METfilter_goodVertices",5,-1,4);
  h.metfilter[1] = new TH1F("METfilter_globalSuperTightHalo2016Filter","METfilter_globalSuperTightHalo2016Filter",5,-1,4);
  h.metfilter[2] = new TH1F("METfilter_HBHENoiseFilter","METfilter_HBHENoiseFilter",5,-1,4);
  h.metfilter[3] = new TH1F("METfilter_HBHENoiseIsoFilter","METfilter_HBHENoiseIsoFilter",5,-1,4);
  h.metfilter[4] = new TH1F("METfilter_EcalDeadCellTriggerPrimitiveFilter","METfilter_EcalDeadCellTriggerPrimitiveFilter",5,-1,4);
  h.metfilter[5] = new TH1F("METfilter_BadPFMuonFilter","METfilter_BadPFMuonFilter",5,-1,4);
  h.metfilter[6] = new TH1F("METfilter_eeBadScFilter","METfilter_eeBadScFilter",5,-1,4);
  h.metfilter[7] = new TH1F("METfilter_GoodEvt2016","METfilter_GoodEvt2016",5,-1,4);
  h.metfilter[8] = new TH1F("METfilter_GoodEvt2017","METfilter_GoodEvt2017",5,-1,4);
  h.metfilter[9] = new TH1F("METfilter_GoodEvt2018","METfilter_GoodEvt2018",5,-1,4);
  h.metfilter[10] = new TH1F("METfilter_GoodEvt","METfilter_GoodEvt",5,-1,4);


  //Basic plots starts
  //lepton(ele,mu,tau)
  h.nlep[0] = new TH1F("nMu","Number of Muon Candidates",20,0,20);
  h.nlep[1] = new TH1F("ngoodMu","Number of good Muon Candidates",20,0,20);
  h.nlep[2] = new TH1F("nEl","Number of Electron Candidates",20,0,20);
  h.nlep[3] = new TH1F("ngoodEl","Number of good Electron Candidates",20,0,20);
  h.nlep[4] = new TH1F("nTau","Number of Tau Candidates",20,0,20);
  h.nlep[5] = new TH1F("ngoodTau","Number of good Tau Candidates",20,0,20);
  h.nlep[6] = new TH1F("nPho","Number of Photon Candidates",20,0,20);
  
  for(int i=0; i<7; i++) h.nlep[i]->Sumw2();
  
  //jets
  h.nJet[0]= new TH1F("njet","No of goodjets",20,0,20);
  h.nJet[1]= new TH1F("nbjet","No of good b-tagged jets",20,0,20);
  for(int i=0;i<2;i++) h.nJet[i]->Sumw2();
  
  
  //lepton properties
  h.ptlep[0] = new TH1F("Mu_pt","Muon candidate p_{T}",1000,0,1000);
  h.ptlep[1] = new TH1F("goodMu_pt","Muon p_{T}",1000,0,1000);
  h.ptlep[2] = new TH1F("El_pt","Electron candidate p_{T}",1000,0,1000);
  h.ptlep[3] = new TH1F("goodEl_pt","Electron p_{T}",1000,0,1000);
  h.ptlep[4] = new TH1F("Tau_pt","Tau candidate p_{T}",1000,0,1000);
  h.ptlep[5] = new TH1F("Tau_corrpt","Tau candidate p_{T}",1000,0,1000);
  h.ptlep[6] = new TH1F("goodTau_pt","Tau p_{T}",1000,0,1000);
  h.ptlep[7] = new TH1F("Pho_pt","Photon candidate p_{T}",1000,0,1000);
  h.ptlep[8] = new TH1F("goodPho_pt","Photon p_{T}",1000,0,1000);
  for(int i=0; i<9; i++) h.ptlep[i]->Sumw2();
  
  //missing ET of the event
  h.etmiss= new TH1F("etmiss_beforeMTcut","Missing E_{T}",1000,0,1000); h.etmiss->Sumw2();
  
  //object cutflow
  h.mucut = new TH1F("mucut","0=pt,1=eta,2=dxydz,3=loose,4=Medium,5=Iso:0.25",10,0,10);h.mucut->Sumw2();
  h.elcut = new TH1F("elcut","0=pt,1=eta,2=dxydz,3=loose,4=Medium,5=muoncleaning",10,0,10);h.elcut->Sumw2();
  h.taucut = new TH1F("taucut","0=All,1=NewDM,2=DeepCSV,3=AntiEle,4=AntiMu,5=Prompt,6=LepClean,7=Eta,8=PT",10,0,10);h.taucut->Sumw2();
  h.phocut = new TH1F("phocut","phocuts",10,0,10);
  
  
  //////////////////////////////   GEN PARTICLE BLOCK STARTS   /////////////////////////////////////////////////
  
  
  //GEN MUON BLOCK//
  h.genpltmu[0] = new TH1F("ngenMu","no of genMuon",10,0,10);
  h.genpltmu[1] = new TH1F("genMu_pt","genMuon Pt",1000,0,1000);
  h.genpltmu[2] = new TH1F("genMu_Eta","Eta of genMuon",200,-10,10);
  h.genpltmu[3] = new TH1F("genMu_phi","Phi of genMuon",80,-4,4);
  h.genpltmu[4] = new TH1F("genMu_mom","Mother of genMuon",2000,-1000,1000);

  for(int i=0; i<5; i++) h.genpltmu[i]->Sumw2();

  //GEN ELE BLOCK//
  h.genpltele[0] = new TH1F("ngenEle","no of genElectron",10,0,10);
  h.genpltele[1] = new TH1F("genEle_pt","genElectron Pt",1000,0,1000);
  h.genpltele[2] = new TH1F("genEle_Eta","Eta of genElectron",200,-10,10);
  h.genpltele[3] = new TH1F("genEle_phi","Phi of genElectron",80,-4,4);
  h.genpltele[4] = new TH1F("genEle_mom","Mother of genElectron",2000,-1000,1000);

  for(int i=0; i<5; i++) h.genpltele[i]->Sumw2();

  //GEN TAU BLOCK//
  h.genplttau[0] = new TH1F("ngentau","no of genTau",10,0,10);
  h.genplttau[1] = new TH1F("gentau_pt","genTau Pt",1000,0,1000);
  h.genplttau[2] = new TH1F("gentau_Eta","Eta of genTau",200,-10,10);
  h.genplttau[3] = new TH1F("gentau_phi","Phi of genTau",80,-4,4);
  h.genplttau[4] = new TH1F("gentau_mom","Mother of genTau",2000,-1000,1000);

  for(int i=0; i<5; i++) h.genplttau[i]->Sumw2();

  //genlightlepton
  h.genPart[0]=new TH1F("ngenPart0","no of gen Particles",200,0,200);
  h.genPart[1]=new TH1F("ngenllep","no of gen lightlepton",10,0,10);
  h.genPart[2]=new TH1F("genpdgid","Pdgid of genllep",100,-50,50);
  for(int i=0; i<3; i++) h.genPart[i]->Sumw2();
  
  //genjet
  h.genjet[0] = new TH1F("nbgenjet_partflav","No of true b-jet by part flav",10,0,10);
  h.genjet[1] = new TH1F("nbgenjet_hadflav","No of true b-jet by had flav",10,0,10);
  h.genjet[2] = new TH1F("nbgenjet_bflav","No of true b-jet by manual matching",10,0,10);
  for(int i=0;i<3;i++)h.genjet[i]->Sumw2();
  
  //Lep Pt/b-quark Pt//                                                    
  h.fracpt = new TH1F("fracPt"        ,"Lep Pt/ b quark Pt",1000,0,10);h.fracpt->Sumw2();
  
  //NNScore
  h.nnprob[0] = new TH1F("nnscore","NN score at signal Neuron",120,0,1.2);
  h.nnprob[1] = new TH1F("nnscore1","ttjets score",120,0,1.2);
  for(int i=0;i<2;i++)h.nnprob[i]->Sumw2();
  
  //For Sourabh(July18,2022)
  h.sourabh[0] = new TH1F("mtlep_PFMET","Leading Lepton MT (PF)",1000,0,1000);
  h.sourabh[1] = new TH1F("mtlep_PuppiMET","Leading Lepton MT (Puppi)",1000,0,1000);
  h.sourabh[2] = new TH1F("mtlep_PFMET_cut","Leading Lepton MT after PFMET>30 GeV",1000,0,1000);
  h.sourabh[3] = new TH1F("mtlep_PuppiMET_cut","Leading Lepton MT after PuppiMet>30 GeV",1000,0,1000);
  for(int i=0;i<4;i++)h.sourabh[i]->Sumw2();



}//end of BOOK HISTOS


