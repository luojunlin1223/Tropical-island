#include "renderer.h"
#include <algorithm>

Renderer::Renderer(Window& parent) : OGLRenderer(parent) {
	//--------------------------------------------root----------------------------------------
	root = new SceneNode();
	//-------------------------------------------terrain--------------------------------------
	terrain = new HeightMap(TEXTUREDIR "/heightmap/Height Map.png");
	terrainShader = new Shader("terrainVertex.vert","terrainFragment.frag");
	terrainTex= SOIL_load_OGL_texture(TEXTUREDIR "Grass01_DIF.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	
	terrainBump= SOIL_load_OGL_texture( // Add this line !
		TEXTUREDIR "normal.png", SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	SetTextureRepeating(terrainTex, true);
	SetTextureRepeating(terrainBump,true);

	waterTex = SOIL_load_OGL_texture(
		TEXTUREDIR "water.tga", SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	SetTextureRepeating(waterTex, true);
	waterRotate = 0.0f;
	waterCycle = 0.0f;
	beach= SOIL_load_OGL_texture(TEXTUREDIR "BeachSand_DIF.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	SetTextureRepeating(beach, true);

	//---------------------------------------skybox-----------------------------------------
	skybox_quad = Mesh::GenerateQuad();
	cubeMapTex = SOIL_load_OGL_cubemap(
		TEXTUREDIR "/cubemap/right.jpg", TEXTUREDIR "/cubemap/left.jpg",
		TEXTUREDIR "/cubemap/top.jpg", TEXTUREDIR "/cubemap/bottom.jpg",
		TEXTUREDIR "/cubemap/front.jpg", TEXTUREDIR "/cubemap/back.jpg",
		SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0); 
	skyboxShader = new Shader("skyboxVertex.vert", "skyboxFragment.frag");
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	//-------------------------------------camera&light----------------------------------------
	camera = new Camera(-45.0f, -125.0f, Vector3(0, 15*terrain->GetHeightmapSize().y, 0));

	light = new Light(terrain->GetHeightmapSize() * Vector3(0.0f, 5.0f, 0.0f),
		Vector4(1, 1, 1, 1), 5*terrain->GetHeightmapSize().x);
	DirectionallightShader = new Shader("PerPixelVertex.vert", "LightFragment.frag");
	lightShader = new Shader("PerPixelVertex.vert", "PerPixelFragment.frag");

	//-----------------------------------RockWall--------------------------------------------
	RockWall= Mesh::LoadFromMeshFile("RockWall01.msh");
	RockWall_mat= new MeshMaterial("RockWall01.mat");
	loadMat(RockWall, RockWall_mat,RockWall_matTextures,RockWall_matBumpTextures);
	textured_bump_shader= new Shader("TexturedVertex.vert", "TexturedFragment.frag");
	
	//-----------------------------------Plam--------------------------------------------------
	Palm = Mesh::LoadFromMeshFile("Palm01.msh");
	Palm_mat = new MeshMaterial("Palm01.mat");
	loadMat(Palm, Palm_mat, Palm_matTextures,Palm_matBumpTextures);

	
	//-----------------------------------Rock--------------------------------------------------
	Rock = Mesh::LoadFromMeshFile("Rock01.msh");
	Rock_mat = new MeshMaterial("Rock01.mat");
	loadMat(Rock, Rock_mat, Rock_matTextures, Rock_matBumpTextures);

	//-----------------------------------House--------------------------------------------------
	House = Mesh::LoadFromMeshFile("House02.msh");
	House_mat = new MeshMaterial("House02.mat");
	loadMat(House, House_mat, House_matTextures, House_matBumpTextures);

	//-----------------------------------BoatWreck--------------------------------------------------
	BoatWreck = Mesh::LoadFromMeshFile("BoatWreck.msh");
	BoatWreck_mat = new MeshMaterial("BoatWreck.mat");
	loadMat(BoatWreck, BoatWreck_mat, BoatWreck_matTextures, BoatWreck_matBumpTextures);

	//-----------------------------------Watchtower--------------------------------------------------
	Watchtower = Mesh::LoadFromMeshFile("Watchtower.msh");
	Watchtower_mat = new MeshMaterial("Watchtower.mat");
	loadMat(Watchtower, Watchtower_mat, Watchtower_matTextures, Watchtower_matBumpTextures);


	//----------------------------------Role---------------------------------
	Role = Mesh::LoadFromMeshFile("Role_T.msh");
	Role_mat = new MeshMaterial("Role_T.mat");
	anim = new MeshAnimation("Role_T.anm");
	loadMat(Role, Role_mat, Role_matTextures, Role_matBumpTextures);


	vector<Vector3> Rockwall_ins;

	Rockwall_ins.emplace_back(Vector3(0.0f,0.0f, 0.0f));
	Rockwall_ins.emplace_back(Vector3(0.0f,5.0f, 250.0f));

	vector<Vector3> Palm_ins;

	Palm_ins.emplace_back(Vector3(0.0f, 12.0f, 0.0f));
	Palm_ins.emplace_back(Vector3(13.0f, 14.0f, 20.0f));
	Palm_ins.emplace_back(Vector3(15.0f, 10.0f, -10.0f));
	Palm_ins.emplace_back(Vector3(-30.0f, 10.0f, 20.0f));
	Palm_ins.emplace_back(Vector3(-25.0f, 13.0f, 30.0f));
	Palm_ins.emplace_back(Vector3(-22.0f, 12.0f, -5.0f));
	Palm_ins.emplace_back(Vector3(-7.0f, 12.0f, 17.0f));
	Palm_ins.emplace_back(Vector3(-5.0f, 12.0f, 35.0f));

	vector<Vector3> Rock_ins;
	Rock_ins.emplace_back(Vector3(0.0f, 0.0f, 0.0f));
	Rock_ins.emplace_back(Vector3(-50.0f, -3.0f, -5.0f));
	Rock_ins.emplace_back(Vector3(-20.0f, -1.0f, -25.0f));
	Rock_ins.emplace_back(Vector3(-18.0f, -2.0f, -24.0f));

	Rock_ins.emplace_back(Vector3(-35.0f, -2.0f, -30.0f));
	Rock_ins.emplace_back(Vector3(-34.0f, -3.0f, -32.0f));

	vector<Vector3> house_ins;
	house_ins.emplace_back(Vector3(0.0f, 0.0f, 0.0f));

	vector<Vector3> watchtower_ins;
	watchtower_ins.emplace_back(Vector3(0.0f, 0.0f, 0.0f));

	vector<Vector3> boat_ins;
	boat_ins.emplace_back(Vector3(0.0f, 0.0f, 0.0f));

	vector<Vector3> din_ins;
	din_ins.emplace_back(Vector3(0.0f, 0.0f, 0.0f));


	add_child(Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f) * 300,
		Matrix4::Translation(Vector3(3500, 180, 3500)),
		20000.0f,
		Role,
		Role_matTextures,
		Role_matBumpTextures,
		root, din_ins.size(), din_ins, true);

	add_child(Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f) * 20,
		Matrix4::Translation(Vector3(-2000,0,4000))*Matrix4::Rotation(125.0f,Vector3(0,1,0)),
		20000.0f,
		RockWall,
		RockWall_matTextures,
		RockWall_matBumpTextures,
		root, Rockwall_ins.size(), Rockwall_ins,false);

	add_child(Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f) * 100,
		Matrix4::Translation(Vector3(20000,-1700,2000)),
		20000.0f,
		Palm,
		Palm_matTextures,
		Palm_matBumpTextures,
		root, Palm_ins.size(), Palm_ins, false);

	add_child(Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f) * 100,
		Matrix4::Translation(Vector3(20000, -3000, 2000)),
		20000.0f,
		Rock,
		Rock_matTextures,
		Rock_matBumpTextures,
		root, Rock_ins.size(), Rock_ins, false);

	add_child(Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f) * 100,
		Matrix4::Translation(Vector3(20000, -3800, -3000)),
		20000.0f,
		House,
		House_matTextures,
		House_matBumpTextures,
		root, house_ins.size(), house_ins, false);

	add_child(Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f) * 50,
		Matrix4::Translation(Vector3(0,-9000,1000))*Matrix4::Rotation(60.0f,Vector3(0,0,1))*Matrix4::Translation(Vector3(20000, -4000, -2000)),
		20000.0f,
		BoatWreck,
		BoatWreck_matTextures,
		BoatWreck_matBumpTextures,
		root, boat_ins.size(), boat_ins, false);

	add_child(Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f) * 100,
		Matrix4::Translation(Vector3(20000, -3300, 2000)),
		20000.0f,
		Watchtower,
		Watchtower_matTextures,
		Watchtower_matBumpTextures,
		root, watchtower_ins.size(), watchtower_ins, false);


	



	projMatrix = Matrix4::Perspective(1.0f, 20000.0f,
		(float)width / (float)height, 45.0f);
	if (!skyboxShader->LoadSuccess() || !terrainShader->LoadSuccess()||!DirectionallightShader->LoadSuccess()||!textured_bump_shader->LoadSuccess()) {
		return;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	init = true;
}
Renderer ::~Renderer(void) {
	delete skybox_quad;
	delete skyboxShader;
}
void Renderer::UpdateScene(float dt) {
	camera->UpdateCamera(dt);
	viewMatrix = camera->BuildViewMatrix();
	waterRotate += dt * 0.1f; //2 degrees a second
	waterCycle += dt * 0.1f; // 10 units a second
	frameFrustum.FromMatrix(projMatrix * viewMatrix);
	root->Update(dt);
	frameTime -= dt;
	while (frameTime < 0.0) {
		currentFrame = (currentFrame + 1) % anim->GetFrameCount();
		frameTime += 1.0f / anim->GetFrameRate();
	}
}
void Renderer::RenderScene() {
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	DrawSkybox();
	DrawTerrain();

	BuildNodeLists(root);
	SortNodeLists();
	BindShader(textured_bump_shader);
	UpdateShaderMatrices();
	glUniform1i(glGetUniformLocation(textured_bump_shader->GetProgram(), "diffuseTex"), 0);
	glUniform1i(glGetUniformLocation(textured_bump_shader->GetProgram(), "bumpTex"), 1);
	
	vector < Matrix4 > frameMatrices;

	const Matrix4* invBindPose = Role->GetInverseBindPose();
	const Matrix4* frameData = anim->GetJointData(currentFrame);

	for (unsigned int i = 0; i < Role->GetJointCount(); ++i) {
		frameMatrices.emplace_back(frameData[i] * invBindPose[i]);
	}

	int j = glGetUniformLocation(textured_bump_shader->GetProgram(), "joints");
	glUniformMatrix4fv(j, frameMatrices.size(), false, (float*)frameMatrices.data());

	Vector3 temp = camera->GetPosition();
	Vector3* temp2 = &temp;
	glUniform3fv(glGetUniformLocation(terrainShader->GetProgram(),
		"cameraPos"), 2, (float*)temp2);
	SetShaderLight(*light);
	DrawNodes();
	ClearNodeLists();
	
}
void Renderer::DrawSkybox() {
	glDepthMask(GL_FALSE);
	//绘制天空盒时，我们需要将它变为场景中的第一个渲染的物体，并且禁用深度写入。这样子天空盒就会永远被绘制在其它物体的背后了。
	BindShader(skyboxShader);
	UpdateShaderMatrices();
	skybox_quad->Draw();
	glDepthMask(GL_TRUE);
}

