void PlotRadiographies(int nrun)
{
//.x PlotRadiographies.C(367271)
  char namefil[100];
  char namein[100];
  sprintf(namein,"timingHistograms_%d.root",nrun);
  TFile *f = TFile::Open(namein);

  TH2F *rad45 = (TH2F *)f->Get("diamondHistograms/drad45");
  TH2F *rad56 = (TH2F *)f->Get("diamondHistograms/drad56");

  TH2F *rad45box = (TH2F *)f->Get("diamondHistograms/dboxrad45");
  TH2F *rad56box = (TH2F *)f->Get("diamondHistograms/dboxrad56");

  TH2F *arad45 = (TH2F *)f->Get("diamondHistograms/dantirad45");
  TH2F *arad56 = (TH2F *)f->Get("diamondHistograms/dantirad56");

  TH2F *arad45box = (TH2F *)f->Get("diamondHistograms/dboxantirad45");
  TH2F *arad56box = (TH2F *)f->Get("diamondHistograms/dboxantirad56");






  TCanvas *c1 = new TCanvas("c1","c1");
  c1->Divide(2,1);
  c1->cd(1); rad45->Draw("colz"); rad45->SetStats(0); rad45->SetTitle("Rad 45 cylindrical"); 
  c1->cd(2); rad56->Draw("colz"); rad56->SetStats(0); rad56->SetTitle("Rad 56 cylindrical");

  TCanvas *c2 = new TCanvas("c2","c2");
  c2->Divide(2,1);
  c2->cd(1); rad45box->Draw("colz"); rad45box->SetStats(0); rad45box->SetTitle("Rad 45 box");
  c2->cd(2); rad56box->Draw("colz"); rad56box->SetStats(0); rad56box->SetTitle("Rad 56 box");
 
  TCanvas *c3 = new TCanvas("c3","c3");
  c3->Divide(2,1);
  c3->cd(1); arad45->Draw("colz"); arad45->SetStats(0); arad45->SetTitle("AntiRad 45 cylindrical"); 
  c3->cd(2); arad56->Draw("colz"); arad56->SetStats(0); arad56->SetTitle("AntiRad 56 cylindrical");

  TCanvas *c4 = new TCanvas("c4","c4");
  c4->Divide(2,1);
  c4->cd(1); arad45box->Draw("colz"); arad45box->SetStats(0); arad45box->SetTitle("AntiRad 45 box");
  c4->cd(2); arad56box->Draw("colz"); arad56box->SetStats(0); arad56box->SetTitle("AntiRad 56 box");

sprintf(namefil,"RadioCyl_%d.pdf",nrun);
c1->SaveAs(namefil);
sprintf(namefil,"RadioBox_%d.pdf",nrun);
c2->SaveAs(namefil);
sprintf(namefil,"AntiRadioCyl_%d.pdf",nrun);
c3->SaveAs(namefil);
sprintf(namefil,"AntiRadioBox_%d.pdf",nrun);
c4->SaveAs(namefil);

}
