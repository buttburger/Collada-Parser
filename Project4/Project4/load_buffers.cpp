#include "Common.h"

extern GLuint MatrixID;
extern glm::mat4 projection, view, ModelMatrix, MVP, RotationMatrix, TranslationMatrix, ScalingMatrix;

extern float deltaTime;
extern float modelX, modelY, modelZ;
extern float rotX, rotY, rotZ;
extern float scalingX, scalingY, scalingZ;

GLuint programID;
GLuint TextureID;
GLuint Texture[10];
GLuint VertexArrayID[10];
GLuint vertexbuffer[10];
GLuint colorbuffer[10];
GLuint uvbuffer[10];
GLuint normalbuffer[10];
GLuint elementbuffer[10];

GLuint LightID[10];
extern GLuint uniformModel[10], uniformView[10], uniformProjection[10];

std::vector<glm::vec3> vectorvertices[10];
std::vector<glm::vec2> vectoruvs[10];
std::vector<glm::vec3> vectornormals[10];
std::vector<unsigned short> indices[10], daeindices[10];
std::vector<glm::vec3> indexed_vertices[10];
std::vector<glm::vec2> indexed_uvs[10];
std::vector<glm::vec3> indexed_normals[10];

quat gOrientation2[10];


//////////////////////////////////////////////////////////////////////////////////////////////////////
//LIBXML GLOBALS
int newarraytest = 0;
bool verticesfound = 0;
bool normalsfound = 0;
bool uvmapfound = 0;
bool indicesfound = 0;

int verticescount = 0;
int normalscount = 0;
int uvmapscount = 0;
int indicescount = 0;

float*storedvertices;
float*storednormals;
float*storeduvmaps;

int *intarray;
float *floatarray;

//int *meshindices;

int *vertindices;
int *normindices;
int *uvindices;

float *meshvertices;
float *meshnormals;
float *meshuvmaps;

//int *meshnormals;
//int *meshtexturemaps;

//////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
//std::vector<glm::vec3> temp_vertices, temp_indicesvertices;
//std::vector<glm::vec2> temp_uvs;
//std::vector<glm::vec3> temp_normals;

//////////////////////////////////////////////////////////////////////////////////////////////////////

float ftest[] =
{
	//0, 2, 0, 1, 0, 0,
	//-2, -2, 0, 0, 1, 0,
	//2, -2, 0, 0, 0, 1,

	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -0.9999998f, -1.0f,
	-0.9999997f, 1.0f, -1.0f,
	1.0f, 0.9999995f, 1.0f,
	0.9999994f,	-1.000001f, 1.0f,
	-1.0f, -0.9999997f, 1.0f,
	-1.0f, 1.0f, 1.0f
};


