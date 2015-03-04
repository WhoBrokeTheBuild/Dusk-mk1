#ifndef DUSK_INTER_MESH_H
#define DUSK_INTER_MESH_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include <Arc/ArrayList.h>
#include <Arc/ManagedObject.h>

#include <Intermediate/InterMaterial.h>

using std::string;
using glm::vec3;
using glm::vec2;
using Arc::ArrayList;

class InterMesh :
	public Arc::ManagedObject
{
public:

	virtual inline string getClassName(void) const { return "Intermediate Mesh"; }

    string              Name;
    InterMaterial       Material;

    ArrayList<vec3>     Verts;
    ArrayList<vec3>     Norms;
    ArrayList<vec2>     TexCoords;

    ArrayList<int>      VertInds;
    ArrayList<int>      NormInds;
    ArrayList<int>      TexCoordInds;
};

#endif // DUSK_INTER_MESH_H