void Renderer::DrawTerrain() {
	BindShader(terrainShader);

	glUniform1i(glGetUniformLocation(terrainShader->GetProgram(),
		"diffuseTex"), 0);

	Vector3 temp= camera->GetPosition();
	Vector3* temp2 = &temp;

	glUniform3fv(glGetUniformLocation(terrainShader->GetProgram(),
		"cameraPos"),1,(float*)temp2);

	glUniform1i(glGetUniformLocation(
		terrainShader->GetProgram(), "cubeTex"), 2);

	glUniform1i(glGetUniformLocation(terrainShader->GetProgram(),
		"waterTex"), 3);

	glUniform1i(glGetUniformLocation(
		terrainShader->GetProgram(), "bumpTex"), 4);

	glUniform1i(glGetUniformLocation(
		terrainShader->GetProgram(), "beachTex"), 5);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, terrainTex);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP,cubeMapTex);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, waterTex);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, terrainBump);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, beach);

	
	Vector3 hSize = terrain->GetHeightmapSize();
	
	modelMatrix =
		Matrix4::Translation(Vector3(0, 20, 0)) *
		Matrix4::Scale(Vector3(2, 3, 2));
		


	textureMatrix =
		Matrix4::Translation(Vector3(waterCycle, 0.0f, waterCycle)) *
		Matrix4::Scale(Vector3(1/15.0f, 1 / 15.0f, 1 / 15.0f)) *
		Matrix4::Rotation(waterRotate, Vector3(0, 0, 1));
	

	UpdateShaderMatrices();

	SetShaderLight(*light);

	terrain->Draw();
}


