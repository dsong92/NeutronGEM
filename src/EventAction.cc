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
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "EventAction.hh"

#include "Run.hh"
#include "HistoManager.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
:G4UserEventAction(),
 fTotalEnergyDeposit(0.), fTotalEnergyFlow(0.), fTotalLength(0.), fTotalEnergyDepositAll(0.),fTotalEnergyDepositGamma(0.),fTotalEnergyDepositEl(0.),fTotalEnergyDepositLi(0.)
 ,fTID(-1), fPID(-1.), fEnergy(-999.), fDepth(-999.), iter_alpha(0.), iter_gamma(0.), iter_electron(0.)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
  fTotalEnergyDeposit = 0.;
  fTotalEnergyFlow = 0.; 
  fTotalLength = 0.;
  fTotalEnergyDepositAll = 0.;
  fTotalEnergyDepositGamma = 0.;
  fTotalEnergyDepositEl = 0.;
  fTotalEnergyDepositLi = 0.;
  fTID = -1;
  fPID = -1;
  fEnergy = -999.;
  fDepth = -999.;
  iter_alpha = 0;
  iter_gamma = 0;
  iter_electron = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventAction::FillAlpha(G4double energy, G4int TID, G4int PID, G4double Depth)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  fEnergy = energy;
  fTID = TID; 
  fPID = PID;
  if(Depth != 0.) fDepth = Depth;
  analysisManager->FillNtupleDColumn(5, fEnergy);
  analysisManager->FillNtupleDColumn(8, fDepth);
  analysisManager->FillNtupleIColumn(9, fTID);
  analysisManager->FillNtupleIColumn(10,fPID);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventAction::FillLithium(G4double energy, G4int TID, G4int PID, G4double Depth)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  fEnergy = energy;
  fTID = TID; 
  fPID = PID;
  if(Depth != 0.) fDepth = Depth;
  analysisManager->FillNtupleIColumn(24, fTID);
  analysisManager->FillNtupleIColumn(25, fPID);
  analysisManager->FillNtupleDColumn(26, fDepth);
  analysisManager->FillNtupleDColumn(27, fEnergy);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventAction::FillGamma(G4double energy, G4int TID, G4int PID)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  fEnergy = energy;
  fTID = TID; 
  fPID = PID;
  analysisManager->FillNtupleDColumn(11, fEnergy);
  analysisManager->FillNtupleIColumn(12, fTID);
  analysisManager->FillNtupleIColumn(13, fPID);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventAction::FillElectron(G4double energy, G4int TID, G4int PID)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  fEnergy = energy;
  fTID = TID;
  fPID = PID;
  analysisManager->FillNtupleDColumn(14, fEnergy);
  analysisManager->FillNtupleIColumn(17, fTID);
  analysisManager->FillNtupleIColumn(18, fPID);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventAction::AddEdep(G4double Edep)
{
  if( Edep > 0 ) fTotalEnergyDeposit += Edep;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventAction::AddEflow(G4double Eflow) 
{ 
  fTotalEnergyFlow += Eflow;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// song add
void EventAction::AddLength(G4double Length)
{
  fTotalLength += Length;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// song add
void EventAction::AddEdepAll(G4double EdepAll)
{
  if( EdepAll > 0) fTotalEnergyDepositAll += EdepAll;
}

void EventAction::AddEdepGamma(G4double EdepGamma)
{
  if( EdepGamma > 0 ) fTotalEnergyDepositGamma += EdepGamma;
}

void EventAction::AddEdepEl(G4double EdepEl)
{
  if( EdepEl > 0 ) fTotalEnergyDepositEl += EdepEl;
}

void EventAction::AddEdepLi(G4double EdepLi)
{
  if( EdepLi > 0 ) fTotalEnergyDepositLi += EdepLi;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)//original
{
  //Run* run = static_cast<Run*>(
  //           G4RunManager::GetRunManager()->GetNonConstCurrentRun());

  G4double eventID = event->GetEventID();
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager->FillH1(0, fTotalEnergyDepositAll);
  analysisManager->FillH1(1, fTotalEnergyDeposit);

  analysisManager->FillNtupleDColumn(0, eventID);
  analysisManager->FillNtupleDColumn(1, fTotalEnergyDepositAll);
  analysisManager->FillNtupleDColumn(2, fTotalEnergyDeposit);
  analysisManager->FillNtupleDColumn(3, fTotalEnergyDepositGamma);
  analysisManager->FillNtupleDColumn(4, fTotalEnergyDepositEl);
  analysisManager->FillNtupleDColumn(19, fTotalLength);
  analysisManager->FillNtupleDColumn(23, fTotalEnergyDepositLi);
  analysisManager->AddNtupleRow(); 
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

