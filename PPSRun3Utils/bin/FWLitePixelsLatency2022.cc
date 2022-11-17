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
#include "DataFormats/CTPPSDetId/interface/CTPPSPixelDetId.h"
#include "DataFormats/CTPPSReco/interface/CTPPSPixelRecHit.h"
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
  std::string outputFile_ = "pixelHistogramsRecHits_test.root";

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
  std::string xrootdprefix = "root://cms-xrd-global.cern.ch/";
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

  TH2F *xy45210pl0_ = dir.make<TH2F>("xy45210pl0","xy45210pl0",500,-15,15,500,-15,15);
  TH2F *xy45220pl0_ = dir.make<TH2F>("xy45220pl0","xy45220pl0",500,-15,15,500,-15,15);
  TH2F *xy56210pl0_ = dir.make<TH2F>("xy56210pl0","xy56210pl0",500,-15,15,500,-15,15);
  TH2F *xy56220pl0_ = dir.make<TH2F>("xy56220pl0","xy56220pl0",500,-15,15,500,-15,15);

  TH2F *xy45210pl1_ = dir.make<TH2F>("xy45210pl1","xy45210pl1",500,-15,15,500,-15,15);
  TH2F *xy45220pl1_ = dir.make<TH2F>("xy45220pl1","xy45220pl1",500,-15,15,500,-15,15);
  TH2F *xy56210pl1_ = dir.make<TH2F>("xy56210pl1","xy56210pl1",500,-15,15,500,-15,15);
  TH2F *xy56220pl1_ = dir.make<TH2F>("xy56220pl1","xy56220pl1",500,-15,15,500,-15,15);

  TH2F *xy45210pl2_ = dir.make<TH2F>("xy45210pl2","xy45210pl2",500,-15,15,500,-15,15);
  TH2F *xy45220pl2_ = dir.make<TH2F>("xy45220pl2","xy45220pl2",500,-15,15,500,-15,15);
  TH2F *xy56210pl2_ = dir.make<TH2F>("xy56210pl2","xy56210pl2",500,-15,15,500,-15,15);
  TH2F *xy56220pl2_ = dir.make<TH2F>("xy56220pl2","xy56220pl2",500,-15,15,500,-15,15);

  TH2F *xy45210pl3_ = dir.make<TH2F>("xy45210pl3","xy45210pl3",500,-15,15,500,-15,15);
  TH2F *xy45220pl3_ = dir.make<TH2F>("xy45220pl3","xy45220pl3",500,-15,15,500,-15,15);
  TH2F *xy56210pl3_ = dir.make<TH2F>("xy56210pl3","xy56210pl3",500,-15,15,500,-15,15);
  TH2F *xy56220pl3_ = dir.make<TH2F>("xy56220pl3","xy56220pl3",500,-15,15,500,-15,15);

  TH2F *xy45210pl4_ = dir.make<TH2F>("xy45210pl4","xy45210pl4",500,-15,15,500,-15,15);
  TH2F *xy45220pl4_ = dir.make<TH2F>("xy45220pl4","xy45220pl4",500,-15,15,500,-15,15);
  TH2F *xy56210pl4_ = dir.make<TH2F>("xy56210pl4","xy56210pl4",500,-15,15,500,-15,15);
  TH2F *xy56220pl4_ = dir.make<TH2F>("xy56220pl4","xy56220pl4",500,-15,15,500,-15,15);

  TH2F *xy45210pl5_ = dir.make<TH2F>("xy45210pl5","xy45210pl5",500,-15,15,500,-15,15);
  TH2F *xy45220pl5_ = dir.make<TH2F>("xy45220pl5","xy45220pl5",500,-15,15,500,-15,15);
  TH2F *xy56210pl5_ = dir.make<TH2F>("xy56210pl5","xy56210pl5",500,-15,15,500,-15,15);
  TH2F *xy56220pl5_ = dir.make<TH2F>("xy56220pl5","xy56220pl5",500,-15,15,500,-15,15);

  TH2F *trxy45210_ = dir.make<TH2F>("trxy45210","trxy45210",500,-15,15,500,-15,15);
  TH2F *trxy45220_ = dir.make<TH2F>("trxy45220","trxy45220",500,-15,15,500,-15,15);
  TH2F *trxy56210_ = dir.make<TH2F>("trxy56210","trxy56210",500,-15,15,500,-15,15);
  TH2F *trxy56220_ = dir.make<TH2F>("trxy56220","trxy56220",500,-15,15,500,-15,15);

  TH2F *trx56210rh220pl0_ = dir.make<TH2F>("trx56210rh220pl0","trx56210rh220pl0_",500,-5,25,500,-15,15);
  TH2F *trx56210rh220pl4_ = dir.make<TH2F>("trx56210rh220pl4","trx56210rh220pl4_",500,-5,25,500,-15,15);
  TH2F *trx56210rh220pl5_ = dir.make<TH2F>("trx56210rh220pl5","trx56210rh220pl5_",500,-5,25,500,-15,15);
  TH2F *try56210rh220pl0_ = dir.make<TH2F>("try56210rh220pl0","try56210rh220pl0_",500,-5,25,500,-15,15);
  TH2F *try56210rh220pl4_ = dir.make<TH2F>("try56210rh220pl4","try56210rh220pl4_",500,-5,25,500,-15,15);
  TH2F *try56210rh220pl5_ = dir.make<TH2F>("try56210rh220pl5","try56210rh220pl5_",500,-5,25,500,-15,15);

  TH2F *trtrx5621056220_ = dir.make<TH2F>("trtrx5621056220","trtrx5621056220",500,-5,25,500,-5,25);

  TH2F *planevsbx = dir.make<TH2F>("planevsbx","planevsbx",4000,0,4000,50,0,50);
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
	edm::Handle<std::vector<CTPPSLocalTrackLite> > ppstracks;
        // Use this for running on standard Physics AOD                                                                                                                                 
        event.getByLabel(std::string("ctppsLocalTrackLiteProducer"), ppstracks);
        for (std::vector<CTPPSLocalTrackLite>::const_iterator track0 = ppstracks->begin(); track0 != ppstracks->end(); ++track0)
          {
            //      std::cout << "RPID = " << track0->rpId() << std::endl;                                        
	    if(track0->rpId() == 2014838784)                                                                      
              {
		trxy45210_->Fill(track0->x(),track0->y());
              }
	    if(track0->rpId() == 2031616000)                                                                      
              {
                trxy56210_->Fill(track0->x(),track0->y());
		x56210 = track0->x();
		y56210 = track0->y();
		n56210++;
              }
            if(track0->rpId() == 2040004608)                                                                      
               {                                                                                                  
		 trxy56220_->Fill(track0->x(),track0->y());
		 x56220 = track0->x();
		 n56220++;
	       }                                                                                                  
            if(track0->rpId() == 2023227392)                              
              {                                                                                                   
                trxy45220_->Fill(track0->x(),track0->y());
              }                                           
          }

	if(n56220==1 && n56210==1)
	  trtrx5621056220_->Fill(x56210,x56220);

	edm::Handle< edm::DetSetVector<CTPPSPixelRecHit> > pixelRecHits;
	event.getByLabel(std::string("ctppsPixelRecHits"), pixelRecHits);

	//	std::cout << "Checking rechits" << std::endl;
	int nplane0=0; int nplane4=0; int nplane5=0;

	analyzed++;

	for ( const auto& rechits_ds : *pixelRecHits ) 
	  {
	    const CTPPSPixelDetId detidforrh( rechits_ds.detId() );
	    for ( const auto& rechit : rechits_ds ) 
	      {
                int arm = detidforrh.arm();                                                                               
		int plane = detidforrh.plane();                                                                           
		int station = detidforrh.station();

		int simplestation = station;

		if(station == 2)
		  simplestation = 1;

                int code = (arm*12) + (simplestation*6) + plane;
		planevsbx->Fill(BX,code);

		//		std::cout << "\tarm, station, plane = " << arm << ", " << simplestation << ", " << plane << ", code = " << code << std::endl;

		if(arm == 0 && station == 0)
		  {
		    if(plane == 0)
		      xy45210pl0_->Fill(rechit.point().x(),rechit.point().y());
		    if(plane == 1)
                      xy45210pl1_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 2)
                      xy45210pl2_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 3)
                      xy45210pl3_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 4)
                      xy45210pl4_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 5)
                      xy45210pl5_->Fill(rechit.point().x(),rechit.point().y());

		  }
		if(arm == 0 && station == 2)
		  {
		    if(plane == 0)
		      xy45220pl0_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 1)
                      xy45220pl1_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 2)
                      xy45220pl2_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 3)
                      xy45220pl3_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 4)
                      xy45220pl4_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 5)
                      xy45220pl5_->Fill(rechit.point().x(),rechit.point().y());
		  }
                if(arm == 1 && station == 0)
                  {
		    if(plane == 0)
		      xy56210pl0_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 1)
                      xy56210pl1_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 2)
                      xy56210pl2_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 3)
                      xy56210pl3_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 4)
                      xy56210pl4_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 5)
                      xy56210pl5_->Fill(rechit.point().x(),rechit.point().y());
                  }
                if(arm == 1 && station == 2)
                  {
		    if(plane == 0)
		      {
			xy56220pl0_->Fill(rechit.point().x(),rechit.point().y());
			if(n56210==1)
			  {
			    trx56210rh220pl0_->Fill(x56210,rechit.point().y());
                            try56210rh220pl0_->Fill(y56210,rechit.point().x());
                          }

			//			std::cout << "\tFound " << n56220 << "tracks: 56-220-plane0 x = " << rechit.point().x() << ", y = " << rechit.point().y() << std::endl;
		      }
                    if(plane == 1)
                      xy56220pl1_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 2)
                      xy56220pl2_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 3)
                      xy56220pl3_->Fill(rechit.point().x(),rechit.point().y());
                    if(plane == 4)
		      {
			xy56220pl4_->Fill(rechit.point().x(),rechit.point().y());
                        if(n56210==1)
			  {
			    trx56210rh220pl4_->Fill(x56210,rechit.point().y());
                            try56210rh220pl4_->Fill(y56210,rechit.point().x());
                          }

			//			std::cout << "\tFound " << n56220 << "tracks: 56-220-plane4 x = " << rechit.point().x() << ", y = " << rechit.point().y() << std::endl;
                      }
                    if(plane == 5)
		      {
			xy56220pl5_->Fill(rechit.point().x(),rechit.point().y());
                        if(n56210==1)
			  {
			    trx56210rh220pl5_->Fill(x56210,rechit.point().y());
			    try56210rh220pl5_->Fill(y56210,rechit.point().x());
			  }
			//			std::cout << "\tFound " << n56220 << "tracks: 56-220-plane5 x = " << rechit.point().x() << ", y = " << rechit.point().y() << std::endl;
                      }

                  }
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
