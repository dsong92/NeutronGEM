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
/// \file PhysicsList.cc
/// \brief Implementation of the PhysicsList class
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PhysicsList.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "HadronElasticPhysicsHP.hh"

#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronPhysicsQGSP_BIC_AllHP.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4HadronPhysicsINCLXX.hh"

#include "G4IonElasticPhysics.hh"
#include "G4IonPhysicsXS.hh"
#include "G4IonPhysicsPHP.hh"
#include "G4IonINCLXXPhysics.hh"

#include "G4StoppingPhysics.hh"
#include "GammaNuclearPhysics.hh"

#include "ElectromagneticPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

#include "G4Neutron.hh"
#include "G4ProcessManager.hh"
#include "G4HadronicInteraction.hh"
//songadd
#include "G4RadioactiveDecay.hh"
#include "G4PhysicsListHelper.hh"
#include "G4GenericIon.hh"
#include "G4EmPenelopePhysics.hh" // for low EM physics
#include "G4EmLivermorePhysics.hh" // for low EM physics
#include "G4PhotoElectricEffect.hh"
#include "G4PenelopePhotoElectricModel.hh"
#include "G4LivermorePhotoElectricModel.hh"



#include "G4ComptonScattering.hh"
#include "G4PenelopeComptonModel.hh"

#include "G4GammaConversion.hh"
#include "G4PenelopeGammaConversionModel.hh"

#include "G4RayleighScattering.hh"
#include "G4PenelopeRayleighModel.hh"

// gamma

#include "G4PhotoElectricEffect.hh"
#include "G4PenelopePhotoElectricModel.hh"

#include "G4ComptonScattering.hh"
#include "G4PenelopeComptonModel.hh"

#include "G4GammaConversion.hh"
#include "G4PenelopeGammaConversionModel.hh"

#include "G4RayleighScattering.hh"
#include "G4PenelopeRayleighModel.hh"
#include "G4LivermorePhotoElectricModel.hh"

#include "G4ComptonScattering.hh"
#include "G4LivermoreComptonModel.hh"

#include "G4GammaConversion.hh"
#include "G4LivermoreGammaConversionModel.hh"

#include "G4RayleighScattering.hh"
#include "G4LivermoreRayleighModel.hh"



// e-

#include "G4eIonisation.hh"
#include "G4PenelopeIonisationModel.hh"
#include "G4UniversalFluctuation.hh"

#include "G4eBremsstrahlung.hh"
#include "G4PenelopeBremsstrahlungModel.hh"
// e+

#include "G4eplusAnnihilation.hh"
#include "G4PenelopeAnnihilationModel.hh"


// hadrons, ions

#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"
#include "G4hMultipleScattering.hh"
#include "G4NuclearStopping.hh"
//#include "G4NeutronCaptureAtRest.hh"
// deexcitation

#include "G4LossTableManager.hh"
#include "G4UAtomicDeexcitation.hh"


