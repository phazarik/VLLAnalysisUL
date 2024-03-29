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

#include "skimmerHelper.h"
//#include "/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/setup/anaCodesetup/2muStudy.h"

void VLLAna::Begin(TTree * /*tree*/)
{
  iiserlogo();
  //   cout<<"Inside Begin()"<<endl;
  TString option = GetOption();
  ReadNNWeights();

  //NEW MVA TTree
  InitializeMVATreeBranch();
}

void VLLAna::SlaveBegin(TTree *tree /*tree*/)
{
  time(&start);
  
  //   cout<<"Inside SlaveBegin()"<<endl;
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

  n_os=0, n_ss=0, n_ossf=0, n_osof=0, n_sssf=0, n_ssof=0;

  //Create the histogram file
  //_HstFile = new TFile(_HstFileName,"recreate");
  //Call the function to book the histograms we declared in Hists.
  BookHistograms();
  //ReadNNWeights();
  //std::ofstream file1out,file2out;
  //file1out.open("ttz_eval_promptmu.txt",ios::out | ios::trunc);
  //file2out.open("ttz_eval_fakemu.txt",ios::out | ios::trunc);

  //For skimmer
  tree->SetBranchStatus("*",0);
  ActivateBranch(tree);

   
}
void VLLAna::SlaveTerminate()
{
  //   cout<<"Inside SlaveTerminate()"<<endl;
  //Write histograms and close histogram file
  //_mvaFile->Write();
  //_mvaFile->Close();
  //_HstFile->Write();
  //_HstFile->Close();
  //cout<<"Writing MVA Tree...."<<endl;

  //For skimmer
  cout<<"Writing Skim File....";
  skimTree->Write();
  _SkimFile->Close();
  cout<<"   Done!  "<<endl;
  
  //tree->Write();
  //Output to screen.
  cout<<"Total events in the file = "<<nEvtTotal<<endl;
  cout<<"Total events the code run on = "<<nEvtRan<<endl;
  cout<<"Total events that passed the trigger = "<< nEvtTrigger <<endl;
  cout<<"Total events after skimming = "<< nEvtSkim <<endl;

  /*
  //Open the text output file
  ofstream fout(_SumFileName);
  //Put text output in the summary file.
  fout<<"Total events in the file = "<<nEvtTotal<<endl;
  fout<<"Total events the code run on = "<<nEvtRan<<endl;
  fout<<"Total events that passed the trigger = "<< nEvtTrigger <<endl;
  fout<<"Total events after skimming = "<< nEvtSkim <<endl;*/

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
  
  //For skimmer:
  ReadBranch();
  //nEvtSkim++;
  //skimTree->Fill();  

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
      
      
      //triggerRes = trigger2018 && trigger2017 && trigger2016;
      triggerRes = true;
      
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
      //                                                EVENT WEIGHTS                                                         |
      //-----------------------------------------------------------------------------------------------------------------------
      
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
      
      h.evtwt[0]->Fill(evtwt);


      //-----------------------------------------------------------------------------------------------------------------------
      //                                        EVENT SELECTION                                                               |
      //-----------------------------------------------------------------------------------------------------------------------
      is_ll_event=false,is_lt_event=false,is_tt_event=false,is_l2j_event=false;  //Global variable
      
      EventSelection();
       

      //-----------------------------------------------------------------------------------------------------------------------
      //                                          1L2J Analysis                                                               |
      //-----------------------------------------------------------------------------------------------------------------------
      
      /*
      if(is_l2j_event && (LooseLep.size()==1)){
	n_l2j++,h.vllclass->Fill(4);
	
	//Properties
	float HT=-1.0;
	for(int i=0;i<(int)jets.size();i++)
	  HT=HT+jets.at(i).v.Pt();
  
	float mtlep0=sqrt(2.0*llep[0].v.Pt()*metpt*(1-cos(delta_phi(llep[0].v.Phi(),metphi))));
	float mtjet0=sqrt(2.0*jets[0].v.Pt()*metpt*(1-cos(delta_phi(jets[0].v.Phi(),metphi))));
	float mtjet1=sqrt(2.0*jets[1].v.Pt()*metpt*(1-cos(delta_phi(jets[1].v.Phi(),metphi))));
	float MET=metpt;
	float ST=llep[0].v.Pt()+MET+HT;
	float dijetMass=getInvMass(jets[0].v,jets[1].v);
	float drjet01=jets[0].v.DeltaR(jets[1].v);
	float dijetMT=sqrt(2.0*(jets[0].v+jets[1].v).Pt()*metpt*(1-cos(delta_phi((jets[0].v+jets[1].v).Phi(),metphi))));
	float dijetPT=(jets[0].v+jets[1].v).Pt();
	int njet=jets.size();
	int nbjet=BTaggedJet.size();
	float dphimetjet0=delta_phi(jets[0].v.Phi(),metphi);
	float dphimetjet1=delta_phi(jets[1].v.Phi(),metphi);
	float dphimetlep0=delta_phi(llep[0].v.Phi(),metphi);
	float dphijet0lep0=delta_phi(llep[0].v.Phi(),jets[0].v.Phi());
	float dphijet1lep0=delta_phi(llep[0].v.Phi(),jets[1].v.Phi());
	float dphidijetlep0=delta_phi(llep[0].v.Phi(),(jets[0].v+jets[1].v).Phi());
	float dphimetdijet=delta_phi(metphi,(jets[0].v+jets[1].v).Phi());
	float LeadingJetPt=jets[0].v.Pt();
	float drjet0lep0=llep[0].v.DeltaR(jets[0].v);
	float drjet1lep0=llep[0].v.DeltaR(jets[1].v);
	
	//bool l2jSelection=BTaggedJet.size()==0 && (LooseLep.size()==1);//No medium b-jets in events, No 2nd loose lepton
	bool l2jSelection=true;
	bool l2jSelection_global=jets.at(0).v.Pt()>30 && drjet01>0.4 && drjet0lep0>0.4 && drjet1lep0>0.4;
	bool l2jSelection_dijetmasscut=(dijetMass<110) && (dijetMass>60);
	bool l2jSelection_drjetcut= (drjet01<1.5);
	bool wjet_bkg=(mtlep0>50)&&(mtlep0<150) && nbjet==0 &&l2jSelection_drjetcut;
	bool l2jSelection_wjet_bkg=l2jSelection_global && wjet_bkg;
	
	bool MuonChannel= (abs(llep[0].id)==13);

	//if(l2jSelection_global && MuonChannel)
	//VLL_wjetsEstimation(0);
	
	//ABCD Method
	bool regA=l2jSelection_wjet_bkg && dijetMass>50 && (mtlep0>50)&&(mtlep0<100); 
	bool regB=l2jSelection_wjet_bkg && dijetMass<50 && (mtlep0>50)&&(mtlep0<100);
	bool regC=l2jSelection_wjet_bkg && dijetMass>50 && (mtlep0>100)&&(mtlep0<150); 
	bool regD=l2jSelection_wjet_bkg && dijetMass<50 && (mtlep0>100)&&(mtlep0<150);

	
	//Produce Histos
	if(MuonChannel){
	  if(regA)VLL_wjetsEstimation(2);
	  if(regB)VLL_wjetsEstimation(3);
	  if(regC)VLL_wjetsEstimation(4);
	  if(regD)VLL_wjetsEstimation(5);
	}
	

	//Fill the MVA Variables
	nEvt = nEvtTotal;
	lep0_flavor=llep[0].id; 
	lep0_pt=llep[0].v.Pt();
	jet0_pt=jets[0].v.Pt();
	jet1_pt=jets[1].v.Pt();
	lep0_mt = mtlep0;
	jet0_mt =mtjet0;
	jet1_mt =mtjet1;
	dijet_mass = dijetMass;
	deltaR_jet01 = drjet01;
	deltaPhi_metjet0 = dphimetjet0;
	deltaPhi_metjet1 = dphimetjet1;
	deltaPhi_metlep0 = dphimetlep0;
	deltaPhi_jet0lep0 = dphijet0lep0;
	deltaPhi_jet1lep0 = dphijet1lep0;
	deltaPhi_dijetlep0 = dphidijetlep0;
	deltaPhi_metdijet = dphimetdijet;
	dijet_pt = dijetPT;
	dijet_mt = dijetMT;
	event_MET = MET;
	event_HT = HT;
	event_ST = ST;
	n_Jet = njet;
	n_bJet = nbjet;
	
	//Fill MVA Tree
	//tree->Fill();

	//Text File output method
	//ofstream fout;fout.open("VLLM100_InputVar_Jul5.txt",ios::app);
	//printout the variables
	//fout<<"Arnab"<<" "<<nEvtTotal<<" "<<mtlep0<<" "<<mtjet0<<" "<<mtjet1<<" "<<dijetMass<<" "<<drjet01<<" "<<MET<<" "<<HT<<" "<<dphimetjet0<<" "<<dphimetjet1<<" "<<dphimetlep0<<" "<<njet<<" "<<nbjet<<" "<<dijetPT<<" "<<dijetMT<<" "<<dphijet0lep0<<" "<<dphijet1lep0<<" "<<dphidijetlep0<<" "<<dphimetdijet<<" "<<ST<<" "<<llep[0].v.Pt()<<" "<<jets[0].v.Pt()<<" "<<jets[1].v.Pt()<<endl;
	//fout.close();
	
	
	
	//Get the NNScore and Analyze
	auto itr=nnop.find(nEvtTotal);
	prob=itr->second;
	auto itr1=nnop1.find(nEvtTotal);
	prob1=itr1->second;
	//cout<<"prob of event "<<nEvtTotal<<" is="<<prob<<endl;
	h.nnprob[0]->Fill(prob,evtwt);
	h.nnprob[1]->Fill(prob1,evtwt);
	bool highMVA= prob>0.1 && prob1>0.2;
	bool mediumMVA= (prob>0.2 && prob<0.4);	  
	bool lowMVA=prob<0.2;
	
	if(highMVA){
	  VLL_wjetsEstimation(1);
	}
      }*/
      
      //###########################
      // Analysis of 2Mu events
      //###########################
      /*
      if((int)Muon.size()>1){

	//New Skimmer definition:
	float leading_pT = Muon.at(0).v.Pt();
	bool samesign = false;
	float samesign_dimuon_mass = 0;
	for(int i=1; i<(int)Muon.size(); i++){
	  if(Muon.at(0).charge == Muon.at(i).charge){
	    samesign = true;
	    samesign_dimuon_mass = (Muon.at(0).v+Muon.at(i).v).M();
	    break;
	  }
	}
	
	bool baseSelection = (samesign_dimuon_mass>15
			      && leading_pT>26
			      && samesign);
	
	if(baseSelection){
	  //Make2muPlots();
	  nEvtSkim++;
	  skimTree->Fill();
	}
      }*/
      
      //Preselection on the lepton:
      bool single_muon = (int)Muon.size()>0 && Muon.at(0).v.Pt()>24;
      bool single_electron = (int)Electron.size()>0 && Electron.at(0).v.Pt()>32;
      bool triggered_events = single_muon || single_electron;
	
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

	if(baseSelection){
	  nEvtSkim++;
	  skimTree->Fill();
	}
	
      }

      
     

      /*
      //tt
      if(is_tt_event){
	//VLLPlots(2,14);
	n_tt++,h.vllclass->Fill(3);//tt plots
	}*/

      
      // Signal CutFlow
      //SignalCutflow();
      
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
void VLLAna::VLLPlots(int opt,int index)
{
  Lepton lep0,lep1;
  if(opt==0) lep0=llep.at(0), lep1=llep.at(1);//ll
  if(opt==1) lep0=llep.at(0), lep1=taus.at(0);//lt
  if(opt==2) lep0=taus.at(0), lep1=taus.at(1);//tt
  //if(opt==3) lep0=jets.at(0), lep1=jets.at(1);//tt

  
  float LT=lep0.v.Pt()+lep1.v.Pt();
  float MET=metpt;
  float HT=-1.0;
  for(int i=0;i<(int)jets.size();i++)
    HT=HT+jets.at(i).v.Pt();
  float ST=LT+MET+HT;
  float mtlep0=sqrt(2.0*lep0.v.Pt()*metpt*(1-cos(delta_phi(lep0.v.Phi(),metphi))));
  float mtlep1=sqrt(2.0*lep1.v.Pt()*metpt*(1-cos(delta_phi(lep1.v.Phi(),metphi))));
  float dileppt=(lep0.v+lep1.v).Pt();
  float mtlep01=sqrt(2.0*dileppt*metpt*(1-cos(delta_phi((lep0.v+lep1.v).Phi(),metphi))));
  float Mass=getInvMass(lep0.v,lep1.v);
  float OSMass=-1.0,SSMass=-1.0;
  if(lep0.charge != lep1.charge)OSMass=getInvMass(lep0.v,lep1.v);
  if(lep0.charge == lep1.charge)SSMass=getInvMass(lep0.v,lep1.v);
  float dPhijetmet=-1.0,dRlep0jet0=-1.0,dRlep1jet0=-1.0;
  if((int)jets.size()>0){
    dPhijetmet=delta_phi(jets.at(0).v.Phi(),metphi);
    dRlep0jet0=lep0.v.DeltaR(jets.at(0).v);
    dRlep1jet0=lep1.v.DeltaR(jets.at(0).v);    
  }
  float njet=(int)jets.size();
  float nbjet=(int)BTaggedJet.size();
  
  h.vllplot[0][opt][index]->Fill(lep0.v.Pt(),evtwt);
  h.vllplot[1][opt][index]->Fill(lep1.v.Pt(),evtwt);
  h.vllplot[2][opt][index]->Fill(lep0.v.Eta(),evtwt);
  h.vllplot[3][opt][index]->Fill(lep1.v.Eta(),evtwt);
  h.vllplot[4][opt][index]->Fill(lep0.v.Phi(),evtwt);
  h.vllplot[5][opt][index]->Fill(lep1.v.Phi(),evtwt);
  h.vllplot[6][opt][index]->Fill(lep0.v.DeltaR(lep1.v),evtwt);
  h.vllplot[7][opt][index]->Fill(delta_phi(lep0.v.Phi(),metphi),evtwt);
  h.vllplot[8][opt][index]->Fill(delta_phi(lep1.v.Phi(),metphi),evtwt);
  h.vllplot[9][opt][index]->Fill(dRlep0jet0,evtwt);
  h.vllplot[10][opt][index]->Fill(dRlep1jet0,evtwt);
  h.vllplot[11][opt][index]->Fill(dPhijetmet,evtwt);
  h.vllplot[12][opt][index]->Fill(Mass,evtwt);
  if(lep0.charge != lep1.charge)
    h.vllplot[13][opt][index]->Fill(getInvMass(lep0.v,lep1.v),evtwt);
  if(lep0.charge == lep1.charge)
    h.vllplot[14][opt][index]->Fill(getInvMass(lep0.v,lep1.v),evtwt);
  h.vllplot[15][opt][index]->Fill(mtlep0,evtwt);
  h.vllplot[16][opt][index]->Fill(mtlep1,evtwt);
  h.vllplot[17][opt][index]->Fill(LT,evtwt);
  h.vllplot[18][opt][index]->Fill(MET,evtwt);
  h.vllplot[19][opt][index]->Fill(HT,evtwt);
  h.vllplot[20][opt][index]->Fill(ST,evtwt);
  h.vllplot[21][opt][index]->Fill(njet,evtwt);
  h.vllplot[22][opt][index]->Fill(nbjet,evtwt);
  
  //unusual variables
  h.vllplot[23][opt][index]->Fill((lep0.v+lep1.v).Pt(),evtwt);
  h.vllplot[24][opt][index]->Fill(mtlep01,evtwt);
  if((int)jets.size()>0){
    h.vllplot[25][opt][index]->Fill((lep0.v+jets[0].v).Pt(),evtwt);
    h.vllplot[26][opt][index]->Fill((lep1.v+jets[0].v).Pt(),evtwt);
    h.vllplot[27][opt][index]->Fill((lep0.v+lep1.v+jets[0].v).Pt(),evtwt);
    float lepjetpt=(lep0.v+lep1.v+jets[0].v).Pt();
    h.vllplot[28][opt][index]->Fill(2.0*lepjetpt*metpt*(1-cos(delta_phi((lep0.v+lep1.v+jets[0].v).Phi(),metphi))),evtwt);}
  if((int)jets.size()>1){
    h.vllplot[29][opt][index]->Fill((lep0.v+jets[0].v+jets[1].v).Pt(),evtwt);
    h.vllplot[30][opt][index]->Fill((lep1.v+jets[0].v+jets[1].v).Pt(),evtwt);
    h.vllplot[31][opt][index]->Fill((lep0.v+lep1.v+jets[0].v+jets[1].v).Pt(),evtwt);
    float lepjet0pt=(lep0.v+lep1.v+jets[0].v).Pt();
    float lepjet1pt=(lep0.v+lep1.v+jets[1].v).Pt();
    float lepjet01pt=(lep0.v+lep1.v+jets[0].v+jets[1].v).Pt();
    h.vllplot[32][opt][index]->Fill(2.0*lepjet0pt*metpt*(1-cos(delta_phi((lep0.v+lep1.v+jets[0].v).Phi(),metphi))),evtwt);
    h.vllplot[33][opt][index]->Fill(2.0*lepjet1pt*metpt*(1-cos(delta_phi((lep0.v+lep1.v+jets[1].v).Phi(),metphi))),evtwt);
    h.vllplot[34][opt][index]->Fill(2.0*lepjet01pt*metpt*(1-cos(delta_phi((lep0.v+lep1.v+jets[1].v+jets[1].v).Phi(),metphi))),evtwt);
  }
  
}

