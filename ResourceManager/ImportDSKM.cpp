#include "ImportDSKM.h"

#include <fstream>
#include <glm/glm.hpp>

#include "Functions.h"

using glm::vec3;
using glm::vec2;

bool ImportDSKM( const string& filename, InterModel* pModel )
{
    std::ifstream file(filename.c_str(), std::ios::binary);

    if (!file.is_open())
    {
        error("Cannot open file");
    }

    char fileTypeCode[4];
    file.read(fileTypeCode, 4);

    if (string(fileTypeCode, 4) != "DSKM")
    {
        error("Invalid or Corrupt File");
    }

    unsigned short nameLength = 0;
    file.read((char*)&nameLength, sizeof(unsigned short));

	if (nameLength > 0)
	{
		pModel->Name.resize(nameLength);
		file.read(&pModel->Name[0], nameLength);
	}

    unsigned int vertCount = 0;
    file.read((char*)&vertCount, sizeof(unsigned int));

	if (vertCount > 0)
	{
		pModel->Verts.resize(vertCount);
		file.read((char*)&pModel->Verts[0], sizeof(vec3) * vertCount);
	}

    unsigned int vertIndCount = 0;
    file.read((char*)&vertIndCount, sizeof(unsigned int));

	if (vertIndCount > 0)
	{
		pModel->VertInds.resize(vertIndCount);
		file.read((char*)&pModel->VertInds[0], sizeof(int) * vertIndCount);
	}

    unsigned int normCount = 0;
    file.read((char*)&normCount, sizeof(unsigned int));

	if (normCount > 0)
	{
		pModel->Norms.resize(normCount);
		file.read((char*)&pModel->Norms[0], sizeof(vec3) * normCount);
	}

    unsigned int normIndCount = 0;
    file.read((char*)&normIndCount, sizeof(unsigned int));

	if (normIndCount > 0)
	{
		pModel->NormInds.resize(normIndCount);
		file.read((char*)&pModel->NormInds[0], sizeof(int) * normIndCount);
	}

    unsigned int texCoordCount = pModel->TexCoords.getSize();
    file.read((char*)&texCoordCount, sizeof(unsigned int));

	if (texCoordCount > 0)
	{
		pModel->TexCoords.resize(texCoordCount);
		file.read((char*)&pModel->TexCoords[0], sizeof(vec2) * texCoordCount);
	}

    unsigned int texCoordIndCount = pModel->TexCoordInds.getSize();
    file.read((char*)&texCoordIndCount, sizeof(unsigned int));

	if (texCoordIndCount > 0)
	{
		pModel->TexCoordInds.resize(texCoordIndCount);
		file.read((char*)&pModel->TexCoordInds[0], sizeof(int) * texCoordIndCount);
	}

    file.close();

    printf("Successfully loaded OBJ File: %s\n", filename.c_str());
    printf("Triangles: %i \n", vertIndCount / 3);

    return true;
}