void Renderer::BuildNodeLists(SceneNode* from) {
	if (frameFrustum.InsideFrustum(*from)) {
		Vector3 dir = from->GetWorldTransform().GetPositionVector() -
			camera->GetPosition();
		from->SetCameraDistance(Vector3::Dot(dir, dir));

		if (from->GetColour().w < 1.0f) {
			transparentNodeList.push_back(from);
		}
		else {
			nodeList.push_back(from);
		}

	}
	for (vector < SceneNode* >::const_iterator i =
		from->GetChildIteratorStart();
		i != from->GetChildIteratorEnd(); ++i) {
		BuildNodeLists((*i));
	}
}


void Renderer::SortNodeLists() {
	std::sort(transparentNodeList.rbegin(), // note the r!
		transparentNodeList.rend(), // note the r!  
		SceneNode::CompareByCameraDistance);
	std::sort(nodeList.begin(),
		nodeList.end(),
		SceneNode::CompareByCameraDistance);
}

void Renderer::DrawNodes() {
	for (const auto& i : nodeList) {
		DrawNode(i);

	}
	for (const auto& i : transparentNodeList) {
		DrawNode(i);
	}
}

void Renderer::DrawNode(SceneNode* n) {
	if (n->GetMesh()) {
		Matrix4 model = n->GetWorldTransform() *
			Matrix4::Scale(n->GetModelScale());
		glUniformMatrix4fv(
			glGetUniformLocation(textured_bump_shader->GetProgram(), "modelMatrix"), 1, false, model.values);
		//glUniform4fv(glGetUniformLocation(tree_shader->GetProgram(), "nodeColour"), 1, (float*)&n->GetColour());

		if (n->GetAnimation()) {
			glUniform1i(glGetUniformLocation(textured_bump_shader->GetProgram(), "useAnimation"), anim->GetFrameCount());
		}
		else {
			glUniform1i(glGetUniformLocation(textured_bump_shader->GetProgram(), "useAnimation"), 0);
		}

		vector<GLuint> diff_temp = n->GetMatTextures();
		vector<GLuint> bump_temp = n->GetMatBumpTextures();
		for (GLint j = 0; j < n->GetDrawTimes(); j++) {
			string index;
			index = std::to_string(j);
			vector<Vector3> instance = n->GetInstance_location();

			glUniform3f(
				glGetUniformLocation(textured_bump_shader->GetProgram(), ("offsets[" + index + "]").c_str()),
				instance.at(j).x, 
				instance.at(j).y,
				instance.at(j).z);
		}
		for (int i = 0; i < diff_temp.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, diff_temp[i]);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, bump_temp[i]);


			n->GetMesh()->DrawSubMesh(i, n->GetDrawTimes());
		}
	}
}

