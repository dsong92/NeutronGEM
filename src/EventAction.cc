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
 fTotalEnergyDeposit(0.), fTotalEnergyFlow(0.), fTotalLength(0.), fTotalEnergyDepositAll(0.),fTotalEnergyDepositGamma(0.),fTotalEnergyDepositEl(0.)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
  fTotalEnergyDeposit = 0.;
  fTotalEnergyFlow = 0.; 
  fTotalLength = 0.; //song add
  fTotalEnergyDepositAll = 0.; //song add
  fTotalEnergyDepositGamma = 0.; //song add
  fTotalEnergyDepositEl = 0.; //song add
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventAction::AddEdep(G4double Edep)
{
  fTotalEnergyDeposit += Edep;
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
  fTotalEnergyDepositAll += EdepAll;
}

void EventAction::AddEdepGamma(G4double EdepGamma)
{
  fTotalEnergyDepositGamma += EdepGamma;
}

void EventAction::AddEdepEl(G4double EdepEl)
{
  fTotalEnergyDepositEl += EdepEl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*)//original
{
  Run* run = static_cast<Run*>(
             G4RunManager::GetRunManager()->GetNonConstCurrentRun());
             
  //run->AddEdep(fTotalEnergyDeposit);
  //run->AddLength(fTotalLength);
  //run->AddEdepAll(fTotalEnergyDepositAll);
  //run->AddEflow(fTotalEnergyFlow);
  
  if(fTotalEnergyDepositAll != 0.) G4AnalysisManager::Instance()->FillH1(1,fTotalEnergyDepositAll);
  if(fTotalEnergyDeposit != 0. ) G4AnalysisManager::Instance()->FillH1(2,fTotalEnergyDeposit);
  if(fTotalEnergyDepositGamma != 0.) G4AnalysisManager::Instance()->FillH1(3,fTotalEnergyDepositGamma);
  if(fTotalEnergyDepositEl != 0.) G4AnalysisManager::Instance()->FillH1(4,fTotalEnergyDepositEl);
  //if(fTotalEnergyFlow != 0. ) G4AnalysisManager::Instance()->FillH1(3,fTotalEnergyFlow);
  //if(fTotalEnergyDepositGamma != 0.) G4cout<<"EndOfEvtAction ->"<<fTotalEnergyDepositGamma<<G4endl;
  if(fTotalLength!=0.) G4AnalysisManager::Instance()->FillH1(13,fTotalLength); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

