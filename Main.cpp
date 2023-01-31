#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

//Vertices coordinates
GLfloat vertices[] =
{
	-0.50f, -0.5f * float(sqrt(3)) / 3,		0.0f, 0.8f, 0.3f,  0.02f,//Lower left corner
	 0.50f, -0.5f * float(sqrt(3)) / 3,		0.0f, 0.8f, 0.3f,  0.02f,//Lower right corner
	 0.00f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 1.0f, 0.6f,  0.32f,//Upper corner
	-0.25f,  0.5f * float(sqrt(3)) / 6,		0.0f, 0.9f, 0.45f, 0.17f,//Inner left
	 0.25f,  0.5f * float(sqrt(3)) / 6,		0.0f, 0.9f, 0.45f, 0.17f,//Inner right
	 0.00f, -0.5f * float(sqrt(3)) / 3,		0.0f, 0.8f, 0.3f,  0.02f //Inner down
};

GLuint indices[] =
{
	0, 3, 5, //Lower left triangle
	3, 2, 4, //Lower right triangle
	5, 4, 1 //Upper triangle
};

int main()
{
	//Initialize GLFW
	glfwInit();

	//Tell GLFW what version of OpenGL we are using: 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tell GLFW we are using the CORE profile which has no outdated functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "YouTubeOpenGL", NULL, NULL);
	//Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();

	//Specify the viewport of OpenGL in the window
	//In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	//Creates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	//Generates Vertex Array object and binds it
	VAO vao1;
	vao1.Bind();

	//Generates Vertex Buffer object and links it to vertices
	VBO vbo1(vertices, sizeof(vertices));
	//Generates Element Buffer object and links it to indices
	EBO ebo1(indices, sizeof(indices));

	//Link VBO attributes such as coordinates and colors to VAO
	vao1.LinkAttrib( vbo1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0 );
	vao1.LinkAttrib( vbo1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)) );

	//Unbind all to prevent accidentally modifying them
	vao1.Unbind();
	vbo1.Unbind();
	ebo1.Unbind();

	//Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.id, "scale");
	
	//Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		//Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		//Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);
		//Bind the VAO so OpenGL knows to use it
		vao1.Bind();
		//Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		//Take care of all GLFW events
		glfwPollEvents();
	}

	//Delete all the objects we have created
	vao1.Delete();
	vbo1.Delete();
	ebo1.Delete();
	shaderProgram.Delete();

	//Delete window before ending the program
	glfwDestroyWindow(window);
	//Terminate GLFW
	glfwTerminate();
	return 0;
}