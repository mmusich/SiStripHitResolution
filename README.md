Markup: # HitResolutionProject #
The scripts should be run inside CMSSW_11_1_0_pre6. Firstly, the following commands should be used:

* cd CMSSW_11_1_0_pre6/src
* cmsenv
* cd UserCode/SiStripHitResolution
* scram b
* cmsRun test/SiStripHitResol_testULcosmics.py

This will produce an output root file, which will be called hitresol_ALCARECO_UL.root (for when ultra legacy samples have been used as input) or hitresol_ALCARECO.root (for ALCARECO, non-ultra legacy samples). This root file is then used as input to the macro Resolutions.cc, for which the following command should be used:

* root -l Resolutions.cc

This will produce two output files: GaussianFits_Micrometres.root and HitResolutionValues_Micrometres.txt (for hit resolution values expressed in micrometres), and GaussianFits_PitchUnits.root and HitResolutionValues_PitchUnits.txt (for hit resolution values expressed in pitch units) 
