#include "ExportDSKM.h"

#include <fstream>
#include <glm/glm.hpp>

#include "Functions.h"

using glm::vec3;
using glm::vec2;

bool ExportDSKM( const string& filename, InterModel* pModel )
{
    std::ofstream file(filename.c_str(), std::ios::binary);

    if (!file.is_open())
    {
        error("Cannot open file");
    }

    if (pModel->VertInds.getSize() != pModel->NormInds.getSize())
    {
        error("Vertex/Normal count mismatch");
    }

    file.write("DSKM", 4);

    unsigned short nameLength = pModel->Name.size();
    file.write((const char*)&nameLength, sizeof(unsigned short));
    file.write(pModel->Name.c_str(), nameLength);

    unsigned int vertCount = pModel->Verts.getSize();
    file.write((const char*)&vertCount, sizeof(unsigned int));
    file.write((const char*)&pModel->Verts[0], sizeof(vec3) * vertCount);

    unsigned int vertIndCount = pModel->VertInds.getSize();
    file.write((const char*)&vertIndCount, sizeof(unsigned int));
    file.write((const char*)&pModel->VertInds[0], sizeof(int) * vertIndCount);


    unsigned int normCount = pModel->Norms.getSize();
    file.write((const char*)&normCount, sizeof(unsigned int));
    file.write((const char*)&pModel->Norms[0], sizeof(vec3) * normCount);

    unsigned int normIndCount = pModel->NormInds.getSize();
    file.write((const char*)&normIndCount, sizeof(unsigned int));
    file.write((const char*)&pModel->NormInds[0], sizeof(int) * normIndCount);


    unsigned int texCoordCount = pModel->TexCoords.getSize();
    file.write((const char*)&texCoordCount, sizeof(unsigned int));
    file.write((const char*)&pModel->TexCoords[0], sizeof(vec2) * texCoordCount);

    unsigned int texCoordIndCount = pModel->TexCoordInds.getSize();
    file.write((const char*)&texCoordIndCount, sizeof(unsigned int));
    file.write((const char*)&pModel->TexCoordInds[0], sizeof(int) * texCoordIndCount);

    file.close();

    printf("Successfully wrote DSKM File: %s\n", filename.c_str());

    return true;

    return true;
}