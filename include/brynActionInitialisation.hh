#ifndef brynActionInitialisation_hh
#define brynActionInitialisation_hh

#include "G4VUserActionInitialization.hh"

class brynActionInitialisation : public G4VUserActionInitialization {
public:
    brynActionInitialisation() = default;
    virtual ~brynActionInitialisation() = default;
    // const after function just says that the function won't modify any member variables
    virtual void Build() const;
};

#endif
