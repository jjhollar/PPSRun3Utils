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

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/CTPPSDetId/interface/CTPPSDetId.h"
#include "DataFormats/CTPPSDetId/interface/CTPPSDiamondDetId.h"
#include "DataFormats/CTPPSDetId/interface/CTPPSPixelDetId.h"
#include "DataFormats/CTPPSReco/interface/CTPPSLocalTrackLite.h"
#include "DataFormats/Common/interface/DetSet.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/CTPPSReco/interface/CTPPSTimingRecHit.h"
#include "DataFormats/CTPPSReco/interface/CTPPSDiamondRecHit.h"
#include "DataFormats/CTPPSReco/interface/CTPPSPixelRecHit.h"
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h"

int main(int argc, char* argv[]) {
  // define what muon you are using; this is necessary as FWLite is not
  // capable of reading edm::Views
  using reco::Muon;

  // ----------------------------------------------------------------------
  // First Part:
  //
  //  * enable FWLite
  //  * book the histograms of interest
  //  * open the input file
  // ----------------------------------------------------------------------

  // load framework libraries
  gSystem->Load("libFWCoreFWLite");
  FWLiteEnabler::enable();

  // initialize command line parser
  optutl::CommandLineParser parser("Analyze FWLite Histograms");

  // set defaults
  parser.integerValue("maxEvents") = 120000000;
  parser.integerValue("outputEvery") = 10000;
  parser.stringValue("outputFile") = "timingHistograms.root";

  // parse arguments
  parser.parseArguments(argc, argv);
  int maxEvents_ = parser.integerValue("maxEvents");
  unsigned int outputEvery_ = parser.integerValue("outputEvery");
  std::string outputFile_ = parser.stringValue("outputFile");
  std::string inputfilelist = "InputFiles.txt";

  // AOD input files
  std::vector<std::string> inFiles_;
  std::ifstream ifs2(inputfilelist);

  std::string filename;
  std::string xrootdprefix = "root://cms-xrd-global.cern.ch/";
  std::string fullfilename;

  while ( getline (ifs2,filename) )
    {
      fullfilename = xrootdprefix + filename;
      inFiles_.push_back(fullfilename);
    }
  ifs2.close();

  // book a set of histograms
  fwlite::TFileService fs = fwlite::TFileService(outputFile_);
  TFileDirectory dir = fs.mkdir("diamondHistograms");

  // Pixel-diamond x-correlation to define matching cuts
  TH2F *xtpix21045_ = dir.make<TH2F>("xtpix21045","xtpix21045",40,-10,30,40,-10,30);
  TH2F *xtpix21056_ = dir.make<TH2F>("xtpix21056","xtpix21056",40,-10,30,40,-10,30);

  // Denominator for all efficiencies
  TH2F* deffden45_ = dir.make<TH2F>("deffden45","deffden45",400,-10,30,200,-10,10);
  TH2F* deffden56_ = dir.make<TH2F>("deffden56","deffden56",400,-10,30,200,-10,10);

  // Numerator for per-arm/track efficiencies
  TH2F* deffnum45_ = dir.make<TH2F>("deffnum45","deffnum45",400,-10,30,200,-10,10);
  TH2F* deffnum56_ = dir.make<TH2F>("deffnum56","deffnum56",400,-10,30,200,-10,10);

  // Numerator for per-plane efficiencies
  TH2F* deffnum45plane0_ = dir.make<TH2F>("deffnum45plane0","deffnum45plane0",400,-10,30,200,-10,10);
  TH2F* deffnum56plane0_ = dir.make<TH2F>("deffnum56plane0","deffnum56plane0",400,-10,30,200,-10,10);
  TH2F* deffnum45plane1_ = dir.make<TH2F>("deffnum45plane1","deffnum45plane1",400,-10,30,200,-10,10);
  TH2F* deffnum56plane1_ = dir.make<TH2F>("deffnum56plane1","deffnum56plane1",400,-10,30,200,-10,10);
  TH2F* deffnum45plane2_ = dir.make<TH2F>("deffnum45plane2","deffnum45plane2",400,-10,30,200,-10,10);
  TH2F* deffnum56plane2_ = dir.make<TH2F>("deffnum56plane2","deffnum56plane2",400,-10,30,200,-10,10);
  TH2F* deffnum45plane3_ = dir.make<TH2F>("deffnum45plane3","deffnum45plane3",400,-10,30,200,-10,10);
  TH2F* deffnum56plane3_ = dir.make<TH2F>("deffnum56plane3","deffnum56plane3",400,-10,30,200,-10,10);

  // Radiographies and anti-radiographies
  TH2F* drad45_ = dir.make<TH2F>("drad45","drad45",400,-10,30,200,-10,10);
  TH2F* drad56_ = dir.make<TH2F>("drad56","drad56",400,-10,30,200,-10,10);
  TH2F* dantirad45_ = dir.make<TH2F>("dantirad45","dantirad45",400,-10,30,200,-10,10);
  TH2F* dantirad56_ = dir.make<TH2F>("dantirad56","dantirad56",400,-10,30,200,-10,10);


  TH1F *ls_ = dir.make<TH1F>("ls","ls",2000,0,2000);
  
  // loop the events
  int ievt = 0;

  int lumiblock_ = -99;

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
      fwlite::Event ev(inFile);
      for (ev.toBegin(); !ev.atEnd(); ++ev, ++ievt) {
        edm::EventBase const& event = ev;
        // break loop if maximal number of events is reached
        if (maxEvents_ > 0 ? ievt + 1 > maxEvents_ : false)
          break;
        // simple event counter
        if (outputEvery_ != 0 ? (ievt > 0 && ievt % outputEvery_ == 0) : false)
          std::cout << "  processing event: " << ievt << std::endl;


	// LumiSection
        lumiblock_ = ev.luminosityBlock();
	ls_->Fill(lumiblock_);

	// Long RP IDs for Lite tracks
	// Pixels
	// 2031616000
	// 2040004608
	// 2014838784
	// 2023227392
	//
	// Diamonds
	// 2070937600
	// 2054160384

        float x45210=-999.;
        float y45210=-999.;
        float x56210=-999.;
        float y56210=-999.;


	// If 220 pixels are needed
	//        float x56220=-999.;
	//        float y56220=-999.;
	//        float x45220=-999.;
	//        float y45220=-999.;


	float xtimetrack45=-999.;
	float xtimetrack56=-999.;

	
	int n45210=0; int n56210=0; int ntimetrack56=0; int ntimetrack45=0;
	// int n45220=0; int n56220=0; 


        // Handle to the collection of lite tracks                                                                                                                                  
	edm::Handle<std::vector<CTPPSLocalTrackLite> > ppstracks;

	// Use this for running on standard Physics AOD
	event.getByLabel(std::string("ctppsLocalTrackLiteProducer"), ppstracks);
	// Use this instead for running on AlCaPPS AOD
	//	event.getByLabel(std::string("ctppsLocalTrackLiteProducerAlCaRecoProducer"), ppstracks);

	/*
	 * Loop on tracks to get pixel tracks for the efficiency denominator
	 */
        for (std::vector<CTPPSLocalTrackLite>::const_iterator track0 = ppstracks->begin(); track0 != ppstracks->end(); ++track0) 
	  {
	    if(track0->rpId() == 2014838784)
	      {
		n45210++;
		x45210=track0->x();
		y45210=track0->y();
	      }
	    if(track0->rpId() == 2031616000)
	      {
		n56210++;
		x56210=track0->x();
		y56210=track0->y();
	      }
	    /*
	     * If 220 pixels are needed
	    if(track0->rpId() == 2040004608)
	      {
		n56220++;
		x56220=track0->x();
		y56220=track0->y();
	      }
	    if(track0->rpId() == 2023227392)
	      {
		n45220++;
		x45220=track0->x();
		y45220=track0->y();
	      }
	    */
	  }

	// Skip everything unless the event has exactly 1 pixel track on at least one arm
	if((n45210 == 1) || (n56210 == 1))
	  {
	    // Denominator for efficiency: events with exactly 1 pixel track in the 45-210 pixels
	    if(n45210 == 1)
	      deffden45_->Fill(x45210,y45210);
	    
	    // Denominator for efficiency: events with exactly 1 pixel track in the 56-210 pixels                                                                                         
	    if(n56210 == 1)
	      deffden56_->Fill(x56210,y56210);
	    
	    /*
	     * Loop again to check time-tracks for the per-arm efficiency numerator
	     */
	    for (std::vector<CTPPSLocalTrackLite>::const_iterator track1 = ppstracks->begin(); track1 != ppstracks->end(); ++track1)
	      {
		if(track1->rpId() == 2054160384)
		  {
		    xtimetrack45 = track1->x();
		    
		    if(n45210 == 1)
		      {
			// Pixel-diamond correlation to define matching cuts                                                                                                             
			xtpix21045_->Fill(x45210,xtimetrack45);
			
			// Histogram for radiography                                                                                                                                     
			drad45_->Fill(x45210,y45210);
			
			if(fabs(x45210 - xtimetrack45) < 999) // x-matching between pixel+time tracks for eff. numerator                                                  
			  deffnum45_->Fill(x45210,y45210);
		      }
		    
		    ntimetrack45++;
		  }
		
		if(track1->rpId() == 2070937600)
		  {
		    xtimetrack56 = track1->x();
		    
		    if(n56210 == 1)
		      {
			// Pixel-diamond correlation to define matching cuts                                                                                                             
			xtpix21056_->Fill(x56210,xtimetrack56);
			
			// Histogram for radiography                                                                                                                                     
			drad56_->Fill(x56210,y56210);
			
			if(fabs(x56210 - xtimetrack56) < 999) // x-matching between pixel+time tracks for eff. numerator
			  deffnum56_->Fill(x56210,y56210);
			
		      }
		    
		    ntimetrack56++;
		  }
	      }
	    
	    
	    /*
	     *Histograms for anti-radiography: events with 1 track in pixels and none in the diamonds
	     */
	    if(n45210 == 1 && ntimetrack45==0)
	      dantirad45_->Fill(x45210,y45210);
	    
	    if(n56210 == 1 && ntimetrack56==0)
	      dantirad56_->Fill(x56210,y56210);
	    
	
	    /*
	     * Now loop on Diamond rechits to do plane-by-plane efficiencies
	     */
	    edm::Handle< edm::DetSetVector<CTPPSDiamondRecHit> > diamondRecHits;
	    // Use this for running on standard Physics AOD                                                                                                                              
	    event.getByLabel(std::string("ctppsDiamondRecHits"), diamondRecHits);                                                                                                       
	    
	    // Use this instead for running on AlCaPPS AOD                                                                                                                               
	    //        event.getByLabel(std::string("ctppsDiamondRecHitsAlCaRecoProducer"), diamondRecHits);
	
	    for ( const auto& rechits_ds : *diamondRecHits )
	      {
		const CTPPSDiamondDetId detidforrh( rechits_ds.detId() );
		for ( const auto& rechit : rechits_ds )
		  {
		    int arm = detidforrh.arm();
		    int plane = detidforrh.plane();
		    float xrh = rechit.x();
		    
		    // Not currently used
		    //		float tot = rechit.toT();
		    //		int channel = detidforrh.channel();
		    
		    // Sector 45
		    if(plane==0 && arm==0 && n45210==1)
		      {
			if(fabs(x45210 - xrh) < 999) //  x-matching between pixel+diamond rechits for eff. numerator
			  deffnum45plane0_->Fill(x45210,y45210);
		      }
		    if(plane==1 && arm==0 && n45210==1)
		      {
			if(fabs(x45210 - xrh) < 999) //  x-matching between pixel+diamond rechits for eff. numerator                                                            
			  deffnum45plane1_->Fill(x45210,y45210);
		      }
		    if(plane==2 && arm==0 && n45210==1)
		      {
			if(fabs(x45210 - xrh) < 999) //  x-matching between pixel+diamond rechits for eff. numerator                                                            
			  deffnum45plane2_->Fill(x45210,y45210);
		      }
		    if(plane==3 && arm==0 && n45210==1)
		      {
			if(fabs(x45210 - xrh) < 999) //  x-matching between pixel+diamond rechits for eff. numerator                                                            
			  deffnum45plane3_->Fill(x45210,y45210);
		      }

		    // Sector 56
		    if(plane==0 && arm==1 && n56210==1)
		      {
			if(fabs(x56210 - xrh) < 999) //  x-matching between pixel+diamond rechits for eff. numerator
			  deffnum56plane0_->Fill(x56210,y56210);
		      }		
		    if(plane==1 && arm==1 && n56210==1)
		      {
			if(fabs(x56210 - xrh) < 999) //  x-matching between pixel+diamond rechits for eff. numerator                                                            
			  deffnum56plane1_->Fill(x56210,y56210);
		      }
		    if(plane==2 && arm==1 && n56210==1)
		      {
			if(fabs(x56210 - xrh) < 999) //  x-matching between pixel+diamond rechits for eff. numerator                                                             
			  deffnum56plane2_->Fill(x56210,y56210);
		      }
		    if(plane==3 && arm==1 && n56210==1)
		      {
			if(fabs(x56210 - xrh) < 999) //  x-matching between pixel+diamond rechits for eff. numerator                                                            
			  deffnum56plane3_->Fill(x56210,y56210);
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
 
  return 0;
}
