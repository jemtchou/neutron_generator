#include "SimpleParticleSource.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4Neutron.hh"
#include "G4Gamma.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"


using namespace std;

SimpleParticleSource::SimpleParticleSource()
: G4VUserPrimaryGeneratorAction()
{//-500.*cm,50.*cm,0.*cm
  fParticleGun = new G4ParticleGun(1);
  fParticleGun->SetParticleDefinition(G4Neutron::NeutronDefinition());
  fParticleGun->SetParticleEnergy(14*MeV);
  fParticleGun->SetParticlePosition(G4ThreeVector(485.*cm,20.*cm,0.*cm));
}

SimpleParticleSource::~SimpleParticleSource()
{
 
}

void SimpleParticleSource::GeneratePrimaries(G4Event* evt)
{
  double costheta =2*G4UniformRand()-1;
  double sintheta =sqrt(1-costheta*costheta);
  double phi =2*3.14159*G4UniformRand();
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.*sintheta*cos(phi),1.*sintheta*sin(phi),1.*costheta));
  fParticleGun->GeneratePrimaryVertex(evt);
}
