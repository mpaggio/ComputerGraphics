#pragma once
#include <glad/glad.h>
#include "ShaderMaker.h"
#include "strutture.h"

extern unsigned int programId, programIdS, programId_text;
extern unsigned int VAO_Text, VBO_Text;
extern ViewSetup SetupTelecamera;
extern PerspectiveSetup SetupProspettiva;
extern int width, height;
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

    //EBO di tipo indici
    glGenBuffers(1, &mesh->EBO_indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(GLuint), mesh->indices.data(), GL_STATIC_DRAW);


}

void INIT_CAMERA_PROJECTION(void)
{
    //Imposto la telecamera

    SetupTelecamera.position = glm::vec4(0.0, 0.5, 20.0, 0.0);
    SetupTelecamera.target = glm::vec4(0.0, 0.0, 0.0, 0.0);
    SetupTelecamera.direction = SetupTelecamera.target - SetupTelecamera.position;
    SetupTelecamera.upVector = glm::vec4(0.0, 1.0, 0.0, 0.0);


    //Imposto la proiezione prospettica

    SetupProspettiva.aspect = (GLfloat)width / (GLfloat)height;
    SetupProspettiva.fovY = 45.0f;
    SetupProspettiva.far_plane = 2000.0f;
    SetupProspettiva.near_plane = 0.1f;
}