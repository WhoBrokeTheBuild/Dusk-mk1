#include "ImportOBJ.h"

#include <fstream>
#include <sstream>
#include <glm/glm.hpp>

#include <Util/Functions.h>
#include <Arc/ArrayList.h>
#include <Arc/Map.h>
#include <Arc/StringFunctions.h>

using glm::vec3;
using glm::vec2;
using Arc::ArrayList;
using Arc::Map;

bool ImportMTL( const string& filename, Map<string, InterMaterial>& materials )
{
    std::ifstream file(filename.c_str());

    if (!file.is_open())
    {
        printf("Cannot open MTL file %s\n", filename.c_str());
        return false;
    }

    string line;
    string name;
    while (std::getline(file, line))
    {
        if (line.size() == 0 || line[0] == '#')
            continue;

        size_t spacePos = line.find(' ');
		if (spacePos == string::npos)
			continue;

		string cmd;
		cmd.assign(line, 0, spacePos);

		string data;
		data.assign(line, spacePos + 1, line.size() - spacePos);

		std::stringstream ss(data);

		if (cmd == "newmtl")
		{
            //printf("New Material: %s\n", data.c_str());
            name = data;
            materials.add(name, InterMaterial());
            materials[name].Name = name;
            continue;
		}

		if (materials.isEmpty())
            continue;

        InterMaterial& mat = materials[name];

        if (cmd == "Ka")
        {
			ss >> mat.AmbientColor.x >> mat.AmbientColor.y >> mat.AmbientColor.z;
        }
        else if (cmd == "Kd")
        {
			ss >> mat.DiffuseColor.x >> mat.DiffuseColor.y >> mat.DiffuseColor.z;
        }
        else if (cmd == "Ks")
        {
			ss >> mat.SpecularColor.x >> mat.SpecularColor.y >> mat.SpecularColor.z;
        }
        else if (cmd == "d" || cmd == "Tr")
        {
            ss >> mat.Transparency;
        }
        else if (cmd == "map_Ka")
        {
            mat.AmbientMap = Arc::Arc_Dirname(filename) + "/" + data;
        }
        else if (cmd == "map_Kd")
        {
            mat.DiffuseMap = Arc::Arc_Dirname(filename) + "/" + data;
        }
        else if (cmd == "map_Ks")
        {
            mat.SpecularMap = Arc::Arc_Dirname(filename) + "/" + data;
        }
        else if (cmd == "map_Na")
        {
            mat.SpecularHilightMap = Arc::Arc_Dirname(filename) + "/" + data;
        }
        else if (cmd == "map_d" || cmd == "map_Tr")
        {
            mat.AlphaMap = Arc::Arc_Dirname(filename) + "/" + data;
        }
        else if (cmd == "bump" || cmd == "map_bump")
        {
            mat.BumpMap = Arc::Arc_Dirname(filename) + "/" + data;
        }
    }

    file.close();

    printf("Successfully loaded MTL File: %s\n", filename.c_str());

    return true;
}