void initVBO(char*modelfile, char*texturefile, int vboLoop)
{
	loadShaders(programID, "shaders/vert_shader.glsl", "shaders/frag_shader.glsl");

	int imgwidth, imgheight;
	bool hasAlpha;
	//Load the texture
	Texture[vboLoop] = loadPngImage(texturefile, imgwidth, imgheight, hasAlpha, &textureImage);
		//loadBMP_custom("test.bmp");
		//LoadBMP("test.bmp");
		//loadDDS("uvmap.DDS");
		
	//Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(programID, "myTexture");
	MatrixID = glGetUniformLocation(programID, "MVP");

	uniformModel[0] = glGetUniformLocation(programID, "model");
	uniformView[0] = glGetUniformLocation(programID, "view");
	uniformProjection[0] = glGetUniformLocation(programID, "projection");
		

	/*
	char getFileExtension[64];
	for(int i = strlen(modelfile)-1; i >= 0; i--)
	{
		//printf("strNum: %d\n", i);
		//printf("strChar: %c\n", modelfile[i]);
		getFileExtension[i] = modelfile[i];
		if(strncmp(&getFileExtension[i],".obj", 4) == 0)//if(getFileExtension == ".obj")
		{
			printf(".obj file detected!\n");
			loadOBJ(modelfile, vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop]);
			indexVBO(vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop], indices[vboLoop], indexed_vertices[vboLoop], indexed_uvs[vboLoop], indexed_normals[vboLoop]);
			break;
		}
		if(strncmp(&getFileExtension[i],".dae", 4) == 0)//if(getFileExtension == ".obj")
		{
			//printf(".fbx file detected!\n");
			//loadmyFBX(modelfile, vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop]);
			//indexVBO(vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop], indices[vboLoop], indexed_vertices[vboLoop], indexed_uvs[vboLoop], indexed_normals[vboLoop]);
			break;
		}
	}
	*/


	//loadOBJ(modelfile, vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop]);
	//indexVBO(vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop], indices[vboLoop], indexed_vertices[vboLoop], indexed_uvs[vboLoop], indexed_normals[vboLoop]);
	loadmyDAE(modelfile, vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop], daeindices[vboLoop]);
	indexVBO(vectorvertices[vboLoop], vectoruvs[vboLoop], vectornormals[vboLoop], indices[vboLoop], indexed_vertices[vboLoop], indexed_uvs[vboLoop], indexed_normals[vboLoop]);
	
	
	/*
	for(int i = 0; i < 36; i++)
	{
		printf("%d polyV X: %f Y: %f Z: %f\n", i, vectorvertices[vboLoop][i*3+0], vectorvertices[vboLoop][i*3+1], vectorvertices[vboLoop][i*3+2]);


		//printf("%d X: %f Y: %f Z: %f\n", i, vectorvertices[vboLoop][i].x, vectorvertices[vboLoop][i].y, vectorvertices[vboLoop][i].z);


		//printf("%d polyUV X: %f Y: %f\n", i, indexed_uvs[vboLoop][i*2+0], indexed_uvs[vboLoop][i*2+1]);
		//printf("%d polyN X: %f Y: %f Z: %f\n", i, indexed_normals[vboLoop][i*3+0], indexed_normals[vboLoop][i*3+1], indexed_normals[vboLoop][i*3+2]);
	}
	_getch();
	*/


	glGenVertexArrays(1, &VertexArrayID[vboLoop]);
	glBindVertexArray(VertexArrayID[vboLoop]);
	
	//for(int iii = 0; iii <= 23; iii++)printf("MeshV %d - %d: %.7f\n", sizeof(meshvertices), verticescount, meshvertices[iii]);
	
	//glGenBuffers(1, &vertexbuffer[vboLoop]);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[vboLoop]);
	//glBufferData(GL_ARRAY_BUFFER, vectorvertices[vboLoop].size() * sizeof(glm::vec3), &vectorvertices[vboLoop][0], GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(meshvertices), meshvertices, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(ftest), ftest, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, indexed_vertices[vboLoop].size() * sizeof(glm::vec3), &indexed_vertices[vboLoop][0], GL_STATIC_DRAW);
	//COLOR
	//glGenBuffers(1, &colorbuffer[vboLoop]);
	//glBindBuffer(GL_ARRAY_BUFFER, colorbuffer[vboLoop]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(ftest), ftest, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, indexed_uvs[vboLoop].size() * sizeof(glm::vec2), &indexed_uvs[vboLoop][0], GL_STATIC_DRAW);

	LightID[0] = glGetUniformLocation(programID, "LightPosition_worldspace");
	
	//VERTEXBUFFER
	glGenBuffers(1, &vertexbuffer[vboLoop]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[vboLoop]);
	//glBufferData(GL_ARRAY_BUFFER, vectorvertices[vboLoop].size() * sizeof(glm::vec3), &vectorvertices[vboLoop][0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices[vboLoop].size() * sizeof(glm::vec3), &indexed_vertices[vboLoop][0], GL_STATIC_DRAW);
	//UVBUFFER
	glGenBuffers(1, &uvbuffer[vboLoop]);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[vboLoop]);
	//glBufferData(GL_ARRAY_BUFFER, vectoruvs[vboLoop].size() * sizeof(glm::vec2), &vectoruvs[vboLoop][0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs[vboLoop].size() * sizeof(glm::vec2), &indexed_uvs[vboLoop][0], GL_STATIC_DRAW);
	//NORMALBUFFER
	glGenBuffers(1, &normalbuffer[vboLoop]);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[vboLoop]);
	//glBufferData(GL_ARRAY_BUFFER, vectornormals[vboLoop].size() * sizeof(glm::vec3), &vectornormals[vboLoop][0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals[vboLoop].size() * sizeof(glm::vec3), &indexed_normals[vboLoop][0], GL_STATIC_DRAW);
	//INDICEBUFFERS
	glGenBuffers(1, &elementbuffer[vboLoop]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[vboLoop]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices[vboLoop].size() * sizeof(unsigned short), &indices[vboLoop][0], GL_STATIC_DRAW);

	printf("INDSIZE: %d\n", indices[vboLoop].size() * sizeof(unsigned short));


	vboLoop++;
}

