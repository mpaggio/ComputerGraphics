/*
#pragma once //: È una direttiva che indica al compilatore di includere il file una sola volta per unità di compilazione.
//  Il meccanismo esatto varia a seconda del compilatore, ma in generale si basa su un meccanismo interno per tenere traccia dei file già inclusi.
//Non è parte dello standard C++, quindi la sua disponibilità e il comportamento preciso possono variare tra diversi compilatori. Tuttavia, è supportata dalla maggior parte dei compilatori moderni.
*/


#pragma once

#include "lib.h"
#include <string>
#pragma once
#include "Lib.h"

#include <string>

typedef struct {

    vector<vec3> vertices;   // Vettore contenente le coordinate dei vertici della mesh
    vector<vec4> colors;  // Vettore contenente i colori associati a ciascun vertice
    vector<GLuint> indices; // Vettore contenente gli indici dei vertici che definiscono i triangoli (o altre primitive)
    vector<vec3> normals; // Vettore contenente i vettori normali ai vertici (utili per il calcolo dell'illuminazione)
    vector<vec2> texCoords;  // Vettore contenente le coordinate delle texture per ciascun vertice
    mat4 Model;  // Matrice di modellazione per applicare trasformazioni alla mesh
    // Indice del vertex shader da utilizzare
    int sceltaVS;
    // Indice del fragment shader da utilizzare
    int sceltaFS;
    GLuint VAO;  // Vertex Array Object: identificatore dell'oggetto che contiene tutte le informazioni sulla mesh
    GLuint VBO_vertices;  // Vertex Buffer Object per le coordinate dei vertici
    GLuint VBO_colors;  // Vertex Buffer Object per i colori dei vertici
    GLuint VBO_normals;  // Vertex Buffer Object per le normali dei vertici
    GLuint EBO_indices;  // Element Buffer Object per gli indici dei vertici
    GLuint VBO_coord_texture;   // Vertex Buffer Object per le coordinate delle texture
    string nome;  // Nome della mesh (utile per l'identificazione)
    vec4 ancora_obj;  // Punto di ancoraggio della mesh nello spazio locale dell'oggetto
    vec4 ancora_world;   // Punto di ancoraggio della mesh nello spazio del mondo
} Mesh;



//Gestione Vista

typedef struct {
    vec3 position; // Posizione della camera nello spazio 3D
    vec3 target; // Punto verso cui la camera è puntata
    vec3 upVector; // Vettore che indica la direzione "up" della camera
    vec3 direction; // Vettore che indica la direzione di visione della camera
} ViewSetup;

//gestione proiezione
typedef struct {
    float fovY; // Campo visivo verticale in gradi
    float aspect; // Rapporto tra larghezza e altezza del viewport
    float near_plane; // Distanza del piano di clipping vicino
    float far_plane; // Distanza del piano di clipping lontano
} PerspectiveSetup;

