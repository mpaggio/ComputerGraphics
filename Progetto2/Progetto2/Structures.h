#pragma once
#include "Lib.h"

using namespace glm;

typedef struct {
    GLuint VAO;
    GLuint VBO_vertices;
    GLuint VBO_colors;
    int nTriangles;

    //Vertices geometry:
    vector<vec3> vertices;  // Array dinamicamente aggiornabile (ognuno dei suoi elementi è un vec3)
    vector<vec4> colors;
    int nVertices; // Number of vertices
    int render; // Type of render: GL_POINTS(senza collegamento), GL_LINES(collegati con una retta), GL_LINES_STRIP(collegati con linea spezzata), ...
} Figura;