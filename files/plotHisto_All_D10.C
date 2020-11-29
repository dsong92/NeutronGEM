{
  gROOT->Reset();
  gStyle->SetOptStat(0);  
  // Draw histos filled by Geant4 simulation 
  //   
  TCanvas* c1 = new TCanvas("c1", "  ");
 
  TFile a("myresult_B5um_D10mm.root");      
  TFile b("myresult_B50um_D10mm.root");
  TFile c("myresult_B500um_D10mm.root");
 
  TH1D *hist1 = new TH1D("E_dep B5D10", "E_dep from All particle in DriftGap;MeV;Entries", 50, 0, 2);
  TH1D *hist2 = new TH1D("E_dep B50D10", "E_dep from All particle in DriftGap;MeV;Entreis", 50, 0, 2);
  TH1D *hist3 = new TH1D("E_dep B500D10", "E_dep from All particle in DriftGap;MeV;Entreis", 50, 0, 2);
 
  hist1 = (TH1D*)a.Get("E_deposit e+-");
  hist2 = (TH1D*)b.Get("E_deposit e+-");
  hist3 = (TH1D*)c.Get("E_deposit e+-");

  hist1->SetLineColor(1);  
  hist2->SetLineColor(2);  
  hist3->SetLineColor(4);  
  
  hist1->SetLineWidth(2);  
  hist2->SetLineWidth(2);  
  hist3->SetLineWidth(2);  

  int minbin = 0;  
  int maxbin = 50;  
  //char const *filename = "CompareEdep_noZoom.png";
  char const *filename = "Compare_Drift10mm_B5to500.png";

  hist1->SetTitle("E_dep from e- in DriftGap");

  hist1->Scale(1/hist1->Integral());
  hist2->Scale(1/hist2->Integral());
  hist3->Scale(1/hist3->Integral());

  hist1->Rebin(2);
  hist2->Rebin(2);
  hist3->Rebin(2);

  hist1->GetXaxis()->SetRange(minbin,maxbin);
  hist2->GetXaxis()->SetRange(minbin,maxbin);
  hist3->GetXaxis()->SetRange(minbin,maxbin);

  //hist1->SetMaximum(2000);
  
  hist1->Draw("HIST");
  hist2->Draw("HIST Same");
  hist3->Draw("HIST Same");

  auto legend = new TLegend(0.6,0.75,0.9,0.9);
  legend->AddEntry(hist1,"B 5um   / Drift 10mm");
  legend->AddEntry(hist2,"B 50um  / Drift 10mm");
  legend->AddEntry(hist3,"B 500um / Drift 10mm");
  legend->Draw();

  c1->SaveAs(filename);
}
