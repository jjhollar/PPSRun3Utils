# PPSRun3Utils

----------------------------------------------------------------
Producing plane-by-plane pixel latency plots with random 
triggers in Run 3 RECO/AOD data (tested in CMSSW_12_4_6)
----------------------------------------------------------------

   * Requires a valid certificate/proxy to find data in DAS and access 
     remote files. The example here is for run 361971

cmsrel CMSSW_12_4_6

cd CMSSW_12_4_6/src

cmsenv

git clone git@github.com:jjhollar/PPSRun3Utils.git

cd PPSRun3Utils

scram b

dasgoclient --query='dataset run=361971 dataset=/ZeroBias/*/AOD'

dasgoclient --query='file dataset=/ZeroBias/Run2022F-PromptReco-v1/AOD run=361971' > & InputFiles.txt

../../bin/slc7_amd64_gcc10/FWLitePixelsLatency2022

----------------------------------------------------------------
Output
----------------------------------------------------------------

   * The default output is a file "pixelHistogramsRecHits_test.root", with histograms 
     stored in a sub-folder "histograms/"

   * The main latency histogram is named "planevsbx", containing the number of rechits in each 
     plane in each BX. The numbering convention on the y-axis is:

     o 0-5:   	45-210
     o 6-11:	45-220
     o 12-17: 	56-210  
     o 18-23:	56-220

   * The other histograms in the file are track x-y maps for each RP, the rechit x-y for each plane, and the 
     range of lumisections analyzed

----------------------------------------------------------------
Overriding defaults
----------------------------------------------------------------
 
   * Default settings can be changed by modifying the variables defined at the beginning of the 
     PPSRun3Utils/PPSRun3Utils/bin/FWLitePixelsLatency2022.cc file and recompiling: 

     int minLS_ = 0;	// first lumisection to analyze				      
     int maxLS_ = 9999; // last lumisection to analyzer
     std::string hlt = "HLT_Random_v3"; // name of HLT path to filter on
     std::string inputfilelist = "InputFiles.txt"; // name of file containing input PromptReco files
     std::string outputFile_ = "pixelHistogramsRecHits_test.root"; // name of output histogram file


