{
  gROOT->Reset();
  gStyle->SetOptStat(0);  
  // Draw histos filled by Geant4 simulation 
  //   
  TCanvas* c1 = new TCanvas("c1", "  ");
 
  TFile a("AllEnvOn_250umGd_10mmDrift_20meVNeutron.root");      
  TFile b("AllEnvOn_250umGd_10mmDrift_25meVNeutron.root");    
  TFile c("AllEnvOn_250umGd_10mmDrift_30meVNeutron.root");      
  TFile d("AllEnvOn_250umGd_10mmDrift_40meVNeutron.root");      
 
  TH1D *hist1 = new TH1D("Neutron E : 20 meV", "E_dep in 10mm DriftGap;keV;Events", 250, 0, 250);
  TH1D *hist2 = new TH1D("Neutron E : 25 meV", "E_dep in 10mm DriftGap;keV;Events", 250, 0, 250);
  TH1D *hist3 = new TH1D("Neutron E : 30 meV", "E_dep in 10mm DriftGap;keV;Events", 250, 0, 250);
  TH1D *hist4 = new TH1D("Neutron E : 40 meV", "E_dep in 10mm DriftGap;keV;Events", 250, 0, 250);
 
  hist1 = (TH1D*)a.Get("1");
  hist2 = (TH1D*)b.Get("1");
  hist3 = (TH1D*)c.Get("1");
  hist4 = (TH1D*)d.Get("1");

  hist1->SetLineColor(1);  
  hist2->SetLineColor(2);  
  hist3->SetLineColor(3);  
  hist4->SetLineColor(6);  
  
  hist1->SetLineWidth(2);  
  hist2->SetLineWidth(2);  
  hist3->SetLineWidth(2);  
  hist4->SetLineWidth(2);  

  int minbin = 1;  
  int maxbin = 60;  
  //char const *filename = "CompareEdep_noZoom.png";
  char const *filename = "CompareEdep_Zoom2.png";

  hist1->GetXaxis()->SetRange(minbin,maxbin);
  hist2->GetXaxis()->SetRange(minbin,maxbin);
  hist3->GetXaxis()->SetRange(minbin,maxbin);
  hist4->GetXaxis()->SetRange(minbin,maxbin);

  hist1->Draw("HIST");
  hist2->Draw("HIST Same");
  hist3->Draw("HIST Same");
  hist4->Draw("HIST Same");

  auto legend = new TLegend(0.6,0.75,0.9,0.9);
  legend->AddEntry(hist1,"E_{Neutron} : 20 meV");
  legend->AddEntry(hist2,"E_{Neutron} : 25 meV");
  legend->AddEntry(hist3,"E_{Neutron} : 30 meV");
  legend->AddEntry(hist4,"E_{Neutron} : 40 meV");
  legend->Draw();

  c1->SaveAs(filename);
}
