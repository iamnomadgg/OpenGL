#include "VAO.h"

//Constructor that generates a Vertex Array Object ID
VAO::VAO()
{
	//Generate the VAO with only 1 object each
	glGenVertexArrays(1, &id);
}

//Links a VBO to the VAO using a certain layout
void VAO::LinkVBO(VBO vbo, GLuint layout)
{
	vbo.Bind();

	//Configure the Vertex Attribute so that OpenGL how to read the VBO
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(layout);

	vbo.Unbind();
}

//Binds the VAO
void VAO::Bind()
{
	//Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(id);
}

//Unbinds the VAO
void VAO::Unbind()
{
	//Bind both the VAO to 0 so that we don't accidentally modify the VAO we created
	glBindVertexArray(0);
}

//Deletes the VAO
void VAO::Delete()
{
	//Delete the object we have created
	glDeleteVertexArrays(1, &id);
}