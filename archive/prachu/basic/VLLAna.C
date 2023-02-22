#define VLLAna_cxx
#include "VLLAna.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

//Include SF correction header files
#include "/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/setup/anaCodesetup/IISERLogo.h"
#include "/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/setup/anaCodesetup/corrections/MuonScaleFactor.h"
#include "/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/setup/anaCodesetup/corrections/ElectronScaleFactor.h"
#include "/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/setup/anaCodesetup/corrections/TauScaleFactor.h"
#include "/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/setup/anaCodesetup/corrections/TriggerEfficiencyScaleFactor.h"
#include "/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/setup/anaCodesetup/corrections/ApplyScaleFactors.h"
#include "/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/setup/anaCodesetup/ProduceGenCollection.h"
#include "/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/setup/anaCodesetup/ObjectCleaning.h"
#include "/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/setup/anaCodesetup/ProduceRecoCollection.h"
#include "/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/setup/anaCodesetup/EventSelection.h"
#include "/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/setup/anaCodesetup/SignalCutflow.h"
#include "/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/setup/anaCodesetup/CustomFunctions.h"
#include "MVAVar.h"

void VLLAna::Begin(TTree * /*tree*/)
{
  iiserlogo();
  //   cout<<"Inside Begin()"<<endl;
  TString option = GetOption();
  //ReadNNWeights();

  //NEW MVA TTree
  InitializeMVATreeBranch();
}

