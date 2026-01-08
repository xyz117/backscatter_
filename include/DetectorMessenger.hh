#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAString.hh"

class G4UIcmdWithAString;
class G4UIcmdWithADouble;
class G4UIdirectory;

namespace B1
{
class DetectorConstruction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorMessenger: public G4UImessenger
{
  public:
  
    DetectorMessenger(DetectorConstruction* );
   ~DetectorMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);

  private:
  
    DetectorConstruction*   fDetector;
   
    G4UIdirectory* fGparameter;
    G4UIcmdWithADouble* fThicknessCmd;
    G4UIcmdWithADouble* fAxisxCmd;
};
}
#endif