void VLLAna::VLL_wjetsEstimation(int index)  //index: Apply different cut and call this function
{
  //Properties
  float HT=-1.0;
  for(int i=0;i<(int)jets.size();i++)
    HT=HT+jets.at(i).v.Pt();
  
  float mtlep0=sqrt(2.0*llep[0].v.Pt()*metpt*(1-cos(delta_phi(llep[0].v.Phi(),metphi))));
  float mtjet0=sqrt(2.0*jets[0].v.Pt()*metpt*(1-cos(delta_phi(jets[0].v.Phi(),metphi))));
  float mtjet1=sqrt(2.0*jets[1].v.Pt()*metpt*(1-cos(delta_phi(jets[1].v.Phi(),metphi))));
  float MET=metpt;
  float ST=llep[0].v.Pt()+MET+HT;
  float dijetMass=getInvMass(jets[0].v,jets[1].v);
  float drjet01=jets[0].v.DeltaR(jets[1].v);
  float dijetMT=sqrt(2.0*(jets[0].v+jets[1].v).Pt()*metpt*(1-cos(delta_phi((jets[0].v+jets[1].v).Phi(),metphi))));
  float dijetPT=(jets[0].v+jets[1].v).Pt();
  int njet=jets.size();
  int nbjet=BTaggedJet.size();
  float dphimetjet0=delta_phi(jets[0].v.Phi(),metphi);
  float dphimetjet1=delta_phi(jets[1].v.Phi(),metphi);
  float dphimetlep0=delta_phi(llep[0].v.Phi(),metphi);
  float dphijet0lep0=delta_phi(llep[0].v.Phi(),jets[0].v.Phi());
  float dphijet1lep0=delta_phi(llep[0].v.Phi(),jets[1].v.Phi());
  float dphidijetlep0=delta_phi(llep[0].v.Phi(),(jets[0].v+jets[1].v).Phi());
  float dphimetdijet=delta_phi(metphi,(jets[0].v+jets[1].v).Phi());
  float LeadingJetPt=jets[0].v.Pt();
  float drjet0lep0=llep[0].v.DeltaR(jets[0].v);
  float drjet1lep0=llep[0].v.DeltaR(jets[1].v);
	  
  h.vllplotl2j[0][index]->Fill(llep[0].v.Pt(),evtwt);
  h.vllplotl2j[1][index]->Fill(jets[0].v.Pt(),evtwt);
  h.vllplotl2j[2][index]->Fill(jets[1].v.Pt(),evtwt);
  h.vllplotl2j[3][index]->Fill(mtlep0,evtwt);
  h.vllplotl2j[4][index]->Fill(mtjet0,evtwt);
  h.vllplotl2j[5][index]->Fill(mtjet1,evtwt);
  h.vllplotl2j[6][index]->Fill(dijetMass,evtwt);
  h.vllplotl2j[7][index]->Fill(drjet01,evtwt);
  h.vllplotl2j[8][index]->Fill(dijetPT,evtwt);
  h.vllplotl2j[9][index]->Fill(dijetMT,evtwt);
  h.vllplotl2j[10][index]->Fill(MET,evtwt);
  h.vllplotl2j[11][index]->Fill(HT,evtwt);
  h.vllplotl2j[12][index]->Fill(ST,evtwt);
  h.vllplotl2j[13][index]->Fill(njet,evtwt);
  h.vllplotl2j[14][index]->Fill(nbjet,evtwt);
  h.vllplotl2j[15][index]->Fill(dphimetjet0,evtwt);
  h.vllplotl2j[16][index]->Fill(dphimetjet1,evtwt);
  h.vllplotl2j[17][index]->Fill(dphimetlep0,evtwt);
  h.vllplotl2j[18][index]->Fill(dphijet0lep0,evtwt);
  h.vllplotl2j[19][index]->Fill(dphijet1lep0,evtwt);
  h.vllplotl2j[20][index]->Fill(dphidijetlep0,evtwt);
  h.vllplotl2j[21][index]->Fill(dphimetdijet,evtwt);
  
}


