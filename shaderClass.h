#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

//Includes need for OpenGL and the text reader function
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include "glad/glad.h"

std::string get_file_contents(const char* filename);

class Shader
{
public:
	//Reference ID of the Shader Program
	GLuint id;
	//Constructor that builds the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	//Activates the Shader Program
	void Activate();
	//Deletes the Shader Program
	void Delete();
};

#endif
