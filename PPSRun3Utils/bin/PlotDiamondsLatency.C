void PlotDiamondsLatency()
{
  TFile *f = TFile::Open("diamondHistogramsRecHits.root");
  TH2F *plot = (TH2F *)f->Get("histograms/planevsbx");

  TCanvas *c1 = new TCanvas("c1","c1",400, 800);

  plot->SetStats(0);
  plot->SetXTitle("BX");
  plot->GetYaxis()->SetLabelSize(0);
  plot->Draw("colz");

  Int_t bxmin = 113;
  Int_t bxmax = 118;
  //  bxmin = 0; bxmax = 4000;

  TLine *l1 = new TLine(bxmin,48,bxmax,48);
  l1->SetLineWidth(2); l1->Draw("same");

  TLine *l2 = new TLine(bxmin,48*2,bxmax,48*2);
  l2->SetLineWidth(2); l2->Draw("same");

  TLine *l3 = new TLine(bxmin,48*3,bxmax,48*3);
  l3->SetLineWidth(2); l3->Draw("same");

  TLine *l4 = new TLine(bxmin,48*4,bxmax,48*4);
  l4->SetLineWidth(2); l4->Draw("same");

  TLine *la = new TLine(bxmin,12,bxmax,12);
  la->SetLineWidth(2); la->SetLineStyle(2); la->Draw("same");
  TLine *lb = new TLine(bxmin,12*2,bxmax,12*2);
  lb->SetLineWidth(2); lb->SetLineStyle(2); lb->Draw("same");
  TLine *lc = new TLine(bxmin,12*3,bxmax,12*3);
  lc->SetLineWidth(2); lc->SetLineStyle(2); lc->Draw("same");

  TLine *ld = new TLine(bxmin,12*5,bxmax,12*5);
  ld->SetLineWidth(2); ld->SetLineStyle(2); ld->Draw("same");
  TLine *le = new TLine(bxmin,12*6,bxmax,12*6);
  le->SetLineWidth(2); le->SetLineStyle(2); le->Draw("same");
  TLine *lf = new TLine(bxmin,12*7,bxmax,12*7);
  lf->SetLineWidth(2); lf->SetLineStyle(2); lf->Draw("same");

  TLine *lg = new TLine(bxmin,12*9,bxmax,12*9);
  lg->SetLineWidth(2); lg->SetLineStyle(2); lg->Draw("same");
  TLine *lh = new TLine(bxmin,12*10,bxmax,12*10);
  lh->SetLineWidth(2); lh->SetLineStyle(2); lh->Draw("same");
  TLine *li = new TLine(bxmin,12*11,bxmax,12*11);
  li->SetLineWidth(2); li->SetLineStyle(2); li->Draw("same");

  TLine *lj = new TLine(bxmin,12*13,bxmax,12*13);
  lj->SetLineWidth(2); lj->SetLineStyle(2); lj->Draw("same");
  TLine *lk = new TLine(bxmin,12*14,bxmax,12*14);
  lk->SetLineWidth(2); lk->SetLineStyle(2); lk->Draw("same");
  TLine *ll = new TLine(bxmin,12*15,bxmax,12*15);
  ll->SetLineWidth(2); ll->SetLineStyle(2); ll->Draw("same");

  
}
