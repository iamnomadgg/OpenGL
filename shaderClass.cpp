#include "shaderClass.h"

//Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;

		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read( &(contents[0]), contents.size() );
		in.close();

		return contents;
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	//Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//Create Vertex Shader object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach Vertex Shader source to the Vertex Shader object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	//Checks if Shader compiled successfully
	CompileErrors(vertexShader, "VERTEX");

	//Create Fragment Shader object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach Fragment Shader source to the Fragment Shader object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);
	//Checks if Shader compiled successfully
	CompileErrors(fragmentShader, "FRAGMENT");

	//Create Shader Program object and get its reference
	id = glCreateProgram();
	//Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	//Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(id);
	//Checks if Shader compiled successfully
	CompileErrors(id, "PROGRAM");

	//Shaders were added into the program so they can be deleted.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

//Activates the Shader Program
void Shader::Activate()
{
	//Tell OpenGL which Shader Program we want to use
	glUseProgram(id);
}

//Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(id);
}

//Checks if the different shaders have compiled properly
void Shader::CompileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
		}
	}
}