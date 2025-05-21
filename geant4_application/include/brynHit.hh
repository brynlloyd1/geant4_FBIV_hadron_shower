#ifndef brynHit_hh
#define brynHit_hh

#include "G4VHit.hh"
#include "G4THitsCollection.hh"

class brynHit : public G4VHit {
public:
    brynHit() = default;
    ~brynHit() = default;

    // virtual methods
    void Draw() override;
    void Print() override;

    // methods to collect information
    void setParticleName(G4String particleName);
    void setKineticEnergy(G4double kineticEnergy);
    G4String getParticleName();
    G4double getKineticEnergy();

private:
    G4String particleName;
    G4double kineticEnergy;
};


// G4THitsCollection is a template class, so this is basically how you write ur own class on top of it
using brynHitsCollection = G4THitsCollection<brynHit>;
#endif
