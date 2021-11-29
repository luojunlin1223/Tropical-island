#pragma once
/*
Class:OGLRenderer
Author:Rich Davison	 <richard-gordon.davison@newcastle.ac.uk>
Description:Abstract base class for the graphics tutorials. Creates an OpenGL 
3.2+ CORE PROFILE rendering context. Each lesson will create a renderer that 
inherits from this class - so all context creation is handled automatically,
but students still get to see HOW such a context is created.

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*/
#include "Common.h"

#include <string>
#include <fstream>
#include <vector>

#include "..//Third Party/KHR/khrplatform.h"
#include "..///Third Party/glad/glad.h"

#include "GL/GL.h"
#include "..//Third Party/KHR/wglext.h"

#include "../Third Party/SOIL/SOIL.h"

#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Quaternion.h"
#include "Matrix4.h"
#include "Window.h"
#include "Shader.h"
#include "Mesh.h"

using std::vector;

#define OPENGL_DEBUGGING

extern const Matrix4 biasMatrix;

class Shader;
class Light;

class OGLRenderer	{
public:
	friend class Window;
	OGLRenderer(Window &parent);
	virtual ~OGLRenderer(void);
	/**
	* @brief ��Ⱦ����
	*/
	virtual void	RenderScene()		= 0;
	/**
	* @brief ������Ⱦ����
	*/
	virtual void	UpdateScene(float msec);
	/**
	* @brief ����ǰ�󻺴� ��Ҫ��RenderScene�����
	*/
	void			SwapBuffers();
	/**
	* @brief ������еĹ������Ƿ��ռƻ�����
	* @return ��ʼ��״̬
	*/
	bool			HasInitialised() const;	
	
protected:
	virtual void	Resize(int x, int y);
	/**
	* @brief ���µ�ǰshader�е����о���
	*/
	void			UpdateShaderMatrices();
	/**
	* @brief ָ��ʹ��ĳһ������ ��ɫ�������з������Ի�ö�Ӧ�ĳ���ID
	* @param ��ɫ������
	*/
	void			BindShader(Shader*s);

	void SetTextureRepeating(GLuint target, bool state);

	void StartDebugGroup(const std::string& s) {
		glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, (GLsizei)s.length(), s.c_str());
	}

	void EndDebugGroup() {
		glPopDebugGroup();
	}

	Matrix4 projMatrix;		//Projection matrix ͶӰ����
	Matrix4 modelMatrix;	//Model matrix. NOT MODELVIEW �ӱ�������ת������������ 
	Matrix4 viewMatrix;		//View matrix  ����ӿڵľ���
	Matrix4 textureMatrix;	//Texture matrix
	Matrix4 shadowMatrix;

	int		width;			//Render area width (not quite the same as window width)
	int		height;			//Render area height (not quite the same as window height)
	bool	init;			//Did the renderer initialise properly?
	/**
	* @brief ��fragment shader�������� ��Դ��λ�� ��ɫ �Լ����䷶Χ
	*/
	void SetShaderLight(const Light& l);

private:
	Shader* currentShader;	//��ǰ���õ�shader
	HDC		deviceContext;	//...Device context?
	HGLRC	renderContext;	//Permanent Rendering Context
#ifdef _DEBUG
	static void CALLBACK DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
#endif
};