#define VLLAna_cxx
#include "VLLAna.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

//Note: Include the following setup direactory to the c++ library
//before compiling the script. 
//INCLUDE "/work/VLLAnalysis/new_setup/setup/anaCodesetup/";

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

#include "/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/setup/anaCodesetup/2LSSstudy.h"

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
  nEvtPass = 0;
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
  cout<<"Total events = "<<nEvtTotal<<endl;
  cout<<"Total events ran = "<<nEvtRan<<endl;
  cout<<"Total triggered events = "<< nEvtTrigger <<endl;
  cout<<"Total events that passed my selections= "<< nEvtPass <<endl;
  
  //Open the text output file
  ofstream fout(_SumFileName);
  //Put text output in the summary file.
  fout<<"Total events = "<<nEvtTotal<<endl;
  fout<<"Total events ran = "<<nEvtRan<<endl;
  fout<<"Total triggered events = "<< nEvtTrigger <<endl;
  fout<<"Total events that passed my selections= "<< nEvtPass <<endl;

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
  
  /*h.metfilter[0]->Fill(*Flag_goodVertices);
  h.metfilter[1]->Fill(*Flag_globalSuperTightHalo2016Filter);
  h.metfilter[2]->Fill(*Flag_HBHENoiseFilter);
  h.metfilter[3]->Fill(*Flag_HBHENoiseIsoFilter);
  h.metfilter[4]->Fill(*Flag_EcalDeadCellTriggerPrimitiveFilter);
  h.metfilter[5]->Fill(*Flag_BadPFMuonFilter);
  h.metfilter[6]->Fill(*Flag_eeBadScFilter);*/

  GoodEvt2018 = (_year==2018 ? *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter && *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter && (_data ? *Flag_eeBadScFilter : 1) : 1);
  GoodEvt2017 = (_year==2017 ? *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter && *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter && (_data ? *Flag_eeBadScFilter : 1) : 1);
  GoodEvt2016 = (_year==2016 ? *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter && *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter && (_data ? *Flag_eeBadScFilter : 1) : 1);
  
  /*h.metfilter[7]->Fill(GoodEvt2016);
  h.metfilter[8]->Fill(GoodEvt2017);
  h.metfilter[9]->Fill(GoodEvt2018);*/
  
  //GoodEvt = GoodEvt2018 && GoodEvt2017 && GoodEvt2016;
  GoodEvt = true;

  //h.metfilter[10]->Fill(GoodEvt);

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
	/*
	  h.genpltmu[0]->Fill((int)genMuon.size());
	  h.genpltele[0]->Fill((int)genElectron.size());
	  h.genplttau[0]->Fill((int)genHadronicTau.size());
	  h.genPart[1]->Fill((int)genllep.size());*/
	//cout<<"Object are accessible outside functions.GenMuon Size="<<genMuon.size()<<endl;
	


	// SOME GEN LEVEL STUDY (remove this later)
	//for(int i=0;i<(int)genllep.size();i++)
	  //h.genPart[2]->Fill(genllep.at(i).pdgid);	
	
	//GenJet investigation
	int nbgenjet_partflav=0,nbgenjet_hadflav=0,nbgenjet_bflav=0;
	for(int i=0;i<(int)genjet.size();i++){
	  if(abs(genjet.at(i).partonflav)==5)nbgenjet_partflav++;
	  if(genjet.at(i).hadronflav==5)nbgenjet_hadflav++;
	  if(genjet.at(i).bflav)nbgenjet_bflav++;
	}
	//h.genjet[0]->Fill(nbgenjet_partflav);
	//h.genjet[1]->Fill(nbgenjet_hadflav);
	//h.genjet[2]->Fill(nbgenjet_bflav);
	
	
	
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
      
      //h.nlep[1]->Fill(Muon.size());
      
      
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
      //h.nJet[0]->Fill((int)jets.size());
      //h.nJet[1]->Fill((int)BTaggedJet.size());
      
      /*==========================
	       MET
       ===========================*/
      metpt = *MET_pt;
      metphi = *MET_phi;
      
      //h.etmiss->Fill(metpt);//fill a histogram with the missing Et of the event.
      
      //  cout<<"jet & met stored"<<endl;
      
      //-----------------------------------------------------------------------------------------------------------------------
      //                                              RECO OBJECTS BLOCK ENDS                                                 |
      //-----------------------------------------------------------------------------------------------------------------------

      

      //-----------------------------------------------------------------------------------------------------------------------
      //                                                EVENT WEIGHTS                                                         |
      //-----------------------------------------------------------------------------------------------------------------------
      /*
      //evtwt= ID SF * trigg SF * btagging SF
      evtwt=1.0; float lep0SF=-1.0,lep1SF=-1.0,lep2SF=-1.0;
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
	  //h.evtwt[2]->Fill(triggeff);
	  evtwt = evtwt * triggeff;
	  //h.evtwt[3]->Fill(triggeff*evtwt);
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
      
      //h.evtwt[0]->Fill(evtwt);

      


      //-----------------------------------------------------------------------------------------------------------------------
      //                                        EVENT SELECTION                                                               |
      //-----------------------------------------------------------------------------------------------------------------------
      is_ll_event=false,is_lt_event=false,is_tt_event=false,is_l2j_event=false;  //Global variable
      
      EventSelection();
       

      
      //###########################
      // Analysis of 2Mu events
      //###########################
   
      //Event Weights (Prachu)
      float wt = 1.0;
      float global_sf = 1.0;
      //These two are 1.0 by default (for data)

      //Appplying trigger:
      bool single_muon = (int)Muon.size()>0 && Muon.at(0).v.Pt()>24;
      bool single_electron = (int)Electron.size()>0 && Electron.at(0).v.Pt()>32;
      bool triggered_events = false;
      //If there is a single muon passing the HLT trigger, keep the event.
      if(single_muon) triggered_events = true;
      //If the event is not passing the singlemuon trigger, but passing the single-electron trigger, keep it.
      else if (!single_muon && single_electron) triggered_events = true;
      
       //2L same-sign inclusive:
      if((int)llep.size()>1 && triggered_events){
	
	//defining flags:
	bool samesign = false;
	
	float samesign_dilep_mass = 0;
	for(int i=1; i<(int)llep.size(); i++){
	  if(llep.at(0).charge == llep.at(i).charge){
	    samesign = true;
	    samesign_dilep_mass = (llep.at(0).v+llep.at(i).v).M();
	    break;
	  }
	}

	bool dilep_mass_cut = samesign_dilep_mass > 12;
	bool baseSelection = samesign && dilep_mass_cut;	
	
	//ScaleFactors and trigger efficiencies:
	float scalefactor = 1.0;
	float triggeff = 1.0;

	//---------------------------------------------------------------------------------------
	if(_data==0){
	  //If there are three or more leptons: (calculation involves three leptons only)
	  if((int)llep.size()>=3){
	    float lep0SF=LeptonID_SF(llep.at(0).id,llep.at(0).v.Pt(),llep.at(0).v.Eta());
	    float lep1SF=LeptonID_SF(llep.at(1).id,llep.at(1).v.Pt(),llep.at(1).v.Eta());
	    float lep2SF=LeptonID_SF(llep.at(2).id,llep.at(2).v.Pt(),llep.at(2).v.Eta());
	    scalefactor = lep0SF * lep1SF * lep2SF;

	    float e1=SingleLepTrigger_eff(llep.at(0).id,llep.at(0).v.Pt(),llep.at(0).v.Eta());
	    float e2=SingleLepTrigger_eff(llep.at(1).id,llep.at(1).v.Pt(),llep.at(1).v.Eta());
	    float e3=SingleLepTrigger_eff(llep.at(2).id,llep.at(2).v.Pt(),llep.at(2).v.Eta());
	    triggeff=1-((1-e1)*(1-e2)*(1-e3));
	  }
	  //If there are two leptons:
	  if((int)llep.size()==2){
	    float lep0SF=LeptonID_SF(llep.at(0).id,llep.at(0).v.Pt(),llep.at(0).v.Eta());
	    float lep1SF=LeptonID_SF(llep.at(1).id,llep.at(1).v.Pt(),llep.at(1).v.Eta());
	    scalefactor = lep0SF * lep1SF;
	   
	    float e1=SingleLepTrigger_eff(llep.at(0).id,llep.at(0).v.Pt(),llep.at(0).v.Eta());
	    float e2=SingleLepTrigger_eff(llep.at(1).id,llep.at(1).v.Pt(),llep.at(1).v.Eta());
	    triggeff=1-((1-e1)*(1-e2));
	  }
	  
	  wt = scalefactor * triggeff;
	}
	//---------------------------------------------------------------------------------------
	
	h.weight[0]->Fill(scalefactor);
	h.weight[1]->Fill(triggeff);
	h.weight[2]->Fill(wt);
	h.weight[3]->Fill(wt*global_sf);

	//cout<<wt*global_sf<<endl;
	if(baseSelection) Make2LSSPlots(wt);
      }

      
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

/*
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
  }*/


