// geant4 imports
#include "G4RunManagerFactory.hh"
#include "G4RunManager.hh"

#include "G4UIManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "FTFP_BERT.hh"

// bryn imports
#include "brynDetectorConstruction.hh"
#include "brynActionInitialisation.hh"
#include <G4VisManager.hh>



int main(int argc, char** argv) {

    ///////////////////////
    // run manager setup //
    ///////////////////////
    auto* runManager = G4RunManagerFactory::CreateRunManager();

    G4VUserDetectorConstruction* detector = new brynDetectorConstruction;
    // might eventually need to write a whole file for the physics_list
    G4VUserPhysicsList* physics_list = new FTFP_BERT;
    brynActionInitialisation* action = new brynActionInitialisation;

    runManager->SetUserInitialization(detector);
    runManager->SetUserInitialization(physics_list);
    runManager->SetUserInitialization(action);

    runManager->Initialize();

    //////////////////////////
    //scoring manager setup //
    //////////////////////////


    ///////////////////////
    // vis manager setup //
    ///////////////////////
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    //////////////////////
    // UI manager setup //
    //////////////////////
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    if (ui) {
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    } else {
        UImanager->ApplyCommand(std::string("/control/execute") + argv[1]);
        ui->SessionStart();
        delete ui;
    }


    // if (argc == 1) {
    //     G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    //     UImanager->ApplyCommand("control/execute vis.mac");
    //     ui->SessionStart();
    //     delete ui;
    // } else {
    //     UImanager->ApplyCommand(std::string("control/execute") + argv[1]);
    // }

    delete runManager;
    delete visManager;
}

