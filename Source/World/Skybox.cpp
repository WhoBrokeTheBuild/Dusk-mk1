#include "Skybox.h"

#include <Program.h>
#include <Graphics/GraphicsSystem.h>
#include <Graphics/ShaderManager.h>
#include <Graphics/Texture.h>
#include <Graphics/Mesh.h>
#include <World/Camera.h>
#include <Logging/Log.h>

using namespace Dusk::Logging;

Dusk::World::Skybox::~Skybox( void )
{
    delete mp_Mesh;
    mp_Mesh = nullptr;

    delete mp_Texture;
    mp_Texture = nullptr;
}

bool Dusk::World::Skybox::load( const string& filename )
{
    LogInfoFmt(getClassName(), "Load from file \"%s\"", filename.c_str());
    mp_Texture = New Texture();
    if ( ! mp_Texture->load(filename))
    {
        LogErrorFmt(getClassName(), "Failed to load texture \"%s\"", filename.c_str());
        return false;
    }

	const GLfloat SKYBOX_SCALE = 1000.0f;

	const unsigned int SKYBOX_VERT_COUNT = 24;

	vec3 skyboxVerts[SKYBOX_VERT_COUNT] = {
		vec3(-1.0f,  1.0f, -1.0f), vec3( 1.0f,  1.0f, -1.0f), vec3( 1.0f, -1.0f, -1.0f), vec3(-1.0f, -1.0f, -1.0f), // Front
		vec3(-1.0f,  1.0f,  1.0f), vec3(-1.0f,  1.0f, -1.0f), vec3(-1.0f, -1.0f, -1.0f), vec3(-1.0f, -1.0f,  1.0f), // Left
		vec3( 1.0f,  1.0f,  1.0f), vec3(-1.0f,  1.0f,  1.0f), vec3(-1.0f, -1.0f,  1.0f), vec3( 1.0f, -1.0f,  1.0f), // Back
		vec3( 1.0f,  1.0f, -1.0f), vec3( 1.0f,  1.0f,  1.0f), vec3( 1.0f, -1.0f,  1.0f), vec3( 1.0f, -1.0f, -1.0f), // Right
		vec3(-1.0f,  1.0f,  1.0f), vec3( 1.0f,  1.0f,  1.0f), vec3( 1.0f,  1.0f, -1.0f), vec3(-1.0f,  1.0f, -1.0f), // Top
		vec3(-1.0f, -1.0f,  1.0f), vec3( 1.0f, -1.0f,  1.0f), vec3( 1.0f, -1.0f, -1.0f), vec3(-1.0f, -1.0f, -1.0f)  // Bottom
	};

	const GLfloat ONE_FOURTH   = 0.25f;
	const GLfloat TWO_FOURTH   = 0.5f;
	const GLfloat THREE_FOURTH = 0.75f;
	const GLfloat ONE_THIRD    = 1.0f / 3.0f + 0.0015f;
	const GLfloat TWO_THIRD    = 2.0f / 3.0f - 0.0015f;

	vec2 skyboxTexCoords[SKYBOX_VERT_COUNT] = {
		vec2( ONE_FOURTH,   TWO_THIRD ), vec2( TWO_FOURTH,   TWO_THIRD ), vec2( TWO_FOURTH,   ONE_THIRD ), vec2( ONE_FOURTH,   ONE_THIRD ), // Front
		vec2( 0.0f,         TWO_THIRD ), vec2( ONE_FOURTH,   TWO_THIRD ), vec2( ONE_FOURTH,   ONE_THIRD ), vec2( 0.0f,         ONE_THIRD ), // Left
		vec2( THREE_FOURTH, TWO_THIRD ), vec2( 1.0f,         TWO_THIRD ), vec2( 1.0f,         ONE_THIRD ), vec2( THREE_FOURTH, ONE_THIRD ), // Back
		vec2( TWO_FOURTH,   TWO_THIRD ), vec2( THREE_FOURTH, TWO_THIRD ), vec2( THREE_FOURTH, ONE_THIRD ), vec2( TWO_FOURTH,   ONE_THIRD ), // Right
		vec2( ONE_FOURTH,   1.0f      ), vec2( TWO_FOURTH,   1.0f      ), vec2( TWO_FOURTH,   TWO_THIRD ), vec2( ONE_FOURTH,   TWO_THIRD ), // Up
		vec2( ONE_FOURTH,   0.0f      ), vec2( TWO_FOURTH,   0.0f      ), vec2( TWO_FOURTH,   ONE_THIRD ), vec2( ONE_FOURTH,   ONE_THIRD )  // Down
	};

	for (unsigned int i = 0; i < SKYBOX_VERT_COUNT; ++i)
		skyboxVerts[i] *= SKYBOX_SCALE;

    mp_Mesh = New Mesh();
    mp_Mesh->init(GL_QUADS, SKYBOX_VERT_COUNT, skyboxVerts, nullptr, skyboxTexCoords);

    return true;
}

void Dusk::World::Skybox::render( void )
{
    ShaderManager* pShaderManager = Program::getInstance().getGraphicsSystem()->getShaderManager();
    Camera* pCamera = Program::getInstance().getCamera();

    pShaderManager->useProgram("skybox");

	mat4x4 mView = pCamera->getViewMatrix();
	mat4x4 mProj = pCamera->getProjectionMatrix();
	mat4x4 mViewProj = mProj * mView;

	glm::mat4x4 mModel = mat4(1.0f);
	glm::mat4x4 mModelViewProj;

	mModel = glm::translate(mModel, pCamera->getPos());

	static GLint m4ModelViewProjLoc = pShaderManager->getUniformLocation("uModelViewProj");
	static GLint uTexLoc            = pShaderManager->getUniformLocation("uTex");

	mModelViewProj = mViewProj * mModel;

	pShaderManager->setUniformMatrix4fv(m4ModelViewProjLoc, 1, &mModelViewProj);
	pShaderManager->setUniform1i(uTexLoc,   0);

	glActiveTexture(GL_TEXTURE0);
    mp_Texture->bind();

    mp_Mesh->render();
}
