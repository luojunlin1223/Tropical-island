#pragma once
#include "../nclgl/OGLRenderer.h"
#include "../nclgl/Camera.h"
#include "../nclgl/HeightMap.h"
#include "../nclgl/Light.h"
#include "../nclgl/MeshMaterial.h"
#include "../nclgl/SceneNode.h"
#include <nclgl/Frustum.h>
#include "../nclgl/MeshAnimation.h"
class Renderer : public OGLRenderer {
public:
	Renderer(Window& parent);
	virtual ~Renderer(void);
	virtual void RenderScene();
	virtual void UpdateScene(float dt);
	void DrawSkybox();
	void DrawTerrain();
	void loadMat(Mesh* mesh, MeshMaterial* mat, vector <GLuint>& matTextures, vector<GLuint>& BumpTextures);
	void add_child(Vector4 color, Vector3 scale, Matrix4 trans
		,float Radius,Mesh* mesh, vector <GLuint> mat, vector<GLuint> bump,SceneNode* root,GLuint draw_times, vector<Vector3> instance,bool animation);
protected:
	SceneNode* root;
	
	Shader* terrainShader;
	Shader* skyboxShader;
	Shader* DirectionallightShader;
	Shader* lightShader;
	Shader* textured_bump_shader;

	GLuint cubeMapTex;
	GLuint terrainTex;
	GLuint beach;
	GLuint waterTex;
	GLuint terrainBump;

	Camera* camera;

	Mesh* skybox_quad;
	HeightMap* terrain;

	Mesh* RockWall;
	MeshMaterial* RockWall_mat;
	vector <GLuint> RockWall_matTextures;
	vector <GLuint> RockWall_matBumpTextures;

	Mesh* Palm;
	MeshMaterial* Palm_mat;
	vector <GLuint> Palm_matTextures;
	vector <GLuint> Palm_matBumpTextures;


	Mesh* BoatWreck;
	MeshMaterial* BoatWreck_mat;
	vector <GLuint> BoatWreck_matTextures;
	vector <GLuint> BoatWreck_matBumpTextures;

	Mesh* House;
	MeshMaterial* House_mat;
	vector <GLuint> House_matTextures;
	vector <GLuint> House_matBumpTextures;

	Mesh* Rock;
	MeshMaterial* Rock_mat;
	vector <GLuint> Rock_matTextures;
	vector <GLuint> Rock_matBumpTextures;

	Mesh* Watchtower;
	MeshMaterial* Watchtower_mat;
	vector <GLuint> Watchtower_matTextures;
	vector <GLuint> Watchtower_matBumpTextures;

	Mesh* Role;
	MeshMaterial* Role_mat;
	vector <GLuint> Role_matTextures;
	vector <GLuint> Role_matBumpTextures;
	MeshAnimation* anim;

	Light* light;


	float waterRotate;
	float waterCycle;


	void BuildNodeLists(SceneNode* from);
	void SortNodeLists();
	void ClearNodeLists();
	void DrawNodes();
	void DrawNode(SceneNode* n);

	vector <SceneNode*> transparentNodeList;
	vector <SceneNode*> nodeList;
	Frustum frameFrustum;

	int currentFrame;
	float frameTime;
};
