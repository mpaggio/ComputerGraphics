#pragma once
#include "strutture.h"
#include "init_geometrie.h"

#define PI 3.1415926535879323

void INIT_TRIANGLE(Figura* fig) {
    fig->vertices.push_back(vec3(-0.5f, -0.5f, 0.0f));
    fig->vertices.push_back(vec3(0.5f, -0.5f, 0.0f));
    fig->vertices.push_back(vec3(0.0f, 0.5f, 0.0f));

    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));
    fig->colors.push_back(vec4(0.0, 0.0, 1.0, 1.0));
    fig->nv = 3;
    fig->render = GL_TRIANGLES;
}

void INIT_CIRCLE(float centerX, float centerY, float raggioX, float raggioY, Figura* fig){
    // Definizione delle variabili
    int i;
    float t, xX, yY;
    float stepA = (2 * PI) / fig->nTriangles;   // L'angolo di step (ovvero l'angolo di ogni triangolo nel vertice con l'origine)
    
    // Mettiamo per primo il vertice origine del cerchio
    fig->vertices.push_back(vec3(centerX, centerY, 0.0));
    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));

    // Riempiamo i vettori automaticamente
    for (i = 0; i <= fig->nTriangles; i++) {
        t = (float)i * stepA;
        xX = centerX + raggioX * cos(t);
        yY = centerY + raggioY * sin(t);
        fig->vertices.push_back(vec3(xX, yY, 0.0));
        fig->colors.push_back(vec4(0.0, 0.0, 1.0, 0.0));
    }

    // Inizializziamo gli attributi della struttura Figura
    fig->nv = fig->vertices.size();
    fig->render = GL_TRIANGLE_FAN;  // Crea il ventaglio di triangoli (partendo dall'origine definita e prendendo a due a due i vari vertici)
}

void INIT_HEART(float centerX, float centerY, float raggioX, float raggioY, Figura* fig){
    // Definizione delle variabili
    int i;
    float t, xX, yY;
    float stepA = (2 * PI) / fig->nTriangles;   // L'angolo di step (ovvero l'angolo di ogni triangolo nel vertice con l'origine)

    // Mettiamo per primo il vertice origine del cerchio
    fig->vertices.push_back(vec3(centerX, centerY, 0.0));
    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));

    // Riempiamo i vettori automaticamente
    for (i = 0; i <= fig->nTriangles; i++) {
        t = (float)i * stepA;
        xX = centerX + raggioX * 16 * (pow(sin(t), 3));
        yY = centerY + raggioY * (13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t));
        fig->vertices.push_back(vec3(xX, yY, 0.0));
        fig->colors.push_back(vec4(1.0, 0.0, 0.0, 0.0));
    }

    // Inizializziamo gli attributi della struttura Figura
    fig->nv = fig->vertices.size();
    fig->render = GL_TRIANGLE_FAN;  // Crea il ventaglio di triangoli (partendo dall'origine definita e prendendo a due a due i vari vertici)
}

void INIT_BUTTERFLY(float centerX, float centerY, float raggioX, float raggioY, Figura* fig){
    // Definizione delle variabili
    int i;
    float t, xX, yY;
    float stepA = (2 * PI) / fig->nTriangles;   // L'angolo di step (ovvero l'angolo di ogni triangolo nel vertice con l'origine)

    // Mettiamo per primo il vertice origine del cerchio
    fig->vertices.push_back(vec3(centerX, centerY, 0.0));
    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));

    // Riempiamo i vettori automaticamente
    for (i = 0; i <= fig->nTriangles; i++) {
        t = (float)i * stepA;
        xX = centerX + raggioX * (sin(t) * (exp(cos(t)) - 2 * cos(4 * t) + pow(sin(t / 12), 5)));
        yY = centerY + raggioY * (cos(t) * (exp(cos(t)) - 2 * cos(4 * t) + pow(sin(t / 12), 5)));
        fig->vertices.push_back(vec3(xX, yY, 0.0));
        fig->colors.push_back(vec4(1.0, 0.4, 0.0, 0.0));
    }

    // Inizializziamo gli attributi della struttura Figura
    fig->nv = fig->vertices.size();
    fig->render = GL_TRIANGLE_FAN;  // Crea il ventaglio di triangoli (partendo dall'origine definita e prendendo a due a due i vari vertici)
}
