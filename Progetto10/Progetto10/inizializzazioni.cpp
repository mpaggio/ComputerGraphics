#pragma once
#include <glad/glad.h>
#include "ShaderMaker.h"
#include "strutture.h"
#include "Materiali_Base.h"

extern unsigned int programId, programIdS, programId_text;
extern unsigned int VAO_Text, VBO_Text;
extern ViewSetup SetupTelecamera;
extern PerspectiveSetup SetupProspettiva;
extern int width, height;
extern vector<MaterialObj> materials;
extern point_light light;
extern vector<Shader>shaders;
void INIT_SHADER(void)
{
    GLenum ErrorCheckValue = glGetError();

    char* vertexShader = (char*)"vertexshaderM.glsl";
    char* fragmentShader = (char*)"fragmentshaderM.glsl";
    // La funzione successiva crea un programma shader completo a partire da due shader individuali: 
    // uno per la gestione dei vertici e uno per la gestione dei pixel. 
    // Il programma shader risultante viene identificato da un numero univoco (il programId) che verr  utilizzato in seguito per associarlo ad un oggetto grafico e per renderizzarlo.
     //All'interno della funzione ShaderMaker::createProgram
        //Compilazione degli shader : La funzione compila i due shader individuali, verificando che non ci siano errori di sintassi.
        //Linkaggio : Una volta compilati, i due shader vengono collegati insieme per formare un programma shader completo.
        // Creazione dell'identificativo: Viene generato un identificativo univoco per il programma shader e viene restituito alla funzione chiamante.

    programId = ShaderMaker::createProgram(vertexShader, fragmentShader);

    //CCrea un program shader per la renderizzazione del background
    vertexShader = (char*)"vertexshaderM.glsl";
     fragmentShader = (char*)"fragmentShaderM.glsl";
     glUseProgram(programId);


}

void INIT_VAO(Mesh* mesh)
{

    glGenVertexArrays(1, &mesh->VAO);
    glBindVertexArray(mesh->VAO);
    //Genero , rendo attivo, riempio il VBO della geometria dei vertici
    glGenBuffers(1, &mesh->VBO_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO_vertices);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(vec3), mesh->vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    //Genero , rendo attivo, riempio il VBO dei colori
    glGenBuffers(1, &mesh->VBO_colors);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO_colors);
    glBufferData(GL_ARRAY_BUFFER, mesh->colors.size() * sizeof(vec4), mesh->colors.data(), GL_STATIC_DRAW);
    //Adesso carico il VBO dei colori nel layer 2
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

	//Genero , rendo attivo, riempio il VBO delle normali
	glGenBuffers(1, &mesh->VBO_normals);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO_normals);
	glBufferData(GL_ARRAY_BUFFER, mesh->normals.size() * sizeof(vec3), mesh->normals.data(), GL_STATIC_DRAW);
	//Adesso carico il VBO delle NORMALI nel layer 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);

    //EBO di tipo indici
    glGenBuffers(1, &mesh->EBO_indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(GLuint), mesh->indices.data(), GL_STATIC_DRAW);


}

void INIT_CAMERA_PROJECTION(void)
{
    //Imposto la telecamera

    SetupTelecamera.position = glm::vec3(0.0, 0.5, 30.0 );
    SetupTelecamera.target = glm::vec3(0.0, 0.0, 0.0 );
    SetupTelecamera.direction = SetupTelecamera.target - SetupTelecamera.position;
    SetupTelecamera.upVector = glm::vec3(0.0, 1.0, 0.0 );


    //Imposto la proiezione prospettica

    SetupProspettiva.aspect = (GLfloat)width / (GLfloat)height;
    SetupProspettiva.fovY = 45.0f;
    SetupProspettiva.far_plane = 2000.0f;
    SetupProspettiva.near_plane = 0.1f;
}

