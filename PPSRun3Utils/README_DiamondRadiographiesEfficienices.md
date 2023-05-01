# PPSRun3Utils: Diamond efficiencies, radiographies, and time-over-threshold plots

----------------------------------------------------------------
Producing diamond efficiency and radiography histograms from AOD
in Run 3 data (tested in CMSSW_13_0_3)
----------------------------------------------------------------

   * A grid certificate is needed to run the DAS commands (in the example below for Run 357815). 
     The first command finds the dataset/era corresponding to a particular run, the second command 
     finds all the files in that dataset for that run.

cmsrel CMSSW_13_0_3

cd CMSSW_13_0_3/src

cmsenv

git clone git@github.com:jjhollar/PPSRun3Utils.git

cd PPSRun3Utils

scram b

dasgoclient --query='dataset run=357815 dataset=/ZeroBias/*/AOD'

dasgoclient --query='file dataset=/ZeroBias/Run2022D-PromptReco-v2/AOD' > & InputFiles.txt

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

   * By default, all timing rechits are used. For the ToT plots, the code should be changed to use only rechits with a valid ToT>0

