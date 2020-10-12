using namespace ROOT; 
using ROOT::RDF::RNode;
using floats = ROOT::VecOps::RVec<float>;
using ints = ROOT::VecOps::RVec<int>;
using bools = ROOT::VecOps::RVec<bool>;
using chars = ROOT::VecOps::RVec<UChar_t>;
using doubles = ROOT::VecOps::RVec<double>;

vector<float> HitResolutionVector;
vector<float> DoubleDifferenceVector;
vector<float> HitDXVector;
vector<float> TrackDXVector;

std::string InputFileString;
std::string HitResoFileName;
std::string GaussianFitsFileName;



void ResolutionsCalculator(const string& region, const int& Unit_Int, const int& UL){


  switch(UL){
	case 0: switch(Unit_Int){
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

	case 1: switch(Unit_Int){
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
  ROOT::RDataFrame d("anResol/reso", InputFileString);

  int RegionInt = 0;

  if(region == "Pixels"){RegionInt = 0;}
  else if(region == "TIB_L1"){RegionInt = 1;}
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
  auto SubDet_Function{[&RegionInt](const int& detID1_input, const int& detID2_input){
	
        bool OutputBool = 0;

	switch(RegionInt){
		case 0: {OutputBool = (((detID1_input>>25)&0x7) < 3) && (((detID2_input>>25)&0x7) < 3);
			 break;}

		case 1: {OutputBool = (((detID1_input>>25)&0x7) == 3) && ((detID1_input>>14)&0x7) == 1 &&
				      (((detID2_input>>25)&0x7) == 3) && ((detID2_input>>14)&0x7) == 1; 
			 break;}

		case 2: {OutputBool = (((detID1_input>>25)&0x7) == 3) && (((detID1_input>>14)&0x7) == 2) &&
				      (((detID2_input>>25)&0x7) == 3) && (((detID2_input>>14)&0x7) == 2);
			 break;}

		case 3: {OutputBool = (((detID1_input>>25)&0x7) == 3) && (((detID1_input>>14)&0x7) == 3) &&
				      (((detID2_input>>25)&0x7) == 3) && (((detID2_input>>14)&0x7) == 3);
			 break;}

		case 4: {OutputBool = (((detID1_input>>25)&0x7) == 3) && (((detID1_input>>14)&0x7) == 4) &&
				      (((detID2_input>>25)&0x7) == 3) && (((detID2_input>>14)&0x7) == 4);
			 break;}


		case 5: {OutputBool = (((detID1_input>>25)&0x7) == 4) && ( (((detID1_input>>13)&0x3) == 0) || (((detID1_input>>13)&0x3) == 1) ) &&
				      (((detID2_input>>25)&0x7) == 4) && ( (((detID2_input>>13)&0x3) == 0) || (((detID2_input>>13)&0x3) == 1) );
			 break;}

		case 6: {OutputBool = (((detID1_input>>25)&0x7) == 4) && ( (((detID1_input>>13)&0x11) == 0) || (((detID1_input>>13)&0x11) == 1) ) &&
				      (((detID2_input>>25)&0x7) == 4) && ( (((detID2_input>>13)&0x11) == 0) || (((detID2_input>>13)&0x11) == 1) ); 
			 break;}

		case 7: {OutputBool = (((detID1_input>>25)&0x7) == 4) && ( (((detID1_input>>13)&0x9) == 0) || (((detID1_input>>13)&0x9) == 1) ) &&
				      (((detID2_input>>25)&0x7) == 4) && ( (((detID2_input>>13)&0x9) == 0) || (((detID2_input>>13)&0x9) == 1) ); 
			 break;}


		case 8: {OutputBool = (((detID1_input>>25)&0x7) == 5) && (((detID1_input>>14)&0x7) == 1) &&
			 	      (((detID2_input>>25)&0x7) == 5) && (((detID2_input>>14)&0x7) == 1); 
			 break;}

		case 9: {OutputBool = (((detID1_input>>25)&0x7) == 5) && (((detID1_input>>14)&0x7) == 2) &&
			              (((detID2_input>>25)&0x7) == 5) && (((detID2_input>>14)&0x7) == 2); 
			 break;}

		case 10: {OutputBool = (((detID1_input>>25)&0x7) == 5) && (((detID1_input>>14)&0x7) == 3) && 
				       (((detID2_input>>25)&0x7) == 5) && (((detID2_input>>14)&0x7) == 3);
			 break;}

		case 11: {OutputBool = (((detID1_input>>25)&0x7) == 5) && (((detID1_input>>14)&0x7) == 4) &&
				       (((detID2_input>>25)&0x7) == 5) && (((detID2_input>>14)&0x7) == 4); 
			 break;}

		case 12: {OutputBool = (((detID1_input>>25)&0x7) == 5) && (((detID1_input>>14)&0x7) == 5) &&
				       (((detID2_input>>25)&0x7) == 5) && (((detID2_input>>14)&0x7) == 5); 
			 break;}

		case 13: {OutputBool = (((detID1_input>>25)&0x7) == 5) && (((detID1_input>>14)&0x7) == 6) &&
				       (((detID2_input>>25)&0x7) == 5) && (((detID2_input>>14)&0x7) == 6); 
			 break;}


		case 14: {OutputBool = (((detID1_input>>25)&0x7) == 6) && ( (((detID1_input>>18)&0x3) == 0) || (((detID1_input>>18)&0x3) == 1) ) &&
				       (((detID2_input>>25)&0x7) == 6) && ( (((detID2_input>>18)&0x3) == 0) || (((detID2_input>>18)&0x3) == 1) ); 
			 break;}

		case 15: {OutputBool = (((detID1_input>>25)&0x7) == 6) && ( (((detID1_input>>14)&0xF) == 0) || (((detID1_input>>14)&0xF) == 1) ) &&
				       (((detID2_input>>25)&0x7) == 6) && ( (((detID2_input>>14)&0xF) == 0) || (((detID2_input>>14)&0xF) == 1) ); 
			 break;}

		case 16: {OutputBool = (((detID1_input>>25)&0x7) == 6) && ( (((detID1_input>>5)&0x7) == 0) || (((detID1_input>>5)&0x7) == 1) ) &&
				       (((detID2_input>>25)&0x7) == 6) && ( (((detID2_input>>5)&0x7) == 0) || (((detID2_input>>5)&0x7) == 1) );

			 break;}


	}

	return OutputBool;

  }};

  //Function for expressing the hit resolution in either micrometres or pitch units.
  auto Pitch_Function{[&Unit_Int](const float& pitch, const float& input){

	float InputOverPitch;

	switch(Unit_Int){

		case 0: InputOverPitch = input/pitch; break; 
		case 1: InputOverPitch = 1.0; break;
			
	}

	return InputOverPitch;

  }};

  //Applying the filter for the subdetector
  auto dataframe = d.Filter(SubDet_Function, {"detID1", "detID2"});

  if(RegionInt == 5){auto snapshot = dataframe.Snapshot("reso", "snapshot.root");}

  //Implementing selection criteria that were not implemented in HitResol.cc
  auto PairPathCriteriaFunction{[&RegionInt](const float& pairPath_input){

	if((RegionInt > 0 && RegionInt < 5) || (RegionInt > 7 || RegionInt < 13)){return abs(pairPath_input) < 7;} //for TIB and TOB
	else if(RegionInt == 0){return abs(pairPath_input) < 2;} //for pixels
	else{return abs(pairPath_input) < 20;}//for everything else (max value is 15cm so this will return all events anyway)
  }};

  auto MomentaFunction{[&RegionInt](const float& momentum_input){

	if(RegionInt == 0){return momentum_input > 5;} //pixels
	else{return momentum_input > 15;} //strips
  }};

  auto dataframe_filtered = dataframe.Filter(PairPathCriteriaFunction, {"pairPath"})
				     .Filter(MomentaFunction, {"momentum"})
			             .Filter("trackChi2 > 0.001 && numHits > 6 && trackDXE < 0.0025 && (clusterW1 == clusterW2) && clusterW1 <= 4 && clusterW2 <= 4");

  //Creating histograms for the difference between the two hit positions, the difference between the two predicted positions and for the double difference
  //hitDX = the difference in the hit positions for the pair
  //trackDX =  the difference in the track positions for the pair 

  auto HistoName_DoubleDiff = "DoubleDifference_" + region;
  auto HistoName_HitDX = "HitDX_" + region;
  auto HistoName_TrackDX = "TrackDX_" + region; 

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
  TFile * output = new TFile(GaussianFitsFileName.c_str(), "UPDATE");

  h_DoubleDifference->Write();
  h_hitDX->Write();
  h_trackDX->Write();

  output->Close();
  
  //Calculating the hit resolution;
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
  int ULInteger = 1;

  vector<std::string> LayerNames = {"Pixels",   "TIB_L1",    "TIB_L2",    "TIB_L3",    "TIB_L4",
				    "Side_TID", "Wheel_TID", "Ring_TID",  "TOB_L1",
				    "TOB_L2",   "TOB_L3",    "TOB_L4",    "TOB_L5",
				    "TOB_L6",   "Side_TEC",  "Wheel_TEC", "Ring_TEC"};

  for(int i = 0; i < LayerNames.size(); i++){

	ResolutionsCalculator(LayerNames.at(i), UnitInteger, ULInteger);
  }
 

  std::ofstream HitResoTextFile;
  HitResoTextFile.open(HitResoFileName);

  auto Width = 28;

  HitResoTextFile << std::right << "Layer " << std::setw(Width) << " Resolution " << std::setw(Width) << " sigma2_HitDX " << std::setw(Width) << " sigma2_trackDX " << std::setw(Width) << " sigma2_DoubleDifference " << std::endl;

  for(int i = 0; i < HitResolutionVector.size(); i++){
	HitResoTextFile << std::right << LayerNames.at(i) << std::setw(Width) << HitResolutionVector.at(i) << std::setw(Width) << HitDXVector.at(i)  << std::setw(Width) << TrackDXVector.at(i) << std::setw(Width) << DoubleDifferenceVector.at(i) << std::endl;

  }


}