#include "G4BuilderType.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4PhysicsListHelper.hh"




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::PhysicsList()
:G4VModularPhysicsList(),
 fHadronElastic(nullptr), fHadronInelastic(nullptr),
 fIonElastic(nullptr), fIonInelastic(nullptr),
 fGammaNuclear(nullptr), fElectromagnetic(nullptr),
 fDecay(nullptr), fRadioactiveDecay(nullptr),
 //fLowEnergyEM(nullptr), fPhotoElectric(nullptr), fComptonScatter(nullptr), fRayleigh(nullptr), fLowEPhot(nullptr)
 fLowEnergyEM(nullptr) 
{
  G4int verb = 0;
  SetVerboseLevel(verb);
  
  //add new units
  //
  new G4UnitDefinition( "millielectronVolt", "meV", "Energy", 1.e-3*eV);
  new G4UnitDefinition( "mm2/g",  "mm2/g", "Surface/Mass", mm2/g);
  new G4UnitDefinition( "um2/mg", "um2/mg","Surface/Mass", um*um/mg);

  // Hadron Elastic scattering
  fHadronElastic = new HadronElasticPhysicsHP(verb);
  RegisterPhysics(fHadronElastic);
  
  // Hadron Inelastic Physics
  //fHadronInelastic = new G4HadronPhysicsFTFP_BERT_HP(verb);
  fHadronInelastic = new G4HadronPhysicsQGSP_BIC_HP(verb); // original
  //fHadronInelastic = new G4HadronPhysicsQGSP_BIC_AllHP(verb);
  ////fHadronInelastic = new G4HadronInelasticQBBC(verb);
  ////fHadronInelastic = new G4HadronPhysicsINCLXX(verb);
  RegisterPhysics(fHadronInelastic);


  // Ion Elastic Physics
  fIonElastic = new G4IonElasticPhysics(verb);
  RegisterPhysics(fIonElastic);

  // Ion Inelastic Physics
  fIonInelastic = new G4IonPhysicsXS(verb);
  ////fIonInelastic = new G4IonPhysicsPHP(verb)
  ////fIonInelastic = new G4IonINCLXXPhysics(verb);
  RegisterPhysics(fIonInelastic);

  // stopping Particles
  ///RegisterPhysics( new G4StoppingPhysics(verb));

  // Gamma-Nuclear Physics
  fGammaNuclear = new GammaNuclearPhysics("gamma");
  RegisterPhysics(fGammaNuclear);

  // EM physics
  //fElectromagnetic = new ElectromagneticPhysics();
  ////fElectromagnetic = new G4EmStandardPhysics();
  //RegisterPhysics(fElectromagnetic);

//------------ song add
  //fLowEnergyEM = new G4EmLivermorePhysics();
  fLowEnergyEM = new G4EmPenelopePhysics();
  RegisterPhysics(fLowEnergyEM);
 
  //fPhotoElectric = new G4PhotoElectricEffect();
  //RegisterPhysics(fPhotoElectric); 
 
  //fLowEPhot = new G4LivermorePhotoElectricModel();
  //RegisterPhysics(fLowEPhot); 
  

  /*fComptonScatter = new G4ComptonScattering();
  RegisterPhysics(fComptonScatter);

  fRayleigh = new G4RayleighScattering();
  RegisterPhysics(fRayleigh);*/
   
//------------

  // Decay
  fDecay = new G4DecayPhysics();
  RegisterPhysics(fDecay);

  // Radioactive decay
  fRadioactiveDecay = new G4RadioactiveDecayPhysics();
  RegisterPhysics(fRadioactiveDecay);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::~PhysicsList()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructProcess()
{
  //------------------- Penelope ------ song add
  G4PhysicsListHelper* list = G4PhysicsListHelper::GetPhysicsListHelper();

  // Add standard EM Processes

  auto particleIterator=GetParticleIterator();
  particleIterator->reset();
  while( (*particleIterator)() ){
    G4ParticleDefinition* particle = particleIterator->value();
    G4String particleName = particle->GetParticleName();

    //Applicability range for Penelope models
    //for higher energies, the Standard models are used   
    G4double highEnergyLimit = 1*GeV;

    if (particleName == "gamma") {
      // gamma         
/*
      G4PhotoElectricEffect* phot = new G4PhotoElectricEffect();
      G4PenelopePhotoElectricModel*
      photModel = new G4PenelopePhotoElectricModel();
      photModel->SetHighEnergyLimit(highEnergyLimit);
      phot->AddEmModel(0, photModel);
      list->RegisterProcess(phot, particle);

      G4ComptonScattering* compt = new G4ComptonScattering();
      G4PenelopeComptonModel*
      comptModel = new G4PenelopeComptonModel();
      comptModel->SetHighEnergyLimit(highEnergyLimit);
      compt->AddEmModel(0, comptModel);
      list->RegisterProcess(compt, particle);

      G4GammaConversion* conv = new G4GammaConversion();
      G4PenelopeGammaConversionModel*
      convModel = new G4PenelopeGammaConversionModel();
      convModel->SetHighEnergyLimit(highEnergyLimit);
      conv->AddEmModel(0, convModel);
      list->RegisterProcess(conv, particle);

      G4RayleighScattering* rayl = new G4RayleighScattering();
      G4PenelopeRayleighModel*
      raylModel = new G4PenelopeRayleighModel();
      raylModel->SetHighEnergyLimit(highEnergyLimit);
      rayl->AddEmModel(0, raylModel);
      list->RegisterProcess(rayl, particle);
*/
      G4PhotoElectricEffect* phot = new G4PhotoElectricEffect();
      G4LivermorePhotoElectricModel*
      photModel = new G4LivermorePhotoElectricModel();
      photModel->SetHighEnergyLimit(highEnergyLimit);
      phot->AddEmModel(0, photModel);
      list->RegisterProcess(phot, particle);

      G4ComptonScattering* compt = new G4ComptonScattering();
      G4LivermoreComptonModel*
      comptModel = new G4LivermoreComptonModel();
      comptModel->SetHighEnergyLimit(highEnergyLimit);
      compt->AddEmModel(0, comptModel);
      list->RegisterProcess(compt, particle);

      G4GammaConversion* conv = new G4GammaConversion();
      G4LivermoreGammaConversionModel*
      convModel = new G4LivermoreGammaConversionModel();
      convModel->SetHighEnergyLimit(highEnergyLimit);
      conv->AddEmModel(0, convModel);
      list->RegisterProcess(conv, particle);

      G4RayleighScattering* rayl = new G4RayleighScattering();
      G4LivermoreRayleighModel*
      raylModel = new G4LivermoreRayleighModel();
      raylModel->SetHighEnergyLimit(highEnergyLimit);
      rayl->AddEmModel(0, raylModel);
      list->RegisterProcess(rayl, particle);

      }
      else if (particleName == "e-") {
      //electron

      G4eIonisation* eIoni = new G4eIonisation();
      G4PenelopeIonisationModel*
      eIoniModel = new G4PenelopeIonisationModel();
      eIoniModel->SetHighEnergyLimit(highEnergyLimit);
      eIoni->AddEmModel(0, eIoniModel, new G4UniversalFluctuation() );
      list->RegisterProcess(eIoni, particle);

      G4eBremsstrahlung* eBrem = new G4eBremsstrahlung();
      G4PenelopeBremsstrahlungModel*
      eBremModel = new G4PenelopeBremsstrahlungModel();
      eBremModel->SetHighEnergyLimit(highEnergyLimit);
      eBrem->AddEmModel(0, eBremModel);
      list->RegisterProcess(eBrem, particle);
      }
      else if( particleName == "alpha" || particleName == "GenericIon" ) {
      list->RegisterProcess(new G4ionIonisation, particle);
      list->RegisterProcess(new G4hMultipleScattering, particle);
      list->RegisterProcess(new G4NuclearStopping, particle);
      //list->RegisterProcess(new G4NeutronCaptureAtRest, particle);
      //list->RegisterProcess(new G4HadronPhysicsQGSP_BIC_HP, particle);
      }
  }
  // Transportation first (mandatory)

  AddTransportation();

  // Physics constructors

  fHadronElastic->ConstructProcess();
  fHadronInelastic->ConstructProcess();
  fIonElastic->ConstructProcess();
  fIonInelastic->ConstructProcess();
  fGammaNuclear->ConstructProcess();
  //fElectromagnetic->ConstructProcess();
  fDecay->ConstructProcess();
  fRadioactiveDecay->ConstructProcess();
  //fLowEnergyEM->ConstructProcess(); //songad
  //fPhotoElectric->ConstructProcess();
  //fComptonScatter->ConstructProcess();
  //fRayleigh->ConstructProcess(); 
  //fRadioactiveDecay->SetICM(true);

  // example of GetHadronicModel (due to bug in QGSP_BIC_AllHP)
  //
  G4ProcessManager* pManager = G4Neutron::Neutron()->GetProcessManager();
  G4HadronicProcess* process
       = dynamic_cast<G4HadronicProcess*>(pManager->GetProcess("nCapture"));
  G4HadronicInteraction* model = process->GetHadronicModel("nRadCapture");
  if(model) model->SetMinEnergy(19.9*MeV);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::SetCuts()
{
  SetCutValue(0*mm, "proton");
  SetCutValue(10*km, "e-");
  //SetCutValue(0.01*mm, "e-");
  SetCutValue(10*km, "e+");
  //SetCutValue(0.01*mm, "e+");
  SetCutValue(10*km, "gamma");
  //SetCutValue(0.01*mm, "gamma");
  SetCutValue(0.0001*um, "neutron");
  SetCutValue(0.0001*um, "alpha");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
