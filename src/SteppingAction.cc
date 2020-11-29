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
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SteppingAction.hh"
#include "Run.hh"
#include "EventAction.hh"
#include "HistoManager.hh"

#include "G4RunManager.hh"

#include "TrackingAction.hh"

#include "G4StepStatus.hh"
#include "G4ParticleTypes.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
                           
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* event)
: G4UserSteppingAction(), fEventAction(event)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  G4AnalysisManager* analysis = G4AnalysisManager::Instance(); // for Fill(ih,energy)
  if(aStep->GetTrack()->GetVolume()->GetName()=="Envelope" && aStep->GetTrack()->GetNextVolume()->GetName() =="DriftGap"){
  	if(aStep->GetTrack()->GetParentID()==0 && aStep->GetTrack()->GetTrackID()==1){
  	  analysis->FillH2(0,aStep->GetTrack()->GetPosition().x(),aStep->GetTrack()->GetPosition().y());
  	}
  }
  
  if(aStep->GetPreStepPoint()->GetTouchable()->GetVolume()->GetName()=="boron" && aStep->GetPostStepPoint()->GetTouchable()->GetVolume()->GetName() =="boron"){
  	if(aStep->GetTrack()->GetParentID()==0 && aStep->GetTrack()->GetTrackID()==1){
  	  analysis->FillH2(4,aStep->GetPostStepPoint()->GetPosition().z(),aStep->GetPreStepPoint()->GetKineticEnergy());
  	}
  }

  if(aStep->GetTrack()->GetParticleDefinition()->GetParticleName()=="alpha" && aStep->GetTrack()->GetCurrentStepNumber()==1){
        analysis->FillH2(5,aStep->GetPostStepPoint()->GetPosition().z(),aStep->GetPreStepPoint()->GetKineticEnergy());
	analysis->FillH1(12,aStep->GetPostStepPoint()->GetPosition().z());
    }

  // count processes
  const G4StepPoint* endPoint = aStep->GetPostStepPoint(); //original
  const G4VProcess* process   = endPoint->GetProcessDefinedStep(); //original
  Run* run = static_cast<Run*>(
        G4RunManager::GetRunManager()->GetNonConstCurrentRun()); //original
  run->CountProcesses(process);

  //if(aStep->GetTrack()->GetTrackID() == 1 ) return; // for reject neutron beam track  ** origial line _1
  if(aStep->GetTrack()->GetParentID() == 0 ) return; // for accept only secondary particle from neutron beam ** original line_2
  
  G4String PreStepVol = aStep->GetPreStepPoint()->GetTouchable()->GetVolume()->GetName();
  if(PreStepVol=="World") return; // If PreStepPoint is World then track is disappeared so volume of poststep is null
  G4String PostStepVol = aStep->GetPostStepPoint()->GetTouchable()->GetVolume()->GetName();

  const G4ParticleDefinition* particle = aStep->GetTrack()->GetParticleDefinition();
  //G4double charge = particle->GetPDGCharge();
  G4double energy = aStep->GetPostStepPoint()->GetKineticEnergy(); // For getting kinetic energy

  if(PreStepVol =="boron"&&PostStepVol=="DriftGap"){
	//fEventAction->AddEdepAll(aStep->GetTotalEnergyDeposit());
	if(particle->GetParticleName()=="alpha"){
		//fEventAction->AddEdep(aStep->GetTotalEnergyDeposit());	
  		//analysis->FillH1(9,aStep->GetPreStepPoint()->GetKineticEnergy());
  		analysis->FillH1(10,aStep->GetPreStepPoint()->GetKineticEnergy());
  		analysis->FillH1(11,aStep->GetPostStepPoint()->GetKineticEnergy());
	}
	if(particle->GetParticleName()=="e-"){
  		analysis->FillH1(9,aStep->GetPostStepPoint()->GetKineticEnergy());
	}
  }
  
  G4ThreeVector Position_Alpha;
  if(PreStepVol =="DriftGap"&&PostStepVol=="DriftGap"){
	fEventAction->AddEdepAll(aStep->GetTotalEnergyDeposit());
	if(particle->GetParticleName()=="alpha"){
		fEventAction->AddEdep(aStep->GetTotalEnergyDeposit());
		fEventAction->AddLength(aStep->GetStepLength());
		Position_Alpha = aStep->GetPostStepPoint()->GetPosition();
		analysis->FillH2(1,Position_Alpha.x(), Position_Alpha.y());
		analysis->FillH2(2,Position_Alpha.x(), Position_Alpha.z());
		analysis->FillH2(3,Position_Alpha.y(), Position_Alpha.z());
	}
	if(particle->GetParticleName()=="gamma"){
		fEventAction->AddEdepGamma(aStep->GetTotalEnergyDeposit());
	}
	if(particle->GetParticleName()=="e-"){
		fEventAction->AddEdepEl(aStep->GetTotalEnergyDeposit());
	}
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
