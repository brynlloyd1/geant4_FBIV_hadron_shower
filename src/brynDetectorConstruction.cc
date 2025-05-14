#include "brynDetectorConstruction.hh"
#include "brynSensitiveDetector.hh"

// imports for materials
#include "G4NistManager.hh"
// #include "G4Material.hh"

// imports for volumes
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"

G4VPhysicalVolume* brynDetectorConstruction::Construct() {

    ////////////////////////
    // defining materials //
    ////////////////////////
    G4NistManager* NistManager = G4NistManager::Instance();
    G4Material* vacuumMaterial = NistManager->FindOrBuildMaterial("G4_Galactic");
    // will be Fe + Ni + trace amounts of high Z elements eventually
    G4Material* meteoriteMaterial = NistManager->FindOrBuildMaterial("G4_Fe");
    G4Material* detectorMaterial = NistManager->FindOrBuildMaterial("G4_Galactic");

    ///////////////////////
    // setup of geometry //
    ///////////////////////
    G4bool checkOverlaps = true;

    // world
    G4VSolid* solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, vacuumMaterial, "logicWorld");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld,"logicWorld", 0, false, 0, checkOverlaps);

    // meteorite
    G4VSolid* solidMeteorite = new G4Tubs("solidMeteorite", 0.*m, 0.005*m, 0.05*m, 0., 360.0*deg);
    G4LogicalVolume* logicMeteorite = new G4LogicalVolume(solidMeteorite, meteoriteMaterial, "logicMeteorite");
    G4VPhysicalVolume* physMeteorite = new G4PVPlacement(0, G4ThreeVector(), logicMeteorite, "logicMeteorite", logicWorld, false, 0, checkOverlaps);

    //detector
    // hollow sphere around everything
    G4VSolid* solidDetector = new G4Sphere("solidDetector", 0.45*m, 0.475*m, 0*degree, 360*degree, 0*degree, 360*degree);
    logicDetector = new G4LogicalVolume(solidDetector, detectorMaterial, "logicDetector");
    G4VPhysicalVolume* physDetector = new G4PVPlacement(0, G4ThreeVector(), logicDetector, "logicDetector", logicWorld, false, 0, checkOverlaps);


    return physWorld;
}

void brynDetectorConstruction::ConstructSDandField() {
    brynSensitiveDetector* sensitiveDetector = new brynSensitiveDetector("sensitiveDetector", "fHitsCollection");
    logicDetector->SetSensitiveDetector(sensitiveDetector);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensitiveDetector);
}
