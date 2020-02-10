#include "Mesh.h"


Mesh::Mesh(std::vector<Vertex>* vertexList_, GLuint shaderProgram_, GLuint textureId_)
{
	vertextList = std::vector<Vertex>();
	vertextList.reserve(100);

	VAO = 0;
	VBO = 0;
	vertextList = *vertexList_;
	modelLocation = 0;
	viewLocation = 0;
	projectionLocation = 0;
	textureLocation = 0;
	textureId = textureId_;
	shaderProgram = shaderProgram_;

	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Mesh::Render(Camera* camera_, glm::mat4 transform_)
{	
	glUniform1i(textureLocation, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(transform_));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertextList.size());
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertextList.size() * sizeof(Vertex), &vertextList[0], GL_STATIC_DRAW);

	// Vertex Pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	// Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	//Colour
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLocation = glGetUniformLocation(shaderProgram, "model");
	viewLocation = glGetUniformLocation(shaderProgram, "view");
	projectionLocation = glGetUniformLocation(shaderProgram, "projection");
	textureLocation = glGetUniformLocation(shaderProgram, "inputTexture");

}
