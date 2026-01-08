#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
namespace B1{
DetectorMessenger::DetectorMessenger(DetectorConstruction * Det)
:fDetector(Det)
{ 
  fGparameter = new G4UIdirectory("/GeometryParameter/");
  fGparameter->SetGuidance("Geometry parameter control.");
  
  fThicknessCmd = new G4UIcmdWithADouble("/GeometryParameter/setThickness",this);
  fThicknessCmd->SetGuidance("Set thickness of the plate.");
  fThicknessCmd->SetParameterName("Thickness",false);
  fThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  fAxisxCmd = new G4UIcmdWithADouble("/GeometryParameter/setAxisx",this);
  fAxisxCmd->SetGuidance("Set x axis of the plate.");
  fAxisxCmd->SetParameterName("Axisx",false);
  fAxisxCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
  delete fThicknessCmd;
  delete fAxisxCmd;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == fThicknessCmd )
   { fDetector->setThickness(fThicknessCmd->GetNewDoubleValue(newValue));}

  if( command == fAxisxCmd )
   { fDetector->setAxisx(fAxisxCmd->GetNewDoubleValue(newValue));}


}
}