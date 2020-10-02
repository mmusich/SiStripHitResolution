using namespace ROOT; 


vector<float> HitResolutionVector;
vector<float> DoubleDifferenceVector;
vector<float> HitDXVector;
vector<float> TrackDXVector;

std::string InputFileString;
std::string HitResoFileName;
std::string GaussianFitsFileName;

void ResolutionsCalculator(const string& region, const int& UnitInt, const int& UL){


  switch(UL){
	case 0: switch(UnitInt){
        		case 0: GaussianFitsFileName = "GaussianFits_PitchUnits_ALCARECO.root"; 
				HitResoFileName = "HitResolutionValues_PitchUnits_ALCARECO.txt"; 
				break;

        		case 1: GaussianFitsFileName = "GaussianFits_Micrometres_ALCARECO.root"; 
				HitResoFileName = "HitResolutionValues_Micrometres_ALCARECO.txt"; 
				break;

        		default: std::cout << "ERROR: UnitInt must be 0 or 1." << std::endl; break;
  		}

		InputFileString = "hitresol_ALCARECO.root"; 
		break;

	case 1: switch(UnitInt){
                        case 0: GaussianFitsFileName = "GaussianFits_PitchUnits_ALCARECO_UL.root"; 
                                HitResoFileName = "HitResolutionValues_PitchUnits_ALCARECO_UL.txt"; 
                                break;

                        case 1: GaussianFitsFileName = "GaussianFits_Micrometres_ALCARECO_UL.root"; 
                                HitResoFileName = "HitResolutionValues_Micrometres_ALCARECO_UL.txt"; 
                                break;

                        default: std::cout << "ERROR: UnitInt must be 0 or 1." << std::endl; break;
                }

		InputFileString = "hitresol_ALCARECO_UL.root"; 
		break;
	default: std::cout << "The UL input parameter must be set to 0 (for ALCARECO) or 1 (for UL ALCARECO)." << std::endl; break;
  }

  //opening the root file
  ROOT::RDataFrame d("anResol/reso", InputFileString.c_str());

  int RegionInt = 0;
  int UnitInt = 0;

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


  if(unit == "pitch"){UnitInt = 0;}
  else if(unit == "micrometres"){UnitInt = 1;}
  else{std::cout << "Error: The unit " << unit << " was chosen. Please choose a unit out of pitch or micrometres." << std::endl; return 0; }

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


  auto Pitch_Function{[&UnitInt](const float& pitch, const float& input){

	float InputOverPitch;

	switch(UnitInt){

		case 0: InputOverPitch = input/pitch; break; 
		case 1: InputOverPitch = 1.0; break;
			
	}

	return InputOverPitch;

  }};

  //Applying the filter
  auto dataframe = d.Filter(SubDet_Function, {"detID1"});

  //hitDX = the difference in the hit positions for the pair
  //trackDX =  the difference in the track positions for the pair 

  auto HistoName_DoubleDiff = "DoubleDifference_" + region;
  auto HistoName_HitDX = "HitDX_" + region;
  auto HistoName_TrackDX = "TrackDX_" + region;
  auto HistoName_ClusterW1 = "ClusterW1_" + region;
  auto HistoName_ExpectedW1 = "ExpectedW1_" + region;
  auto HistoName_ClusterW2 = "ClusterW2_" + region;
  auto HistoName_ExpectedW2 = "ExpectedW2_" + region;
  auto HistoName_DetID1 = "DetID1_" + region;
  auto HistoName_Pitch = "Pitch_" + region;

  auto dataframe_filtered = dataframe.Filter("trackChi2 > 0.001 && numHits > 5 && trackDXE < 0.0025");

  auto h_DoubleDifference = dataframe_filtered.Define(HistoName_DoubleDiff, {"trackDX-hitDX"}).Histo1D({HistoName_DoubleDiff.c_str(), HistoName_DoubleDiff.c_str(), 40, -0.5, 0.5}, HistoName_DoubleDiff); 
  auto h_hitDX = dataframe_filtered.Define(HistoName_HitDX, {"hitDX"}).Histo1D(HistoName_HitDX);
  auto h_trackDX = dataframe_filtered.Define(HistoName_TrackDX, {"trackDX"}).Histo1D(HistoName_TrackDX);

  //Applying gaussian fits, taking the resolutions and squaring them
  h_DoubleDifference->Fit("gaus");
  h_hitDX->Fit("gaus");
  h_trackDX->Fit("gaus");

  auto double_diff_StdDev = h_DoubleDifference->GetStdDev();
  auto hitDX_StdDev = h_hitDX->GetStdDev();
  auto trackDX_StdDev = h_trackDX->GetStdDev();

  auto sigma2_PredMinusMeas = pow(double_diff_StdDev, 2);
  auto sigma2_Meas = pow(hitDX_StdDev, 2);
  auto sigma2_Pred = pow(trackDX_StdDev, 2); 
  
  auto DoubleDifferenceWidth = sigma2_Pred + sigma2_Meas;

  DoubleDifferenceVector.push_back(sigma2_PredMinusMeas);
  HitDXVector.push_back(sigma2_Meas);
  TrackDXVector.push_back(sigma2_Pred);

  //Saving the histograms with gaussian fits applied to an output root file
  h_DoubleDifference->Write();
  h_hitDX->Write();
  h_trackDX->Write();
  //sigma2_PredMinusMeas - sigma2_Meas;
  std::cout << "sigma2_PredMinusMeas = " << sigma2_PredMinusMeas << std::endl;
  std::cout << "sigma2_Meas = " << sigma2_Meas << std::endl;

  auto numerator = sigma2_PredMinusMeas - sigma2_Meas;

  auto HitResolution = sqrt( numerator/2 );
  HitResolutionVector.push_back(HitResolution);

  //Printing the resolution 
  std::cout << '\n' << std::endl;
  std::cout << "The hit resolution for tracker region " << region << " is: " << HitResolution << std::endl;
  std::cout << '\n' << std::endl;

}




