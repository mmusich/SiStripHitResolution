using namespace ROOT; 


vector<float> HitResolutionVector;
vector<float> DoubleDifferenceVector;
vector<float> HitDXVector;
vector<float> TrackDXVector;
vector<float> ExpectedW1Vector;
vector<float> ClusterW1Vector;


void ResolutionsCalculator(const string& region){

  //opening the root file
  ROOT::RDataFrame d("anResol/reso", "hitresol.root");

  //Layers 1-4 of the TIB
  auto SubDet_TIB_L1_Function{[](const unsigned int& detID1_input){return (((detID1_input>>25)&0x7) == 3) && (((detID1_input>>14)&0x7) == 1);}};
  auto SubDet_TIB_L2_Function{[](const unsigned int& detID1_input){return (((detID1_input>>25)&0x7) == 3) && (((detID1_input>>14)&0x7) == 2);}};
  auto SubDet_TIB_L3_Function{[](const unsigned int& detID1_input){return (((detID1_input>>25)&0x7) == 3) && (((detID1_input>>14)&0x7) == 3);}};
  auto SubDet_TIB_L4_Function{[](const unsigned int& detID1_input){return (((detID1_input>>25)&0x7) == 3) && (((detID1_input>>14)&0x7) == 4);}};

  //TID
  auto SubDet_SideTID_Function{[](const unsigned int& detID1_input){return (((detID1_input>>25)&0x7) == 4) && (detID1_input>>13)&0x3;}};
  auto SubDet_WheelTID_Function{[](const unsigned int& detID1_input){return (((detID1_input>>25)&0x7) == 4) && (detID1_input>>13)&0x11;}};
  auto SubDet_RingTID_Function{[](const unsigned int& detID1_input){return (((detID1_input>>25)&0x7) == 4) && (detID1_input>>13)&0x9;}};


  //Layers 1-6 of the TOB
  auto SubDet_TOB_L1_Function{[](const unsigned int& detID1_input){return (((detID1_input>>25)&0x7) == 5) && (((detID1_input>>14)&0x7) == 1);}};
  auto SubDet_TOB_L2_Function{[](const unsigned int& detID1_input){return (((detID1_input>>25)&0x7) == 5) && (((detID1_input>>14)&0x7) == 2);}};
  auto SubDet_TOB_L3_Function{[](const unsigned int& detID1_input){return (((detID1_input>>25)&0x7) == 5) && (((detID1_input>>14)&0x7) == 3);}};
  auto SubDet_TOB_L4_Function{[](const unsigned int& detID1_input){return (((detID1_input>>25)&0x7) == 5) && (((detID1_input>>14)&0x7) == 4);}};
  auto SubDet_TOB_L5_Function{[](const unsigned int& detID1_input){return (((detID1_input>>25)&0x7) == 5) && (((detID1_input>>14)&0x7) == 5);}};
  auto SubDet_TOB_L6_Function{[](const unsigned int& detID1_input){return (((detID1_input>>25)&0x7) == 5) && (((detID1_input>>14)&0x7) == 6);}};  

  //TEC
  auto SubDet_SideTEC_Function{[](const unsigned int& detID1_input){return (((detID1_input>>25)&0x7) == 6) && ((detID1_input>>18)&0x3);}};
  auto SubDet_WheelTEC_Function{[](const unsigned int& detID1_input){return (((detID1_input>>25)&0x7) == 6) && ((detID1_input>>14)&0xF);}};
  auto SubDet_RingTEC_Function{[](const unsigned int& detID1_input){return (((detID1_input>>25)&0x7) == 6) && ((detID1_input>>5)&0x7);}};


  //Filtering the RDataFrame to consider each tracker region
  auto dataframe = d.Filter("detID1"); //this is just to define dataframe and is overwritten in the if else statements below

  if(region == "TIB_L1"){auto dataframe = d.Filter(SubDet_TIB_L1_Function, {"detID1"});} 
  else if(region == "TIB_L2"){auto dataframe = d.Filter(SubDet_TIB_L2_Function, {"detID1"});}
  else if(region == "TIB_L3"){auto dataframe = d.Filter(SubDet_TIB_L3_Function, {"detID1"});} 
  else if(region == "TIB_L4"){auto dataframe = d.Filter(SubDet_TIB_L4_Function, {"detID1"});}
  else if(region == "Side_TID"){auto dataframe = d.Filter(SubDet_SideTID_Function, {"detID1"});}
  else if(region == "Wheel_TID"){auto dataframe = d.Filter(SubDet_WheelTID_Function, {"detID1"});}
  else if(region == "Ring_TID"){auto dataframe = d.Filter(SubDet_RingTID_Function, {"detID1"});}
  else if(region == "TOB_L1"){auto dataframe = d.Filter(SubDet_TOB_L1_Function, {"detID1"});}
  else if(region == "TOB_L2"){auto dataframe = d.Filter(SubDet_TOB_L2_Function, {"detID1"});}
  else if(region == "TOB_L3"){auto dataframe = d.Filter(SubDet_TOB_L3_Function, {"detID1"});}
  else if(region == "TOB_L4"){auto dataframe = d.Filter(SubDet_TOB_L4_Function, {"detID1"});}
  else if(region == "TOB_L5"){auto dataframe = d.Filter(SubDet_TOB_L5_Function, {"detID1"});}
  else if(region == "TOB_L6"){auto dataframe = d.Filter(SubDet_TOB_L6_Function, {"detID1"});}
  else if(region == "Side_TEC"){auto dataframe = d.Filter(SubDet_SideTEC_Function, {"detID1"});}
  else if(region == "Wheel_TEC"){auto dataframe = d.Filter(SubDet_WheelTEC_Function, {"detID1"});}
  else if(region == "Ring_TEC"){auto dataframe = d.Filter(SubDet_RingTEC_Function, {"detID1"});}
  else{std::cout << "Error: The tracker region " << region << " was chosen. Please choose a region out of: TIB L1, TIB L2, TIB L3, TIB L4, Side TID, Wheel TID, Ring TID, TOB L1, TOB L2, TOB L3, TOB L4, TOB L5, TOB L6, Side TEC, Wheel TEC or Ring TEC." << std::endl; return 0;}



  //obtaining the branches trackDX and hitDX
  //hitDX = the difference in the hit positions for the pair
  //trackDX =  the difference in the track positions for the pair 
  auto DifferenceFunction{[](const float& hitDX, const float& trackDX){auto DoubleDiff = hitDX-trackDX; return DoubleDiff;}};

  auto HistoName_DoubleDiff = "DoubleDifference_" + region;
  auto HistoName_HitDX = "HitDX_" + region;
  auto HistoName_TrackDX = "TrackDX_" + region;
  auto HistoName_ClusterW1 = "ClusterW1_" + region;
  auto HistoName_ExpectedW1 = "ExpectedW1_" + region;
  auto HistoName_DetID1 = "DetID1_" + region;

  auto h_DoubleDifference = dataframe.Define(HistoName_DoubleDiff, DifferenceFunction, {"hitDX", "trackDX"}).Histo1D({HistoName_DoubleDiff.c_str(), HistoName_DoubleDiff.c_str(), 40, -0.5, 0.5}, HistoName_DoubleDiff); 
  auto h_hitDX = dataframe.Define(HistoName_HitDX, {"hitDX"}).Histo1D(HistoName_HitDX);
  auto h_trackDX = dataframe.Define(HistoName_TrackDX, {"trackDX"}).Histo1D(HistoName_TrackDX);
  auto h_expectedW1 = dataframe.Define(HistoName_ExpectedW1, {"expectedW1"}).Histo1D(HistoName_ExpectedW1);
  auto h_clusterW1 = dataframe.Define(HistoName_ClusterW1, {"clusterW1"}).Histo1D(HistoName_ClusterW1);
  auto h_DetID1 = dataframe.Define(HistoName_DetID1, {"detID1"}).Histo1D(HistoName_DetID1);

  //Applying gaussian fits, taking the resolutions and squaring them
  h_DoubleDifference->Fit("gaus");
  h_hitDX->Fit("gaus");
  h_trackDX->Fit("gaus");
  h_expectedW1->Fit("gaus");
  h_clusterW1->Fit("gaus");

  auto hitDX_trackDX_StdDev = h_DoubleDifference->GetStdDev();
  auto hitDX_StdDev = h_hitDX->GetStdDev();
  auto trackDX_StdDev = h_trackDX->GetStdDev();
  auto expectedW1_StdDev = h_expectedW1->GetStdDev();
  auto clusterW1_StdDev = h_clusterW1->GetStdDev();

  auto sigma2_PredMinusMeas = pow(hitDX_trackDX_StdDev, 2);
  auto sigma2_Meas = pow(hitDX_StdDev, 2);
  auto sigma2_Pred = pow(trackDX_StdDev, 2); 
  auto sigma2_expectedW1 = pow(expectedW1_StdDev, 2);
  auto sigma2_clusterW1 = pow(clusterW1_StdDev, 2);

  auto DoubleDifferenceWidth = sigma2_Pred + sigma2_Meas;

  DoubleDifferenceVector.push_back(sigma2_PredMinusMeas);
  HitDXVector.push_back(sigma2_Meas);
  TrackDXVector.push_back(sigma2_Pred);
  ExpectedW1Vector.push_back(sigma2_expectedW1);
  ClusterW1Vector.push_back(sigma2_clusterW1);

  //Saving the histograms with gaussian fits applied to an output root file
  h_DoubleDifference->Write();
  h_hitDX->Write();
  h_trackDX->Write();
  h_expectedW1->Write();
  h_clusterW1->Write();
  h_DetID1->Write();

  //Calculating the hit resolution
  //sigma2_PredMinusMeas - sigma2_Meas;
  auto HitResolution = sqrt( (sigma2_PredMinusMeas - sigma2_Meas)/2 );
  HitResolutionVector.push_back(HitResolution);

  //Printing the resolution 
  std::cout << '\n' << std::endl;
  std::cout << "The hit resolution for tracker region " << region << " is: " << HitResolution << std::endl;
  std::cout << '\n' << std::endl;

}


