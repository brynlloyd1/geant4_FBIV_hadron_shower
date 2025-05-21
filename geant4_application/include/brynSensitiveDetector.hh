#ifndef brynSensitiveDetector_hh
#define brynSensitiveDetector_hh

#include "brynHit.hh"

#include "G4VSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"

class brynSensitiveDetector : public G4VSensitiveDetector {
public:
    brynSensitiveDetector(const G4String& name,
                          const G4String& hitsCollectionName);
    ~brynSensitiveDetector() override = default;

private:
    virtual void Initialize(G4HCofThisEvent* hitsCollection) override;
    virtual G4bool ProcessHits(G4Step* step,
                       G4TouchableHistory* history) override;
    virtual void EndOfEvent(G4HCofThisEvent* hitsCollection) override;

    brynHitsCollection* fHitsCollection = nullptr;
};
#endif
