#include "brynHit.hh"


// virtual methods
void brynHit::Draw() {;}
void brynHit::Print() {;}

// methods to collect information
void brynHit::setParticleName(G4String particleName) {
    this->particleName = particleName;
}

void brynHit::setKineticEnergy(G4double kineticEnergy) {
    this->kineticEnergy = kineticEnergy;
}

G4String brynHit::getParticleName() {
    return this->particleName;
}

G4double brynHit::getKineticEnergy() {
    return this->kineticEnergy;
}
