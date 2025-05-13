#include "brynDetectorConstruction.hh"

#include "G4NistManager.hh"
// will need this to create my own material for the meteorite
// #include "G4Material.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4SystemOfUnits.hh"

G4VPhysicalVolume* brynDetectorConstruction::Construct() {

    ///////////////////////
    // defining materials //
    ///////////////////////
    G4NistManager* NistManager = G4NistManager::Instance();
    G4Material* vacuumMaterial = NistManager->FindOrBuildMaterial("G4_Galactic");
    // will be Fe + Ni + trace amounts of high Z elements eventually
    G4Material* meteoriteMaterial = NistManager->FindOrBuildMaterial("G4_Fe");

    ///////////////////////
    // setup of geometry //
    ///////////////////////
    G4bool checkOverlaps = true;

    // world
    G4VSolid* solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, vacuumMaterial, "logicWorld");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld,"logicWorld", 0, false, checkOverlaps);

    // meteorite
    G4VSolid* solidMeteorite = new G4Tubs("solidMeteorite", 0.*m, 0.005*m, 0.05*m, 0., 360.0*deg);
    G4LogicalVolume* logicMeteorite = new G4LogicalVolume(solidMeteorite, meteoriteMaterial, "logicMeteorite");
    G4VPhysicalVolume* physMeteorite = new G4PVPlacement(0, G4ThreeVector(), logicMeteorite, "logicMeteorite", logicWorld, false, checkOverlaps);

    return physWorld;
}