void Resolutions(){

  int UnitInteger = 0;
  int ULInteger = 0;

  TFile * output = new TFile(GaussianFitsFileName.c_str(), "RECREATE");

  vector<std::string> LayerNames = {"TIB_L1",   "TIB_L2",    "TIB_L3",    "TIB_L4",
				    "Side_TID", "Wheel_TID", "Ring_TID",  "TOB_L1",
				    "TOB_L2",   "TOB_L3",    "TOB_L4",    "TOB_L5",
				    "TOB_L6",   "Side_TEC",  "Wheel_TEC", "Ring_TEC"};


  vector<std::string> UnitNames = {"pitch", "micrometres"};

  std::ofstream HitResoTextFile;
  HitResoTextFile.open(HitResoFileName);

  auto Width = 28; 

  for(int i = 0; i < LayerNames.size(); i++){

	ResolutionsCalculator(LayerNames.at(i), UnitNames.at(UnitInteger));
  }
 
  HitResoTextFile << std::right << "Layer " << std::setw(Width) << " Resolution " << std::setw(Width) << " sigma2_HitDX " << std::setw(Width) << " sigma2_trackDX " << std::setw(Width) << " DoubleDifference " << std::setw(Width) << " sigma2_expectedW1 " << std::setw(Width) << " sigma2_clusterW1 "<< std::endl;

  for(int i = 0; i < HitResolutionVector.size(); i++){

	HitResoTextFile << std::right << LayerNames.at(i) << std::setw(Width) << HitResolutionVector.at(i) << std::setw(Width) << HitDXVector.at(i)  << std::setw(Width) << TrackDXVector.at(i) << std::setw(Width) << DoubleDifferenceVector.at(i) << std::setw(Width) << ExpectedW1Vector.at(i) << std::setw(Width) << ClusterW1Vector.at(i) << endl;

  }

  output->Close();

}
