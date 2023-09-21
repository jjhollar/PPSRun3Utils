# PPSRun3Utils: Diamond efficiencies, radiographies, and time-over-threshold plots

----------------------------------------------------------------
Producing diamond efficiency and radiography histograms from PPS ALCARECO 
in Run 3 data (tested in CMSSW_13_0_9)
----------------------------------------------------------------

   * Updated 20/09/2023 to allow a configurable range of LumiSections to be chosen
     The recipe corresponds to one specific example for LumiSections 1-100 of Run 370102

cmsrel CMSSW_13_0_9

cd CMSSW_13_0_9/src

cmsenv

git clone git@github.com:jjhollar/PPSRun3Utils.git
(note that if you don't need to commit changes, you can use https://github.com/jjhollar/PPSRun3Utils.git to clone the repository without a password)

scram b

cd PPSRun3Utils/PPSRun3Utils/bin

eos ls /eos/cms/store/express/Run2023D/StreamALCAPPSExpress/ALCARECO/PPSCalMaxTracks-Express-v1/000/370/102/00000/ > & InputFiles.txt

../../../../bin/slc7_amd64_gcc11/FWLiteTimingEfficiencyRadiography inputPath=/eos/cms/store/express/Run2023D/StreamALCAPPSExpress/ALCARECO/PPSCalMaxTracks-Express-v1/000/370/102/00000/ minLS=1 maxLS=100 outputFile=timingHistograms_Run370102_LS1to100.root

In this example the output file will be named "timingHistograms_Run370102_LS1to100.root", with a subfolder "diamondHistograms" containing all the histograms

In addition to the "inputPath" example above, the following options can be passed at the command line when running the 
FWLiteTimingEfficiencyRadiography binary:

   minimumToT=[float]		
   	This imposes a minimum ToT on the rechits used to fill the efficiency and ToT plots. By default no cut is applied. 
	In order to properly interpret the average ToT plots, a cut of 0 should be applied.
   minLS=[int]
	The first LumiSection to process
   maxLS=[int]
	The last LumiSection to process
   outputFile=[string]
	The output file name can be changed from the default value of "timingHistograms.root"
   mode=[integer]
	By default the program uses the collection names from the PPS AlCaReco (mode 1). By setting mode=2, the collection 
	names from the standard PromptReco/AOD will be used instead.	 


A plotting macro PlotTimingEfficiencies.C gives an example of drawing the output histograms of efficiency, ToT, and
radiographies. To use it with the above example, open a ROOT session and do:

	       [0] .L PlotTimingEfficiencies.C
	       [1] PlotTimingEfficiencies("timingHistograms_Run370102_LS1to100.root")

This will produce pdf files with x-y efficiency maps per RP and per plane.



----------------------------------------------------------------
Notes
----------------------------------------------------------------

   * The source code is in PPSRun3Utils/PPSRun3Utils/bin/FWLiteTimingEfficiencyRadiography.cc

   * As of April 2023, the code is updated for 2023 conditions. This means both the 210 and 220m pixel tracks are used for the event selection 
     in the efficiency/ToT/radiography plots, and both the cylindrical and 220-near timing stations are included. For 2022 data, this 
     could be modified to use only 210 pixels and only cylindrical timing. 

   * The pixel-diamond matching cuts in the efficiency numerator have not been tuned for Run 3 data. Currently they are all set 
     to +-20 (effectively no matching)

      * The efficiency numerator histogram is filled for each time-track/rechit found on the relevant arm/plane. This means if more than 1 
        time-track or rechit is found, the efficiency can artificially appear >100%. Adding a tighter pixel-diamond matching cut for the 
	efficiency numerator should improve this

   * By default, all timing rechits are used. In order to make sensible ToT plots, the code should be changed to use only rechits 
     with a valid ToT>0. This can be done using the "minimumToT" command line option as described above.


