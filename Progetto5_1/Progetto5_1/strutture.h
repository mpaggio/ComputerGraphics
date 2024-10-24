/*
#pragma once //: È una direttiva che indica al compilatore di includere il file una sola volta per unità di compilazione.
//  Il meccanismo esatto varia a seconda del compilatore, ma in generale si basa su un meccanismo interno per tenere traccia dei file già inclusi.
//Non è parte dello standard C++, quindi la sua disponibilità e il comportamento preciso possono variare tra diversi compilatori. Tuttavia, è supportata dalla maggior parte dei compilatori moderni.
*/


#pragma once

#include "lib.h"
typedef struct {
    GLuint VAO;  //identificatore del  Vertex Array Object (VAO)
    GLuint  VBO_vertices; //identificatore del  Vertex Buffer Object (VBO) che contiene le coordinate dei vertici dell'oggetto.
    GLuint  VBO_colors;   // l'identificatore di un VBO che contiene i colori dei vertici dell'oggetto.
    int nTriangles;  // numero di triangoli che costituiscono l'oggetto.
    // vertices
    vector<vec3> vertices;  //vector che contiene le coordinate dei vertici dell'oggetto. Ogni elemento del vettore è un vec3, che rappresenta una posizione 3D (x, y, z).
    vector<vec4> colors; //vector che contiene i colori dei vertici dell'oggetto. Ogni elemento del vettore è un vec4, che rappresenta un colore RGBA (red, green, blue, alpha).
    // Numero vertices  
    int nv;  //Numero di vertici della figura geometrica
    int render; //specifica come devono essere interpretati i vertici onella fase di rendering
    unsigned int progamId;
    mat4 Model;
    vec2 position;
    vec4 min_BB_obj;
    vec4 max_BB_obj;
    vec4 min_BB;
    vec4 max_BB;
    bool isalive;
    float updateTimer;
} Figura;