void INIT_Illuminazione()
{
	//Setup della luce
	light.position = { 1.0, 0.0, 4.0 };
	light.color = { 1.0,1.0,1.0 };
	light.power = 2.f;

	//Setup dei materiali
	// Materials setup
	materials.resize(8);
	materials[MaterialType::RED_PLASTIC].name = "Red Plastic";
	materials[MaterialType::RED_PLASTIC].ambient = red_plastic_ambient;
	materials[MaterialType::RED_PLASTIC].diffuse = red_plastic_diffuse;
	materials[MaterialType::RED_PLASTIC].specular = red_plastic_specular;
	materials[MaterialType::RED_PLASTIC].shininess = red_plastic_shininess;

	materials[MaterialType::EMERALD].name = "Emerald";
	materials[MaterialType::EMERALD].ambient = emerald_ambient;
	materials[MaterialType::EMERALD].diffuse = emerald_diffuse;
	materials[MaterialType::EMERALD].specular = emerald_specular;
	materials[MaterialType::EMERALD].shininess = emerald_shininess;

	materials[MaterialType::BRASS].name = "Brass";
	materials[MaterialType::BRASS].ambient = brass_ambient;
	materials[MaterialType::BRASS].diffuse = brass_diffuse;
	materials[MaterialType::BRASS].specular = brass_specular;
	materials[MaterialType::BRASS].shininess = brass_shininess;

	materials[MaterialType::SNOW_WHITE].name = "Snow_White";
	materials[MaterialType::SNOW_WHITE].ambient = snow_white_ambient;
	materials[MaterialType::SNOW_WHITE].diffuse = snow_white_diffuse;
	materials[MaterialType::SNOW_WHITE].specular = snow_white_specular;
	materials[MaterialType::SNOW_WHITE].shininess = snow_white_shininess;

	materials[MaterialType::YELLOW].name = "Yellow";
	materials[MaterialType::YELLOW].ambient = yellow_ambient;
	materials[MaterialType::YELLOW].diffuse = yellow_diffuse;
	materials[MaterialType::YELLOW].specular = yellow_specular;
	materials[MaterialType::YELLOW].shininess = yellow_shininess;

	materials[MaterialType::PINK].name = "ROSA";
	materials[MaterialType::PINK].ambient = pink_ambient;
	materials[MaterialType::PINK].diffuse = pink_diffuse;
	materials[MaterialType::PINK].specular = pink_specular;
	materials[MaterialType::PINK].shininess = pink_shininess;

	materials[MaterialType::BROWN].name = "MARRONE";
	materials[MaterialType::BROWN].ambient = brown_ambient;
	materials[MaterialType::BROWN].diffuse = brown_diffuse;
	materials[MaterialType::BROWN].specular = brown_specular;
	materials[MaterialType::BROWN].shininess = brown_shininess;
	materials[MaterialType::NO_MATERIAL].name = "NO_MATERIAL";
	materials[MaterialType::NO_MATERIAL].ambient = glm::vec3(1, 1, 1);
	materials[MaterialType::NO_MATERIAL].diffuse = glm::vec3(0, 0, 0);
	materials[MaterialType::NO_MATERIAL].specular = glm::vec3(0, 0, 0);
	materials[MaterialType::NO_MATERIAL].shininess = 1.f;

	//Setup degli shader
	shaders.resize(7);
	shaders[ShaderOption::NONE].value = 0;
	shaders[ShaderOption::NONE].name = "NONE";
	shaders[ShaderOption::GOURAD_SHADING].value = 1;
	shaders[ShaderOption::GOURAD_SHADING].name = "GOURAD SHADING";
	shaders[ShaderOption::BLINNPHONG_SHADING].value = 2;
	shaders[ShaderOption::BLINNPHONG_SHADING].name = "BLINN PHONG SHADING";
	shaders[ShaderOption::PHONG_SHADING].value = 3;
	shaders[ShaderOption::PHONG_SHADING].name = "PHONG SHADING";
	shaders[ShaderOption::NO_TEXTURE].value = 4;
	shaders[ShaderOption::NO_TEXTURE].name = "NO TEXTURE";
	shaders[ShaderOption::WAVE].value = 5;
	shaders[ShaderOption::WAVE].name = "WAVE";
	shaders[ShaderOption::FLAG].value = 6;
	shaders[ShaderOption::FLAG].name = "FLAG";

}
 