void Renderer::ClearNodeLists() {
	transparentNodeList.clear();
	nodeList.clear();
}

void Renderer::loadMat(Mesh* mesh, MeshMaterial* mat, vector <GLuint>& matTextures,vector<GLuint>& BumpTextures) {
	for (int i = 0; i < mesh->GetSubMeshCount(); ++i) {//例子有5个mesh
		const MeshMaterialEntry* matEntry = mat->GetMaterialForLayer(i);//RealisticCharacter/Role/Hair.tag 

		const string* filename = nullptr;
		matEntry->GetEntry("Diffuse", &filename);
		string path = TEXTUREDIR + *filename;         //+		path	"../Textures//RealisticCharacter/Role/Hair.tga"	std::string
		GLuint texID = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		matTextures.emplace_back(texID);   //使用了多个纹理贴图 对应不同的mesh

		matEntry->GetEntry("Bump", &filename);
		path = TEXTUREDIR + *filename;         //+		path	"../Textures//RealisticCharacter/Role/Hair.tga"	std::string
		texID = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		BumpTextures.emplace_back(texID);
	}

}

void Renderer::add_child(Vector4 color, Vector3 scale, Matrix4 trans, float Radius
	, Mesh* mesh, vector <GLuint> mat,vector<GLuint> bump, SceneNode* root, GLuint draw_times, vector<Vector3> instance
,bool animation) {
	SceneNode* s = new SceneNode();
	s->SetColour(color);
	s->SetModelScale(scale);
	s->SetTransform(trans);
	s->SetBoundingRadius(Radius);
	s->SetMesh(mesh);
	s->SetMatTextures(mat);
	s->SetDrawTimes(draw_times);
	s->SetInstance_location(instance);
	s->SetMatBumpTextures(bump);
	s->SetAnimation(animation);
	root->AddChild(s);
}