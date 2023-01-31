#include "EBO.h"

//Constructor that generates a Elements Buffer Object and links it to indices
EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	//Generate the EBO with only 1 object each
	glGenBuffers(1, &id);
	//Bind the EBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	//Introduce the vertices into the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

//Binds the EBO
void EBO::Bind()
{
	//Bind the EBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

//Unbinds the EBO
void EBO::Unbind()
{
	//Unbind the EBO to 0 so that we don't accidentally modify the EBO we created
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//Deletes the EBO
void EBO::Delete()
{
	//Delete all the objects we have created
	glDeleteBuffers(1, &id);
}