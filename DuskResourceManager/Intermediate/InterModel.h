#ifndef DUSK_INTER_MODEL_H
#define DUSK_INTER_MODEL_H

#include <Arc/ManagedObject.h>
#include <Intermediate/InterMesh.h>

#include <Arc/ArrayList.h>

using Arc::ArrayList;

class InterModel :
    public Arc::ManagedObject
{
    public:

        virtual inline string getClassName( void ) const { return "Intermediate Model"; }

        string                  Name;
        ArrayList<InterMesh>    Meshes;
};

#endif // DUSK_INTER_MODEL_H
