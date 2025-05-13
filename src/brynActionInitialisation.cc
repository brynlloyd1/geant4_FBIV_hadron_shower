#include "brynActionInitialisation.hh"
#include "brynPrimaryActionGenerator.hh"

void brynActionInitialisation::Build() const {
    SetUserAction(new brynPrimaryGeneratorAction);
}
