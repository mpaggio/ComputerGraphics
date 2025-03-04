#pragma once
#include "Lib.h"
#include "ShaderMaker.h"
#include "Structures.h"

extern unsigned int programId;

void INIT_SHADER(void)
{
    GLenum ErrorCheckValue = glGetError();

    char* vertexShader = (char*)"vertex_shader_c.glsl";
    char* fragmentShader = (char*)"fragment_shader_c.glsl";

    programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
    glUseProgram(programId);



}

void INIT_VAO(Figura* fig)
{
    //Genero un VAO
    glGenVertexArrays(1, &fig->VAO);
    //Ne faccio il bind (lo collego, lo attivo)
    glBindVertexArray(fig->VAO);

    //AL suo interno genero un VBO
    glGenBuffers(1, &fig->VBO_vertices);
    //Ne faccio il bind (lo collego, lo attivo, assegnandogli il tipo GL_ARRAY_BUFFER)
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_vertices);
    //Carico i dati vertices sulla GPU
    glBufferData(GL_ARRAY_BUFFER, fig->vertices.size() * sizeof(vec3), fig->vertices.data(), GL_STATIC_DRAW);

    // Configurazione dell'attributo posizione: informo il vertex shader su: dove trova le informazioni sulle posizioni e come le deve leggere
    //dal buffer caricato sulla GPU
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // Perch� abbiamo 7 informazioni per vertice (x,y,z,r,g,b,a)
    //Abilitazione degli attributi : glEnableVertexAttribArray abilita gli attributi per l'utilizzo nella pipeline grafica.
    glEnableVertexAttribArray(0);

    // Faccio lo stesso per il buffer dei colors
    glGenBuffers(1, &fig->VBO_colors);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_colors);
    glBufferData(GL_ARRAY_BUFFER, fig->colors.size() * sizeof(vec4), fig->colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);
}

void INIT_TRIANGLE(Figura* fig) {
    fig->vertices.push_back(vec3(-0.5f, -0.5f, 0.0f));
    fig->vertices.push_back(vec3(0.5f, -0.5f, 0.0f));
    fig->vertices.push_back(vec3(0.0f, 0.5f, 0.0f));

    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->colors.push_back(vec4(0.0, 0.0, 1.0, 1.0));
    fig->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));

    fig->nVertices = 3;
    fig->nTriangles = 1;
    fig->render = GL_TRIANGLES;
}

void INIT_SQUARE(Figura* fig) {
    // Triangolo 1:
    fig->vertices.push_back(vec3(-0.5f, -0.5f, 0.0f));
    fig->vertices.push_back(vec3(0.5f, -0.5f, 0.0f));
    fig->vertices.push_back(vec3(0.5f, 0.5f, 0.0f));
    
    // Triangolo 2:
    fig->vertices.push_back(vec3(-0.5f, -0.5f, 0.0f));
    fig->vertices.push_back(vec3(0.5f, 0.5f, 0.0f));
    fig->vertices.push_back(vec3(-0.5f, 0.5f, 0.0f));
    
    // Colori per i vertici:
    // --> Triangolo 1
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->colors.push_back(vec4(0.0, 0.0, 1.0, 1.0));
    fig->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));
    // --> Triangolo 2
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));
    fig->colors.push_back(vec4(0.0, 0.0, 1.0, 1.0));

    // Settings generali:
    fig->nVertices = fig->vertices.size();
    fig->nTriangles = 2;
    fig->render = GL_TRIANGLES;
}

void INIT_HEART(Figura* fig) {
    // Triangolo 1:
    fig->vertices.push_back(vec3(-0.8f, 0.4f, 0.0f));
    fig->vertices.push_back(vec3(-0.4f, 0.8f, 0.0f)); 
    fig->vertices.push_back(vec3(0.0f, 0.6f, 0.0f));

    // Triangolo 2:
    fig->vertices.push_back(vec3(0.0f, 0.6f, 0.0f));
    fig->vertices.push_back(vec3(0.4f, 0.8f, 0.0f));
    fig->vertices.push_back(vec3(0.8f, 0.4f, 0.0f));

    // Triangolo 3:
    fig->vertices.push_back(vec3(0.0f, 0.6f, 0.0f));
    fig->vertices.push_back(vec3(0.0f, -0.6f, 0.0f));
    fig->vertices.push_back(vec3(0.8f, 0.4f, 0.0f));

    // Triangolo 4:
    fig->vertices.push_back(vec3(0.0f, 0.6f, 0.0f));
    fig->vertices.push_back(vec3(0.0f, -0.6f, 0.0f));
    fig->vertices.push_back(vec3(-0.8f, 0.4f, 0.0f));

    // Colori:
    // --> Triangolo 1
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->colors.push_back(vec4(0.0, 0.0, 1.0, 1.0));
    fig->colors.push_back(vec4(1.0, 1.0, 0.0, 1.0));
    // --> Triangolo 2
    fig->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->colors.push_back(vec4(0.0, 0.0, 1.0, 1.0));
    // --> Triangolo 3
    fig->colors.push_back(vec4(1.0, 1.0, 0.0, 1.0));
    fig->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    // --> Triangolo 4
    fig->colors.push_back(vec4(0.0, 0.0, 1.0, 1.0));
    fig->colors.push_back(vec4(1.0, 1.0, 0.0, 1.0));
    fig->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));

    fig->nTriangles = 4;
    fig->nVertices = fig->nTriangles*3;
    fig->render = GL_TRIANGLES;
}

