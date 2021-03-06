#include "SimpleDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4EventManager.hh"
#include "SimpleAnalysis.hh"

using namespace CLHEP;

SimpleDetector::SimpleDetector(G4String name) : G4VSensitiveDetector(name)
{
}

SimpleDetector::~SimpleDetector() 
{
}

void SimpleDetector::Initialize(G4HCofThisEvent*)
{
}

G4bool SimpleDetector::ProcessHits(G4Step* step, G4TouchableHistory*)
{  
  G4Track* track = step->GetTrack();

  if (!(step->GetPreStepPoint()->GetStepStatus() == fGeomBoundary )) return false;

  auto energy = track->GetKineticEnergy();
  auto pdg_code = track->GetParticleDefinition()->GetPDGEncoding();
  auto dnumber = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetCopyNo();
  
  //G4cout << "Detector: " << dnumber << " Energy: " <<  energy/MeV << " [MeV] "<< "PDG:" << pdg_code << G4endl;

  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleIColumn(0, dnumber);
  analysisManager->FillNtupleDColumn(1, energy/MeV);
  analysisManager->FillNtupleIColumn(2, pdg_code);
  analysisManager->AddNtupleRow();
  
  return true;
}

void SimpleDetector::EndOfEvent(G4HCofThisEvent*)
{
}
