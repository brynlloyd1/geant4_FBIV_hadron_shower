#ifndef brynDetectorConstruction_hh
#define brynDetectorConstruction_hh

#include <G4RunManager.hh>
#include "G4VPhysicalVolume.hh"
#include "G4VUserDetectorConstruction.hh"

// (public => public inheritiance => public members will stay public and private members will stay private)
class brynDetectorConstruction : public G4VUserDetectorConstruction {
    public:
        // default just asks the compiler to write the constructor and destructor methods for us
        brynDetectorConstruction() = default;
        ~brynDetectorConstruction() override = default;

        // Construct() returns an instance of G4VPhysicalVolume. It is a virtual method, so we have to overwrite it
        virtual G4VPhysicalVolume* Construct() override;

    private:
        G4Material* vacuum_material;
        G4Material* meteorite_material;
};
#endif
