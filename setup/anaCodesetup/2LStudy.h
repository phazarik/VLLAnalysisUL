void VLLAna::Make2LPlots()
{
  //This function is called in the main VLLAna.C file.
  //It runs for all the 2L events.

  //Filling out different boxes:
  //bin0 -> n2L
  //bin1 -> OS
  //bin2 -> OSSF
  //bin3 -> OSOF
  //bin4 -> SS
  //bin5 -> SSSF
  //bin6 -> SSOF
  h.study2L[0]->Fill(0);//n2L

  //For opposite signed lepton pairs:
  if(llep.at(0).charge == -llep.at(1).charge){
    n_os++;
    h.study2L[0]->Fill(1);
    //for same flavoured pairs:
    if(fabs(llep.at(0).id) == fabs(llep.at(1).id)){
      n_ossf++;
      h.study2L[0]->Fill(2); //OSSF
    }
    else{
      //for different flavoured pairs:
      n_osof++;
      h.study2L[0]->Fill(3); //OSOF
    }
  }
  
  //For same signed lepton pairs:
  if(llep.at(0).charge == llep.at(1).charge){
    n_ss++;
    h.study2L[0]->Fill(4);//SS
    if(fabs(llep.at(0).id) == fabs(llep.at(1).id)){
      n_sssf++;
      h.study2L[0]->Fill(5); //SSSF
    }
    else{
      n_ssof++;
      h.study2L[0]->Fill(6); //SSOF
    }
  }
  
}
