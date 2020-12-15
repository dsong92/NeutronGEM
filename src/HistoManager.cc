//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file HistoManager.cc
/// \brief Implementation of the HistoManager class
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "HistoManager.hh"
#include "G4UnitsTable.hh"

#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
  : fFileName("NeutronSource")
{
  Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book()
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile(fFileName);

  // Creating histograms
  analysisManager->CreateH1("EdepAll","Edep from All particle", 100, 0., 3);
  analysisManager->CreateH1("EdepAlpha","Edep from Alpha", 100, 0., 3);

  analysisManager->CreateNtuple("event", "event");
  analysisManager->CreateNtupleDColumn("eventID");  		 // id 0
  analysisManager->CreateNtupleDColumn("EdepAll");  		 // id 1
  analysisManager->CreateNtupleDColumn("EdepAlpha"); 		 // id 2
  analysisManager->CreateNtupleDColumn("EdepGamma"); 		 // id 3
  analysisManager->CreateNtupleDColumn("EdepElectron"); 	 // id 4
  analysisManager->CreateNtupleDColumn("gen_Ekin_Alpha"); 	 // id 5
  analysisManager->CreateNtupleDColumn("PreB_Ekin_Alpha");	 // id 6
  analysisManager->CreateNtupleDColumn("PostB_Ekin_Alpha");	 // id 7
  analysisManager->CreateNtupleDColumn("BNCap_depth_Alpha");	 // id 8
  analysisManager->CreateNtupleIColumn("TID_AlPha");		 // id 9
  analysisManager->CreateNtupleIColumn("PID_Alpha");		 // id 10
  analysisManager->CreateNtupleDColumn("EofGamma");		 // id 11
  analysisManager->CreateNtupleIColumn("TID_Gamma");		 // id 12
  analysisManager->CreateNtupleIColumn("PID_Gamma");		 // id 13
  analysisManager->CreateNtupleDColumn("EofElectron");		 // id 14
  analysisManager->CreateNtupleIColumn("TID_Electron");		 // id 15
  analysisManager->CreateNtupleIColumn("PID_Electron");		 // id 16
  analysisManager->CreateNtupleDColumn("DriftLength_Alpha");  	 // id 17
  
  analysisManager->FinishNtuple();

/*
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFileName(fFileName);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);     //enable inactivation of histograms

  // Define histograms start values
  const G4int kMaxHisto = 21;
  //const G4String id[] = {"0","1","2","3","4","5","6","7","8","9",
  //                       "10","11","12","13","14","15","16","17","18","19","20"};
  const G4String id[] = 
      { "dummy",							//0
        "E_deposit_All",                          //1
        "E_deposit Alpha",                        //2
        "E_deposit gamma",                        //3
        "E_deposit e+-",                          //4
        "E_spectrum of emerging alpha",                            //5
        "E_spectrum of emerging gamma",                            //6
        "E_spectrum of secondary gamma",                           //7
        "E_spectrum of third gamma",                               //8
        "E_spectrum of emerging e-",                               //9
        "PreStep_E_kin of alphas",                 //10
        "PostStep_E_kin of alphas",                //11
        "Num of N_cap",                                   //12
        "Drift Length of Alpha",                        //13
	"E_spectrum of emerging e+",				//14
        "Incident Neutron",                                             //15 --- fixed
        "Alpha, XY",                                   //16
        "Alpha, XZ",                                   //17
        "Alpha, YZ",                                   //18
        "Penetration depth of Neutron vs E_kin",                        //19
        "Generated alpha position vs E_kin"                             //20 
      };
  const G4String title[] = 
      { "dummy",							//0
        "Energy deposit from All in DriftGap",                          //1
        "Energy deposit from Alpha in DriftGap",                        //2
        "Energy deposit from gamma in DriftGap",                        //3
        "Energy deposit from e+- in DriftGap",                          //4
        "energy spectrum of emerging alpha",                            //5
        "energy spectrum of emerging gamma",                            //6
        "energy spectrum of secondary gamma",                           //7
        "energy spectrum of third gamma",                               //8
        "Post_E_Kin of e- at entering Drift from B",                               //9
        "pre_E_kin of alphas at entering Drift from B",                 //10
        "post_E_kin of alphas at entering Drift from B",                //11
        "number of captured neutron",                                   //12
        "Length of Alpha particle in Drift gap",                        //13
	"energy spectrum of emerging e+",				//14
        "Incident Neutron",                                             //15 --- fixed
        "Spread of Alpha , XY plane",                                   //16
        "Spread of Alpha , XZ plane",                                   //17
        "Spread of Alpha , YZ plane",                                   //18
        "Penetration depth of Neutron vs E_kin",                        //19
        "Generated alpha position vs E_kin"                             //20 
      };
  // Default values (to be reset via /analysis/h1/set command) 
  G4int nbins = 100;
  G4double vmin = 0.;
  G4double vmax = 100.;
  // Create all histograms as inactivated 
  // as we have not yet set nbins, vmin, vmax
  for (G4int k=0; k<kMaxHisto; k++) {
	if(k<15){
	G4int ih = analysisManager->CreateH1(id[k], title[k], nbins, vmin, vmax);
        analysisManager->SetH1Activation(ih, false);}
	else{
  	G4int ig = analysisManager->CreateH2(id[k], title[k], nbins, vmin, vmax, nbins, vmin, vmax);
  	analysisManager->SetH2Activation(ig, false);}
  }
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
