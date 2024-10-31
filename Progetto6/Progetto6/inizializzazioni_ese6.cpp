#pragma once
#include <glad/glad.h>
#include "ShaderMaker.h"
#include "strutture.h"

extern unsigned int programId;

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

}

void INIT_VAO_DYNAMIC_Curva(Curva* fig)
{

    glGenVertexArrays(1, &fig->VAO);
    glBindVertexArray(fig->VAO);
     
    //Genero , rendo attivo, riempio il VBO della geometria dei vertici di COntrollo
    glGenBuffers(1, &fig->VBO_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_vertices);
    glBufferData(GL_ARRAY_BUFFER, fig->nv * sizeof(vec3), NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    //Genero , rendo attivo, riempio il VBO dei colori nei vertici di controllo
    glGenBuffers(1, &fig->VBO_colors);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_colors);
    glBufferData(GL_ARRAY_BUFFER, fig->nv * sizeof(vec4), NULL, GL_DYNAMIC_DRAW);
    //Adesso carico il VBO dei colori nel layer 2
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);
     

    //Genero , rendo attivo, riempio il VBO della geometria dei vertici di COntrollo
    glGenBuffers(1, &fig->VBO_CP);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_CP);
    glBufferData(GL_ARRAY_BUFFER, fig->ncp * sizeof(vec3), NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);

    //Genero , rendo attivo, riempio il VBO dei colori nei vertici di controllo
    glGenBuffers(1, &fig->VBO_CP_colors);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_CP_colors);
    glBufferData(GL_ARRAY_BUFFER, fig->ncp * sizeof(vec4), NULL, GL_DYNAMIC_DRAW);
    //Adesso carico il VBO dei colori nel layer 2
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(3);
    
    //Genero , rendo attivo, riempio il VBO della geometria dei vertici di COntrollo
    glGenBuffers(1, &fig->VBO_TG);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_TG);
    glBufferData(GL_ARRAY_BUFFER, fig->ntg * sizeof(vec3), NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(4);

    //Genero , rendo attivo, riempio il VBO dei colori nei vertici di controllo
    glGenBuffers(1, &fig->VBO_TG_colors);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_TG_colors);
    glBufferData(GL_ARRAY_BUFFER, fig->ntg * sizeof(vec4), NULL, GL_DYNAMIC_DRAW);
    //Adesso carico il VBO dei colori nel layer 2
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(5);

    
}
void UPDATE_VAO_Curva(Curva* fig)
{

   

    glBindVertexArray(fig->VAO);
    //Genero , rendo attivo, riempio il VBO della geometria dei vertici di COntrollo
     
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_vertices);
    glBufferSubData(GL_ARRAY_BUFFER, 0, fig->vertices.size() * sizeof(vec3), fig->vertices.data());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    //Genero , rendo attivo, riempio il VBO dei colori nei vertici di controllo
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_colors);
    glBufferSubData(GL_ARRAY_BUFFER, 0, fig->colors.size() * sizeof(vec4), fig->colors.data());
    //Adesso carico il VBO dei colori nel layer 2
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);
     


    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_CP);
    glBufferSubData(GL_ARRAY_BUFFER, 0, fig->CP.size() * sizeof(vec3), fig->CP.data());

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);

    //Genero , rendo attivo, riempio il VBO dei colori nei vertici di controllo
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_CP_colors);
    glBufferSubData(GL_ARRAY_BUFFER, 0, fig->colCP.size() * sizeof(vec4), fig->colCP.data());
    //Adesso carico il VBO dei colori nel layer 2
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(3);
    
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_TG);
    glBufferSubData(GL_ARRAY_BUFFER, 0, fig->tg.size() * sizeof(vec3), fig->tg.data());

    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(4);

    //Genero , rendo attivo, riempio il VBO dei colori nei vertici di controllo
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_TG_colors);
    glBufferSubData(GL_ARRAY_BUFFER, 0, fig->col_tg.size() * sizeof(vec4), fig->col_tg.data());
    //Adesso carico il VBO dei colori nel layer 2
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(5);
    
}

