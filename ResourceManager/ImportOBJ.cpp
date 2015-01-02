#include "ImportOBJ.h"

#include <fstream>
#include <sstream>
#include <glm/glm.hpp>

#include "Functions.h"
#include "ArrayList.h"

using glm::vec3;
using glm::vec2;

bool ImportOBJ( const string& filename, InterModel* pModel )
{
    std::ifstream file(filename.c_str());

    if (!file.is_open())
    {
        error("Cannot open file");
    }

	int triCount = 0;

    string line;
    while (std::getline(file, line))
    {
        if (line.size() < 2 || line[0] == '#')
            continue;

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

			pModel->Verts.add(vert);
		}
		else if (cmd == "vt")
		{
			static vec2 coord;

			ss >> coord.x >> coord.y;

			pModel->TexCoords.add(coord);
		}
		else if (cmd == "vn")
		{
			static vec3 norm;

			ss >> norm.x >> norm.y >> norm.z;

			pModel->Norms.add(norm);
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

				for (unsigned int j = 0; j < piece.size(); ++j)
				{
					if (piece[j] == '/')
						piece[j] = ' ';
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
					ssPiece >> tmpNormInds[i];

					--tmpVertInds[i];
					--tmpTexCoordInds[i];
					--tmpNormInds[i];
				}
			}

			if (count == 3)
			{
				triCount += 1;

				if (tmpVertInds[0] != -1 && tmpVertInds[1] != -1 && tmpVertInds[2] != -1)
				{
					pModel->VertInds.add(tmpVertInds[0]);
					pModel->VertInds.add(tmpVertInds[1]);
					pModel->VertInds.add(tmpVertInds[2]);
				}

				if (tmpNormInds[0] != -1 && tmpNormInds[1] != -1 && tmpNormInds[2] != -1)
				{
					pModel->NormInds.add(tmpNormInds[0]);
					pModel->NormInds.add(tmpNormInds[1]);
					pModel->NormInds.add(tmpNormInds[2]);
				}

				if (tmpTexCoordInds[0] != -1 && tmpTexCoordInds[1] != -1 && tmpTexCoordInds[2] != -1)
				{
					pModel->TexCoordInds.add(tmpTexCoordInds[0]);
					pModel->TexCoordInds.add(tmpTexCoordInds[1]);
					pModel->TexCoordInds.add(tmpTexCoordInds[2]);
				}
			}
			else if (count == 4)
			{
				triCount += 2;

				if (tmpVertInds[0] != -1 && tmpVertInds[1] != -1 && tmpVertInds[2] != -1 && tmpVertInds[3] != -1)
				{
					pModel->VertInds.add(tmpVertInds[0]);
					pModel->VertInds.add(tmpVertInds[1]);
					pModel->VertInds.add(tmpVertInds[2]);

					pModel->VertInds.add(tmpVertInds[0]);
					pModel->VertInds.add(tmpVertInds[2]);
					pModel->VertInds.add(tmpVertInds[3]);
				}

				if (tmpNormInds[0] != -1 && tmpNormInds[1] != -1 && tmpNormInds[2] != -1 && tmpNormInds[3] != -1)
				{
					pModel->NormInds.add(tmpNormInds[0]);
					pModel->NormInds.add(tmpNormInds[1]);
					pModel->NormInds.add(tmpNormInds[2]);

					pModel->NormInds.add(tmpNormInds[0]);
					pModel->NormInds.add(tmpNormInds[2]);
					pModel->NormInds.add(tmpNormInds[3]);
				}

				if (tmpTexCoordInds[0] != -1 && tmpTexCoordInds[1] != -1 && tmpTexCoordInds[2] != -1 && tmpTexCoordInds[3] != -1)
				{
					pModel->TexCoordInds.add(tmpTexCoordInds[0]);
					pModel->TexCoordInds.add(tmpTexCoordInds[1]);
					pModel->TexCoordInds.add(tmpTexCoordInds[2]);

					pModel->TexCoordInds.add(tmpTexCoordInds[0]);
					pModel->TexCoordInds.add(tmpTexCoordInds[2]);
					pModel->TexCoordInds.add(tmpTexCoordInds[3]);
				}
			}
		}
		else if (cmd == "o" || cmd == "g")
		{
            pModel->Name = data;
		}
		else if (cmd == "mtllib")
		{
		}
		else if (cmd == "usemtl")
		{
		}
    }

    file.close();

    printf("Successfully loaded OBJ File: %s\n", filename.c_str());
    printf("Triangles: %i \n", triCount);

    return true;
}