void VLLAna::BookHistograms()
{
  //  cout<<"Inside BookHist()"<<endl;
  h.nevt = new TH1F("nEvents","0-Total events, 1-Total events ran, 2-Total events with trigger applied",5,-1,4);


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
  
  
  //Lep Pt/b-quark Pt//                                                    
  h.fracpt = new TH1F("fracPt"        ,"Lep Pt/ b quark Pt",1000,0,10);h.fracpt->Sumw2();

  //evtwt
  h.evtwt[0] = new TH1F("evtwt"        ,"EventWeight",100,0,1);
  h.evtwt[1] = new TH1F("evtwt_mu"        ,"EventWeight after mumumu selection",100,0,1);
  h.evtwt[2] = new TH1F("triggereff"        ,"Trigger Efficiency",100,0,1);
  h.evtwt[3] = new TH1F("totwt"        ,"Trigger Eff x evtwt",100,0,1);
  for(int i=0;i<4;i++) h.evtwt[i]->Sumw2();
  
  h.vllclass = new TH1F("vll_event","VLL event: 1=ll,2=lt,3=tt",5,0,5);h.vllclass->Sumw2();
  
  h.region[0]=new TH1F("llchannel","ll decomp",15,0,15);
  h.region[1]=new TH1F("ltchannel","lt decomp",15,0,15);
  for(int i=0;i<2;i++)h.region[i]->Sumw2();


  //1L1T Acceptance PT plots
  h.tauacc[0]=new TH1F("pt_base","Baseic 1L1T events Pt",1000,0,1000);
  h.tauacc[1]=new TH1F("pt_loose","Pt: Tau Pass loose deepcsv",1000,0,1000);
  h.tauacc[2]=new TH1F("pt_passEta","Pt: Tau Pass Eta cut",1000,0,1000);
  h.tauacc[3]=new TH1F("pt_passAntiEle","Pt: Tau Pass Loose Anti Ele",1000,0,1000);
  h.tauacc[4]=new TH1F("pt_passAntiMu","Pt: Tau Pass Loose Anti Mu",1000,0,1000);
  h.tauacc[5]=new TH1F("pt_prompt","Pt: Tau Pass prompt cut",1000,0,1000);
  h.tauacc[6]=new TH1F("pt_lepclean","Pt: Tau Pass lep cleaning",1000,0,1000);
  h.tauacc[7]=new TH1F("pt_passPt","Pt: Tau Pass Pt cut",1000,0,1000);
  for(int i=0;i<8;i++)h.tauacc[i]->Sumw2();
  
  
  //NNScore
  h.nnprob[0] = new TH1F("nnscore","NN score at signal Neuron",120,0,1.2);
  h.nnprob[1] = new TH1F("nnscore1","ttjets score",120,0,1.2);
  for(int i=0;i<2;i++)h.nnprob[i]->Sumw2();


  //#####################################
  // Prachu's additions:
  //#####################################
  h.cutflow[0] = new TH1F("cutflow_SS","cutflow_SS", 15, 0, 15);
  for(int i=0; i<1; i++) h.cutflow[i]->Sumw2();
  
  //2L channel plots:
  h.study2L[0] = new TH1F("2L_llep0_Pt",  "2L_llep0_Pt", 1000, 0, 1000);
  h.study2L[1] = new TH1F("2L_llep0_Eta", "2L_llep0_Eta", 200, -4, 4);
  h.study2L[2] = new TH1F("2L_llep0_Phi", "2L_llep0_Phi", 200, -4, 4);
  h.study2L[3] = new TH1F("2L_llep1_Pt",  "2L_llep1_Pt", 1000, 0, 1000);
  h.study2L[4] = new TH1F("2L_llep1_Eta", "2L_llep1_Eta", 200, -4, 4);
  h.study2L[5] = new TH1F("2L_llep1_Phi", "2L_llep1_Phi", 200, -4, 4);
  h.study2L[6] = new TH1F("2L_llep_dEta", "2L_llep_dEta", 200, 0, 10);
  h.study2L[7] = new TH1F("2L_llep_dPhi", "2L_llep_dPhi", 200, 0, 10);
  h.study2L[8] = new TH1F("2L_llep_dR",   "2L_llep_dR",  1000, 0, 10);
  h.study2L[9] = new TH1F("2L_dilep_mass", "2L_dilep_mass", 1000, 0, 1000);
  h.study2L[10] = new TH1F("2L_met", "2L_met", 1000, 0, 1000);
  h.study2L[11] = new TH1F("2L_metphi", "2L_met", 200, -4, 4);
  h.study2L[12] = new TH1F("2L_llep0mT", "2L_llep0mT", 1000, 0, 1000);
  h.study2L[13] = new TH1F("2L_llep1mT", "2L_llep1mT", 1000, 0, 1000);
  h.study2L[14] = new TH1F("2L_sumcos", "2L_sumcos", 300, -3, 3);
  h.study2L[15] = new TH1F("2L_llep0_sip3d",    "2L_llep0_sip3d", 300, 0, 30);
  h.study2L[16] = new TH1F("2L_llep0_reliso03", "2L_llep0_reliso03", 200, 0, 1);
  h.study2L[17] = new TH1F("2L_llep0_reliso04", "2L_llep0_reliso04", 200, 0, 1);
  h.study2L[18] = new TH1F("2L_llep1_sip3d",    "2L_llep1_sip3d", 300, 0, 30);
  h.study2L[19] = new TH1F("2L_llep1_reliso03", "2L_llep1_reliso03", 200, 0, 1);
  h.study2L[20] = new TH1F("2L_llep1_reliso04", "2L_llep1_reliso04", 200, 0, 1);
  h.study2L[21] = new TH1F("2L_llep0_jetdeepB", "2L_llep0_jetdeepB", 400, -1, 3);
  h.study2L[22] = new TH1F("2L_llep1_jetdeepB", "2L_llep1_jetdeepB", 400, -1, 3);
  for(int i=0; i<23; i++) h.study2L[i]->Sumw2();

  //Studying SS events
  h.studySS[0] = new TH1F("SS_llep0_Pt",  "SS_llep0_Pt", 1000, 0, 1000);
  h.studySS[1] = new TH1F("SS_llep0_Eta", "SS_llep0_Eta", 200, -4, 4);
  h.studySS[2] = new TH1F("SS_llep0_Phi", "SS_llep0_Phi", 200, -4, 4);
  h.studySS[3] = new TH1F("SS_llep1_Pt",  "SS_llep1_Pt", 1000, 0, 1000);
  h.studySS[4] = new TH1F("SS_llep1_Eta", "SS_llep1_Eta", 200, -4, 4);
  h.studySS[5] = new TH1F("SS_llep1_Phi", "SS_llep1_Phi", 200, -4, 4);
  h.studySS[6] = new TH1F("SS_llep_dEta", "SS_llep_dEta", 200, 0, 10);
  h.studySS[7] = new TH1F("SS_llep_dPhi", "SS_llep_dPhi", 200, 0, 10);
  h.studySS[8] = new TH1F("SS_llep_dR",   "SS_llep_dR",  1000, 0, 10);
  h.studySS[9] = new TH1F("SS_dilep_mass", "SS_dilep_mass", 1000, 0, 1000);
  h.studySS[10] = new TH1F("SS_met", "SS_met", 1000, 0, 1000);
  h.studySS[11] = new TH1F("SS_metphi", "SS_met", 200, -4, 4);
  h.studySS[12] = new TH1F("SS_llep0mT", "SS_llep0mT", 1000, 0, 1000);
  h.studySS[13] = new TH1F("SS_llep1mT", "SS_llep1mT", 1000, 0, 1000);
  h.studySS[14] = new TH1F("SS_sumcos", "SS_sumcos", 300, -3, 3);
  h.studySS[15] = new TH1F("SS_llep0_sip3d",    "SS_llep0_sip3d", 300, 0, 30);
  h.studySS[16] = new TH1F("SS_llep0_reliso03", "SS_llep0_reliso03", 200, 0, 1);
  h.studySS[17] = new TH1F("SS_llep0_reliso04", "SS_llep0_reliso04", 200, 0, 1);
  h.studySS[18] = new TH1F("SS_llep1_sip3d",    "SS_llep1_sip3d", 300, 0, 30);
  h.studySS[19] = new TH1F("SS_llep1_reliso03", "SS_llep1_reliso03", 200, 0, 1);
  h.studySS[20] = new TH1F("SS_llep1_reliso04", "SS_llep1_reliso04", 200, 0, 1);
  h.studySS[21] = new TH1F("SS_llep0_jetdeepB", "SS_llep0_jetdeepB", 400, -1, 3);
  h.studySS[22] = new TH1F("SS_llep1_jetdeepB", "SS_llep1_jetdeepB", 400, -1, 3);
  for(int i=0; i<23; i++) h.studySS[i]->Sumw2();

  //Studying OS events
  h.studyOS[0] = new TH1F("OS_llep0_Pt",  "OS_llep0_Pt", 1000, 0, 1000);
  h.studyOS[1] = new TH1F("OS_llep0_Eta", "OS_llep0_Eta", 200, -4, 4);
  h.studyOS[2] = new TH1F("OS_llep0_Phi", "OS_llep0_Phi", 200, -4, 4);
  h.studyOS[3] = new TH1F("OS_llep1_Pt",  "OS_llep1_Pt", 1000, 0, 1000);
  h.studyOS[4] = new TH1F("OS_llep1_Eta", "OS_llep1_Eta", 200, -4, 4);
  h.studyOS[5] = new TH1F("OS_llep1_Phi", "OS_llep1_Phi", 200, -4, 4);
  h.studyOS[6] = new TH1F("OS_llep_dEta", "OS_llep_dEta", 200, 0, 10);
  h.studyOS[7] = new TH1F("OS_llep_dPhi", "OS_llep_dPhi", 200, 0, 10);
  h.studyOS[8] = new TH1F("OS_llep_dR",   "OS_llep_dR",  1000, 0, 10);
  h.studyOS[9] = new TH1F("OS_dilep_mass", "OS_dilep_mass", 1000, 0, 1000);
  h.studyOS[10] = new TH1F("OS_met", "OS_met", 1000, 0, 1000);
  h.studyOS[11] = new TH1F("OS_metphi", "OS_met", 200, -4, 4);
  h.studyOS[12] = new TH1F("OS_llep0mT", "OS_llep0mT", 1000, 0, 1000);
  h.studyOS[13] = new TH1F("OS_llep1mT", "OS_llep1mT", 1000, 0, 1000);
  h.studyOS[14] = new TH1F("OS_sumcos", "OS_sumcos", 300, -3, 3);
  h.studyOS[15] = new TH1F("OS_llep0_sip3d",    "OS_llep0_sip3d", 300, 0, 30);
  h.studyOS[16] = new TH1F("OS_llep0_reliso03", "OS_llep0_reliso03", 200, 0, 1);
  h.studyOS[17] = new TH1F("OS_llep0_reliso04", "OS_llep0_reliso04", 200, 0, 1);
  h.studyOS[18] = new TH1F("OS_llep1_sip3d",    "OS_llep1_sip3d", 300, 0, 30);
  h.studyOS[19] = new TH1F("OS_llep1_reliso03", "OS_llep1_reliso03", 200, 0, 1);
  h.studyOS[20] = new TH1F("OS_llep1_reliso04", "OS_llep1_reliso04", 200, 0, 1);
  h.studyOS[21] = new TH1F("OS_llep0_jetdeepB", "OS_llep0_jetdeepB", 400, -1, 3);
  h.studyOS[22] = new TH1F("OS_llep1_jetdeepB", "OS_llep1_jetdeepB", 400, -1, 3);
  for(int i=0; i<23; i++) h.studyOS[i]->Sumw2();
  
}//end of BOOK HISTOS
