using namespace ROOT; 


vector<float> HitResolutionVector;

void ResolutionsCalculator(const string& region){

  //opening the root file
  ROOT::RDataFrame d("anResol/reso", "hitresol.root");

  //Filtering the RDataFrame to consider each tracker region

  /*uint32_t detID1 = ...;
    auto subdet = (detID1>>25)&0x7; // TIB = 3, TID = 4, TOB = 5, TEC = 6
    for TIB and TOB: auto layerBarrel = (detID1>>14)&0x7;
    for TID: auto sideTID = (detID1>>13)&0x3;
	     auto wheelTID = (detID1>>11)&0x3;
	     auto ringTID = (detID1>>9)&0x3;
    for TEC: auto sideTEC = (detID1>>18)&0x3;
	     auto wheelTEC = (detID1>>14)&0xF;
  	     auto ringTEC = (detID1>>5)&0x7;*/

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

  auto h_DoubleDifference = dataframe.Define(HistoName_DoubleDiff, DifferenceFunction, {"hitDX", "trackDX"}).Histo1D(HistoName_DoubleDiff); 
  auto h_hitDX = dataframe.Define(HistoName_HitDX, {"hitDX"}).Histo1D(HistoName_HitDX);

  //Applying gaussian fits, taking the resolutions and squaring them
  h_DoubleDifference->Fit("gaus");
  h_hitDX->Fit("gaus");
  auto hitDX_trackDX_StdDev = h_DoubleDifference->GetStdDev();
  auto hitDX_StdDev = h_hitDX->GetStdDev(); 
  auto sigma2_PredMinusMeas = pow(hitDX_trackDX_StdDev, 2);
  auto sigma2_Meas = pow(hitDX_StdDev, 2);
 

  //Saving the histograms with gaussian fits applied to an output root file
  h_DoubleDifference->Write();
  h_hitDX->Write();

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

  ResolutionsCalculator("TIB_L1");
  ResolutionsCalculator("TIB_L2");
  ResolutionsCalculator("TIB_L3");
  ResolutionsCalculator("TIB_L4");
  ResolutionsCalculator("Side_TID");
  ResolutionsCalculator("Wheel_TID");
  ResolutionsCalculator("Ring_TID");
  ResolutionsCalculator("TOB_L1");
  ResolutionsCalculator("TOB_L2");
  ResolutionsCalculator("TOB_L3");
  ResolutionsCalculator("TOB_L4");
  ResolutionsCalculator("TOB_L5");
  ResolutionsCalculator("TOB_L6");
  ResolutionsCalculator("Side_TEC");
  ResolutionsCalculator("Wheel_TEC");
  ResolutionsCalculator("Ring_TEC");

  std::ofstream HitResoTextFile;
  HitResoTextFile.open("HitResolutionValues.txt");

  for(int i = 0; i < HitResolutionVector.size(); i++){HitResoTextFile << HitResolutionVector.at(i) << endl;}

  output->Close();

}
