# PPSRun3Utils: Diamond efficiencies, radiographies, and time-over-threshold plots

----------------------------------------------------------------
Producing diamond efficiency and radiography histograms from PPS ALCARECO 
in Run 3 data (tested in CMSSW_13_0_3)
----------------------------------------------------------------

   * Here it's assumed the code is run on ALCA PPS express files from Tier0. Temporarily, 
     the path to the files must be hardcoded in the .cc file before compilation (to be improved...)
     The recipe corresponds to one specific example for Run 367337

cmsrel CMSSW_13_0_3

cd CMSSW_13_0_3/src

cmsenv

git clone git@github.com:jjhollar/PPSRun3Utils.git
(note that if you don't need to commit changes, you can use https://github.com/jjhollar/PPSRun3Utils.git to clone the repository without a password)

cd PPSRun3Utils/PPSRun3Utils/bin

eos ls /eos/cms/tier0/store/express/Run2023C/StreamALCAPPSExpress/ALCARECO/PPSCalMaxTracks-Express-v1/000/367/337/00000 > & InputFiles.txt

[TEMPORARY WORKAROUND: edit the line L71 in FWLiteTimingEfficiencyRadiography.cc. The variable std::string xrootdprefix should point to the 
same eos directory used to generate the InputFiles.txt list in the previous step]

cd ../../..

scram b

cd PPSRun3Utils/PPSRun3Utils/bin

../../bin/slc7_amd64_gcc10/FWLiteTimingEfficiencyRadiography

The ouput will be a file timingHistograms.root, with a subfolder diamondHistograms containing all the histograms

A plotting macro PlotTimingEfficiencies.C gives an example of drawing the output histograms of efficiency, ToT, and 
radiographies. 

----------------------------------------------------------------
Notes
----------------------------------------------------------------

   * The source code is in PPSRun3Utils/PPSRun3Utils/bin/FWLiteTimingEfficiencyRadiography.cc

   * As of April 2023, the code is updated for 2023 conditions. This means both the 210 and 220m pixel tracks are used for the event selection 
     in the efficiency/ToT/radiography plots, and both the cylindrical and 220-near timing stations are included. For 2022 data, this 
     could be modified to use only 210 pixels and only cylindrical timing. 

   * The pixel-diamond matching cuts in the efficiency numerator have not been tuned for Run 3 data. Currently they are all set to +-20 (effectively no matching)

      * The efficiency numerator histogram is filled for each time-track/rechit found on the relevant arm/plane. This means if more than 1 
        time-track or rechit is found, the efficiency can artificially appear >100%. Adding a tighter pixel-diamond matching cut for the 
	efficiency numerator should improve this

   * By default, all timing rechits are used. In order to make sensible ToT plots, the code should be changed to use only rechits with a valid ToT>0


