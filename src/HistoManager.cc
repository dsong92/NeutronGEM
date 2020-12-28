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
#include "EventAction.hh"
//#include "G4TNtupleManager.hh" // for create vector ntuple
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
/*  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile(fFileName);
 
  //EventAction* fEventAction;  

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
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
