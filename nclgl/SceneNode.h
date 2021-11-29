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
	* @brief ����һ������ڵ� Ĭ����ɫΪ1 1 1 1
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
	* @brief �ݹ����ÿһ����������� ���е��ӽڵ㶼Ҫ���Ը��ڵ����������
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
	SceneNode* parent; //���ڵ�
	Mesh* mesh; //��ǰ�ڵ��������
	Matrix4 worldTransform;//��ǰ�ڵ����������
	Matrix4 transform;//��ǰ�ڵ�ı任����
	Vector3 modelScale;//��ǰ�ڵ�Ĵ�С
	Vector4 colour;//��ǰ�ڵ����ɫ
	std::vector <SceneNode*> children;//�ӽڵ�
	float distanceFromCamera;
	float boundingRadius;
	GLuint draw_times;
	
	MeshMaterial* mat;
	vector <GLuint> matTextures;
	vector <GLuint> matBumpTextures;
	
	vector<Vector3> instanced_location;
	bool animation;
};

