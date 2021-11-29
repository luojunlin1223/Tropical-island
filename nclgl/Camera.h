#pragma once
#include "Matrix4.h"
#include "Vector3.h"

class Camera
{
public:
	Camera(void) {
		yaw = 0.0f;
		pitch = 0.0f;
		lock = true;
		
	};
	Camera(float pitch, float yaw, Vector3 position) {
		this-> pitch = pitch;
		this-> yaw = yaw;
		this-> position = position;
		this-> lock = true;
	}
	~Camera(void) {};
	/**
	* @brief ��������ĸ������� ���������� λ�õȵ�
	* @param dt ��λ�ı�Ĳ���
	*/
	void UpdateCamera(float dt = 1.0f);
	/**
	* @brief �������ƶ����� ����viewmatrix
	*/
	Matrix4 BuildViewMatrix();

	Vector3 GetPosition() const { return position; }
	void SetPosition(Vector3 val) { position = val; }

	float GetYaw() const { return yaw; }
	void SetYaw(float y) { yaw = y; }

	float GetPitch() const { return pitch; }
	void SetPitch(float p) { pitch = p; }

protected:
	float yaw;//ƫ��
	float pitch;//����
	//roll ����
	Vector3 position; // Set to 0 ,0 ,0 by Vector3 constructor ;)
	bool lock;
};

