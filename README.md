# Hit Resolution Project #

## Explanation for the pair method ## 
The hit resolution, $`\sigma_{hit}`$, can be obtained by using the following equation:

$`\sigma_{hit} = \sqrt{\frac{\sigma^{2}_{pred-meas} - \sigma^{2}_{meas}}{2}}`$,

where $`\sigma_{pred-meas}`$ is the standard deviation for the distribution of the double difference between the predicted and measured hit positions, and $`\sigma_{meas}`$ is the standard deviation of the distribution of the measured hit positions. 

The following criteria are used:

* The charged particle must have traversed through two sufficiently-overlapping detector modules. 
* Tracks must have transverse momenta greater than 3 GeV ([permalink](https://gitlab.cern.ch/coldham/hitresolutionproject/-/blob/master/src/HitResol.cc#L324)).
* More than six hits must be left in the SST layers and the pixel detector. No more than four of these can have a large cluster width. ([permalink](https://gitlab.cern.ch/coldham/hitresolutionproject/-/blob/master/Resolutions.cc#L106)).
* The track fit must yield a good $`\chi^{2}`$ probability of $`\chi^{2} \geqslant 10^{-2}`$ ([permalink](https://gitlab.cern.ch/coldham/hitresolutionproject/-/blob/master/Resolutions.cc#L106)).
* The predicted path (the distance of propagation of the charged particle from one layer to the next) must be < 7cm
* The error in the distance between two hit resolution measurements must be < 0.0025 ([permalink](https://gitlab.cern.ch/coldham/hitresolutionproject/-/blob/master/Resolutions.cc#L106)).
* Clusters in the silicon module under consideration must have the same width ([permalink](https://gitlab.cern.ch/coldham/hitresolutionproject/-/blob/master/Resolutions.cc#L135)).
* Clusters positioned on the edge of modules are not considered ([permalink](https://gitlab.cern.ch/coldham/hitresolutionproject/-/blob/master/src/HitResol.cc#L346))

## How to run the code ##
The following scripts are used for the hit resolution study:
* [src/HitResol.cc](https://gitlab.cern.ch/coldham/hitresolutionproject/-/blob/master/src/HitResol.cc) (original author: Denis Gele)
* [test/SiStripHitResol_testULcosmics.py](https://gitlab.cern.ch/coldham/hitresolutionproject/-/blob/master/test/SiStripHitResol_testULcosmics.py) (original author: Pieter David)
* [Resolutions.cc](https://gitlab.cern.ch/coldham/hitresolutionproject/-/blob/master/Resolutions.cc) (original author: Kathryn Coldham)
 
The scripts should be run inside CMSSW_11_1_0_pre6. Firstly, the following commands should be used:

* cd CMSSW_11_1_0_pre6/src
* cmsenv
* cd UserCode/SiStripHitResolution
* scram b
* cmsRun test/SiStripHitResol_testULcosmics.py

This will produce an output root file, which will be called hitresol_ALCARECO_UL.root (for when ultra legacy samples have been used as input) or hitresol_ALCARECO.root (for ALCARECO, non-ultra legacy samples). This root file is then used as input to the macro Resolutions.cc, for which the following command should be used:

* root -l Resolutions.cc

This will produce two output files: GaussianFits_Micrometres.root and HitResolutionValues_Micrometres.txt (for hit resolution values expressed in micrometres), or GaussianFits_PitchUnits.root and HitResolutionValues_PitchUnits.txt (for hit resolution values expressed in pitch units). To choose between pitch units or micrometres, [UnitInteger](https://gitlab.cern.ch/coldham/hitresolutionproject/-/blob/master/Resolutions.cc#L190) must be set as 0 (for pitch units) or 1 (for micrometres). To choose between using the UL or non-UL ALCARECO samples, the value of [ULInteger](https://gitlab.cern.ch/coldham/hitresolutionproject/-/blob/master/Resolutions.cc#L191) must be set as 0 (for non-UL samples) or 1 (for UL samples). 

## References ##

* [Butz, E. (2017). Operation and Performance of the CMS Outer Tracker. The Compact Muon Solenoid Experiment Conference Report. 2017/428.](https://gitlab.cern.ch/coldham/hitresolutionproject/-/blob/master/Resources/CR2017_428.pdf)
* [Chiochia, V et al. (2005). Track reconstruction in the CMS tracker. CMS Analysis Note. CMS AN 2005/063.](https://gitlab.cern.ch/coldham/hitresolutionproject/-/blob/master/Resources/AN2005_063_v2.pdf)
* [Gelé, D. (2018). Status of SiStripHitResolution studies.](https://gitlab.cern.ch/coldham/hitresolutionproject/-/blob/master/Resources/PresentationTracker_17072018.pdf)
* [Ulmer, K. (2009). Tracker Hit Resolution Measurements in 2009 CRAFT Data.](https://gitlab.cern.ch/coldham/hitresolutionproject/-/blob/master/Resources/HitResLPCPhysics_10_15_09.ppt) 
