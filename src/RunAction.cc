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
/// \file RunAction.cc
/// \brief Implementation of the RunAction class
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "RunAction.hh"
#include "Run.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "HistoManager.hh"

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "EventAction.hh"
#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(DetectorConstruction* det, PrimaryGeneratorAction* prim)
  : G4UserRunAction(),
    fDetector(det), fPrimary(prim), fRun(0), fHistoManager(0)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetNtupleDirectoryName("Ntuple");
  
  // Book predefined histograms
  //fHistoManager = new HistoManager(); //original
  //
  //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile("NeutronSource");

  analysisManager->CreateH1("EdepAll","Edep from All particle", 100, 0., 3);
  analysisManager->CreateH1("EdepAlpha","Edep from Alpha", 100, 0., 3);
  analysisManager->CreateH1("NCDepth","Neutron capture Depth", 100, -1., 0.1);

  analysisManager->CreateNtuple("event", "event");
  analysisManager->CreateNtupleDColumn("eventID");           // id 0
  analysisManager->CreateNtupleDColumn("EdepAll");           // id 1
  analysisManager->CreateNtupleDColumn("EdepAlpha");         // id 2
  analysisManager->CreateNtupleDColumn("EdepGamma");         // id 3
  analysisManager->CreateNtupleDColumn("EdepElectron");      // id 4
  analysisManager->CreateNtupleDColumn("gen_Ekin_Alpha");    // id 5
  analysisManager->CreateNtupleDColumn("PreB_Ekin_Alpha");   // id 6
  analysisManager->CreateNtupleDColumn("PostB_Ekin_Alpha");  // id 7
  analysisManager->CreateNtupleDColumn("BNCap_depth_Alpha");     // id 8
  analysisManager->CreateNtupleIColumn("TID_AlPha");         // id 9
  analysisManager->CreateNtupleIColumn("PID_Alpha");         // id 10
  analysisManager->CreateNtupleDColumn("EofGamma");      // id 11
  analysisManager->CreateNtupleIColumn("TID_Gamma");         // id 12
  analysisManager->CreateNtupleIColumn("PID_Gamma");         // id 13
  analysisManager->CreateNtupleDColumn("gen_Ekin_El");       // id 14
  analysisManager->CreateNtupleDColumn("PreB_Ekin_El");       // id 15
  analysisManager->CreateNtupleDColumn("PostB_Ekin_El");       // id 16
  analysisManager->CreateNtupleIColumn("TID_Electron");      // id 17
  analysisManager->CreateNtupleIColumn("PID_Electron");      // id 18
  analysisManager->CreateNtupleDColumn("DriftLength_Alpha");     // id 19
  analysisManager->CreateNtupleDColumn("BNCap_depth");   //id 20 
  analysisManager->CreateNtupleDColumn("PreB_Ekin_Li");   //id 21 
  analysisManager->CreateNtupleDColumn("PostB_Ekin_Li");    //id 22 
  analysisManager->CreateNtupleDColumn("EdepLi");    //id 23 
  analysisManager->CreateNtupleIColumn("TID_Li");    //id 24 
  analysisManager->CreateNtupleIColumn("PID_Li");    //id 25 
  analysisManager->CreateNtupleDColumn("gen_Li_position");    //id 26
  analysisManager->CreateNtupleDColumn("gen_Ekin_Li");    //id 27
  analysisManager->FinishNtuple();
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
 delete fHistoManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* RunAction::GenerateRun()
{ 
  fRun = new Run(fDetector); 
  return fRun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{ 
  // show Rndm status
  if (isMaster) G4Random::showEngineStatus();
  
  // keep run condition
  if (fPrimary) { 
    G4ParticleDefinition* particle 
      = fPrimary->GetParticleGun()->GetParticleDefinition();
    G4double energy = fPrimary->GetParticleGun()->GetParticleEnergy();
    fRun->SetPrimary(particle, energy);
  }
             
  //histograms
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->IsActive() ) {
    analysisManager->OpenFile();
  }  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run*)
{
  if (isMaster) fRun->EndOfRun();    
  
  //save histograms      
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  /*if ( analysisManager->IsActive() ) {
    analysisManager->Write();
    analysisManager->CloseFile();
  }*/
     
  analysisManager->Write();
  analysisManager->CloseFile();
 
  // show Rndm status
  if (isMaster) G4Random::showEngineStatus();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
