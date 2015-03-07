#include "Mesh.h"

const Dusk::Graphics::GLAttribute Dusk::Graphics::Mesh::ATTR_VERTEX     = 0;
const Dusk::Graphics::GLAttribute Dusk::Graphics::Mesh::ATTR_NORMAL     = 1;
const Dusk::Graphics::GLAttribute Dusk::Graphics::Mesh::ATTR_TEX_COORD  = 2;

bool Dusk::Graphics::Mesh::init( const string& name, const GLPrimitiveType& primitiveType, const ArrayList<vec3>& vertexes, const ArrayList<vec3>& normals /* = ArrayList<vec3>() */, const ArrayList<vec2>& texCoords /* = ArrayList<vec2>() */ )
{
    float* pVertexes = nullptr;
    float* pNormals = nullptr;
    float* pTexCoords = nullptr;

    if (vertexes.isEmpty()) return false;

    unsigned int vertexCount = vertexes.getSize();
    pVertexes = (float*)&vertexes[0];

    if ( ! normals.isEmpty())
        pNormals = (float*)&normals[0];

    if ( ! texCoords.isEmpty())
        pTexCoords = (float*)&texCoords[0];

    return init(name, primitiveType, vertexCount, pVertexes, pNormals, pTexCoords);
}

bool Dusk::Graphics::Mesh::init( const string& name, const GLPrimitiveType& primitiveType, const unsigned int& vertexCount, const vec3* pVertexes, const vec3* pNormals /* = nullptr */, const vec2* pTexCoords /* = nullptr */ )
{
    return init(name, primitiveType, vertexCount, (const float*)pVertexes, (const float*)pNormals, (const float*)pTexCoords);
}

bool Dusk::Graphics::Mesh::init( const string& name, const GLPrimitiveType& primitiveType, const unsigned int& vertexCount, const float* pVertexes, const float* pNormals /* = nullptr */, const float* pTexCoords /* = nullptr */ )
{
    term();

    m_Name = name;
    m_PrimitiveType = primitiveType;
    m_VertexCount = vertexCount;

    m_VertexBuffer = m_NormalBuffer = m_TexCoordBuffer = 0;
    m_VertexArray = 0;

    if (m_VertexCount == 0)
        return false;

    if (pVertexes == nullptr)
        return false;

    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_VertexCount, pVertexes, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(ATTR_VERTEX);
    glVertexAttribPointer(ATTR_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, 0);

    if (pNormals != nullptr)
    {
        glGenBuffers(1, &m_NormalBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_NormalBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_VertexCount, pNormals, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(ATTR_NORMAL);
        glVertexAttribPointer(ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }

    if (pTexCoords != nullptr)
    {
        glGenBuffers(1, &m_TexCoordBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * m_VertexCount, pTexCoords, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(ATTR_TEX_COORD);
        glVertexAttribPointer(ATTR_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    glBindVertexArray(0);

    return true;
}

void Dusk::Graphics::Mesh::term( void )
{
    if (m_VertexBuffer != 0)
        glDeleteBuffers(1, &m_VertexBuffer);

    if (m_NormalBuffer != 0)
        glDeleteBuffers(1, &m_NormalBuffer);

    if (m_TexCoordBuffer != 0)
        glDeleteBuffers(1, &m_TexCoordBuffer);

    if (m_VertexArray != 0)
        glDeleteVertexArrays(1, &m_VertexArray);

    delete mp_Material;
}

void Dusk::Graphics::Mesh::render( void )
{
    if (m_VertexArray == 0)
        return;

    if (mp_Material)
        mp_Material->bind();

    glBindVertexArray(m_VertexArray);

    glDrawArrays(m_PrimitiveType, 0, m_VertexCount);

    glBindVertexArray(0);
}
