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

  int RegionInt = 0;

  if(region == "TIB_L1"){RegionInt = 1;}
  else if(region == "TIB_L2"){RegionInt = 2;}
  else if(region == "TIB_L3"){RegionInt = 3;}
  else if(region == "TIB_L4"){RegionInt = 4;}
  else if(region == "Side_TID"){RegionInt = 5;}
  else if(region == "Wheel_TID"){RegionInt = 6;}
  else if(region == "Ring_TID"){RegionInt = 7;}
  else if(region == "TOB_L1"){RegionInt = 8;}
  else if(region == "TOB_L2"){RegionInt = 9;}
  else if(region == "TOB_L3"){RegionInt = 10;}
  else if(region == "TOB_L4"){RegionInt = 11;}
  else if(region == "TOB_L5"){RegionInt = 12;}
  else if(region == "TOB_L6"){RegionInt = 13;}
  else if(region == "Side_TEC"){RegionInt = 14;}
  else if(region == "Wheel_TEC"){RegionInt = 15;}
  else if(region == "Ring_TEC"){RegionInt = 16;}
  else{std::cout << "Error: The tracker region " << region << " was chosen. Please choose a region out of: TIB L1, TIB L2, TIB L3, TIB L4, Side TID, Wheel TID, Ring TID, TOB L1, TOB L2, TOB L3, TOB L4, TOB L5, TOB L6, Side TEC, Wheel TEC or Ring TEC." << std::endl; return 0;}


  //Lambda function to filter the detID for different layers
  auto SubDet_Function{[&RegionInt](const int& detID1_input){
	
        bool OutputBool = 0;

	switch(RegionInt){

		case 1: {OutputBool = (((detID1_input>>25)&0x7) == 3) && ((detID1_input>>14)&0x7) == 1; break;}
		case 2: {OutputBool = (((detID1_input>>25)&0x7) == 3) && (((detID1_input>>14)&0x7) == 2); break;}
		case 3: {OutputBool = (((detID1_input>>25)&0x7) == 3) && (((detID1_input>>14)&0x7) == 3); break;}
		case 4: {OutputBool = (((detID1_input>>25)&0x7) == 3) && (((detID1_input>>14)&0x7) == 4); break;}
		case 5: {OutputBool = (((detID1_input>>25)&0x7) == 4) && (detID1_input>>13)&0x3; break;}
		case 6: {OutputBool = (((detID1_input>>25)&0x7) == 4) && (detID1_input>>13)&0x11; break;}
		case 7: {OutputBool = (((detID1_input>>25)&0x7) == 4) && (detID1_input>>13)&0x9; break;}
		case 8: {OutputBool = (((detID1_input>>25)&0x7) == 5) && (((detID1_input>>14)&0x7) == 1); break;}
		case 9: {OutputBool = (((detID1_input>>25)&0x7) == 5) && (((detID1_input>>14)&0x7) == 2); break;}
		case 10: {OutputBool = (((detID1_input>>25)&0x7) == 5) && (((detID1_input>>14)&0x7) == 3); break;}
		case 11: {OutputBool = (((detID1_input>>25)&0x7) == 5) && (((detID1_input>>14)&0x7) == 4); break;}
		case 12: {OutputBool = (((detID1_input>>25)&0x7) == 5) && (((detID1_input>>14)&0x7) == 5); break;}
		case 13: {OutputBool = (((detID1_input>>25)&0x7) == 5) && (((detID1_input>>14)&0x7) == 6); break;}
		case 14: {OutputBool = (((detID1_input>>25)&0x7) == 6) && ((detID1_input>>18)&0x3); break;}
		case 15: {OutputBool = (((detID1_input>>25)&0x7) == 6) && ((detID1_input>>14)&0xF); break;}
		case 16: {OutputBool = (((detID1_input>>25)&0x7) == 6) && ((detID1_input>>5)&0x7); break;}

	}

	return OutputBool;

  }};


  //Applying the filter
  auto dataframe = d.Filter(SubDet_Function, {"detID1"});

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




//main function
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
