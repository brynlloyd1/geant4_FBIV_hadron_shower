#ifndef brynActionInitialisation_hh
#define brynActionInitialisation_hh

#include "G4VUserActionInitialization.hh"

class brynActionInitialisation : public G4VUserActionInitialization {
public:
    brynActionInitialisation() = default;
    virtual ~brynActionInitialisation() = default;
    virtual void Build() const;
};
#endif
