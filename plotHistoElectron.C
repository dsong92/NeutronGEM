{
  gROOT->Reset();
  gStyle->SetOptStat(0);  
  // Draw histos filled by Geant4 simulation 
  //   
  TCanvas* c1 = new TCanvas("c1","",2000,1200);
 
  //TFile a("AllEnvOn_250umGd_10mmDrift_20meVNeutron.root");      
  TFile a("myresult.root");      
 
  TH1D *hist1 = new TH1D("Neutron E : 20 meV", "E_dep in 10mm DriftGap;keV;Events", 250, 0, 250);
 
  hist1 = (TH1D*)a.Get("5");

  hist1->SetLineColor(1);  
  hist1->SetLineWidth(2); 
  hist1->SetTitle(""); 

  int minbin = 5;  
  int maxbin = 250;  
  //char const *filename = "CompareEdep_noZoom.png";
  char const *filename = "EnergyOfElectron.png";

  hist1->GetXaxis()->SetRange(minbin,maxbin);
  hist1->GetXaxis()->SetTitle("Kinetic Energy [keV]");
  hist1->GetYaxis()->SetTitle("Event [%]");

  hist1->GetXaxis()->SetTitleSize(.05);
  hist1->GetYaxis()->SetTitleSize(.05);
  hist1->GetXaxis()->SetLabelSize(.05);
  hist1->GetYaxis()->SetLabelSize(.05);


  hist1->Scale(1/hist1->Integral());
  hist1->Scale(100);
  hist1->Draw("HIST");

  //auto legend = new TLegend(0.6,0.75,0.9,0.9);
  //legend->AddEntry(hist1,"E_{kin} of electron");
  //legend->Draw();

  c1->SaveAs(filename);
}
