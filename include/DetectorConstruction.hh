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
/// \file B1/include/DetectorConstruction.hh
/// \brief Definition of the B1::DetectorConstruction class

#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "G4Threading.hh"
#include "globals.hh"
#include "G4NistManager.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;


/// Detector construction class to define materials and geometry.
namespace B1{
class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction() ;
    virtual ~DetectorConstruction() ;

    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;
    void SetDETMaterial(G4String);
    void SetOBJ1Material(G4String);
    void SetOBJ2Material(G4String);

    void setThickness(G4float);
    void setAxisx(G4float);
    G4float GetThickness() { return Thickness; };
    G4float GetAxisx() { return Axisx; };
    G4float Thickness, Axisx;

    G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; };

  protected:
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
    G4int fNbOfDets = 0;
    G4LogicalVolume **fLogicDET = nullptr;
    G4LogicalVolume* fLogicOBJ1 = nullptr;
    G4LogicalVolume* fLogicOBJ2 = nullptr;

    G4Material* fDETMaterial = nullptr;
    G4Material* fOBJ1Material = nullptr;
    G4Material* fOBJ2Material = nullptr;

    G4LogicalVolume* fScoringVolume = nullptr;
    DetectorMessenger* fDetectorMessenger;
};


}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
