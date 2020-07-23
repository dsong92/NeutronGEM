{
  gROOT->Reset();
  //gStyle->SetOptStat(0);  
  // Draw histos filled by Geant4 simulation 
  //   
  TCanvas* c1 = new TCanvas("c1", "  ");
 
  TFile a("myresult.root");      
 
  TH1D *hist1 = new TH1D("hist1", "Electron Energy;keV;Events", 120, 0, 120);
 
  hist1 = (TH1D*)a.Get("5");

  hist1->SetLineColor(1);  
  
  hist1->SetLineWidth(2);  

  hist1->GetXaxis()->SetLimits(2,120);

  hist1->Draw("HIST");

  auto legend = new TLegend(0.1,0.7,0.48,0.9);
  legend->AddEntry(hist1,"E_{e-} at the moment of entring driftgap");
  legend->Draw();

}
