#pragma once
#include"..//nclgl/SceneNode.h"
class CubeRobot:public SceneNode
{
public:
	/**
	* @brief ����һ��������
	* @param cube ����������ʹ�õĻ�������������
	*/
	CubeRobot(Mesh * cube);
	~CubeRobot(void) {};
	void Update(float dt) override;
	
protected:
	SceneNode * head;
	SceneNode * leftArm;
	SceneNode * rightArm;
};

