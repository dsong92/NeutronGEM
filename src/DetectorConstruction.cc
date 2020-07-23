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
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

//-----------------------
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4GeometryManager.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"
//----------------------



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction(),
 fAbsorMaterial(0), fLAbsor(0), fContainMaterial(0), fLContain(0),
 fWorldMaterial(0), fPWorld(0), fDetectorMessenger(0), 
 physWorld(0), env_copper(0), env_gadolinium(0), world_mat(0),
 Argon(0), CO2(0), ArCO2(0)*/
DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction(),
 fAbsorMaterial(0), fLAbsor(0), fContainMaterial(0), fLContain(0),
 fWorldMaterial(0), fPWorld(0), fDetectorMessenger(0) 
{
  fAbsorRadius = 10*cm;
  fAbsorLength = 10*cm;
  fContainThickness = 10*cm;
  DefineMaterials();
  //SetAbsorMaterial  ("BeO");
  SetAbsorMaterial  ("G4_Gd");
  //SetContainMaterial("Stainless-Steel");
  fDetectorMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ delete fDetectorMessenger;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::DefineMaterials()
{
  G4int ncomponents, natoms;
  
  G4Element* Be = new G4Element("Beryllium","Be" ,  4.,  9.01*g/mole);
  G4Element* N  = new G4Element("Nitrogen" ,"N"  ,  7., 14.01*g/mole);
  G4Element* O  = new G4Element("Oxygen"   ,"O"  ,  8., 16.00*g/mole);
  
  G4Material* BeO = 
  new G4Material("BeO", 3.05*g/cm3, ncomponents=2);
  BeO->AddElement(Be, natoms=1);
  BeO->AddElement( O, natoms=1);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* DetectorConstruction::MaterialWithSingleIsotope( G4String name,
                           G4String symbol, G4double density, G4int Z, G4int A)
{
 // define a material from an isotope
 //
 G4int ncomponents;
 G4double abundance, massfraction;

 G4Isotope* isotope = new G4Isotope(symbol, Z, A);
 
 G4Element* element  = new G4Element(name, symbol, ncomponents=1);
 element->AddIsotope(isotope, abundance= 100.*perCent);
 
 G4Material* material = new G4Material(name, density, ncomponents=1);
 material->AddElement(element, massfraction=100.*perCent);

 return material;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::ConstructVolumes()
{
  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();


  //DefineMaterials() ;
  G4NistManager* nist = G4NistManager::Instance();

  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");
  G4Material *Argon = G4NistManager::Instance()->FindOrBuildMaterial("G4_Ar") ;
  G4Material *CO2 = G4NistManager::Instance()->FindOrBuildMaterial("G4_CARBON_DIOXIDE") ;

  // Ar:CO2 (70:30) @ STP conditions
  G4double mixtureDensity = (Argon->GetDensity() * 70/100.0 + CO2->GetDensity() * 30/100.0) ;
  G4double Temperature = 300.*kelvin;
  G4double pressure = 10.*atmosphere;
  G4Material *ArCO2 = new G4Material("Ar/CO2",mixtureDensity,2,kStateGas,Temperature, pressure);
  //G4Material *ArCO2 = new G4Material("Ar/CO2",mixtureDensity,2, kStateGas, 300*kelvin, 200.e3*pascal);
  ArCO2->AddMaterial(Argon, 0.7) ;
  ArCO2->AddMaterial(CO2, 0.3) ;

  G4Material* env_copper = nist->FindOrBuildMaterial("G4_Cu");
  G4Material* env_gadolinium = nist->FindOrBuildMaterial("G4_Gd");
  G4Material* env_boron = nist->FindOrBuildMaterial("G4_B");
  G4Material* env_cadmium = nist->FindOrBuildMaterial("G4_Cd");
  G4Material* env_paraffin = nist->FindOrBuildMaterial("G4_PARAFFIN");
  G4Material* env_kapton = nist->FindOrBuildMaterial("G4_KAPTON");



  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = true;

  //     
  // World
  //
  //G4double env_sizeXY = 100*cm, env_sizeZ = 100*cm;
  G4double env_sizeXY = 20*cm, env_sizeZ = 20*cm;
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        //world_mat,           //its material
                        vacuum,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      77,                     //copy number
                      checkOverlaps);        //overlaps checking

  // Envelope
  //  
  G4Box* solidEnv =
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size

  G4LogicalVolume* logicEnv =
    new G4LogicalVolume(solidEnv,            //its solid
                        //ArCO2,             //its material
                        vacuum,             //its material
                        "Envelope");         //its name

  G4VPhysicalVolume* physLogic =
    new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    1,                       //copy number
                    checkOverlaps);          //overlaps checking

  // GEM structure
  G4double chamberX =  10.*cm, chamberY = 10.*cm;
  //@@@@@@@@@@@@ Gadolinium setting
  G4double GdZ =  125.*um;
  G4double Gap_Drift = 5.*mm;
  G4ThreeVector pos1 = G4ThreeVector(0*cm, 0*cm, -125.*um);
  G4ThreeVector pos2 = G4ThreeVector(0*cm, 0*cm, -5.25*mm);
  //@@@@@@@@@@@@ Gd 3mm setting
  //G4double GdZ =  125.*um;
  //G4double Gap_Drift = 1.5*mm;
  //G4ThreeVector pos1 = G4ThreeVector(0*cm, 0*cm, -125.*um);
  //G4ThreeVector pos2 = G4ThreeVector(0*cm, 0*cm, -1.75*mm);
  //@@@@@@@@@@@@ Gd 10mm setting
  //G4double GdZ =  50.*um;
  //G4double Gap_Drift = 1.5*mm;
  //G4ThreeVector pos1 = G4ThreeVector(0*cm, 0*cm, -50.*um);
  //G4ThreeVector pos2 = G4ThreeVector(0*cm, 0*cm, -1.6*mm);
  //@@@@@@@@@@@@ Gd 20mm setting
  //G4double GdZ =  125.*um;
  //G4double Gap_Drift = 10*mm;
  //G4ThreeVector pos1 = G4ThreeVector(0*cm, 0*cm, -125.*um);
  //G4ThreeVector pos2 = G4ThreeVector(0*cm, 0*cm, -10.25*mm);
  //@@@@@@@@@@@@ Gd 30mm setting
  //G4double GdZ =  125.*um;
  //G4double Gap_Drift = 15*mm;
  //G4ThreeVector pos1 = G4ThreeVector(0*cm, 0*cm, -125.*um);
  //G4ThreeVector pos2 = G4ThreeVector(0*cm, 0*cm, -15.25*mm);
  //@@@@@@@@@@@@ Normal 3mm setting
  //G4double GdZ =  50.*um;
  //G4double Gap_Drift = 1.5*mm;
  //G4ThreeVector pos1 = G4ThreeVector(0*cm, 0*cm, -50.*um);
  //G4ThreeVector pos2 = G4ThreeVector(0*cm, 0*cm, -1.6*mm);
  //@@@@@@@@@@@@ Normal 10mm setting
  //G4double GdZ =  50.*um;
  //G4double Gap_Drift = 5.*mm;
  //G4ThreeVector pos1 = G4ThreeVector(0*cm, 0*cm, -50.*um);
  //G4ThreeVector pos2 = G4ThreeVector(0*cm, 0*cm, -5.1*mm);
   

  G4VSolid* Gadolinium =
    new G4Box("Gd", chamberX, chamberY, GdZ);

  G4VSolid* DriftGapS =
    new G4Box("DriftGapname", chamberX, chamberY, Gap_Drift);
  //G4VSolid* CopperGEM =
  //  new G4Box("CopperGEMname", chamberX, chamberY, GEM_Cu_Thickness);
 
  //****************************************************************
  //2020_06_16_boron simulation 
/* 
  G4ThreeVector pos3 = G4ThreeVector(0*cm, 0*cm, -50*mm); // -------> the position that cadimum plate from the chamber
 
  G4VSolid* box =
    new G4Box("ShieldingMaterial", chamberX, chamberY, 30*mm);
  G4VSolid* cylinder =
    new G4Tubs("EmptySpace", 0, chamberX*0.4, 30*mm , 0., 360.0*deg);
  G4VSolid* substract =
    new G4SubtractionSolid("box-cylinder",box, cylinder);

  G4LogicalVolume* PlateLogic =
    new G4LogicalVolume(substract,
		    	//env_cadmium,
		    	env_paraffin,
			"Shielding");
  G4VPhysicalVolume* physPlate =
    new G4PVPlacement(0,
		    pos3,
		    PlateLogic,
		    "HollowPlate",
		    logicEnv,
		    false,
		    4,
                    checkOverlaps);          //overlaps checking
*/
  //Until that, made hallow plate
  //****************************************************************



  G4LogicalVolume* GdLogic =
    new G4LogicalVolume(Gadolinium,         //its solid
                        //env_gadolinium,          //its material ---------> Gadolnium
                        env_boron,          //its material -------> BORON
                        //env_kapton,          //its material
                        "logicGd");           //its name

  G4LogicalVolume* DriftLogic =
    new G4LogicalVolume(DriftGapS,         //its solid
                        ArCO2,          //its material
                        //vacuum,          //its material
                        //world_mat,          //its material
                        "logicDriftVol");           //its name

    //G4LogicalVolume* CuGEMLogic =
  //  new G4LogicalVolume(CopperGEM,         //its solid
  //                      env_copper,          //its material
  //                      "logicCuVol");           //its name

  G4VPhysicalVolume* physGd =
     new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    GdLogic,             //its logical volume
                    "gadolinium",                //its name
                    //"boron",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    2,                       //copy number
                    checkOverlaps);          //overlaps checking

  G4VPhysicalVolume* physDrift =
     new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    DriftLogic,             //its logical volume
                    "DriftGap",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    3,                       //copy number
                    checkOverlaps);          //overlaps checking

  return physWorld;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::PrintParameters()
{
/*
 G4cout << "\n The Absorber  is a cylinder of " << fAbsorMaterial->GetName()
        << "  radius = " << G4BestUnit(fAbsorRadius,"Length")
        << "  length = " << G4BestUnit(fAbsorLength,"Length") << G4endl;
 G4cout << " The Container is a cylinder of " << fContainMaterial->GetName()
        << "  thickness = " << G4BestUnit(fContainThickness,"Length") << G4endl;
 
 G4cout << "\n" << fAbsorMaterial << G4endl;
 G4cout << "\n" << fContainMaterial << G4endl;
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetAbsorMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =
     G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);   
  
  if (pttoMaterial) { 
    fAbsorMaterial = pttoMaterial;
    if(fLAbsor) { fLAbsor->SetMaterial(fAbsorMaterial); }
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  } else {
    G4cout << "\n--> warning from DetectorConstruction::SetAbsorMaterial : "
           << materialChoice << " not found" << G4endl;
  }              
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetContainMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =
     G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);   
  
  if (pttoMaterial) { 
    fContainMaterial = pttoMaterial;
    if(fLContain) { fLContain->SetMaterial(fContainMaterial); }
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  } else {
    G4cout << "\n--> warning from DetectorConstruction::SetContainMaterial : "
           << materialChoice << " not found" << G4endl;
  }              
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetAbsorRadius(G4double value)
{
  fAbsorRadius = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetAbsorLength(G4double value)
{
  fAbsorLength = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetContainThickness(G4double value)
{
  fContainThickness = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