void VLLAna::BookHistograms()
{
  //  cout<<"Inside BookHist()"<<endl;
  h.nevt = new TH1F("nEvents","0-Total events, 1-Total events ran, 2-Total events with trigger applied",5,-1,4);
  
  //jets
  // h.nJet[0]= new TH1F("njet","No of goodjets",20,0,20);
  //h.nJet[1]= new TH1F("nbjet","No of good b-tagged jets",20,0,20);
  //for(int i=0;i<2;i++) h.nJet[i]->Sumw2();
  
  //missing ET of the event
  //h.etmiss= new TH1F("etmiss_beforeMTcut","Missing E_{T}",1000,0,1000); h.etmiss->Sumw2();
  
  //object cutflow
  /*
  h.mucut = new TH1F("mucut","0=pt,1=eta,2=dxydz,3=loose,4=Medium,5=Iso:0.25",10,0,10);h.mucut->Sumw2();
  h.elcut = new TH1F("elcut","0=pt,1=eta,2=dxydz,3=loose,4=Medium,5=muoncleaning",10,0,10);h.elcut->Sumw2();
  h.taucut = new TH1F("taucut","0=All,1=NewDM,2=DeepCSV,3=AntiEle,4=AntiMu,5=Prompt,6=LepClean,7=Eta,8=PT",10,0,10);h.taucut->Sumw2();
  h.phocut = new TH1F("phocut","phocuts",10,0,10);*/
  
  //Lep Pt/b-quark Pt//                                                    
  h.fracpt = new TH1F("fracPt"        ,"Lep Pt/ b quark Pt",1000,0,10);h.fracpt->Sumw2();

  //evtwt
  /*
  h.evtwt[0] = new TH1F("evtwt"        ,"EventWeight",100,0,1);
  h.evtwt[1] = new TH1F("evtwt_mu"        ,"EventWeight after mumu selection",100,0,1);
  h.evtwt[2] = new TH1F("triggereff"        ,"Trigger Efficiency",100,0,1);
  h.evtwt[3] = new TH1F("totwt"        ,"Trigger Eff x evtwt",100,0,1);
  for(int i=0;i<4;i++) h.evtwt[i]->Sumw2();*/
 
  //h.vllclass = new TH1F("vll_event","VLL event: 1=ll,2=lt,3=tt",5,0,5);h.vllclass->Sumw2();

  h.cutflow[0] = new TH1F("SS_cutflow",   "cutflow", 10, 0, 10);
  h.cutflow[1] = new TH1F("SS_cutflow_leading","cutflow (leading muon)", 20, 0, 20);
  h.cutflow[2] = new TH1F("SS_cutflow_ssmuon",   "cutflow (ss muon)", 20, 0, 20);
  //h.cutflow[3] = new TH1F("SS_cutflow_combined",   "cutflow (combined)", 20, 0, 20);
  for(int i=0; i<3; i++) h.cutflow[i]->Sumw2();

  //---------------------------------------------------------------------------------
  //Studying SS events
  //------------------
  //Leading lepton:
  h.studySS[0] = new TH1F("SS_llep0_Pt",       "SS_llep0_Pt",       1000,  0, 1000);
  h.studySS[1] = new TH1F("SS_llep0_Eta",      "SS_llep0_Eta",       200, -4,    4);
  h.studySS[2] = new TH1F("SS_llep0_Phi",      "SS_llep0_Phi",       200, -4,    4);
  h.studySS[3] = new TH1F("SS_llep0_mT",       "SS_llep0_mT",       1000,  0, 1000);
  h.studySS[4] = new TH1F("SS_llep0_reliso03", "SS_llep0_reliso03",  200,  0,   10);
  h.studySS[5] = new TH1F("SS_llep0_sip3d",    "SS_llep0_sip3d",    1000,  0,   50);
  //Samesign lepton:
  h.studySS[6] = new TH1F("SS_llepss_Pt",      "SS_llepss_Pt",      1000,  0, 1000);
  h.studySS[7] = new TH1F("SS_llepss_Eta",     "SS_llepss_Eta",      200, -4,    4);
  h.studySS[8] = new TH1F("SS_llepss_Phi",     "SS_llepss_Phi",      200, -4,    4);
  h.studySS[9]= new TH1F("SS_llepss_mT",      "SS_llepss_mT",      1000,  0, 1000);
  h.studySS[10]= new TH1F("SS_llepss_reliso03","SS_llepss_reliso03", 200,  0,   10);
  h.studySS[11]= new TH1F("SS_llepss_sip3d",   "SS_llepss_sip3d",   1000,  0,   50);
  //dilepton system:
  h.studySS[12] = new TH1F("SS_dilep_mass",  "SS_dilep_mass", 1000, 0, 1000);
  h.studySS[13] = new TH1F("SS_dEta_llep", "SS_dEta_llep", 600, 0, 6);
  h.studySS[14] = new TH1F("SS_dPhi_llep", "SS_dPhi_llep", 600, 0, 6);
  h.studySS[15] = new TH1F("SS_dR_llep", "SS_dR_llep", 600, 0, 6);
  h.studySS[16] = new TH1F("SS_ptratio", "SS_ptratio", 200, 0, 1);
  //Event level plots:
  h.studySS[17] = new TH1F("SS_nllep",  "SS_nllep", 10, 0, 10);
  h.studySS[18] = new TH1F("SS_nJet",   "SS_nJet",  10, 0, 10);
  h.studySS[19] = new TH1F("SS_nbJet",  "SS_nbJet", 10, 0, 10);
  h.studySS[20] = new TH1F("SS_met",  "SS_met", 1000, 0, 1000);
  h.studySS[21] = new TH1F("SS_metphi", "SS_metphi", 200, -4, 4);
  h.studySS[22] = new TH1F("SS_LT",  "SS_LT", 1000, 0, 1000);
  h.studySS[23] = new TH1F("SS_HT",  "SS_HT", 1000, 0, 1000);
  h.studySS[24] = new TH1F("SS_ST",  "SS_ST", 1000, 0, 1000);
  h.studySS[25] = new TH1F("SS_STfrac",  "SS_STfrac", 200, 0, 2);
  h.studySS[26] = new TH1F("SS_dPhi_met0", "SS_dPhi_met0", 600, 0, 6);
  h.studySS[27] = new TH1F("SS_dPhi_metss", "SS_dPhi_metss", 600, 0, 6);
  h.studySS[28] = new TH1F("SS_dPhi_met_max", "SS_dPhi_met_max", 600, 0, 6);
  h.studySS[29] = new TH1F("SS_dPhi_met_min", "SS_dPhi_met_min", 600, 0, 6);
  for(int i=0; i<30; i++) h.studySS[i]->Sumw2();
  //---------------------------------------------------------------------------------
  
  //For event weights (Prachu)
  h.weight[0] = new TH1F("ew_scalefactor", "Scale Factor", 150, 0, 1.5);
  h.weight[1] = new TH1F("ew_triggeff", "Trigger Efficiency", 150, 0, 1.5);
  h.weight[2] = new TH1F("ew_sfandeff", "SF * TriggerEff", 150, 0, 1.5);
  h.weight[3] = new TH1F("ew_global", "SF * TriggerEff * GLobalSF", 150, 0, 1.5);
  for(int i=0; i<4; i++) h.weight[i]->Sumw2();

  h.regions[0] = new TH2F("region_ht_met",  "region_ht_met",  1000, 0, 1000, 1000, 0, 1000);
  h.regions[1] = new TH2F("region_ht_deta", "region_ht_deta", 1000, 0, 1000,  600, 0,    6);
  h.regions[2] = new TH2F("region_ht_njet", "region_ht_njet", 1000, 0, 1000,   10, 0,   10);
  
}//end of BOOK HISTOS


