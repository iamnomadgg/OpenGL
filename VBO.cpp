#include "VBO.h"

//Constructor that generates a Vertex Buffer Object and links it to vertices
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	//Generate the VBO with only 1 object each
	glGenBuffers(1, &id);
	//Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, id);
	//Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

//Binds the VBO
void VBO::Bind()
{
	//Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

//Unbinds the VBO
void VBO::Unbind()
{
	//Unbind the VBO to 0 so that we don't accidentally modify the VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Deletes the VBO
void VBO::Delete()
{
	//Delete all the objects we have created
	glDeleteBuffers(1, &id);
}