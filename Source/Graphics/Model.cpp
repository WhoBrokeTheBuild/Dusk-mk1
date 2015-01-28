#include "Model.h"
#include <Graphics/Mesh.h>
#include <Logging/Log.h>

#include <fstream>

using namespace Dusk::Logging;

Dusk::Graphics::Model::~Model( void )
{
    for (auto it = m_Meshes.itBegin(); it != m_Meshes.itEnd(); ++it)
    {
        Mesh* pMesh = *it;
        delete pMesh;
    }
    m_Meshes.clear();
}

bool Dusk::Graphics::Model::load( const string& filename )
{
    LogInfoFmt(getClassName(), "Load from file \"%s\"", filename.c_str());

    std::ifstream file(filename.c_str(), std::ios::binary);

    if (!file)
    {
        LogErrorFmt(getClassName(), "Failed to open file \"%s\"", filename.c_str());
        return false;
    }

    char fileTypeCode[4];
    file.read(fileTypeCode, 4);

    if (string(fileTypeCode, 4) != "DSKM")
    {
        LogErrorFmt(getClassName(), "Invalid Format for file \"%s\"", filename.c_str());
        return false;
    }

    unsigned short nameLength = 0;
    file.read((char*)&nameLength, sizeof(unsigned short));

    string name;
    ArrayList<vec3> vertList;
    ArrayList<int> vertInds;
    ArrayList<vec3> normList;
    ArrayList<int> normInds;
    ArrayList<vec2> texCoordList;
    ArrayList<int> texCoordInds;

	if (nameLength > 0)
	{
		name.resize(nameLength);
		file.read(&name[0], nameLength);
	}

    unsigned int vertCount = 0;
    file.read((char*)&vertCount, sizeof(unsigned int));

	if (vertCount > 0)
	{
		vertList.resize(vertCount);
		file.read((char*)&vertList[0], sizeof(vec3) * vertCount);
	}

    unsigned int vertIndCount = 0;
    file.read((char*)&vertIndCount, sizeof(unsigned int));

	if (vertIndCount > 0)
	{
		vertInds.resize(vertIndCount);
		file.read((char*)&vertInds[0], sizeof(int) * vertIndCount);
	}


    unsigned int normCount = 0;
    file.read((char*)&normCount, sizeof(unsigned int));

	if (normCount > 0)
	{
		normList.resize(normCount);
		file.read((char*)&normList[0], sizeof(vec3) * normCount);
	}

    unsigned int normIndCount = 0;
    file.read((char*)&normIndCount, sizeof(unsigned int));

	if (vertIndCount > 0)
	{
		normInds.resize(normIndCount);
		file.read((char*)&normInds[0], sizeof(int) * normIndCount);
	}


    unsigned int texCoordCount = 0;
    file.read((char*)&texCoordCount, sizeof(unsigned int));

	if (texCoordCount > 0)
	{
		texCoordList.resize(texCoordCount);
		file.read((char*)&texCoordList[0], sizeof(vec2) * texCoordCount);
	}

    unsigned int texCoordIndCount = 0;
    file.read((char*)&texCoordIndCount, sizeof(unsigned int));

	if (texCoordIndCount > 0)
	{
		texCoordInds.resize(texCoordIndCount);
		file.read((char*)&texCoordInds[0], sizeof(int) * texCoordIndCount);
	}

    ArrayList<vec3> verts;
    verts.resize(vertIndCount);
    ArrayList<vec3> norms;
    norms.resize(normIndCount);
    ArrayList<vec2> texCoords;
    texCoords.resize(texCoordIndCount);

    for (unsigned int i = 0; i < vertInds.getSize(); ++i)
        verts.add(vertList[vertInds[i]]);

    for (unsigned int i = 0; i < normInds.getSize(); ++i)
        norms.add(normList[normInds[i]]);

    for (unsigned int i = 0; i < texCoordInds.getSize(); ++i)
        texCoords.add(texCoordList[texCoordInds[i]]);

    m_Meshes.clear();

    Mesh* pMesh = New Mesh();
    bool success = pMesh->init(GL_TRIANGLES, verts, norms, texCoords);

    if (success)
    {
        m_Meshes.add(pMesh);
    }

    return success;
}

void Dusk::Graphics::Model::render( void )
{
    for (auto it = m_Meshes.itBegin(); it != m_Meshes.itEnd(); ++it)
    {
        Mesh* pMesh = *it;
        pMesh->render();
    }
}
