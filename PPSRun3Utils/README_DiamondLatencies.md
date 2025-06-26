# PPSRun3Utils

----------------------------------------------------------------
Producing channel-by-channel diamond latency plots with random 
triggers in Run 3 RECO/AOD data (tested in CMSSW_15_0_8)
----------------------------------------------------------------

cmsrel CMSSW_15_0_8

cd CMSSW_15_0_8/src

cmsenv

git clone git@github.com:jjhollar/PPSRun3Utils.git

scram b

cd PPSRun3Utils/PPSRun3Utils/bin

eos ls /eos/cms/tier0/store/express/Run2023C/StreamALCAPPSExpress/ALCARECO/PPSCalMaxTracks-Express-v1/000/367/337/00000 > & InputFiles.txt

../../../../bin/slc7_amd64_gcc11/FWLiteDiamondsLatency2023

----------------------------------------------------------------
Output
----------------------------------------------------------------

   * The default output is a file "diamondHistogramsRecHits_test.root", with histograms 
     stored in a sub-folder "histograms/"

   * The main latency histogram is named "planevsbx", containing the number of rechits in each 
     channel in each BX. The numbering convention on the y-axis is:

     o 0-47:   	45 cylindrical

     o 48-95:	45 box

     o 96-143: 	56 cylindrical

     o 144-191:	56 box



