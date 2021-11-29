/******************************************************************************
Class:Shader
Implements:
Author:Rich Davison	 <richard-gordon.davison@newcastle.ac.uk>
Description:VERY simple class to encapsulate GLSL shader loading, linking,
and binding. Useful additions to this class would be overloaded functions to
replace the glUniformxx functions in external code, and possibly a map to store
uniform names and their resulting bindings. 

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "OGLRenderer.h"

enum ShaderStage {
	SHADER_VERTEX,
	SHADER_FRAGMENT,
	SHADER_GEOMETRY,
	SHADER_DOMAIN,
	SHADER_HULL,
	SHADER_MAX
};

class Shader	{
public:
	/**
	* @brief Shader�Ĺ��췽�� �Ѵ�����shader ���� vector allshaders��
	* @param vertex ������ɫ����·��
	* @param fragment Ƭ����ɫ����·��
	* @param geometry ͼ����ɫ����·��
	* @param domain δ֪
	* @param hull δ֪
	*/
	Shader(const std::string& vertex, const std::string& fragment, const std::string& geometry = "", const std::string& domain = "", const std::string& hull = "");
	~Shader(void);
	/**
	* @brief ��õ�ǰshader�����Ӧ�ĳ���ID
	* @return ����ID
	*/
	GLuint  GetProgram() { return programID;}
	/**
	* @brief ���¼���������ɫ��
	* @param deleteOld �Ƿ���Ҫɾ��֮ǰ��shader�ͳ���
	*/
	void	Reload(bool deleteOld = true);
	/**
	* @brief shader�ͳ����Ƿ񴴽��ɹ�
	* @return �Ƿ�ɹ�
	*/
	bool	LoadSuccess() {
		return shaderValid[0] == GL_TRUE && programValid == GL_TRUE;
	}
	/**
	* @brief ���¼������е�shader
	*/
	static void ReloadAllShaders();
	/**
	* @brief ��ӡ������
	*/
	static void	PrintCompileLog(GLuint object);
	/**
	* @brief ��ӡ������Ϣ
	*/
	static void	PrintLinkLog(GLuint program);

protected:
	/**
	* @brief ɾ����ǰ����ɫ�����shader����
	*/
	void	DeleteIDs();
	/**
	* @brief ���ļ�����shader����
	* @param filename �ļ���ַ
	* @param into ���ݻ���
	* @return �Ƿ���سɹ�
	*/
	bool	LoadShaderFile(const  std::string& from, std::string &into);
	/**
	* @brief ����shader���� ���ļ��ж�ȡshader���ݲ��ұ���
	* @param i Ҫ���ɵ�Shader���������
	*/
	void	GenerateShaderObject(unsigned int i);
	/**
	* @brief ��shader�еı�������ͨ���� ����һ�ְ취��ֱ����shader��ֱ��ָ��(layout = 0)��
	*/
	void	SetDefaultAttributes();
	/**
	* @brief ���ӳ��� ȷ�������Ƿ����ӳɹ�
	*/
	void	LinkProgram();

	GLuint	programID; //��ɫ����ı�ʶID
	GLuint	objectIDs[SHADER_MAX];//������ɫ���������ID
	GLint	programValid;//�����Ƿ����ӳɹ���״̬
	GLint	shaderValid[SHADER_MAX];//������ɫ�������Ľ�� �Ƿ����ɹ�

	std::string  shaderFiles[SHADER_MAX]; //����Ÿ�����ɫ�����ļ���ַ

	static std::vector<Shader*> allShaders;
};

