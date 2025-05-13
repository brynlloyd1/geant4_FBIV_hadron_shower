#ifndef brynPrimaryGeneratorAction_hh
#define brynPrimaryGeneratorAction_hh

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

class brynPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    brynPrimaryGeneratorAction();
    ~brynPrimaryGeneratorAction();
    virtual void GeneratePrimaries(G4Event*);

public:
    G4ParticleGun* particleGun;
};
#endif
