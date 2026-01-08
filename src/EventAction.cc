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
/// \file B1/src/EventAction.cc
/// \brief Implementation of the B1::EventAction class

#include "EventAction.hh"
#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4ios.hh"
#include "RunAction.hh"
#include "TrackerHit.hh"
#include "G4SDManager.hh"
namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* runAction) : fRunAction(runAction),fHCID(-1) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
  fEdep = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
  // accumulate statistics in run action
  auto analysisManager = G4AnalysisManager::Instance();

    // 获取 HitsCollection (你需要知道它的 CollectionID)
    // 假设你在 Initialize 中获取了 fHCID (Hits Collection ID)
  
        
        // 注意：这里的字符串必须是 "SD名称/Collection名称"
        // 例如：你在 DetectorConstruction 中定义的 SD 名字是 "TrackerSD"
        // 且在 TrackerSD.cc 中定义的 Collection 名字是 "TrackerHits"
  if (fHCID <0)
  {
    auto sdManager = G4SDManager::GetSDMpointer();
    fHCID = sdManager->GetCollectionID("DetSD/TrackerHitsCollection");
  }
  
  auto hce = event->GetHCofThisEvent();
  if(!hce)
    return;
  auto hc=hce->GetHC(fHCID);
  if(!hc)
    return;
  auto hitsCollection = static_cast<TrackerHitsCollection *>(hc);
  G4int eventID = event->GetEventID();// 获取当前的 Event ID

    // 遍历这个 Event 中的所有 Hits
  int n_hit = hitsCollection->entries();
  for (int i = 0; i < n_hit; i++) {
      TrackerHit* hit = (*hitsCollection)[i];

        // 填入数据 (注意顺序要和 RunAction 中的 CreateNtuple 一致)
      analysisManager->FillNtupleIColumn(0, eventID);        // EventID
      analysisManager->FillNtupleIColumn(1, hit->fTrackID);  // TrackID
      analysisManager->FillNtupleDColumn(2, hit->fEdep);     // Edep
      analysisManager->FillNtupleDColumn(3, hit->fPos.x());  // PosX
      analysisManager->FillNtupleDColumn(4, hit->fPos.y());  // PosY
      analysisManager->FillNtupleDColumn(5, hit->fPos.z());  // PosZ

        // 增加一行 (完成当前 Hit 的写入)
      analysisManager->AddNtupleRow();
    }
  G4TrajectoryContainer* trajectoryContainer = event->GetTrajectoryContainer();
  std::size_t n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();
  fRunAction->AddEdep(fEdep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace B1