void drawShapes()
{
	printf("DRAW!\n");
}

void loadVBO(int vboID)
{
	glUseProgram(programID);

	vec3 desiredDir = glm::vec3(rotX, rotY, rotZ);//gPosition1-gPosition2;
	vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f);//+Y
	//EULER TO QUATERNION
	quat targetOrientation = normalize(qLookAt(desiredDir, desiredUp));//Compute the desired orientation
	gOrientation2[vboID] = RotateTowards(gOrientation2[vboID], targetOrientation, 1.0f*deltaTime);//And interpolate
	//printf("ROT X: %f Y: %f Z: %f W: %f\n", gOrientation2[0], gOrientation2[1], gOrientation2[2], gOrientation2[3]);
	RotationMatrix = mat4_cast(gOrientation2[vboID]);
		
	//RotationMatrix = eulerAngleYXZ(rotX, rotY, rotZ);
	TranslationMatrix = translate(mat4(), glm::vec3(modelX, modelY, modelZ));
	ScalingMatrix = scale(mat4(), vec3(scalingX, scalingY, scalingZ));//1.0f, 1.0f, 1.0f));
	
	ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;
	MVP = projection * view * ModelMatrix;

	//glm::mat4 view = LookAt(eye, eye+target, up);
	glUniformMatrix4fv(uniformView[0], 1, GL_FALSE, glm::value_ptr(view));
	//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(modelx, modely, modelz));
	glUniformMatrix4fv(uniformModel[0], 1, GL_FALSE, glm::value_ptr(ModelMatrix));

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform


	/*
	printf("MVPTEST: X: %f Y: %f Z: %f W: %f\n", ModelMatrix[0][0], ModelMatrix[0][1], ModelMatrix[0][2], ModelMatrix[0][3]);
	printf("MVPTEST: X: %f Y: %f Z: %f W: %f\n", ModelMatrix[1][0], ModelMatrix[1][1], ModelMatrix[1][2], ModelMatrix[1][3]);
	printf("MVPTEST: X: %f Y: %f Z: %f W: %f\n", ModelMatrix[2][0], ModelMatrix[2][1], ModelMatrix[2][2], ModelMatrix[2][3]);
	printf("MVPTEST: X: %f Y: %f Z: %f W: %f\n", ModelMatrix[3][0], ModelMatrix[3][1], ModelMatrix[3][2], ModelMatrix[3][3]);
		
	printf("MVPTEST: X: %f Y: %f Z: %f W: %f\n", view[0][0], view[0][1], view[0][2], view[0][3]);
	printf("MVPTEST: X: %f Y: %f Z: %f W: %f\n", view[1][0], view[1][1], view[1][2], view[1][3]);
	printf("MVPTEST: X: %f Y: %f Z: %f W: %f\n", view[2][0], view[2][1], view[2][2], view[2][3]);
	printf("MVPTEST: X: %f Y: %f Z: %f W: %f\n", view[3][0], view[3][1], view[3][2], view[3][3]);
		
	printf("MVPTEST: X: %f Y: %f Z: %f W: %f\n", MVP[0][0], MVP[0][1], MVP[0][2], MVP[0][3]);
	printf("MVPTEST: X: %f Y: %f Z: %f W: %f\n", MVP[1][0], MVP[1][1], MVP[1][2], MVP[1][3]);
	printf("MVPTEST: X: %f Y: %f Z: %f W: %f\n", MVP[2][0], MVP[2][1], MVP[2][2], MVP[2][3]);
	printf("MVPTEST: X: %f Y: %f Z: %f W: %f\n", MVP[3][0], MVP[3][1], MVP[3][2], MVP[3][3]);
		
	printf("MVPTEST: X: %f Y: %f Z: %f W: %f\n", TranslationMatrix[0][0], TranslationMatrix[0][1], TranslationMatrix[0][2], TranslationMatrix[0][3]);
	printf("MVPTEST: X: %f Y: %f Z: %f W: %f\n", TranslationMatrix[1][0], TranslationMatrix[1][1], TranslationMatrix[1][2], TranslationMatrix[1][3]);
	printf("MVPTEST: X: %f Y: %f Z: %f W: %f\n", TranslationMatrix[2][0], TranslationMatrix[2][1], TranslationMatrix[2][2], TranslationMatrix[2][3]);
	printf("MVPTEST: X: %f Y: %f Z: %f W: %f\n", TranslationMatrix[3][0], TranslationMatrix[3][1], TranslationMatrix[3][2], TranslationMatrix[3][3]);
	*/


	glm::vec3 lightPos = glm::vec3(4,4,4);
	glUniform3f(LightID[0], lightPos.x, lightPos.y, lightPos.z);


	glActiveTexture(GL_TEXTURE0);//Bind our texture in Texture Unit 0
	glBindTexture(GL_TEXTURE_2D, Texture[vboID]);
	glUniform1i(TextureID, 0);//Set "myTextureSampler" sampler to use Texture Unit 0


	//1st attribute buffer:vertices
	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[vboID]);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
	//2nd attribute buffer:color
	//glEnableVertexAttribArray(1);
	//glBindBuffer(GL_ARRAY_BUFFER, colorbuffer[vboID]);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (GLvoid*)(3 * sizeof(GL_FLOAT)));

	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//glDrawArrays(GL_TRIANGLES, 0, vectorvertices[0].size() * sizeof(glm::vec3));
	
	
	//1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[0]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[0]);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//glDrawArrays(GL_TRIANGLES, 0, vectorvertices[0].size() * sizeof(glm::vec3));
	
	//Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[0]);
	glDrawElements(GL_TRIANGLES, indices[0].size(), GL_UNSIGNED_SHORT, (void*)0);
		

	
	//for(int stuffs = 0; stuffs < 8; stuffs++)printf("MESHV X: %f Y: %f Z: %f\n", meshvertices[stuffs*3+0], meshvertices[stuffs*3+1], meshvertices[stuffs*3+2]);
	//_getch();


	/*
	//2nd attribute buffer:UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[vboID]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//3rd attribute buffer:normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[vboID]);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[vboID]);
	glDrawElements(GL_TRIANGLES, indices[vboID].size(), GL_UNSIGNED_SHORT, (void*)0);
	*/

	/*
	if(vboID == 1)
	{
		vec3 desiredDir = glm::vec3(0.01f, 90.0f, 0.01f);//gPosition1-gPosition2;
		vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f);//+Y
		//EULER TO QUATERNION
		quat targetOrientation = normalize(qLookAt(desiredDir, desiredUp));//Compute the desired orientation
		gOrientation2[vboID] = RotateTowards(gOrientation2[vboID], targetOrientation, 1.0f*deltaTime);//And interpolate
		//printf("ROT X: %f Y: %f Z: %f W: %f\n", gOrientation2[0], gOrientation2[1], gOrientation2[2], gOrientation2[3]);
		RotationMatrix = mat4_cast(gOrientation2[vboID]);
		
		//RotationMatrix = eulerAngleYXZ(rotX, rotY, rotZ);
		TranslationMatrix = translate(mat4(), glm::vec3(6.0f, modelY, modelZ));
		ScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));//scaling[0], scaling[1], scaling[2]));
		ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;
		MVP = projection * view * ModelMatrix;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);//Send our transformation to the currently bound shader in the "MVP" uniform

		glActiveTexture(GL_TEXTURE0);//Bind our texture in Texture Unit 0
		glBindTexture(GL_TEXTURE_2D, Texture[1]);
		glUniform1i(TextureID, 0);//Set "myTextureSampler" sampler to use Texture Unit 0

		//1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[1]);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[1]);
		glDrawElements(GL_TRIANGLES, indices[1].size(), GL_UNSIGNED_SHORT, (void*)0);
	}
	*/
}

void deleteVBO(GLuint vboID)
{
	glDeleteVertexArrays(1, &VertexArrayID[vboID]);
	glDeleteBuffers(1, &vertexbuffer[vboID]);
	glDeleteBuffers(1, &uvbuffer[vboID]);
	glDeleteBuffers(1, &normalbuffer[vboID]);
	glDeleteBuffers(1, &elementbuffer[vboID]);
	glDeleteTextures(1, &Texture[vboID]);

	vectorvertices[vboID].clear(), vectoruvs[vboID].clear(), vectornormals[vboID].clear(), indices[vboID].clear(), indexed_vertices[vboID].clear(), indexed_uvs[vboID].clear(), indexed_normals[vboID].clear();
}

void deleteVBOall()
{
	glDeleteVertexArrays(1, VertexArrayID);
	glDeleteBuffers(1, vertexbuffer);
	glDeleteBuffers(1, uvbuffer);
	glDeleteBuffers(1, normalbuffer);
	glDeleteBuffers(1, elementbuffer);
	glDeleteTextures(1, Texture);
	glDeleteProgram(programID);
}