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
/// \file TrackingAction.cc
/// \brief Implementation of the TrackingAction class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TrackingAction.hh"

#include "Run.hh"
#include "EventAction.hh"
#include "HistoManager.hh"

#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4StepStatus.hh"
#include "G4ParticleTypes.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackingAction::TrackingAction(EventAction* event)
:G4UserTrackingAction(), fEventAction(event)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackingAction::PreUserTrackingAction(const G4Track* track)
{
 //count secondary particle
 if (track->GetTrackID() == 1) return;  
 G4String name   = track->GetDefinition()->GetParticleName();
 G4double energy = track->GetKineticEnergy();
 Run* run = static_cast<Run*>(
       G4RunManager::GetRunManager()->GetNonConstCurrentRun());
 run->ParticleCount(name,energy);

 G4int ih = 0; 
 const G4ParticleDefinition* particle = track->GetParticleDefinition();
 G4AnalysisManager* analysis = G4AnalysisManager::Instance();
 if (particle == G4Gamma::Gamma()){
	analysis->FillH1(6,energy);
	if(track->GetParentID()==1) analysis->FillH1(7,energy);
	if(track->GetParentID()==2) analysis->FillH1(8,energy);
	}
 if (particle == G4Alpha::Alpha())              ih = 5;
 if (ih > 0) analysis->FillH1(ih,energy); //original
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackingAction::PostUserTrackingAction(const G4Track* track)
{

 // keep only outgoing particle
 G4StepStatus status = track->GetStep()->GetPostStepPoint()->GetStepStatus();
 if(status != fWorldBoundary) return; 
 
 const G4ParticleDefinition* particle = track->GetParticleDefinition();
 G4String name   = particle->GetParticleName();
 G4double energy = track->GetKineticEnergy();
 fEventAction->AddEflow(energy); 

 Run* run = static_cast<Run*>(
              G4RunManager::GetRunManager()->GetNonConstCurrentRun());

 run->ParticleFlux(name,energy);            

 // histograms: enery flow


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

