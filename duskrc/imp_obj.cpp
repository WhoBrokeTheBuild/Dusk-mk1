#include "imp_obj.h"

bool import_obj( const string& filename, DuskInterModel* pModel )
{
    std::ifstream file(filename.c_str());

    string line;
    while (std::getline(file, line))
    {
        if (line.size() < 2 || line[0] == '#')
            continue;

        if (line[0] == 'v')
        {
            if (line[1] == 't') // Texture Vertex
            {

            }
            else if (line[1] == 'n') // Normal
            {

            }
            else if (line[1] == ' ') // Vertex
            {

            }
        }
        else if (line[0] == 'f') // Face
        {

        }
        else if (line[0] == 'o' || line[0] == 'g') // Object/Group
        {

        }
    }

    file.close();

    return true;
}
