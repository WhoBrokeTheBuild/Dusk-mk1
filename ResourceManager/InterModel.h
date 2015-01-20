#ifndef DUSK_INTER_MODEL_H
#define DUSK_INTER_MODEL_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include <Arc/ArrayList.h>
#include <Arc/ManagedObject.h>

using std::string;
using glm::vec3;
using glm::vec2;
using Arc::ArrayList;

class InterModel :
	public Arc::ManagedObject
{
public:

	virtual inline string getClassName(void) const { return "Intermediate Model"; }

    string              Name;

    ArrayList<vec3>     Verts;
    ArrayList<vec3>     Norms;
    ArrayList<vec2>     TexCoords;

    ArrayList<int>      VertInds;
    ArrayList<int>      NormInds;
    ArrayList<int>      TexCoordInds;

    inline int getFaceCount( void ) const { return (VertInds.getSize() / 3); }

};

#endif // DUSK_INTER_MODEL_H
