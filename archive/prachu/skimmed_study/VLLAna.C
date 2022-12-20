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

//#include "/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/setup/anaCodesetup/2LStudy.h"
#include "/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/setup/anaCodesetup/2muStudy.h"
//#include "/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/setup/anaCodesetup/SSStudy.h"

void VLLAna::Begin(TTree * /*tree*/)
{
  iiserlogo();
  //   cout<<"Inside Begin()"<<endl;
  TString option = GetOption();
  ReadNNWeights();

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
  /*cout<<"No of 3L events="<<n3L<<endl;
    cout<<"No of 3LonZ events="<<n3LonZ<<endl;
    cout<<"No of ttbarCR satisfied event="<<n_ttbarcr<<endl;
    cout<<"No of ttbarCR satisfied event(2L+Fake)="<<n_ttbar2Lplus1Fake<<endl;
    cout<<"===============--------------==============="<<endl;
    cout<<"No of good leptons(analysisCut)="<<n_mu_anlys<<endl;
    cout<<"No of good leptons(NNScoreCut)="<<n_mu_NNScore<<endl;
    cout<<"No of true b-fake(jethadronflav) leptons="<<n_mu_bfake<<endl;
    cout<<"No of true b-fake(partonflav) leptons="<<n_mu_bfake_flav<<endl;
    cout<<"No of true b-fake(matching) leptons="<<n_bfake_matching<<endl;
    cout<<"No of true prompt good leptons="<<n_mu_prompt<<endl;
  */

  cout<<"No of 2L Events="<<n_ll<<endl;
  cout<<"No of LTau Events="<<n_lt<<endl;
  cout<<"No of TauTau Events="<<n_tt<<endl;
  cout<<"No of L+2j Events="<<n_l2j<<endl;
  cout<<"_______________________________________________"<<endl;
  
  cout<<"2L OSSF events="<<n_ll_OSSF<<endl;
  cout<<"2L OSOF events="<<n_ll_OSOF<<endl;
  cout<<"2L SSSF events="<<n_ll_SSSF<<endl;
  cout<<"2L SSOF events="<<n_ll_SSOF<<endl;
  
  cout<<"2L:OSSF+OSOF+SSSF+SSOF="<<n_ll_OSSF+n_ll_OSOF+n_ll_SSSF+n_ll_SSOF<<endl;
  cout<<"_______________________________________________"<<endl;
  cout<<"                CutFlow                      "<<endl;
  cout<<"_______________________________________________"<<endl;
  cout<<"Events has atleast 1 light lepton(N_evt >=1l)="<<n_l<<endl;
  cout<<"l PT>15 GeV="<<n_l15GeV<<endl;
  cout<<"Satisfy Trigger="<<n_trigg<<endl;
  cout<<"Events has atleast two llep(2nd lep pt>10 GeV)="<<n_2l<<endl;
  
  cout<<"_______________________________________________"<<endl;
  cout<<"               1L + >=1T events                "<<endl;
  cout<<"_______________________________________________"<<endl;
  cout<<"No of 1L + >=1T events       ="<<n_1l1t<<endl;
  cout<<"1L1T: Tau pass loose deepcsv ="<<n_1l1tloose<<endl;
  cout<<"1L1T: Tau pass |n|<2.3 cut   ="<<n_1l1tpassEta<<endl;
  cout<<"1L1T: Tau pass Loose AntiEle ="<<n_1l1tpassAntiEle<<endl;
  cout<<"1L1T: Tau pass Loose AntiMu  ="<<n_1l1tpassAntiMu<<endl;
  cout<<"1L1T: Tau pass dz cut        ="<<n_1l1tprompt<<endl;
  cout<<"1L1T: Tau pass lep cleaned   ="<<n_1l1tlepclean<<endl;
  cout<<"1L1T: Tau pass PT cut        ="<<n_1l1tpassPt<<endl;
  
  cout<<"_______________________________________________"<<endl;
  cout<<"               >=2Tau events                "<<endl;
  cout<<"_______________________________________________"<<endl;
  cout<<"No of >= 1 hadronic tau events="<<n_t<<endl;
  cout<<"No of >= 2 hadronic tau events="<<n_2t<<endl;
  cout<<"Leading tau pT >35 GeV="<<n_t35GeV<<endl;
  cout<<"Leading tau pT >70 GeV="<<n_tautrigg<<endl;

  cout<<"_______________________________________________"<<endl;
  cout<<"Prachu's counts in 2L channel                 "<<endl;
  cout<<"Events with OS leptons = "<<n_os;
  cout<<"  (OSSF : "<<n_ossf<< " and OSOF : "<<n_osof <<" )"<<endl;
  cout<<"Events with SS leptons = "<<n_ss;
  cout<<"  (SSSF : "<<n_sssf<< " and SSOF : "<<n_ssof <<" )"<<endl;
  cout<<"_______________________________________________\n"<<endl;
  
  
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

	/*
	//Produce Histos
	if(MuonChannel){
	  if(regA)VLL_wjetsEstimation(2);
	  if(regB)VLL_wjetsEstimation(3);
	  if(regC)VLL_wjetsEstimation(4);
	  if(regD)VLL_wjetsEstimation(5);
	}*/
	

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
      }

      //########################### 
      // Analysis of 2L events
      //###########################

      /*
      if(is_ll_event){
	//Putting a singleMuon trigger:
	bool singleMuonTrigger = false;
	if(_data == 1) singleMuonTrigger = true;
	else if(_data == 0){
	  if(fabs(llep.at(0).id) == 13 && llep.at(0).v.Pt()>24) singleMuonTrigger=true;
	  else if(fabs(llep.at(1).id) == 13 && llep.at(1).v.Pt()>24) singleMuonTrigger=true;
	}
	//Selecting well separated leptons:
	float dRllep = llep.at(0).v.DeltaR(llep.at(1).v);
	
	//if the leading lepton or the subleading lepton triggers the event,
	//and they are separated by a dR of atleast 0.4
	if(singleMuonTrigger && dRllep>0.4){
	  Make2LPlots();
	  MakeSSPlots();
	}
	}*/
      
      //###########################
      // Analysis of 2Mu events
      //###########################
      if((int)Muon.size()>1){
	float dimuon_mass = (Muon.at(0).v+Muon.at(1).v).M();
	float muon_dr = Muon.at(0).v.DeltaR(Muon.at(1).v);
	float leading_pT = Muon.at(0).v.Pt();
	bool baseSelection = dimuon_mass>20 && muon_dr>0.4 && leading_pT>26;
	
	if(baseSelection) Make2muPlots();
      }
      
      //tt
      if(is_tt_event){
	//VLLPlots(2,14);
	n_tt++,h.vllclass->Fill(3);//tt plots
      }

      
      // Signal CutFlow
      SignalCutflow();
      
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
  /*h.metfilter[0] = new TH1F("METfilter_goodVertices","METfilter_goodVertices",5,-1,4);
  h.metfilter[1] = new TH1F("METfilter_globalSuperTightHalo2016Filter","METfilter_globalSuperTightHalo2016Filter",5,-1,4);
  h.metfilter[2] = new TH1F("METfilter_HBHENoiseFilter","METfilter_HBHENoiseFilter",5,-1,4);
  h.metfilter[3] = new TH1F("METfilter_HBHENoiseIsoFilter","METfilter_HBHENoiseIsoFilter",5,-1,4);
  h.metfilter[4] = new TH1F("METfilter_EcalDeadCellTriggerPrimitiveFilter","METfilter_EcalDeadCellTriggerPrimitiveFilter",5,-1,4);
  h.metfilter[5] = new TH1F("METfilter_BadPFMuonFilter","METfilter_BadPFMuonFilter",5,-1,4);
  h.metfilter[6] = new TH1F("METfilter_eeBadScFilter","METfilter_eeBadScFilter",5,-1,4);
  h.metfilter[7] = new TH1F("METfilter_GoodEvt2016","METfilter_GoodEvt2016",5,-1,4);
  h.metfilter[8] = new TH1F("METfilter_GoodEvt2017","METfilter_GoodEvt2017",5,-1,4);
  h.metfilter[9] = new TH1F("METfilter_GoodEvt2018","METfilter_GoodEvt2018",5,-1,4);
  h.metfilter[10] = new TH1F("METfilter_GoodEvt","METfilter_GoodEvt",5,-1,4);*/


  //Basic plots starts
  //lepton(ele,mu,tau)
  /*
  h.nlep[0] = new TH1F("nMu","Number of Muon Candidates",20,0,20);
  h.nlep[1] = new TH1F("ngoodMu","Number of good Muon Candidates",20,0,20);
  h.nlep[2] = new TH1F("nEl","Number of Electron Candidates",20,0,20);
  h.nlep[3] = new TH1F("ngoodEl","Number of good Electron Candidates",20,0,20);
  h.nlep[4] = new TH1F("nTau","Number of Tau Candidates",20,0,20);
  h.nlep[5] = new TH1F("ngoodTau","Number of good Tau Candidates",20,0,20);
  h.nlep[6] = new TH1F("nPho","Number of Photon Candidates",20,0,20); 
  for(int i=0; i<7; i++) h.nlep[i]->Sumw2();*/
  
  //jets
  h.nJet[0]= new TH1F("njet","No of goodjets",20,0,20);
  h.nJet[1]= new TH1F("nbjet","No of good b-tagged jets",20,0,20);
  for(int i=0;i<2;i++) h.nJet[i]->Sumw2();
  
  /*
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
  for(int i=0; i<9; i++) h.ptlep[i]->Sumw2();*/
  
  //missing ET of the event
  h.etmiss= new TH1F("etmiss_beforeMTcut","Missing E_{T}",1000,0,1000); h.etmiss->Sumw2();
  
  //object cutflow
  h.mucut = new TH1F("mucut","0=pt,1=eta,2=dxydz,3=loose,4=Medium,5=Iso:0.25",10,0,10);h.mucut->Sumw2();
  h.elcut = new TH1F("elcut","0=pt,1=eta,2=dxydz,3=loose,4=Medium,5=muoncleaning",10,0,10);h.elcut->Sumw2();
  h.taucut = new TH1F("taucut","0=All,1=NewDM,2=DeepCSV,3=AntiEle,4=AntiMu,5=Prompt,6=LepClean,7=Eta,8=PT",10,0,10);h.taucut->Sumw2();
  h.phocut = new TH1F("phocut","phocuts",10,0,10);
  
  
  //////////////////////////////   GEN PARTICLE BLOCK STARTS   /////////////////////////////////////////////////
  
  /*
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
  for(int i=0;i<3;i++)h.genjet[i]->Sumw2();*/
  
  //Lep Pt/b-quark Pt//                                                    
  h.fracpt = new TH1F("fracPt"        ,"Lep Pt/ b quark Pt",1000,0,10);h.fracpt->Sumw2();



  //evtwt
  h.evtwt[0] = new TH1F("evtwt"        ,"EventWeight",100,0,1);
  h.evtwt[1] = new TH1F("evtwt_mu"        ,"EventWeight after mumumu selection",100,0,1);
  h.evtwt[2] = new TH1F("triggereff"        ,"Trigger Efficiency",100,0,1);
  h.evtwt[3] = new TH1F("totwt"        ,"Trigger Eff x evtwt",100,0,1);
  for(int i=0;i<4;i++) h.evtwt[i]->Sumw2();
  
  /* //VLL Plots
  TString vllreg[3]={"ll","ltau","tautau"};
  TString vllplot[35]={"FirstLeptonPt","SecondLeptonPt","FirstLeptonEta","SecondLeptonEta","FirstLeptonPhi","SecondLeptonPhi","dRlep01","dPhilep0met","dPhilep1met","dRlep0jet0","dRlep1jet0","dPhijetmet","Mass","OSMass","SSMass","mtlep0","mtlep1","LT","MET","HT","ST","njet","nbjet","dilepPt","dilepMT","lep0jet0Pt","lep1jet0Pt","lep01jet0Pt","lepjetMT","lep0jet01Pt","lep1jet01Pt","lep01jet01Pt","lep01jet0MT","lep01jet1MT","lep01jet01MT"};
  float vllnbins[35]={1000,1000,100,100,100,100,100,100,100,100,100,100,1000,1000,1000,1000,1000,1000,1000,1000,1000,10,10,1000,1000,1000,1000,1000,2000,1000,1000,1000,2000,2000,2000};
  float vllxlow[35]= {0,0,-5,-5,-5,-5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  float vllxhi[35] = {1000,1000,5,5,5,5,5,5,5,5,5,5,1000,1000,1000,1000,1000,1000,1000,1000,1000,10,10,1000,1000,1000,1000,1000,2000,1000,1000,1000,2000,2000,2000};
  TString vllbin[15]={"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14"};
  
  for(int i=0;i<3;i++){
    for(int k=0;k<15;k++){
      for(int j=0;j<35;j++){
	TString title=vllreg[i]+"_"+vllplot[j]+"_bin"+vllbin[k];
	h.vllplot[j][i][k]=new TH1F(title,title,vllnbins[j],vllxlow[j],vllxhi[j]);h.vllplot[j][i][k]->Sumw2();
      }
    }
  }
  */
  h.vllclass = new TH1F("vll_event","VLL event: 1=ll,2=lt,3=tt",5,0,5);h.vllclass->Sumw2();

  /*
  h.region[0]=new TH1F("llchannel","ll decomp",15,0,15);
  h.region[1]=new TH1F("ltchannel","lt decomp",15,0,15);
  for(int i=0;i<2;i++)h.region[i]->Sumw2();*/


  //1L1T Acceptance PT plots
  /*
  h.tauacc[0]=new TH1F("pt_base","Baseic 1L1T events Pt",1000,0,1000);
  h.tauacc[1]=new TH1F("pt_loose","Pt: Tau Pass loose deepcsv",1000,0,1000);
  h.tauacc[2]=new TH1F("pt_passEta","Pt: Tau Pass Eta cut",1000,0,1000);
  h.tauacc[3]=new TH1F("pt_passAntiEle","Pt: Tau Pass Loose Anti Ele",1000,0,1000);
  h.tauacc[4]=new TH1F("pt_passAntiMu","Pt: Tau Pass Loose Anti Mu",1000,0,1000);
  h.tauacc[5]=new TH1F("pt_prompt","Pt: Tau Pass prompt cut",1000,0,1000);
  h.tauacc[6]=new TH1F("pt_lepclean","Pt: Tau Pass lep cleaning",1000,0,1000);
  h.tauacc[7]=new TH1F("pt_passPt","Pt: Tau Pass Pt cut",1000,0,1000);
  for(int i=0;i<8;i++)h.tauacc[i]->Sumw2();*/
  
  
  //l2j events histos
  /*
  TString l2jplot[22]={"ptlep0","ptjet0","ptjet1","mtlep0","mtjet0","mtjet1","dijetmass","drjet01","dijetPT","dijetMT","MET","HT","ST","njet","nbjet","dphimetjet0","dphimetjet1","dphimetlep0","dphijet0lep0","dphijet1lep0","dphidijetlep0","dphimetdijet"};
  TString l2jfancyname[22]={"Lepton PT","Leading Jet PT","SubLeading Jet PT","Lepton MT","Leading Jet MT","SubLeading Jet MT","Dijet Inv Mass","DR(jet0,jet1)","Dijet System PT","Dijet System MT","MET in 1L2J events","HT in 1L2J events","ST in 1L2J events","No of Jets","No of b-jets","dphimetjet0","dphimetjet1","dphimetlep0","dphijet0lep0","dphijet1lep0","dphidijetlep0","dphimetdijet"};
  TString type[6]={"","_highMVA","_regA","_regB","_regC","_regD"};
  float l2jbin[22]={1000,1000,1000,1000,1000,1000,1000,100,1000,1000,1000,1000,1000,10,10,100,100,100,100,100,100,100};
  float l2jbinlow[22]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  float l2jbinhi[22]={1000,1000,1000,1000,1000,1000,1000,10,1000,1000,1000,1000,1000,10,10,10,10,10,10,10,10,10};  
  
  for(int i=0;i<22;i++){
    for(int j=0;j<6;j++){
      TString plottitle= l2jplot[i]+"_l2j"+type[j];
      TString title= l2jfancyname[i]+type[j];
      h.vllplotl2j[i][j]=new TH1F(plottitle,title,l2jbin[i],l2jbinlow[i],l2jbinhi[i]);h.vllplotl2j[i][j]->Sumw2();
      }
      }*/
  
  
  //NNScore
  /*
  h.nnprob[0] = new TH1F("nnscore","NN score at signal Neuron",120,0,1.2);
  h.nnprob[1] = new TH1F("nnscore1","ttjets score",120,0,1.2);
  for(int i=0;i<2;i++)h.nnprob[i]->Sumw2();*/

  /*
  //For Sourabh(July18,2022)
  h.sourabh[0] = new TH1F("mtlep_PFMET","Leading Lepton MT (PF)",1000,0,1000);
  h.sourabh[1] = new TH1F("mtlep_PuppiMET","Leading Lepton MT (Puppi)",1000,0,1000);
  h.sourabh[2] = new TH1F("mtlep_PFMET_cut","Leading Lepton MT after PFMET>30 GeV",1000,0,1000);
  h.sourabh[3] = new TH1F("mtlep_PuppiMET_cut","Leading Lepton MT after PuppiMet>30 GeV",1000,0,1000);
  for(int i=0;i<4;i++)h.sourabh[i]->Sumw2();*/


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


