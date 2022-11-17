# PPSRun3Utils

----------------------------------------------------------------
Producing plane-by-plane pixel latency plots with random 
triggers in Run 3 RECO/AOD data (tested in CMSSW_12_4_6)
----------------------------------------------------------------

   * Requires a valid certificate proxy to find data in DAS and access 
     remote files

cmsrel CMSSW_12_4_6

cd CMSSW_12_4_6/src

cmsenv

git clone git@github.com:jjhollar/PPSRun3Utils.git

cd PPSRun3Utils

scram b

dasgoclient --query='dataset run=361971 dataset=/ZeroBias/*/AOD'
(find the dataset/era containing the desired run)

dasgoclient --query='file dataset=/ZeroBias/Run2022F-PromptReco-v1/AOD run=361971' > & InputFiles.txt
(create a list of files containing data from the desired run+dataset)

../../bin/slc7_amd64_gcc10/FWLitePixelsLatency2022

----------------------------------------------------------------
Output
----------------------------------------------------------------

   * The default output is a file "pixelHistogramsRecHits_test.root", with histograms 
     stored in a sub-folder "histograms/"

   * The main latency histogram is named "planevsbx", containing the number of rechits in each 
     plane in each BX. The numbering convention on the y-axis is:

     # 0-5:   	45-210
     # 6-11:	45-220
     # 12-17: 	56-210  
     # 18-23:	56-220

   * The other histograms in the file are track x-y maps for each RP, the rechit x-y for each plane, and the 
     range of lumisections analyzed

----------------------------------------------------------------
Overriding defaults
----------------------------------------------------------------
 
   * Default settings can be changed by passing command-line flags to the FWLitePixelsLatency2022 executible: 

   --outputFile <name> : name of output histogram file (default = "pixelHistogramsRecHits_test.root")

   --inputFiles <name> : name of file containing input PromptReco files (default = "InputFiles.txt")

   --hlt <name> : name of HLT path to filter on (default = "HLT_Random_v3")

   --minLS <integer> : first lumisection to analyze (default = 0)

   --maxLS <integer> : last lumisection to analyzer (default = 9999)
