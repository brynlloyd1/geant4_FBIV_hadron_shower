#include "brynSensitiveDetector.hh"
#include "brynHit.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include <G4VSensitiveDetector.hh>
#include "G4SystemOfUnits.hh"

#include <fstream>

brynSensitiveDetector::brynSensitiveDetector(const G4String& name,
                                             const G4String& hitsCollectionName) : G4VSensitiveDetector(name) {
    collectionName.insert(hitsCollectionName);
}

void brynSensitiveDetector::Initialize(G4HCofThisEvent* hitsCollection) {
    // called when the sensitive detector is initialised at the start of an event
    // initialise data structures that will hold particle type, energy, etc.

    fHitsCollection = new brynHitsCollection(SensitiveDetectorName, collectionName[0]);
    G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hitsCollection->AddHitsCollection(hcID, fHitsCollection);
}


G4bool brynSensitiveDetector::ProcessHits(G4Step* step,
                   G4TouchableHistory* history) {

    // get information from the track
    G4Track* track = step->GetTrack();
    G4String particleName = track->GetDefinition()->GetParticleName();
    G4double kineticEnergy = track->GetKineticEnergy();

    // add information to the hit
    brynHit* hit = new brynHit();
    hit->setParticleName(particleName);
    hit->setKineticEnergy(kineticEnergy);

    // add hit to the hit collection
    fHitsCollection->insert(hit);
    return true;
}


void brynSensitiveDetector::EndOfEvent(G4HCofThisEvent* hitsCollection) {
    // write results to a file

    std::ofstream outFile("KE_data.csv", std::ios::app);
    if (!outFile) {
        std::cerr << "Error opening file\n";
    }

    outFile << "particleName, kineticEnergy[MeV]\n";

    for (size_t i=0; i<fHitsCollection->entries(); i++) {
        brynHit* hit = (*fHitsCollection)[i];
        G4String particleName = hit->getParticleName();
        G4double kineticEnergy = hit->getKineticEnergy();

        outFile << particleName << "," << kineticEnergy / MeV << "\n";
    }
    outFile.close();
}
