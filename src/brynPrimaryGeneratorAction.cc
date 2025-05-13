#include "brynPrimaryActionGenerator.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

#include "G4SystemofUnits.hh"

brynPrimaryGeneratorAction::brynPrimaryGeneratorAction() {
    G4int nParticles = 1;
    const G4String& particleName = "proton";
    G4double energy = 440 * GeV;
    G4ThreeVector position = G4ThreeVector(0., 0., -0.4*m);
    G4ThreeVector momentum = G4ThreeVector(0., 0., 1.);

    particleGun = new G4ParticleGun(nParticles);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particleDefinition
        = particleTable->FindParticle(particleName);

    particleGun->SetParticleDefinition(particleDefinition);
    particleGun->SetParticleEnergy(energy);
    particleGun->SetParticlePosition(position);
    particleGun->SetParticleMomentumDirection(momentum);
    G4cout << "has this worked??" << G4endl;
}

brynPrimaryGeneratorAction::~brynPrimaryGeneratorAction() {
    delete particleGun;
}

void brynPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    particleGun->GeneratePrimaryVertex(anEvent);
}
