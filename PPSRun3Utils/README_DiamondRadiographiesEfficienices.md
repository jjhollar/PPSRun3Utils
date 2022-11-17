# PPSDiamondEfficiencyRadiography

----------------------------------------------------------------
Producing diamond efficiency and radiography histograms from AOD
in Run 3 data (tested in CMSSW_12_4_6)
----------------------------------------------------------------

cmsrel CMSSW_12_4_6

cd CMSSW_12_4_6/src

cmsenv

git clone git@github.com:jjhollar/PPSDiamondEfficiencyRadiography.git

cd PPSDiamondEfficiencyRadiography

scram b

../../bin/slc7_amd64_gcc10/FWLiteTimingEfficiencyRadiography

The ouput will be a file timingHistograms.root, with a subfolder diamondHistograms containing all the histograms

----------------------------------------------------------------
Notes
----------------------------------------------------------------

   * The source code is in PPSDiamondEfficiencyRadiography/PPSDiamondEfficiencyRadiography/bin/FWLiteTimingEfficiencyRadiography.cc

   * The list of input files is defined in the .cc file. Currently it's set to a random example from a recent run

   * Only the 210 pixels are used for the efficiency denominator, and for the radiographies. Examples for the 220 pixels are commented in the code

   * The pixel-diamond matching cuts in the efficiency numerator have not been tuned for Run 3 data. Currently they are all set to +-999 (no matching)

      * The efficiency numerator histogram is filled for each time-track/rechit found on the relevant arm/plane. This means if more than 1 
        time-track or rechit is found, the efficiency can artificially appear >100%. Adding a tighter pixel-diamond matching cut for the 
	efficiency numerator should improve this