void VLLAna::SlaveBegin(TTree * /*tree*/)
{
  time(&start);
  
  //   cout<<"Inside SlaveBegin()"<<endl;
  TString option = GetOption();
  nEvtTotal = 0;
  nEvtRan = 0;
  nEvtTrigger=0;
  n3L=0; n3LonZ=0; n_mu_anlys=0;      n_mu_NNScore=0;
  n_mu_bfake=0;    n_mu_bfake_flav=0; n_mu_prompt=0;
  n_bfake_matching=0;n_ttbarcr=0;n_ttbar2Lplus1Fake=0;
   
  n_ll=0,n_lt=0,n_tt=0,n_l2j=0;
  n_l=0,n_l15GeV=0,n_trigg=0,n_2l=0,n_1l1t=0;
  n_t=0,n_2t=0,n_t35GeV=0,n_tautrigg=0;
  n_ll_OSSF=0,n_ll_OSOF=0,n_ll_SSSF=0,n_ll_OSOF=0;
  
  n_1l1tloose=0,n_1l1tpassEta=0,n_1l1tpassAntiEle=0,n_1l1tpassAntiMu=0;
  n_1l1tprompt=0,n_1l1tlepclean=0,n_1l1tpassPt=0;

  n_os=0, n_ss=0, n_ossf=0, n_osof=0, n_sssf=0, n_ssof=0;

  //Create the histogram file
  _HstFile = new TFile(_HstFileName,"recreate");
  //Call the function to book the histograms we declared in Hists.
  BookHistograms();
  //ReadNNWeights();
  //std::ofstream file1out,file2out;
  //file1out.open("ttz_eval_promptmu.txt",ios::out | ios::trunc);
  //file2out.open("ttz_eval_fakemu.txt",ios::out | ios::trunc);   
   
}
void VLLAna::SlaveTerminate()
{
  //   cout<<"Inside SlaveTerminate()"<<endl;
  //Write histograms and close histogram file
  _mvaFile->Write();
  _mvaFile->Close();
  _HstFile->Write();
  _HstFile->Close();
  cout<<"Writing MVA Tree...."<<endl;
  //tree->Write();
  //Output to screen.
  cout<<"Total Triggered events = "<< nEvtTrigger <<endl;
  cout<<"Total events ran = "<<nEvtRan<<endl;
  cout<<"Total events = "<<nEvtTotal<<endl;
  
  
  //Open the text output file
  ofstream fout(_SumFileName);
  //Put text output in the summary file.
  fout<<"Total events ran = "<<nEvtRan<<endl;
  fout<<"Total events  = "<<nEvtTotal<<endl;

  time(&end);

  double time_taken = double(end-start);
  cout<<"Time taken by the programe is= "<<fixed<<time_taken<<setprecision(5);
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
  if(_verbosity==0 && nEvtTotal%100000==0)cout<<"Processed "<<nEvtTotal<<" event..."<<endl;      
  else if(_verbosity>0 && nEvtTotal%100000==0)cout<<"Processed "<<nEvtTotal<<" event..."<<endl;
  
  nEvtTotal++;
  h.nevt->Fill(0);

  GoodEvt2018 = (_year==2018 ? *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter && *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter && (_data ? *Flag_eeBadScFilter : 1) : 1);
  GoodEvt2017 = (_year==2017 ? *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter && *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter && (_data ? *Flag_eeBadScFilter : 1) : 1);
  GoodEvt2016 = (_year==2016 ? *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter && *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter && (_data ? *Flag_eeBadScFilter : 1) : 1);
  
  GoodEvt = GoodEvt2018 && GoodEvt2017 && GoodEvt2016;

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
      //                                                EVENT WEIGHTS                                                         |
      //-----------------------------------------------------------------------------------------------------------------------
      
      //evtwt= ID SF * trigg SF * btagging SF
      evtwt=1.0;
      /*
      float lep0SF=-1.0,lep1SF=-1.0,lep2SF=-1.0;
      if(!_data){
	if((int)llep.size()==3){
	  lep0SF=LeptonID_SF(llep.at(0).id,llep.at(0).v.Pt(),llep.at(0).v.Eta());
	  lep1SF=LeptonID_SF(llep.at(1).id,llep.at(1).v.Pt(),llep.at(1).v.Eta());
	  lep2SF=LeptonID_SF(llep.at(2).id,llep.at(2).v.Pt(),llep.at(2).v.Eta());
	  evtwt=lep0SF * lep1SF * lep2SF;
	  //evtwt=1.0;
	  float e1=SingleLepTrigger_eff(llep.at(0).id,llep.at(0).v.Pt(),llep.at(0).v.Eta());
	  float e2=SingleLepTrigger_eff(llep.at(1).id,llep.at(1).v.Pt(),llep.at(1).v.Eta());
	  float e3=SingleLepTrigger_eff(llep.at(2).id,llep.at(2).v.Pt(),llep.at(2).v.Eta());
	  float triggeff=1-((1-e1)*(1-e2)*(1-e3));
	  h.evtwt[2]->Fill(triggeff);
	  evtwt = evtwt * triggeff;
	  h.evtwt[3]->Fill(triggeff*evtwt);
	  //check
	  //cout<<"Event Weight 3L="<<evtwt<<endl;
	}
	if((int)llep.size()==2){
	  lep0SF=LeptonID_SF(llep.at(0).id,llep.at(0).v.Pt(),llep.at(0).v.Eta());
	  lep1SF=LeptonID_SF(llep.at(1).id,llep.at(1).v.Pt(),llep.at(1).v.Eta());
	  //evtwt=lep0SF * lep1SF;
	  evtwt=1.0;
	  float e1=SingleLepTrigger_eff(llep.at(0).id,llep.at(0).v.Pt(),llep.at(0).v.Eta());
	  float e2=SingleLepTrigger_eff(llep.at(1).id,llep.at(1).v.Pt(),llep.at(1).v.Eta());
	  float triggeff=1-((1-e1)*(1-e2));
	  //evtwt = evtwt * triggeff;
	  
	  //check
	  //cout<<"Event Weight 2L="<<evtwt<<endl;
	}
      }
      else
	evtwt=1.0;
      */
      
      h.evtwt[0]->Fill(evtwt);


      //-----------------------------------------------------------------------------------------------------------------------
      //                                        EVENT SELECTION                                                               |
      //-----------------------------------------------------------------------------------------------------------------------
      is_ll_event=false,is_lt_event=false,is_tt_event=false,is_l2j_event=false;  //Global variable     
      EventSelection();

      //#####################
      // Fake rate estimation
      //#####################

      
      //--------------------END OF EVENT ENTRY-----------------------------// 
    }
  }
  return kTRUE;
}


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
  //if(opt==2)lep=Muon;
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


void VLLAna::BookHistograms()
{
  //###########
  //BASIC PLOTS
  //###########
  h.nevt = new TH1F("nEvents","0-Total events, 1-Total events ran, 2-Total events with trigger applied",5,-1,4);  
  //jets
  h.nJet[0]= new TH1F("njet","No of goodjets",20,0,20);
  h.nJet[1]= new TH1F("nbjet","No of good b-tagged jets",20,0,20);
  for(int i=0;i<2;i++) h.nJet[i]->Sumw2();  
  //missing ET of the event
  h.etmiss= new TH1F("MET","Missing E_{T}",1000,0,1000); h.etmiss->Sumw2(); 
  h.fracpt = new TH1F("fracPt"        ,"Lep Pt/ b quark Pt",1000,0,10);h.fracpt->Sumw2();
  //evtwt
  h.evtwt[0] = new TH1F("evtwt"        ,"EventWeight",100,0,1);
  h.evtwt[1] = new TH1F("evtwt_mu"        ,"EventWeight after mumumu selection",100,0,1);
  h.evtwt[2] = new TH1F("triggereff"        ,"Trigger Efficiency",100,0,1);
  h.evtwt[3] = new TH1F("totwt"        ,"Trigger Eff x evtwt",100,0,1);
  for(int i=0;i<4;i++) h.evtwt[i]->Sumw2();
  
  
}//end of BOOK HISTOS