void Resolutions(){

  TFile * output = new TFile("GaussianFits.root", "RECREATE");

  vector<std::string> LayerNames = {"TIB_L1",   "TIB_L2",    "TIB_L3",    "TIB_L4",
				    "Side_TID", "Wheel_TID", "Ring_TID",  "TOB_L1",
				    "TOB_L2",   "TOB_L3",    "TOB_L4",    "TOB_L5",
				    "TOB_L6",   "Side_TEC",  "Wheel_TEC", "Ring_TEC"};


  std::ofstream HitResoTextFile;
  HitResoTextFile.open("HitResolutionValues.txt");

  auto Width = 28; 

  for(int i = 0; i < LayerNames.size(); i++){ResolutionsCalculator(LayerNames.at(i));}
 
  HitResoTextFile << std::right << "Layer " << std::setw(Width) << " Resolution " << std::setw(Width) << " sigma2_HitDX " << std::setw(Width) << " sigma2_trackDX " << std::setw(Width) << " DoubleDifference " << std::setw(Width) << " sigma2_expectedW1 " << std::setw(Width) << " sigma2_clusterW1 "<< std::endl;

  for(int i = 0; i < HitResolutionVector.size(); i++){

	HitResoTextFile << std::right << LayerNames.at(i) << std::setw(Width) << HitResolutionVector.at(i) << std::setw(Width) << HitDXVector.at(i)  << std::setw(Width) << TrackDXVector.at(i) << std::setw(Width) << DoubleDifferenceVector.at(i) << std::setw(Width) << ExpectedW1Vector.at(i) << std::setw(Width) << ClusterW1Vector.at(i) << endl;

  }

  output->Close();

}
