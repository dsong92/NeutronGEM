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

  // count processes
  if(aStep->GetTrack()->GetTrackID() == 1 ) return; // for reject neutron beam track  ** origial line _1
  if(aStep->GetTrack()->GetParentID()!= 1 ) return; // for accept only secondary particle from neutron beam ** original line_2

  const G4StepPoint* endPoint = aStep->GetPostStepPoint(); //original
  const G4VProcess* process   = endPoint->GetProcessDefinedStep(); //original

  Run* run = static_cast<Run*>(
        G4RunManager::GetRunManager()->GetNonConstCurrentRun()); //original
  run->CountProcesses(process);
  
  G4String PreStepVol = aStep->GetPreStepPoint()->GetTouchable()->GetVolume()->GetName();
  if(PreStepVol=="World") return; // If PreStepPoint is World then track is disappeared so volume of poststep is null
  G4String PostStepVol = aStep->GetPostStepPoint()->GetTouchable()->GetVolume()->GetName();

  const G4ParticleDefinition* particle = aStep->GetTrack()->GetParticleDefinition();
 
  /*G4TouchableHandle touchable = aStep->GetPreStepPoint()->GetTouchableHandle();
  G4int copyNo = touchable->GetVolume()->GetCopyNo();
  if(copyNo==3){};
  
  G4double edepStep = aStep->GetTotalEnergyDeposit();
  if(edepStep <= 0.) return;
  fEventAction->AddEdep(edepStep);
  
  if(aStep->GetTrack()->GetVolume()->GetName()=="gadolinium" && aStep->GetTrack()->GetNextVolume()->GetName() =="DriftGap" ){
	  run->CountProcesses(process);
  }*/

  G4int ih = 0; 
  G4String type   = particle->GetParticleType();      
  G4String name   = particle->GetParticleName();
  G4double charge = particle->GetPDGCharge();
  G4double energy = aStep->GetPostStepPoint()->GetKineticEnergy(); // For getting kinetic energy

  //G4cout<<"PreStep = "<<PreStepVol<<" || PostStepVol = "<<PostStepVol<<" || energy = "<<energy<<" || name = "<<name<<"|| process = "<<process->GetProcessName()<<G4endl;
  G4double edepStep=0.;
  if(PreStepVol =="DriftGap"&&PostStepVol=="DriftGap") edepStep = aStep->GetTotalEnergyDeposit();

  if(PreStepVol  != "gadolinium") return;
  if(PostStepVol != "DriftGap")   return;

  if (charge > 3.)  ih = 10;
  else if (particle == G4Gamma::Gamma())       ih = 4;
  else if (particle == G4Electron::Electron()) ih = 5;
  else if (particle == G4Positron::Positron()) ih = 5;
  else if (particle == G4Neutron::Neutron())   ih = 6;
  else if (particle == G4Alpha::Alpha())       ih = 9;
  if (ih > 0) analysis->FillH1(ih,energy); //original

  if(edepStep <= 0.) return;
  fEventAction->AddEdep(edepStep);
  //run->CountProcesses(process);
 
  //G4double energy = aStep->GetPostStepPoint()->GetKineticEnergy(); // For getting kinetic energy
  //G4double energy = aStep->GetTotalEnergyDeposit(); // for getting edep
  //G4double energy = aStep->GetPreStepPoint()->GetKineticEnergy();

  //@@@@@@@@@@@@@@@@ use only stepping action
 
  //G4String PreStepVol = aStep->GetPreStepPoint()->GetTouchable()->GetVolume()->GetName();
  //if(PreStepVol=="World") return; // because, If PreStepPoint is World then track is disappeared so volume of poststep is null
 
  //G4String PostStepVol = aStep->GetPostStepPoint()->GetTouchable()->GetVolume()->GetName();

  //if(aStep->GetTrack()->GetVolume()->GetName()=="boron" && aStep->GetTrack()->GetNextVolume()->GetName() =="DriftGap" ){
  /*if(PreStepVol=="boron"){
         if (charge > 3.)  ih = 10;
         else if (particle == G4Gamma::Gamma())       ih = 4;
         else if (particle == G4Electron::Electron()) ih = 5;
         //else if (particle == G4Positron::Positron()) ih = 5;
         else if (particle == G4Neutron::Neutron())   ih = 6;
         else if (particle == G4Proton::Proton())     ih = 7;
         else if (particle == G4Deuteron::Deuteron()) ih = 8;
         else if (particle == G4Alpha::Alpha())       ih = 9;
         else if (type == "nucleus")                  ih = 10;
         else if (type == "baryon")                   ih = 11;
         else if (type == "meson")                    ih = 12;
         else if (type == "lepton")                   ih = 13;
         if (ih > 0) analysis->FillH1(ih,energy); //original
  }
 */
/*
  G4String PostStepVol = aStep->GetPostStepPoint()->GetTouchable()->GetVolume()->GetName();
  if(aStep->GetTrack()->GetVolume()->GetName()=="Envelope"){ // new
	  //if(PostStepVol == "gadolinium"  ){
	  if(aStep->GetTrack()->GetNextVolume()->GetName()=="DriftGap" ){
		  G4double energy = aStep->GetPostStepPoint()->GetKineticEnergy();
		  fEventAction->AddEflow(energy);  
		  G4int ih = 0; 
		  G4String type   = particle->GetParticleType();      
		  G4double charge = particle->GetPDGCharge();
		  if (charge > 3.)  ih = 10; 
		  else if (particle == G4Gamma::Gamma())       ih = 4; 
		  else if (particle == G4Electron::Electron()) ih = 5; 
		  //else if (particle == G4Positron::Positron()) ih = 5;
		  else if (particle == G4Neutron::Neutron())   ih = 6;
		  else if (particle == G4Proton::Proton())     ih = 7;
		  else if (particle == G4Deuteron::Deuteron()) ih = 8;
		  else if (particle == G4Alpha::Alpha())       ih = 9;
		  else if (type == "nucleus")                  ih = 10;
		  else if (type == "baryon")                   ih = 11;
		  else if (type == "meson")                    ih = 12;
		  else if (type == "lepton")                   ih = 13;
		  //if (ih > 0) analysis->FillH1(ih,energy); //original
	  }
  }
*/

/*
  G4String PostStepVol = aStep->GetPostStepPoint()->GetTouchable()->GetVolume()->GetName();
  if(PreStepVol  != "gadolinium") return;
  if(PostStepVol != "DriftGap"  ) return;

  //G4double energy = aStep->GetPostStepPoint()->GetKineticEnergy();
  //fEventAction->AddEflow(energy);  

  G4int ih = 0; 
  G4String type   = particle->GetParticleType();      
  G4double charge = particle->GetPDGCharge();

  if (charge > 3.)  ih = 10; 
  else if (particle == G4Gamma::Gamma())       ih = 4; 
  else if (particle == G4Electron::Electron()) ih = 5; 
  //else if (particle == G4Positron::Positron()) ih = 5;
  else if (particle == G4Neutron::Neutron())   ih = 6;
  else if (particle == G4Proton::Proton())     ih = 7;
  else if (particle == G4Deuteron::Deuteron()) ih = 8;
  else if (particle == G4Alpha::Alpha())       ih = 9;
  else if (type == "nucleus")                  ih = 10;
  else if (type == "baryon")                   ih = 11;
  else if (type == "meson")                    ih = 12;
  else if (type == "lepton")                   ih = 13;
  if (ih > 0) analysis->FillH1(ih,energy); //original
*/

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
