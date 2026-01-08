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
//
/// \file B1/src/DetectorConstruction.cc
/// \brief Implementation of the B1::DetectorConstruction class

#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Trd.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "TrackerSD.hh"
#include "G4VisAttributes.hh"

namespace B1{
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{
    fDetectorMessenger = new DetectorMessenger(this);
    fNbOfDets = 4;
    Thickness = 6;
    Axisx = 110;
    fLogicDET = new G4LogicalVolume*[fNbOfDets];
}
DetectorConstruction::~DetectorConstruction()
{
  delete[] fLogicDET;
  delete fDetectorMessenger;
}
G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // Define materials
  DefineMaterials();

  // Define volumes
  return DefineVolumes();
}
G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* galatic=nist->FindOrBuildMaterial("G4_Galactic");
  G4double envlop_size = 400 * cm;
  G4double world_size = 1.2*400 * cm;

  G4bool checkOverlaps = true;

  auto solidWorld =
    new G4Box("World",  // its name
              world_size/2, world_size/2,world_size/2);  // its size

  auto logicWorld = new G4LogicalVolume(solidWorld,  // its solid
                                        galatic,  // its material
                                        "World");  // its name

  auto physWorld = new G4PVPlacement(nullptr,  // no rotation
                                     G4ThreeVector(),  // at (0,0,0)
                                     logicWorld,  // its logical volume
                                     "World",  // its name
                                     nullptr,  // its mother  volume
                                     false,  // no boolean operation
                                     0,  // copy number
                                     checkOverlaps);  // overlaps checking

  auto solidEnv = new G4Box("Envelope",  // its name
      0.5 * envlop_size, 0.5 * envlop_size, 0.5 * envlop_size);  // its size

  auto logicEnv = new G4LogicalVolume(solidEnv,  // its solid
                air,  // its material
                "Envelope");  // its name

  new G4PVPlacement(nullptr,  // no rotation
                    G4ThreeVector(),  // at (0,0,0)
                    logicEnv,  // its logical volume
                    "Envelope",  // its name
                    logicWorld,  // its mother  volume
                    false,  // no boolean operation
                    0,  // copy number
                    checkOverlaps);  // overlaps checking

  G4ThreeVector pos_det = G4ThreeVector(40 * cm, 0*cm, -10 * cm);
  // G4ThreeVector pos_det = G4ThreeVector(40 * cm, 22*cm, -28 * cm);
  // G4ThreeVector pos_det = G4ThreeVector(40 * cm, 42*cm, -44 * cm);
  // (2,-12) (22,-28) (42,-44)
  // 8 dets z:{+-28 +-64} y:{+-22 }
  auto solid_det = new G4Box("Detector", 10*cm,8*cm,8*cm);
  auto DetLV = new G4LogicalVolume(solid_det, air, "Detector");
  new G4PVPlacement(nullptr,pos_det,DetLV,"Detector",logicEnv,false,0,checkOverlaps);

 // 塑料
  G4ThreeVector pos_OBJ1 = G4ThreeVector(Axisx*cm+0.5*Thickness*cm, 0* cm, 0*cm);//塑料位置

  auto solid_OBJ1 = new G4Box("Shape2",0.5*Thickness*cm,60*cm,30*cm);//塑料尺寸

  fLogicOBJ1 = new G4LogicalVolume(solid_OBJ1,  // its solid
                                         fOBJ1Material,  // its material
                                         "Shape2");  // its name

  new G4PVPlacement(nullptr,  // no rotation
                    pos_OBJ1,  // at position
                    fLogicOBJ1,  // its logical volume
                    "Shape2",  // its name
                    logicEnv,  // its mother  volume
                    false,  // no boolean operation
                    0,  // copy number
                    checkOverlaps);  // overlaps checking

  G4VisAttributes worldVisAtt(G4Colour::White());
  G4VisAttributes detVisAtt(G4Colour::Yellow());
  G4VisAttributes OBJ1VisAtt(G4Colour::Red());
  G4VisAttributes OBJ2VisAtt(G4Colour::Blue());

  logicWorld->SetVisAttributes(worldVisAtt);
  DetLV->SetVisAttributes(worldVisAtt);
  fLogicOBJ1->SetVisAttributes(OBJ1VisAtt);

  // G4double DetXLength = 10*cm;
  // G4double DetYZLength = 4*cm;
  // G4double DetZpos = -12*cm;
  G4double Yposition[4] = {4*cm,4*cm,-4*cm,-4*cm};
  G4double Zposition[4] = {4*cm,-4*cm,4*cm,-4*cm};
  for (G4int copyNo = 0; copyNo < fNbOfDets;copyNo++)
  {
    // G4double Yposition = -(copyNo / 2) * DetYZLength+DetYZLength/2;
    // G4double Zposition = (copyNo % 2) * DetYZLength + DetZpos;
    auto DetS=new G4Box("Det_solid", 10*cm,4*cm,4*cm);
    fLogicDET[copyNo] = new G4LogicalVolume(DetS,fDETMaterial,"Det_LV");
    fLogicDET[copyNo]->SetVisAttributes(detVisAtt);
    new G4PVPlacement(nullptr, G4ThreeVector(0 * cm, Yposition[copyNo], Zposition[copyNo]), fLogicDET[copyNo], "Det_PV", DetLV, false, copyNo, checkOverlaps);
  }

    return physWorld;
}
void DetectorConstruction::ConstructSDandField()
{
  G4String DetSDname = "/DetSD";
  auto DetSD = new TrackerSD(DetSDname, "TrackerHitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(DetSD);
  // Setting trackerSD to all logical volumes with the same name
  // of "Chamber_LV".
  SetSensitiveDetector("Detector", DetSD, true);

  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
}
void DetectorConstruction::SetOBJ1Material(G4String materialName)
{
  G4NistManager* nist = G4NistManager::Instance();

  G4Material* pttoMaterial = nist->FindOrBuildMaterial(materialName);

  if (fOBJ1Material != pttoMaterial) {
    if (pttoMaterial) {
      fOBJ1Material = pttoMaterial;
      if (fLogicOBJ1) fLogicOBJ1->SetMaterial(fOBJ1Material);
      G4cout << G4endl << "----> The OBJ1 is made of " << materialName << G4endl;
    }
    else {
      G4cout << G4endl << "-->  WARNING from SetTargetMaterial : " << materialName << " not found"
             << G4endl;
    }
  }
}
void DetectorConstruction::SetOBJ2Material(G4String materialName)
{
  G4NistManager* nist = G4NistManager::Instance();

  G4Material* pttoMaterial = nist->FindOrBuildMaterial(materialName);

  if (fOBJ2Material != pttoMaterial) {
    if (pttoMaterial) {
      fOBJ2Material = pttoMaterial;
      if (fLogicOBJ2) fLogicOBJ2->SetMaterial(fOBJ2Material);
      G4cout << G4endl << "----> The OBJ2 is made of " << materialName << G4endl;
    }
    else {
      G4cout << G4endl << "-->  WARNING from SetTargetMaterial : " << materialName << " not found"
             << G4endl;
    }
  }
}
void DetectorConstruction::DefineMaterials()
{
  G4NistManager* nist = G4NistManager::Instance();
  G4double a, z, density;
  G4int ncomponents;
  G4String symbol;  
  G4double fracmass;

  G4Element* O   = new G4Element("Oxygen",symbol="O" , z= 8., a= 15.9994*g/mole);
  G4Element* Lu   = new G4Element("Lutetium",symbol="Lu" , z= 71, a= 174.9668*g/mole);
	G4Element* Y  = new G4Element("Yttrium"  ,symbol="Y" , z= 39, a=88.90584*g/mole);
	G4Element* Si   = new G4Element("Silicon",symbol="Si" , z= 14., a=28.085*g/mole);
	G4Element* Ce  = new G4Element("Cerium"  ,symbol="Ce" , z= 58, a= 140.116*g/mole);

  G4Material* LYSO = new G4Material("LYSO", density= 7.25* g/cm3, ncomponents=5);

	LYSO->AddElement(Lu, 73.856*perCent);
  LYSO->AddElement(Y, 1.975*perCent);
	LYSO->AddElement(Si, 6.240*perCent);
	LYSO->AddElement(O, 17.773*perCent);
	LYSO->AddElement(Ce, 0.156*perCent);

  fDETMaterial = LYSO;

  G4Element *ele_Fe = nist->FindOrBuildElement("Fe");
  G4Element *ele_C = nist->FindOrBuildElement("C");

  G4Material* Iron=new G4Material("Iron",density= 7.85 * g / cm3,ncomponents=2);
  Iron->AddElement(ele_Fe, fracmass=99.5*perCent);
  Iron->AddElement(ele_C,fracmass=0.5*perCent);

  fOBJ1Material = Iron;

  fOBJ2Material=nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
}
void DetectorConstruction::setThickness(G4float value)
{
  Thickness = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}
void DetectorConstruction::setAxisx(G4float value)
{
  Axisx = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}