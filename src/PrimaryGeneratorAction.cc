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
/// \file B1/src/PrimaryGeneratorAction.cc
/// \brief Implementation of the B1::PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName = "gamma");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
  fParticleGun->SetParticleEnergy(6. * MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  // this function is called at the begining of ecah event
  //

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get Envelope volume
  // from G4LogicalVolumeStore.
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1, 0., 0.));
  G4double energy[230] = {0.001, 0.002, 0.003, 0.004, 0.005, 0.006, 0.007, 0.008, 0.009, 0.01, 0.011, 0.012, 0.013, 0.014, 0.015, 0.016, 0.017, 0.018, 0.019, 0.02, 0.021, 0.022, 0.023, 0.024, 0.025, 0.026, 0.027, 0.028, 0.029, 0.03, 0.031, 0.032, 0.033, 0.034, 0.035, 0.036, 0.037, 0.038, 0.039, 0.04, 0.041, 0.042, 0.043, 0.044, 0.045, 0.046, 0.047, 0.048, 0.049, 0.05, 0.051, 0.052, 0.053, 0.054, 0.055, 0.056, 0.057, 0.058, 0.059, 0.06, 0.061, 0.062, 0.063, 0.064, 0.065, 0.066, 0.067, 0.068, 0.069, 0.07, 0.071, 0.072, 0.073, 0.074, 0.075, 0.076, 0.077, 0.078, 0.079, 0.08, 0.081, 0.082, 0.083, 0.084, 0.085, 0.086, 0.087, 0.088, 0.089, 0.09, 0.091, 0.092, 0.093, 0.094, 0.095, 0.096, 0.097, 0.098, 0.099, 0.1, 0.101, 0.102, 0.103, 0.104, 0.105, 0.106, 0.107, 0.108, 0.109, 0.11, 0.111, 0.112, 0.113, 0.114, 0.115, 0.116, 0.117, 0.118, 0.119, 0.12, 0.121, 0.122, 0.123, 0.124, 0.125, 0.126, 0.127, 0.128, 0.129, 0.13, 0.131, 0.132, 0.133, 0.134, 0.135, 0.136, 0.137, 0.138, 0.139, 0.14, 0.141, 0.142, 0.143, 0.144, 0.145, 0.146, 0.147, 0.148, 0.149, 0.15, 0.151, 0.152, 0.153, 0.154, 0.155, 0.156, 0.157, 0.158, 0.159, 0.16, 0.161, 0.162, 0.163, 0.164, 0.165, 0.166, 0.167, 0.168, 0.169, 0.17, 0.171, 0.172, 0.173, 0.174, 0.175, 0.176, 0.177, 0.178, 0.179, 0.18, 0.181, 0.182, 0.183, 0.184, 0.185, 0.186, 0.187, 0.188, 0.189, 0.19, 0.191, 0.192, 0.193, 0.194, 0.195, 0.196, 0.197, 0.198, 0.199, 0.2, 0.201, 0.202, 0.203, 0.204, 0.205, 0.206, 0.207, 0.208, 0.209, 0.21, 0.211, 0.212, 0.213, 0.214, 0.215, 0.216, 0.217, 0.218, 0.219, 0.22, 0.221, 0.222, 0.223, 0.224, 0.225};

  G4double prob[230] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 3.808008792202557e-06, 3.808008792202557e-06, 0.0, 3.808008792202557e-06, 0.0, 0.0, 0.0, 7.606022810672299e-06, 1.1394042055409226e-05, 2.278808411081845e-05, 5.707015801437429e-05, 9.125228418060196e-05, 7.6060228106723e-05, 0.013892735488613, 0.0186902268803642, 0.0180905404563953, 0.0182904359310516, 0.0180905404563953, 0.0175908017697545, 0.0168911676084575, 0.0167912198711293, 0.016591324396473, 0.0159916379725041, 0.0163914289218167, 0.0154918992858634, 0.0153919515485352, 0.01459236964991, 0.0147922651245663, 0.013892735488613, 0.0135928922766285, 0.013293049064644, 0.0133929968019722, 0.0129932058526596, 0.0128932581153314, 0.0124934671660188, 0.0501737641387318, 0.078758817014583, 0.0114939897927373, 0.0115939375300655, 0.0109942511060966, 0.0107943556314403, 0.0106944078941121, 0.0102946169447995, 0.0102946169447995, 0.0340821784288995, 0.0097249148420291, 0.0150921083365508, 0.0076559966793363, 0.0075560489420082, 0.0075160698470769, 0.0074061273360159, 0.0072362161825581, 0.0070563102553674, 0.0070063363867033, 0.0070463154816346, 0.0067264827221845, 0.0066565193060548, 0.0062767179042078, 0.0064466290576657, 0.0062167492618109, 0.0061967597143453, 0.0060868172032844, 0.005836947859964, 0.0059069112760937, 0.0055970732903764, 0.0055570941954452, 0.0055770837429108, 0.0053172196258576, 0.0054471516843842, 0.005457146458117, 0.0051772927935982, 0.0050173764138731, 0.00507734505627, 0.0045076429534996, 0.0049074339028122, 0.0047675070705528, 0.0046675593332246, 0.004647569785759, 0.0046375750120262, 0.0042377840627136, 0.0045076429534996, 0.0041178467779198, 0.0043277370263089, 0.0041778154203167, 0.0040678729092557, 0.0041178467779198, 0.0038679774345994, 0.0039179513032635, 0.0037580349235384, 0.003618108091279, 0.0037180558286072, 0.0036780767336759, 0.0033882282954243, 0.0036880715074087, 0.0033782335216915, 0.0032782857843633, 0.0031583484995695, 0.0031983275945008, 0.0031783380470352, 0.0031283641783711, 0.002968447798646, 0.002968447798646, 0.0029084791562491, 0.0028585052875851, 0.0028285209663866, 0.0029084791562491, 0.0027785470977226, 0.0026686045866616, 0.0027085836815928, 0.0026286254917303, 0.0024886986594709, 0.0024787038857381, 0.0026186307179975, 0.0025286777544022, 0.0022987979585474, 0.0023087927322802, 0.0022888031848146, 0.0022188397686849, 0.0022288345424177, 0.0020889077101583, 0.0022388293161505, 0.0019389861041661, 0.0020689181626927, 0.0018990070092348, 0.0019689704253645, 0.0018490331405707, 0.0018190488193723, 0.0016391428921816, 0.0017390906295098, 0.0017690749507082, 0.0016991115345785, 0.0015891690235176, 0.0016391428921816, 0.0016391428921816, 0.0016591324396473, 0.0016091585709832, 0.0015491899285863, 0.001509210833655, 0.0014892212861894, 0.0014192578700597, 0.0013992683225941, 0.0014692317387238, 0.0013093153589987, 0.0013093153589987, 0.0012793310378003, 0.0012893258115331, 0.0011194146580752, 0.0012093676216706, 0.0011493989792737, 0.0011993728479378, 0.0010894303368768, 0.001079435563144, 0.0010894303368768, 0.0010394564682127, 0.0009924810316685, 0.0011094198843424, 0.0009095244096861, 0.0008672465167963, 0.0009091246187368, 0.0008901345486445, 0.0007570041625234, 0.0008178723345562, 0.0007494081344864, 0.0007873882746711, 0.0007303181166568, 0.0007683982045788, 0.0007227220886198, 0.0007037320185275, 0.0006238737764023, 0.0006428638464946, 0.000699934004509, 0.0005933897165172, 0.0005021374323366, 0.00047545138647, 0.0005630056043694, 0.000513531474392, 0.0004526633023591, 0.0004869453762627, 0.0004336732322668, 0.0004107852004187, 0.0004145832144371, 0.000327128944275, 0.0003119368882011, 0.0003690070462155, 0.0003879971163078, 0.0002776548142976, 0.0002434726881313, 0.0003005428461457, 0.0002129886282462, 0.00017880650208, 0.0002320786460759, 0.000186402530117, 0.0001939985581539, 0.0001483224421949, 0.0001065442879918, 0.0001369284001395, 5.325215444843891e-05, 6.085817725911121e-05, 4.945414042996917e-05, 3.0434086016422016e-05, 2.6626077224219456e-05, 1.1414031602874858e-05};

  G4double final_prob = G4UniformRand();
  G4double total_prob = 0;
  int cnt = 0;
  for (int i = 1; i < 230;i++)
  {
    total_prob += prob[i];
    if(total_prob>=final_prob)
      break;
    cnt++;
  }

  fParticleGun->SetParticleEnergy(energy[cnt] * MeV);
  G4double envSizeXY = 0;
  G4double envSizeZ = 0;

  if (!fEnvelopeBox) {
    G4LogicalVolume* envLV = G4LogicalVolumeStore::GetInstance()->GetVolume("Envelope");
    if (envLV) fEnvelopeBox = dynamic_cast<G4Box*>(envLV->GetSolid());
  }

  if (fEnvelopeBox) {
    envSizeXY = fEnvelopeBox->GetXHalfLength() * 2.;
    envSizeZ = fEnvelopeBox->GetZHalfLength() * 2.;
  }
  else {
    G4ExceptionDescription msg;
    msg << "Envelope volume of box shape not found.\n";
    msg << "Perhaps you have changed geometry.\n";
    msg << "The gun will be place at the center.";
    G4Exception("PrimaryGeneratorAction::GeneratePrimaries()", "MyCode0002", JustWarning, msg);
  }

  G4double x0 = 50*cm;
  G4double y0 = 0.0;
  // G4double y0 = -18*cm;
  G4double z0 = 0.0;

  fParticleGun->SetParticlePosition(G4ThreeVector(x0, y0, z0));

  fParticleGun->GeneratePrimaryVertex(event);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace B1
