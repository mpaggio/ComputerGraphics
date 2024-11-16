/*
#pragma once //: � una direttiva che indica al compilatore di includere il file una sola volta per unit� di compilazione.
//  Il meccanismo esatto varia a seconda del compilatore, ma in generale si basa su un meccanismo interno per tenere traccia dei file gi� inclusi.
//Non � parte dello standard C++, quindi la sua disponibilit� e il comportamento preciso possono variare tra diversi compilatori. Tuttavia, � supportata dalla maggior parte dei compilatori moderni.
*/


#pragma once

#include "lib.h"
#include <string>
typedef struct {
    GLuint VAO;  //identificatore del  Vertex Array Object (VAO)
    GLuint  VBO_vertices; //identificatore del  Vertex Buffer Object (VBO) che contiene le coordinate dei vertici dell'oggetto.
    GLuint  VBO_colors;   // l'identificatore di un VBO che contiene i colori dei vertici dell'oggetto.
    int nTriangles;  // numero di triangoli che costituiscono l'oggetto.
    // vertices
    vector<vec3> vertices;  //vector che contiene le coordinate dei vertici dell'oggetto. Ogni elemento del vettore � un vec3, che rappresenta una posizione 3D (x, y, z).
    vector<vec4> colors; //vector che contiene i colori dei vertici dell'oggetto. Ogni elemento del vettore � un vec4, che rappresenta un colore RGBA (red, green, blue, alpha).
    // Numero vertices  
    int nv;  //Numero di vertici della figura geometrica
    int render; //specifica come devono essere interpretati i vertici onella fase di rendering
    unsigned int programId;
    mat4 Model;
    vec2 position;
    vec3 scale;
    vec4 min_BB_obj;
    vec4 max_BB_obj;
    vec4 min_BB;
    vec4 max_BB;
    float timerFig;
    bool isalive;
    } Figura; 

 
typedef struct {
    // Identificatori OpenGL per la gestione della geometria e degli attributi
    GLuint VAO;                // Vertex Array Object
    GLuint VBO_vertices;       // Vertex Buffer Object per le coordinate dei vertici della curva
    GLuint VBO_colors;         // Vertex Buffer Object per i colori dei vertici della curva
    GLuint VBO_CP;             // Vertex Buffer Object per le coordinate dei control points
    GLuint VBO_CP_colors;      // Vertex Buffer Object per i colori dei control points
    GLuint VBO_TG;             // Vertex Buffer Object per le coordinate delle tangenti
    GLuint VBO_TG_colors;      // Vertex Buffer Object per i colori delle tangenti

     
    vec4 min_BB_obj;
    vec4 max_BB_obj;
    vec4 min_BB;
    vec4 max_BB;
    

    // Dati geometrici della curva
    std::vector<glm::vec3> vertices;  // Coordinate dei vertici della curva
    std::vector<glm::vec4> colors;    // Colori dei vertici della curva
    std::vector<glm::vec3> CP;        // Coordinate dei control points (punti di controllo)
    std::vector<glm::vec4> colCP;     // Colori dei control points
    std::vector<glm::vec3> tg;        // Coordinate dei vettori tangenti ai control points
    std::vector<glm::vec4> col_tg;     // Colori dei vettori tangenti

    // Parametri di interpolazione
    std::vector<glm::vec3> Derivata;  // Vettore derivata (a cosa serve esattamente?)
    std::vector<float> Tens;       // Tensore di tensione
    std::vector<float> Bias;       // Bias
    std::vector<float> Cont;       // Controllo (specificare meglio)

    // Informazioni sulla curva
    int nv;                     // Numero di vertici della curva
    int ncp;                    // Numero di control points
    int ntg;                    // Numero di vettori tangenti
    glm::mat4 Model;            // Matrice di modellazione
    vec2 position;
    vec3 scale;
    // Parametri di rendering
    int render;                // Modalit� di rendering (linee, triangoli, ...)
    unsigned int programId;    // Identificatore del programma shader
    bool isalive;
    float timerFig;

} Curva;


typedef struct {
    float x;
    float y;
    float z;
} Dati;

 