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
    // G4Material* meteoriteMaterial = NistManager->FindOrBuildMaterial("G4_Fe");
    // G4Material* meteoriteMaterial = NistManager->FindOrBuildMaterial("G4_U");
    G4Material* detectorMaterial = NistManager->FindOrBuildMaterial("G4_Galactic");


    // Iron
    G4double z = 26.;
    G4double a = 55.8 * g/mole;
    G4Element* Fe = new G4Element("Iron", "Fe", z, a);
    // Nickel
    z = 28.;
    a = 58.7 * g/mole;
    G4Element* Ni = new G4Element("Nickel", "Ni", z, a);

    // meteorite material is 85% iron, 15% nickel
    G4Material* meteoriteMaterial = new G4Material("meteoriteMaterial", 8.02 * g/cm3, 2);
    meteoriteMaterial->AddElement(Fe, 0.85);
    meteoriteMaterial->AddElement(Ni, 0.15);


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
