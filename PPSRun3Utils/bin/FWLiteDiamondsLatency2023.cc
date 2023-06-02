// dasgoclient --query='dataset run=361971 dataset=/ZeroBias/*/AOD'
// dasgoclient --query='file dataset=/ZeroBias/Run2022F-PromptReco-v1/AOD run=361971' > & InputFiles.txt

#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TSystem.h>

#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/FWLite/interface/FWLiteEnabler.h"

#include "DataFormats/CTPPSDetId/interface/CTPPSDetId.h"
#include "DataFormats/CTPPSDetId/interface/CTPPSDiamondDetId.h"
#include "DataFormats/CTPPSReco/interface/CTPPSDiamondRecHit.h"
#include "DataFormats/CTPPSReco/interface/CTPPSLocalTrackLite.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"


#include "DataFormats/Common/interface/DetSet.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h"

int main(int argc, char* argv[]) {
  // define what muon you are using; this is necessary as FWLite is not
  // capable of reading edm::Views

  // ----------------------------------------------------------------------
  // First Part:
  //
  //  * enable FWLite
  //  * book the histograms of interest
  //  * open the input file
  // ----------------------------------------------------------------------

  // Default values
  int minLS_ = 0;
  int maxLS_ = 9999;
  std::string hlt = "HLT_Random_v3";
  std::string inputfilelist = "InputFiles.txt";
  std::string outputFile_ = "diamondHistogramsRecHits_test.root";

  // load framework libraries
  gSystem->Load("libFWCoreFWLite");
  FWLiteEnabler::enable();

  // initialize command line parser
  optutl::CommandLineParser parser("Analyze FWLite Histograms");

  // set defaults
  parser.integerValue("maxEvents") = 100000000;
  parser.integerValue("outputEvery") = 1000;

  // parse arguments
  parser.parseArguments(argc, argv);
  int maxEvents_ = parser.integerValue("maxEvents");
  unsigned int outputEvery_ = parser.integerValue("outputEvery");

  std::vector<std::string> inFiles_;
  ifstream ifs(inputfilelist);

  std::string filename;
  //  std::string xrootdprefix = "root://cms-xrd-global.cern.ch/";
  std::string xrootdprefix = "/eos/cms/tier0/store/data/Run2023C/ZeroBias/AOD/PromptReco-v4/000/367/883/00000/";
  std::string fullfilename;

  while ( getline (ifs,filename) )
    {
      fullfilename = xrootdprefix + filename;
      inFiles_.push_back(fullfilename);
    }
  ifs.close();


  // book a set of histograms
  fwlite::TFileService fs = fwlite::TFileService(outputFile_);
  TFileDirectory dir = fs.mkdir("histograms");

  TH2F *planevsbx = dir.make<TH2F>("planevsbx","planevsbx",4000,0,4000,200,0,200);
  TH1F *ls = dir.make<TH1F>("ls","ls",2500,0,2500);

  // loop the events
  int ievt = 0;

  int lumiblock_ = -99;
  int BX = -1;

  int analyzed = 0;

  for (unsigned int iFile = 0; iFile < inFiles_.size(); ++iFile) {
    // open input file (can be located on castor)
    TFile* inFile = TFile::Open(inFiles_[iFile].c_str());
    if (inFile) {
      // ----------------------------------------------------------------------
      // Second Part:
      //
      //  * loop the events in the input file
      //  * receive the collections of interest via fwlite::Handle
      //  * fill the histograms
      //  * after the loop close the input file
      // ----------------------------------------------------------------------
      
      std::cout << "Opening " << inFiles_[iFile].c_str() << std::endl;


      fwlite::Event ev(inFile);
      for (ev.toBegin(); !ev.atEnd(); ++ev, ++ievt) {
        edm::EventBase const& event = ev;
        // break loop if maximal number of events is reached
        if (maxEvents_ > 0 ? ievt + 1 > maxEvents_ : false)
          break;
        // simple event counter
        if (outputEvery_ != 0 ? (ievt > 0 && ievt % outputEvery_ == 0) : false)
          std::cout << "  processing event: " << ievt << std::endl;

	lumiblock_ = ev.luminosityBlock();

	BX = ev.bunchCrossing();

	if((lumiblock_ < minLS_) || (lumiblock_ > maxLS_))
	  continue;

        int passhlt = 0;

	edm::Handle<edm::TriggerResults> hltResults;
        event.getByLabel(edm::InputTag("TriggerResults","","HLT"),hltResults);
        const edm::TriggerNames & trigNames = event.triggerNames(*hltResults);
        for(unsigned int i=0; i<trigNames.size();i++)
          {
	    std::string TriggerName = trigNames.triggerName(i);
            if((hltResults->accept(i)>0)&&(TriggerName == "HLT_Random_v3"))
	      //      if((hltResults->accept(i)>0)&&(TriggerName == "HLT_PABptxMinusNotBptxPlus_v1") || (hltResults->accept(i)>0)&&(TriggerName == "HLT_PABptxPlusNotBptxMinus_v1"))               
              passhlt=1;
          }

	if(passhlt==0)
	  continue;

	ls->Fill(lumiblock_);
	
        // Handle to the collection of lite tracks                                                                                                                                      
	int n56210=0; int n56220=0;
	float x56210=0; float y56210=0;
	float x56220=0; float y56220=0;

	edm::Handle< edm::DetSetVector<CTPPSDiamondRecHit> > diamondRecHits;
	event.getByLabel(std::string("ctppsDiamondRecHits"), diamondRecHits);

	//	std::cout << "Checking rechits" << std::endl;
	int nplane0=0; int nplane4=0; int nplane5=0;

	analyzed++;

	for ( const auto& rechits_ds : *diamondRecHits ) 
	  {
	    const CTPPSDiamondDetId detidforrh( rechits_ds.detId() );
	    for ( const auto& rechit : rechits_ds ) 
	      {
                int arm = detidforrh.arm();                                                                               
		int plane = detidforrh.plane();                                                                           
		int station = detidforrh.station();
		int channel = detidforrh.channel();

		int simplestation = station;

		if(station == 1)
		  simplestation = 0;
		if(station == 2)
		  simplestation = 1;

		int code = (arm*96) + (simplestation*48) + (plane*12) + channel;
		planevsbx->Fill(BX,code);
		//		if((code >= 85 && code <= 100) || (code >= 160))
		// std::cout << "\tarm, station, plane, channel, BX = " << arm << ", " << station << ", " << plane << ", " << channel << ", " << BX << ": code = " << code << std::endl;

	      }
	  }	
      }
      // close input file
      inFile->Close();
    }
    // break loop if maximal number of events is reached:
    // this has to be done twice to stop the file loop as well
    if (maxEvents_ > 0 ? ievt + 1 > maxEvents_ : false)
      break;
  }

  std::cout << "Analyzed " << analyzed << std::endl;
  return 0;
}
