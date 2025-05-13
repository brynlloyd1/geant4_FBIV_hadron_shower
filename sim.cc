// geant4 imports
#include "G4RunManagerFactory.hh"
#include "G4RunManager.hh"

#include "G4UIManager.hh"
#include "G4UIExecutive.hh"

#include "FTFP_BERT.hh"

// bryn imports
#include "brynDetectorConstruction.hh"
#include "brynActionInitialisation.hh"



int main(int argc, char** argv) {


    // run manager setup
    auto* runManager = G4RunManagerFactory::CreateRunManager();

    G4VUserDetectorConstruction* detector = new brynDetectorConstruction;
    G4VUserPhysicsList* physics_list = new FTFP_BERT;
    brynActionInitialisation* action = new brynActionInitialisation;

    runManager->SetUserInitialization(detector);
    runManager->SetUserInitialization(physics_list);
    runManager->SetUserInitialization(action);

    runManager->Initialize();

    //scoring manager setup
    // vis manager setup

    // ui manager setup
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // if you pass no macro file as an argument, the default is vis.mac. Otherwise, it runs in batch mode with the macros specified
    if (argc == 1) {
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
        UImanager->ApplyCommand("control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    } else {
        UImanager->ApplyCommand(std::string("control/execute") + argv[1]);
    }
    delete runManager;
}

