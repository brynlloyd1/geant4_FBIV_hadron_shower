#ifndef brynDetectorConstruction_hh
#define brynDetectorConstruction_hh

#include "G4VUserDetectorConstruction.hh"

// (public => public inheritiance => public members will stay public and private members will stay private)
class brynDetectorConstruction : public G4VUserDetectorConstruction {
    public:
        // default just asks the compiler to write the method
        brynDetectorConstruction() = default;
        ~brynDetectorConstruction() override = default;

        // Construct() returns an instance of G4VPhysicalVolume. It is a virtual method, so we have to overwrite it
        virtual G4VPhysicalVolume* Construct() override;

    private:
        virtual void ConstructSDandField() override;
        // needs to be defined in the header because its used in both Construct() and ConstructSDandField()
        G4LogicalVolume* logicDetector;
};
#endif
