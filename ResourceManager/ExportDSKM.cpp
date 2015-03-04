#include "ExportDSKM.h"

#include <fstream>
#include <glm/glm.hpp>

#include "Functions.h"
#include "InterMesh.h"

using glm::vec3;
using glm::vec2;

bool ExportDSKM( const string& filename, InterModel* pModel )
{
    std::ofstream file(filename.c_str(), std::ios::binary);

    if (!file.is_open())
    {
        error("Cannot open file");
    }

    file.write("DSKM", 4);

    unsigned short nameLength = pModel->Name.size();
    file.write((const char*)&nameLength, sizeof(unsigned short));
    file.write(pModel->Name.c_str(), nameLength);

    unsigned short meshCount = pModel->Meshes.getSize();
    file.write((const char*)&meshCount, sizeof(unsigned short));

    for (unsigned int i = 0; i < pModel->Meshes.getSize(); ++i)
    {
        InterMesh& mesh = pModel->Meshes[i];
        InterMaterial& mat = mesh.Material;

        // Material

        nameLength = mesh.Name.size();
        file.write((const char*)&nameLength, sizeof(unsigned short));
        if (nameLength != 0)
        {
            file.write(mesh.Name.c_str(), nameLength);

            file.write((const char*)&mat.DiffuseColor, sizeof(vec3));
            file.write((const char*)&mat.AmbientColor, sizeof(vec3));
            file.write((const char*)&mat.SpecularColor, sizeof(vec3));

            file.write((const char*)&mat.Specular, sizeof(float));
            file.write((const char*)&mat.Transparency, sizeof(float));

            nameLength = mat.DiffuseMap.size();
            file.write((const char*)&nameLength, sizeof(unsigned short));
            file.write(mat.DiffuseMap.c_str(), nameLength);

            nameLength = mat.AmbientMap.size();
            file.write((const char*)&nameLength, sizeof(unsigned short));
            file.write(mat.AmbientMap.c_str(), nameLength);

            nameLength = mat.SpecularMap.size();
            file.write((const char*)&nameLength, sizeof(unsigned short));
            file.write(mat.SpecularMap.c_str(), nameLength);

            nameLength = mat.SpecularHilightMap.size();
            file.write((const char*)&nameLength, sizeof(unsigned short));
            file.write(mat.SpecularHilightMap.c_str(), nameLength);

            nameLength = mat.AlphaMap.size();
            file.write((const char*)&nameLength, sizeof(unsigned short));
            file.write(mat.AlphaMap.c_str(), nameLength);

            nameLength = mat.BumpMap.size();
            file.write((const char*)&nameLength, sizeof(unsigned short));
            file.write(mat.BumpMap.c_str(), nameLength);
        }

        // Mesh

        nameLength = mesh.Name.size();
        file.write((const char*)&nameLength, sizeof(unsigned short));
        file.write(mesh.Name.c_str(), nameLength);

        unsigned int vertCount = mesh.Verts.getSize();
        file.write((const char*)&vertCount, sizeof(unsigned int));

        if (!mesh.Verts.isEmpty())
            file.write((const char*)&mesh.Verts[0], sizeof(vec3) * vertCount);

        unsigned int vertIndCount = mesh.VertInds.getSize();
        file.write((const char*)&vertIndCount, sizeof(unsigned int));

        if (!mesh.VertInds.isEmpty())
            file.write((const char*)&mesh.VertInds[0], sizeof(int) * vertIndCount);

        unsigned int normCount = mesh.Norms.getSize();
        file.write((const char*)&normCount, sizeof(unsigned int));

        if (!mesh.Norms.isEmpty())
            file.write((const char*)&mesh.Norms[0], sizeof(vec3) * normCount);

        unsigned int normIndCount = mesh.NormInds.getSize();
        file.write((const char*)&normIndCount, sizeof(unsigned int));

        if (!mesh.NormInds.isEmpty())
            file.write((const char*)&mesh.NormInds[0], sizeof(int) * normIndCount);

        unsigned int texCoordCount = mesh.TexCoords.getSize();
        file.write((const char*)&texCoordCount, sizeof(unsigned int));

        if (!mesh.TexCoords.isEmpty())
            file.write((const char*)&mesh.TexCoords[0], sizeof(vec2) * texCoordCount);

        unsigned int texCoordIndCount = mesh.TexCoordInds.getSize();
        file.write((const char*)&texCoordIndCount, sizeof(unsigned int));

        if (!mesh.TexCoordInds.isEmpty())
            file.write((const char*)&mesh.TexCoordInds[0], sizeof(int) * texCoordIndCount);
    }

    file.close();

    printf("Successfully wrote DSKM File: %s\n", filename.c_str());

    return true;

    return true;
}
