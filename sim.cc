// geant4 imports
#include "G4RunManagerFactory.hh"
#include "G4RunManager.hh"
#include "G4UIManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4VisManager.hh"
#include "FTFP_BERT.hh"

// bryn imports
#include "brynDetectorConstruction.hh"
#include "brynActionInitialisation.hh"



int main(int argc, char** argv) {

    ///////////////////////
    // run manager setup //
    ///////////////////////
    auto* runManager = G4RunManagerFactory::CreateRunManager();
    runManager->SetUserInitialization(new brynDetectorConstruction);
    runManager->SetUserInitialization(new FTFP_BERT);
    runManager->SetUserInitialization(new brynActionInitialisation);
    runManager->Initialize();

    ///////////////////////
    // vis manager setup //
    ///////////////////////
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    //////////////////////
    // UI manager setup //
    //////////////////////
    // gives user choice between batch mode (specify macro files) or interactive mode (dont specify any macro file)
    // G4UIExecutive* ui;
    // G4UImanager* UImanager = G4UImanager::GetUIpointer();
    // if (argc == 1) {
    //     ui = new G4UIExecutive(argc, argv);
    //     UImanager->ApplyCommand("/control/execute vis.mac");
    // } else {
    //     ui = nullptr;
    //     UImanager->ApplyCommand(std::string("/control/execute ") + argv[1]);
    // }
    // ui->SessionStart();


    
    G4UIExecutive* ui = nullptr;
    if ( argc == 1 ) {
        ui = new G4UIExecutive(argc, argv);
    }


    // Get the pointer to the User Interface manager
    //
    G4UImanager* UImanager = G4UImanager::GetUIpointer();  

    if (ui) {
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    } else { 
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }





    /////////////
    // cleanup //
    /////////////
    // delete ui;
    delete runManager;
    delete visManager;
}
