#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Mesh.h"
#include <vector>
#include "MeshMaterial.h"

class SceneNode {
public:
	/**
	* @brief 创建一个景物节点 默认颜色为1 1 1 1
	*/
	SceneNode(Mesh* m = NULL, Vector4 colour = Vector4(1, 1, 1, 1));
	~SceneNode(void);

	void SetTransform(const Matrix4& matrix) { transform = matrix; }
	const Matrix4& GetTransform() const { return transform; }
	Matrix4 GetWorldTransform() const { return worldTransform; }

	Vector4 GetColour() const { return colour; }
	void SetColour(Vector4 c) { colour = c; }

	Vector3 GetModelScale() const { return modelScale; }
	void SetModelScale(Vector3 s) { modelScale = s; }

	Mesh* GetMesh() const { return mesh; }
	void SetMesh(Mesh* m) { mesh = m; }

	void AddChild(SceneNode* s);
	/**
	* @brief 递归更新每一个物体的坐标 所有的子节点都要乘以父节点的世界坐标
	*/
	virtual void Update(float dt);
	virtual void Draw(const OGLRenderer& r);

	std::vector <SceneNode*>::const_iterator GetChildIteratorStart() {
		return children.begin();
	}
	std::vector <SceneNode*>::const_iterator GetChildIteratorEnd() {
		return children.end();
	}

	float GetBoundingRadius() const { return boundingRadius; }
	void SetBoundingRadius(float f) { boundingRadius = f; }
	
	float GetCameraDistance() const { return distanceFromCamera; }
	void SetCameraDistance(float f) { distanceFromCamera = f; }

	static bool CompareByCameraDistance(SceneNode * a, SceneNode * b) {
		return (a->distanceFromCamera <b->distanceFromCamera) ? true : false;
	}

	void SetMatTextures(vector <GLuint> mat) { this->matTextures = mat; }
	vector <GLuint> GetMatTextures() { return matTextures; }

	void SetMatBumpTextures(vector <GLuint> mat) { this->matBumpTextures = mat; }
	vector <GLuint> GetMatBumpTextures() { return matBumpTextures; }

	GLuint GetDrawTimes() { return draw_times; }
	void SetDrawTimes(GLuint t) { draw_times = t; }

	vector<Vector3> GetInstance_location() { return instanced_location; }
	void SetInstance_location(vector<Vector3> v) { instanced_location = v; }

	bool GetAnimation() const { return animation; }
	void SetAnimation(bool b) { animation = b; }

protected:
	SceneNode* parent; //父节点
	Mesh* mesh; //当前节点的网格体
	Matrix4 worldTransform;//当前节点的世界坐标
	Matrix4 transform;//当前节点的变换矩阵
	Vector3 modelScale;//当前节点的大小
	Vector4 colour;//当前节点的颜色
	std::vector <SceneNode*> children;//子节点
	float distanceFromCamera;
	float boundingRadius;
	GLuint draw_times;
	
	MeshMaterial* mat;
	vector <GLuint> matTextures;
	vector <GLuint> matBumpTextures;
	
	vector<Vector3> instanced_location;
	bool animation;
};

