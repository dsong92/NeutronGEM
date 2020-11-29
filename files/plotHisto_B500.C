{
  gROOT->Reset();
  gStyle->SetOptStat(0);  
  // Draw histos filled by Geant4 simulation 
  //   
  TCanvas* c1 = new TCanvas("c1", "  ");
 
  TFile a("myresult_B500um_D3mm.root");      
  TFile b("myresult_B500um_D10mm.root");
 
  TH1D *hist1 = new TH1D("E_dep B500D3", "E_dep from All particle in DriftGap;MeV;Entries", 50, 0, 2);
  TH1D *hist2 = new TH1D("E_dep B500D10", "E_dep from All particle in DriftGap;MeV;Entreis", 50, 0, 2);
 
  hist1 = (TH1D*)a.Get("E_deposit_All");
  hist2 = (TH1D*)b.Get("E_deposit_All");

  hist1->SetLineColor(1);  
  hist2->SetLineColor(2);  
  
  hist1->SetLineWidth(2);  
  hist2->SetLineWidth(2);  

  int minbin = 0;  
  int maxbin = 200;  
  //char const *filename = "CompareEdep_noZoom.png";
  char const *filename = "Compare_B500um_D3and10mm.png";

  hist1->Scale(1/hist1->Integral());
  hist2->Scale(1/hist2->Integral());

  hist1->GetXaxis()->SetRange(minbin,maxbin);
  hist2->GetXaxis()->SetRange(minbin,maxbin);

  hist1->Rebin(2);
  hist2->Rebin(2);

  hist1->Draw("HIST");
  hist2->Draw("HIST Same");

  auto legend = new TLegend(0.6,0.75,0.9,0.9);
  legend->AddEntry(hist1,"B 500um / Drift 3mm");
  legend->AddEntry(hist2,"B 500um / Drift 10mm");
  legend->Draw();

  c1->SaveAs(filename);
}
