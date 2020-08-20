

using namespace ROOT; 

void Resolutions(){

  //opening the root file
  ROOT::RDataFrame d("anResol/reso", "hitresol.root");
 
  //obtaining the branches trackDX and hitDX
  //hitDX = the difference in the hit positions for the pair
  //trackDX =  the difference in the track positions for the pair 
  auto h_trackDX = d.Histo1D("trackDX");
  auto h_hitDX = d.Histo1D("hitDX");

  //Applying gaussian fits, taking the resolutions and squaring them
  h_trackDX->Fit("gaus");
  h_hitDX->Fit("gaus");
  auto trackDX_StdDev = h_trackDX->GetStdDev();
  auto hitDX_StdDev = h_hitDX->GetStdDev(); 
  auto sigma2_PredMinusMeas = pow(hitDX_StdDev, 2) + pow(trackDX_StdDev, 2);
  auto sigma2_Meas = pow(hitDX_StdDev, 2);
 

  //Saving the histograms with gaussian fits applied to an output root file
  TFile * output = new TFile("GaussianFits.root", "RECREATE");
  h_trackDX->Write();
  h_hitDX->Write();
  output->Close();

  //Calculating the hit resolution
  //sigma2_PredMinusMeas - sigma2_Meas = pow(hitDX_StdDev, 2) + pow(trackDX_StdDev, 2) - pow(hitDX_StdDev, 2) = pow(trackDX_StdDev, 2);
  auto HitResolution = sqrt(pow(trackDX_StdDev, 2)/2);

  //Printing the resolution 
  std::cout << '\n' << std::endl;
  std::cout << "The hit resolution is: " << HitResolution << std::endl;

}