void INIT_BUTTERFLY(Figura* fig) {
    // Vertici della farfalla
    // Triangolo 1:
    fig->vertices.push_back(vec3(-0.8f, 0.8f, 0.0f));
    fig->vertices.push_back(vec3(-0.7f, 0.8f, 0.0f));
    fig->vertices.push_back(vec3(-0.8f, 0.4f, 0.0f));

    // Triangolo 2:
    fig->vertices.push_back(vec3(0.8f, 0.8f, 0.0f));
    fig->vertices.push_back(vec3(0.7f, 0.8f, 0.0f));
    fig->vertices.push_back(vec3(0.8f, 0.4f, 0.0f));

    // Triangolo 3:
    fig->vertices.push_back(vec3(-0.2f, -0.2f, 0.0f));
    fig->vertices.push_back(vec3(-0.7f, 0.8f, 0.0f));
    fig->vertices.push_back(vec3(-0.8f, 0.4f, 0.0f));

    // Triangolo 4:
    fig->vertices.push_back(vec3(0.2f, -0.2f, 0.0f));
    fig->vertices.push_back(vec3(0.7f, 0.8f, 0.0f));
    fig->vertices.push_back(vec3(0.8f, 0.4f, 0.0f));

    // Triangolo 5:
    fig->vertices.push_back(vec3(-0.2f, -0.2f, 0.0f));
    fig->vertices.push_back(vec3(-0.7f, 0.8f, 0.0f));
    fig->vertices.push_back(vec3(0.0f, 0.4f, 0.0f));

    // Triangolo 6:
    fig->vertices.push_back(vec3(0.2f, -0.2f, 0.0f));
    fig->vertices.push_back(vec3(0.7f, 0.8f, 0.0f));
    fig->vertices.push_back(vec3(0.0f, 0.4f, 0.0f));

    // Triangolo 7:
    fig->vertices.push_back(vec3(-0.3f, -0.1f, 0.0f));
    fig->vertices.push_back(vec3(0.0f, -0.2f, 0.0f));
    fig->vertices.push_back(vec3(-0.4f, -0.4f, 0.0f));

    // Triangolo 8:
    fig->vertices.push_back(vec3(0.3f, -0.1f, 0.0f));
    fig->vertices.push_back(vec3(0.0f, -0.2f, 0.0f));
    fig->vertices.push_back(vec3(0.4f, -0.4f, 0.0f));

    // Triangolo 9:
    fig->vertices.push_back(vec3(-0.4f, -0.4f, 0.0f));
    fig->vertices.push_back(vec3(0.0f, -0.2f, 0.0f));
    fig->vertices.push_back(vec3(-0.2f, -0.6f, 0.0f));

    // Triangolo 10:
    fig->vertices.push_back(vec3(0.4f, -0.4f, 0.0f));
    fig->vertices.push_back(vec3(0.0f, -0.2f, 0.0f));
    fig->vertices.push_back(vec3(0.2f, -0.6f, 0.0f));

    // Triangolo 11:
    fig->vertices.push_back(vec3(-0.4f, -0.4f, 0.0f));
    fig->vertices.push_back(vec3(-0.4f, -0.6f, 0.0f));
    fig->vertices.push_back(vec3(-0.2f, -0.6f, 0.0f));

    // Triangolo 12:
    fig->vertices.push_back(vec3(0.4f, -0.4f, 0.0f));
    fig->vertices.push_back(vec3(0.4f, -0.6f, 0.0f));
    fig->vertices.push_back(vec3(0.2f, -0.6f, 0.0f));

    // Triangolo 13:
    fig->vertices.push_back(vec3(0.0f, 0.6f, 0.0f));
    fig->vertices.push_back(vec3(-0.2f, -0.2f, 0.0f));
    fig->vertices.push_back(vec3(0.2f, -0.2f, 0.0f));

    // Triangolo 14:
    fig->vertices.push_back(vec3(-0.2f, -0.2f, 0.0f));
    fig->vertices.push_back(vec3(0.2f, -0.2f, 0.0f));
    fig->vertices.push_back(vec3(0.f, -0.4f, 0.0f));



    // Colori per i vertici della farfalla
    // Colori per i triangoli delle ali
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso

    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso

    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso

    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso

    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso

    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso

    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso

    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso

    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso

    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso

    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso

    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso
    fig->colors.push_back(vec4(1.0, 0.3, 0.0, 1.0)); // Rosso

    fig->colors.push_back(vec4(1.0, 0.7, 0.0, 1.0)); // Rosso scuro per il corpo
    fig->colors.push_back(vec4(1.0, 0.7, 0.0, 1.0)); // Rosso scuro per il corpo
    fig->colors.push_back(vec4(1.0, 0.7, 0.0, 1.0)); // Rosso scuro per il corpo

    fig->colors.push_back(vec4(1.0, 0.7, 0.0, 1.0)); // Rosso scuro per il corpo
    fig->colors.push_back(vec4(1.0, 0.7, 0.0, 1.0)); // Rosso scuro per il corpo
    fig->colors.push_back(vec4(1.0, 0.7, 0.0, 1.0)); // Rosso scuro per il corpo

    // Imposta il numero di vertici e triangoli
    fig->nVertices = fig->vertices.size();
    fig->nTriangles = 13; 
    fig->render = GL_TRIANGLES;
}
