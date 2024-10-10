#pragma once
#include <glad/glad.h>
#include "ShaderMaker.h"
#include "strutture.h"

extern unsigned int programId;

void INIT_SHADER(void)
{
    GLenum ErrorCheckValue = glGetError();

    char* vertexShader = (char*)"vertexshaderC.glsl";
    char* fragmentShader = (char*)"fragmentshaderC.glsl";
    // La funzione successiva crea un programma shader completo a partire da due shader individuali: 
    // uno per la gestione dei vertici e uno per la gestione dei pixel. 
    // Il programma shader risultante viene identificato da un numero univoco (il programId) che verr  utilizzato in seguito per associarlo ad un oggetto grafico e per renderizzarlo.
     //All'interno della funzione ShaderMaker::createProgram
        //Compilazione degli shader : La funzione compila i due shader individuali, verificando che non ci siano errori di sintassi.
        //Linkaggio : Una volta compilati, i due shader vengono collegati insieme per formare un programma shader completo.
        // Creazione dell'identificativo: Viene generato un identificativo univoco per il programma shader e viene restituito alla funzione chiamante.

    programId = ShaderMaker::createProgram(vertexShader, fragmentShader);


    //La funzione successiva specifica al rendering engine quale programma shader deve essere utilizzato per le successive operazioni di rendering. 
    // In pratica, "attiva" il programma shader associato all'identificatore programId.

    glUseProgram(programId);

}


void INIT_VAO(Figura* fig)
{
    //La funzione INIT_VAO  ha per input Figura* fig, che è  un puntatore  che punta all'indirizzo ricevuto.
    //In questo modo è  possibile modificare direttamente i dati della struttura originale, evitando la creazione di copie inutili.

    glGenVertexArrays(1, &fig->VAO);
    glBindVertexArray(fig->VAO);
    //Genero , rendo attivo, riempio il VBO della geometria dei vertices
    glGenBuffers(1, &fig->VBO_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_vertices);

    //fig->vertices.size() : Ottiene il numero di elementi nel vettore vertices della struttura Figura puntata da fig.
    // sizeof(vec3) : Ottiene la dimensione in byte di un singolo elemento di tipo vec3.
    //La moltiplicazione fig->vertices.size() * sizeof(vec3): calcola la dimensione totale in byte dei dati dei vertici. Calcola la dimensione totale in byte di tutti i dati dei vertici.

    //fig->vertices.data() : fornisce un puntatore all'inizio dei dati del vettore vertices. Questo puntatore indica la posizione esatta in memoria dove sono memorizzati i dati

    glBufferData(GL_ARRAY_BUFFER, fig->vertices.size() * sizeof(vec3), fig->vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    //Genero , rendo attivo, riempio il VBO dei colori
    glGenBuffers(1, &fig->VBO_colors);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_colors);
    glBufferData(GL_ARRAY_BUFFER, fig->colors.size() * sizeof(vec4), fig->colors.data(), GL_STATIC_DRAW);
    //Adesso carico il VBO dei coloris nel layer 2
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

}

void INIT_DYNAMIC_VAO(Figura* fig)
{
    //La funzione INIT_VAO  ha per input Figura* fig, che è  un puntatore  che punta all'indirizzo ricevuto.
    //In questo modo è  possibile modificare direttamente i dati della struttura originale, evitando la creazione di copie inutili.

    glGenVertexArrays(1, &fig->VAO);
    glBindVertexArray(fig->VAO);
    //Genero , rendo attivo, riempio il VBO della geometria dei vertices
    glGenBuffers(1, &fig->VBO_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_vertices);

    //fig->vertices.size() : Ottiene il numero di elementi nel vettore vertices della struttura Figura puntata da fig.
    // sizeof(vec3) : Ottiene la dimensione in byte di un singolo elemento di tipo vec3.
    //La moltiplicazione fig->vertices.size() * sizeof(vec3): calcola la dimensione totale in byte dei dati dei vertici. Calcola la dimensione totale in byte di tutti i dati dei vertici.

    //fig->vertices.data() : fornisce un puntatore all'inizio dei dati del vettore vertices. Questo puntatore indica la posizione esatta in memoria dove sono memorizzati i dati

    glBufferData(GL_ARRAY_BUFFER, fig->vertices.size() * sizeof(vec3), fig->vertices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    //Genero , rendo attivo, riempio il VBO dei colori
    glGenBuffers(1, &fig->VBO_colors);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_colors);
    glBufferData(GL_ARRAY_BUFFER, fig->colors.size() * sizeof(vec4), fig->colors.data(), GL_DYNAMIC_DRAW);
    //Adesso carico il VBO dei coloris nel layer 2
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

}
