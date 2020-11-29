{
  gROOT->Reset();
  gStyle->SetOptStat(0);  
  // Draw histos filled by Geant4 simulation 
  //   
  TCanvas* c1 = new TCanvas("c1", "  ");
 
  TFile a("myresult_B5um_D3mm.root");      
  //TFile b("myresult_B50um_D3mm.root");
 
  TH1D *hist1 = new TH1D("Alpha_pre", "Alpha energy;MeV;Entries", 50, 0, 2);
  TH1D *hist2 = new TH1D("Alpha_post", "Alpha energy;MeV;Entries", 50, 0, 2);
  //TH1D *hist2 = new TH1D("E_dep B50D3", "E_dep from All particle in DriftGap;MeV;Entreis", 50, 0, 2);
 
  hist1 = (TH1D*)a.Get("PreStep_E_kin of alphas");
  hist2 = (TH1D*)a.Get("PostStep_E_kin of alphas");

  hist1->SetLineColor(1);  
  hist2->SetLineColor(2);  
  
  hist1->SetLineWidth(2);  
  hist2->SetLineWidth(2);  

  int minbin = 0;  
  int maxbin = 150;  
  //char const *filename = "CompareEdep_noZoom.png";
  char const *filename = "AlphaEnergy.png";

  //hist1->Scale(1/hist1->Integral());
  //hist2->Scale(1/hist2->Integral());
  //hist3->Scale(1/hist3->Integral());
  
  hist1->SetTitle("pre/post alpha energy");
  hist1->GetXaxis()->SetRange(minbin,maxbin);
  hist2->GetXaxis()->SetRange(minbin,maxbin);

  hist1->Rebin(2);
  hist2->Rebin(2);

  hist1->Draw("HIST");
  hist2->Draw("HIST Same");

  auto legend = new TLegend(0.6,0.75,0.9,0.9);
  legend->AddEntry(hist1,"before escaping boron");
  legend->AddEntry(hist2,"after escaping boron");
  legend->Draw();

  c1->SaveAs(filename);
}