bool ImportOBJ( const string& filename, InterModel* pModel )
{
    std::ifstream file(filename.c_str());

    if (!file.is_open())
    {
        printf("Cannot open OBJ file %s\n", filename.c_str());
        return false;
    }

	int triCount = 0;

	pModel->Meshes.add(InterMesh());
	Map<string, InterMaterial> materials;
    ArrayList<vec3> verts, norms;
    ArrayList<vec2> texCoords;
    Map<int, int> vertIndRewrite, normIndRewrite, texCoordIndRewrite;

    string line;
    while (std::getline(file, line))
    {
        if (line.size() < 2 || line[0] == '#')
            continue;

        InterMesh& mesh = pModel->Meshes.getBack();

        size_t spacePos = line.find(' ');
		if (spacePos == string::npos)
			continue;

		string cmd;
		cmd.assign(line, 0, spacePos);

		string data;
		data.assign(line, spacePos + 1, line.size() - spacePos);

		std::stringstream ss(data);

		if (cmd == "v")
		{
			static vec3 vert;

			ss >> vert.x >> vert.y >> vert.z;

            verts.add(vert);
		}
		else if (cmd == "vt")
		{
			static vec2 coord;

			ss >> coord.x >> coord.y;

            texCoords.add(coord);
		}
		else if (cmd == "vn")
		{
			static vec3 norm;

			ss >> norm.x >> norm.y >> norm.z;

            norms.add(norm);
		}
		else if (cmd == "f")
		{
			int tmpVertInds[4]      = { -1, -1, -1, -1 };
			int tmpNormInds[4]      = { -1, -1, -1, -1 };
			int tmpTexCoordInds[4]  = { -1, -1, -1, -1 };

			string piece;
			int count = 0;
			for (int i = 0; getline(ss, piece, ' '); ++i)
			{
				if (piece.size() == 0)
				{
					--i;
					continue;
				}

				count++;

				bool vertAndNorm = (piece.find("//") != string::npos);
				unsigned short slashCount = 0;

				for (unsigned int j = 0; j < piece.size(); ++j)
				{
					if (piece[j] == '/')
					{
						piece[j] = ' ';
                        ++slashCount;
					}
				}

				std::stringstream ssPiece(piece);
				if (vertAndNorm)
				{
					ssPiece >> tmpVertInds[i];
					ssPiece >> tmpNormInds[i];

					--tmpVertInds[i];
					--tmpNormInds[i];
				}
				else
				{
					ssPiece >> tmpVertInds[i];
					ssPiece >> tmpTexCoordInds[i];

					--tmpVertInds[i];
					--tmpTexCoordInds[i];

					if (slashCount == 2)
					{
                        ssPiece >> tmpNormInds[i];
                        --tmpNormInds[i];
					}
				}
			}

            for (int j = 0; j < count; ++j)
            {
                if (tmpVertInds[j] != -1)
                {
                    if (vertIndRewrite.containsKey(tmpVertInds[j]))
                        tmpVertInds[j] = vertIndRewrite[tmpVertInds[j]];
                    else
                    {
                        int newInd = mesh.Verts.getSize();
                        mesh.Verts.add(verts[tmpVertInds[j]]);
                        vertIndRewrite.add(tmpVertInds[j], newInd);
                        tmpVertInds[j] = newInd;
                    }
                }

                if (tmpNormInds[j] != -1)
                {
                    if (normIndRewrite.containsKey(tmpNormInds[j]))
                        tmpNormInds[j] = normIndRewrite[tmpNormInds[j]];
                    else
                    {
                        int newInd = mesh.Norms.getSize();
                        mesh.Norms.add(norms[tmpNormInds[j]]);
                        normIndRewrite.add(tmpNormInds[j], newInd);
                        tmpNormInds[j] = newInd;
                    }
                }

                if (tmpTexCoordInds[j] != -1)
                {
                    if (texCoordIndRewrite.containsKey(tmpTexCoordInds[j]))
                    tmpTexCoordInds[j] = texCoordIndRewrite[tmpTexCoordInds[j]];
                    else
                    {
                        int newInd = mesh.TexCoords.getSize();
                        mesh.TexCoords.add(texCoords[tmpTexCoordInds[j]]);
                        texCoordIndRewrite.add(tmpTexCoordInds[j], newInd);
                        tmpTexCoordInds[j] = newInd;
                    }
                }
            }

			if (count == 3)
			{
				triCount += 1;

				if (tmpVertInds[0] != -1 && tmpVertInds[1] != -1 && tmpVertInds[2] != -1)
				{
					mesh.VertInds.add(tmpVertInds[0]);
					mesh.VertInds.add(tmpVertInds[1]);
					mesh.VertInds.add(tmpVertInds[2]);
				}

				if (tmpNormInds[0] != -1 && tmpNormInds[1] != -1 && tmpNormInds[2] != -1)
				{
					mesh.NormInds.add(tmpNormInds[0]);
					mesh.NormInds.add(tmpNormInds[1]);
					mesh.NormInds.add(tmpNormInds[2]);
				}

				if (tmpTexCoordInds[0] != -1 && tmpTexCoordInds[1] != -1 && tmpTexCoordInds[2] != -1)
				{
					mesh.TexCoordInds.add(tmpTexCoordInds[0]);
					mesh.TexCoordInds.add(tmpTexCoordInds[1]);
					mesh.TexCoordInds.add(tmpTexCoordInds[2]);
				}
			}
			else if (count == 4)
			{
				triCount += 2;

				if (tmpVertInds[0] != -1 && tmpVertInds[1] != -1 && tmpVertInds[2] != -1 && tmpVertInds[3] != -1)
				{
					mesh.VertInds.add(tmpVertInds[0]);
					mesh.VertInds.add(tmpVertInds[1]);
					mesh.VertInds.add(tmpVertInds[2]);

					mesh.VertInds.add(tmpVertInds[2]);
					mesh.VertInds.add(tmpVertInds[0]);
					mesh.VertInds.add(tmpVertInds[3]);
				}

				if (tmpNormInds[0] != -1 && tmpNormInds[1] != -1 && tmpNormInds[2] != -1 && tmpNormInds[3] != -1)
				{
					mesh.NormInds.add(tmpNormInds[0]);
					mesh.NormInds.add(tmpNormInds[1]);
					mesh.NormInds.add(tmpNormInds[2]);

					mesh.NormInds.add(tmpNormInds[3]);
					mesh.NormInds.add(tmpNormInds[2]);
					mesh.NormInds.add(tmpNormInds[0]);
				}

				if (tmpTexCoordInds[0] != -1 && tmpTexCoordInds[1] != -1 && tmpTexCoordInds[2] != -1 && tmpTexCoordInds[3] != -1)
				{
					mesh.TexCoordInds.add(tmpTexCoordInds[0]);
					mesh.TexCoordInds.add(tmpTexCoordInds[1]);
					mesh.TexCoordInds.add(tmpTexCoordInds[2]);

					mesh.TexCoordInds.add(tmpTexCoordInds[3]);
					mesh.TexCoordInds.add(tmpTexCoordInds[2]);
					mesh.TexCoordInds.add(tmpTexCoordInds[0]);
				}
			}
		}
		else if (cmd == "o")
		{
            pModel->Name = data;
            //printf("New Model: %s\n", data.c_str());
		}
		else if (cmd == "g")
		{
            //printf("New Mesh: %s\n", data.c_str());
            if (mesh.VertInds.isEmpty())
                mesh.Name = data;
            else
            {
                pModel->Meshes.add(InterMesh());
                pModel->Meshes.getBack().Name = data;
                vertIndRewrite.clear();
                normIndRewrite.clear();
                texCoordIndRewrite.clear();
            }
		}
		else if (cmd == "mtllib")
		{
            ImportMTL(Arc::Arc_Dirname(filename) + "/" + data, materials);
		}
		else if (cmd == "usemtl")
		{
            if (materials.containsKey(data))
            {
                //printf("Using Material: %s\n", data.c_str());
                mesh.Material = materials[data];
            }
		}
    }

    file.close();

    printf("Vert Inds: %d\n", pModel->Meshes[0].VertInds.getSize());
    for (unsigned int i = 0; i < pModel->Meshes[0].VertInds.getSize(); ++i)
    {
        const vec3& vert = pModel->Meshes[0].Verts[pModel->Meshes[0].VertInds[i]];
        printf("(%d, [%f %f %f]) ", pModel->Meshes[0].VertInds[i], vert.x, vert.y, vert.z);
        if (i % 3 == 2)
            printf("\n");
    }
    printf("\n");

    printf("Norm Inds: %d\n", pModel->Meshes[0].NormInds.getSize());
    for (unsigned int i = 0; i < pModel->Meshes[0].NormInds.getSize(); ++i)
    {
        const vec3& norm = pModel->Meshes[0].Norms[pModel->Meshes[0].NormInds[i]];
        printf("(%d, [%f %f %f]) ", pModel->Meshes[0].NormInds[i], norm.x, norm.y, norm.z);
        if (i % 3 == 2)
            printf("\n");
    }
    printf("\n");

    printf("Tex Coord Inds: %d\n", pModel->Meshes[0].TexCoordInds.getSize());
    for (unsigned int i = 0; i < pModel->Meshes[0].TexCoordInds.getSize(); ++i)
    {
        printf("%d ", pModel->Meshes[0].TexCoordInds[i]);
        if (i % 3 == 2)
            printf("\n");
    }
    printf("\n");

    printf("Successfully loaded OBJ File: %s\n", filename.c_str());
    printf("Triangles: %i \n", triCount);

    return true;
}
