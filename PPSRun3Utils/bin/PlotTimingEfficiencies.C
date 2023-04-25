void PlotTimingEfficiencies()
{
  TFile *f = TFile::Open("timingHistograms.root");

  TH2F *den45 = (TH2F *)f->Get("diamondHistograms/deffden45");
  TH2F *den56 = (TH2F *)f->Get("diamondHistograms/deffden56");

  TH2F *pl0st145 = (TH2F *)f->Get("diamondHistograms/deffnum45plane0");
  TH2F *pl1st145 = (TH2F *)f->Get("diamondHistograms/deffnum45plane1");
  TH2F *pl2st145 = (TH2F *)f->Get("diamondHistograms/deffnum45plane2");
  TH2F *pl3st145 = (TH2F *)f->Get("diamondHistograms/deffnum45plane3");

  TH2F *pl0st156 = (TH2F *)f->Get("diamondHistograms/deffnum56plane0");
  TH2F *pl1st156 = (TH2F *)f->Get("diamondHistograms/deffnum56plane1");
  TH2F *pl2st156 = (TH2F *)f->Get("diamondHistograms/deffnum56plane2");
  TH2F *pl3st156 = (TH2F *)f->Get("diamondHistograms/deffnum56plane3");

  TH2F *pl0st245box = (TH2F *)f->Get("diamondHistograms/deffnum45boxplane0");
  TH2F *pl1st245box = (TH2F *)f->Get("diamondHistograms/deffnum45boxplane1");
  TH2F *pl2st245box = (TH2F *)f->Get("diamondHistograms/deffnum45boxplane2");
  TH2F *pl3st245box = (TH2F *)f->Get("diamondHistograms/deffnum45boxplane3");

  TH2F *pl0st256box = (TH2F *)f->Get("diamondHistograms/deffnum56boxplane0");
  TH2F *pl1st256box = (TH2F *)f->Get("diamondHistograms/deffnum56boxplane1");
  TH2F *pl2st256box = (TH2F *)f->Get("diamondHistograms/deffnum56boxplane2");
  TH2F *pl3st256box = (TH2F *)f->Get("diamondHistograms/deffnum56boxplane3");


  pl0st145->Divide(den45);
  pl1st145->Divide(den45);
  pl2st145->Divide(den45);
  pl3st145->Divide(den45);
  pl0st156->Divide(den56);
  pl1st156->Divide(den56);
  pl2st156->Divide(den56);
  pl3st156->Divide(den56);

  pl0st245box->Divide(den45);
  pl1st245box->Divide(den45);
  pl2st245box->Divide(den45);
  pl0st256box->Divide(den56);
  pl1st256box->Divide(den56);
  pl2st256box->Divide(den56);


  TCanvas *c1 = new TCanvas("c1","c1");
  c1->Divide(4,2);
  c1->cd(1); pl0st145->SetMaximum(1); pl0st145->Draw("colz"); pl0st145->SetTitle("45 cyl plane0"); pl0st145->SetStats(0);
  c1->cd(2); pl1st145->SetMaximum(1); pl1st145->Draw("colz"); pl1st145->SetTitle("45 cyl plane1"); pl1st145->SetStats(0);
  c1->cd(5); pl2st145->SetMaximum(1); pl2st145->Draw("colz"); pl2st145->SetTitle("45 cyl plane2"); pl2st145->SetStats(0);
  c1->cd(6); pl3st145->SetMaximum(1); pl3st145->Draw("colz"); pl3st145->SetTitle("45 cyl plane3"); pl3st145->SetStats(0);

  c1->cd(3); pl0st156->SetMaximum(1); pl0st156->Draw("colz"); pl0st156->SetTitle("56 cyl plane0"); pl0st156->SetStats(0);
  c1->cd(4); pl1st156->SetMaximum(1); pl1st156->Draw("colz"); pl1st156->SetTitle("56 cyl plane1"); pl1st156->SetStats(0);
  c1->cd(7); pl2st156->SetMaximum(1); pl2st156->Draw("colz"); pl3st156->SetTitle("56 cyl plane2"); pl2st156->SetStats(0);
  c1->cd(8); pl3st156->SetMaximum(1); pl3st156->Draw("colz"); pl3st156->SetTitle("56 cyl plane3"); pl3st156->SetStats(0);

  TCanvas *c2 = new TCanvas("c2","c2");
  c2->Divide(4,2);
  c2->cd(1); pl0st245box->SetMaximum(1); pl0st245box->Draw("colz"); pl0st245box->SetTitle("45 box plane0"); pl0st245box->SetStats(0);
  c2->cd(2); pl1st245box->SetMaximum(1); pl1st245box->Draw("colz"); pl1st245box->SetTitle("45 box plane1"); pl1st245box->SetStats(0);
  c2->cd(5); pl2st245box->SetMaximum(1); pl2st245box->Draw("colz"); pl2st245box->SetTitle("45 box plane2"); pl2st245box->SetStats(0);

  c2->cd(3); pl0st256box->SetMaximum(1); pl0st256box->Draw("colz"); pl0st256box->SetTitle("56 box plane0"); pl0st256box->SetStats(0);
  c2->cd(4); pl1st256box->SetMaximum(1); pl1st256box->Draw("colz"); pl1st256box->SetTitle("56 box plane1"); pl1st256box->SetStats(0);
  c2->cd(7); pl2st256box->SetMaximum(1); pl2st256box->Draw("colz"); pl3st256box->SetTitle("56 box plane2"); pl2st256box->SetStats(0);


}