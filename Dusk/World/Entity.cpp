#include "Entity.h"

#include <Program.h>
#include <Graphics/GraphicsSystem.h>
#include <Graphics/ShaderManager.h>
#include <Graphics/Mesh.h>
#include <Graphics/Model.h>
#include <World/Camera.h>

using namespace Dusk::Graphics;

Dusk::World::Entity::Entity( void ) :
    m_Pos(0.0f),
    m_Rot(0.0f),
    m_Scale(1.0f),
    m_Models()
{ }

Dusk::World::Entity::~Entity( void )
{
    for (auto it = m_Models.itBegin(); it != m_Models.itEnd(); ++it)
        delete (*it);
    m_Models.clear();
}

bool Dusk::World::Entity::init( void )
{

    return true;
}

void Dusk::World::Entity::render( void )
{
    ShaderManager* pShaderManager = Program::Inst()->getGraphicsSystem()->getShaderManager();

	mat4x4 mView = Program::Inst()->getCamera()->getViewMatrix();
	mat4x4 mProj = Program::Inst()->getCamera()->getProjectionMatrix();
	mat4x4 mViewProj = mProj * mView;

    Program::Inst()->getGraphicsSystem()->getShaderManager()->useProgram("entity");

	glm::mat4x4 mModel = mat4(1.0f);
	glm::mat4x4 mModelView, mModelViewProj;

	mModel = glm::translate(mModel, m_Pos);
	mModel = glm::scale(mModel, m_Scale);

	mModel = glm::translate(mModel, vec3(0.5f, 0.0f, 0.5f));

	mModel = glm::rotate(mModel, m_Rot.x, vec3(1.0f, 0.0f, 0.0f));
	mModel = glm::rotate(mModel, m_Rot.y, vec3(0.0f, 1.0f, 0.0f));
	mModel = glm::rotate(mModel, m_Rot.z, vec3(0.0f, 0.0f, 1.0f));

	mModel = glm::translate(mModel, vec3(-0.5f, 0.0f, -0.5f));

    mModelView = mView * mModel;
	mModelViewProj = mViewProj * mModel;

	static GLint m4ModelViewLoc      = pShaderManager->getUniformLocation("uModelView");
	static GLint m4ModelViewProjLoc  = pShaderManager->getUniformLocation("uModelViewProj");
	static GLint v3GlobalAmbientLoc  = pShaderManager->getUniformLocation("uGlobalAmbient");
	static GLint v3LightColorLoc     = pShaderManager->getUniformLocation("uLightColor");
	static GLint v3LightDirectionLoc = pShaderManager->getUniformLocation("uLightDirection");

	pShaderManager->setUniformMatrix4fv(m4ModelViewProjLoc, 1, &mModelViewProj);
	pShaderManager->setUniformMatrix4fv(m4ModelViewLoc,     1, &mModelView);

	pShaderManager->setUniform3f(v3GlobalAmbientLoc,  vec3(1.0f));
	pShaderManager->setUniform3f(v3LightColorLoc,     vec3(1.0f));
	pShaderManager->setUniform3f(v3LightDirectionLoc, vec3(-1.0f));

    for (auto it = m_Models.itBegin(); it != m_Models.itEnd(); ++it)
    {
        Model* pModel = (*it);

        const ArrayList<Mesh*>& pMeshes = pModel->getMeshList();
        for (auto meshIt = pMeshes.itConstBegin(); meshIt != pMeshes.itConstEnd(); ++meshIt)
        {
            Mesh* pMesh = (*meshIt);
            pMesh->render();
        }
    }

}

bool Dusk::World::Entity::addModel( Model* pModel )
{
    if (!pModel)
        return false;

    m_Models.add(pModel);
    return true;
}
