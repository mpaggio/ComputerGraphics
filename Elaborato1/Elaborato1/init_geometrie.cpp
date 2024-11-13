#pragma once
#include "strutture.h"
#include "Utilities.h"
#include "gestione_curve.h"
#include <fstream>
#pragma warning(disable:4996)
#define PI 3.14159265358979323


extern float alpha;
 
void INIT_TRIANGLE(Figura* fig) {
    fig->vertices.push_back(vec3(-0.5f, -0.5f, 0.0f));
    fig->vertices.push_back(vec3(0.5f, -0.5f, 0.0f));
    fig->vertices.push_back(vec3(0.0f, 0.5f, 0.0f));

    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));
    fig->colors.push_back(vec4(0.0, 0.0, 1.0, 1.0));
 
    fig->nv = fig->vertices.size();
    fig->render = GL_TRIANGLE_FAN;


    


}

void INIT_CIRCLE(float cx, float cy, float raggiox, float raggioy, Figura* fig) {

    int i;
    float stepA = (2 * PI) / fig->nTriangles;
    float t, xx, yy;


    fig->vertices.push_back(vec3(cx, cy, 0.0));

    fig->colors.push_back(vec4(0.0, 1.0, 1.0, 1.0));

    for (i = 0; i <= fig->nTriangles; i++)
    {
        t = (float)i * stepA;
        xx = cx + raggiox * cos(t);
        yy = cy + raggioy * sin(t);
        fig->vertices.push_back(vec3(xx, yy, 0.0));
        //Colore 
        fig->colors.push_back(vec4(0.0, 0.0, 1.0, 1.0)); //Nota che la quarta componente corrisponde alla trasparenza del colore
    }
    findBB(fig);
 

    fig->vertices.push_back(vec3(fig->min_BB_obj.x, fig->min_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(fig->max_BB_obj.x, fig->min_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(fig->max_BB_obj.x, fig->max_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(fig->min_BB_obj.x, fig->max_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));


    fig->nv = fig->vertices.size();
    fig->render = GL_TRIANGLE_FAN;

}



void INIT_BUTTERFLY(float cx, float cy, float raggiox, float raggioy, Figura* fig)
{
	int i;
	float t,xx,yy;
	float stepA = (2 * PI) / fig->nTriangles;
    fig->vertices.push_back(vec3(cx, cy, 0.0));
    

    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));

	for (i = 0; i <= fig->nTriangles; i++)
	{
		t = (float)i * stepA;
        xx = cx + raggiox * (sin(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5));
        yy = cy + raggioy * (cos(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t/ 12), 5));
        fig->vertices.push_back(vec3(xx, yy, 0.0));
        fig->colors.push_back(vec4(1.0, 0.5, 0.0, alpha));
	}
    
    findBB(fig);
    fig->vertices.push_back(vec3(fig->min_BB_obj.x, fig->min_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(fig->max_BB_obj.x, fig->min_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(fig->max_BB_obj.x, fig->max_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(fig->min_BB_obj.x, fig->max_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));

    fig->nv = fig->vertices.size();
    fig->render = GL_TRIANGLE_FAN;

    fig->nv = fig->vertices.size();
    fig->render = GL_TRIANGLE_FAN;

}

void INIT_HEART(float cx, float cy, float raggiox, float raggioy, Figura* fig) {
     
    int i;
    float t, xx, yy;
    float stepA = (2 * PI) / fig->nTriangles;
    fig->vertices.push_back(vec3(cx, cy, 0.0));

    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));

    for (i = 0; i <= fig->nTriangles; i++)
    {
        t = (float)i * stepA;
        xx = cx + raggiox * (16 * pow(sin(t), 3));
        yy = cy + raggioy * ((13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t)));
        fig->vertices.push_back(vec3(xx, yy, 0.0));
        fig->colors.push_back(vec4(1.0, 0.0, 0.0,1.0));
    }
     
    findBB(fig);
    fig->vertices.push_back(vec3(fig->min_BB_obj.x, fig->min_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(fig->max_BB_obj.x, fig->min_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(fig->max_BB_obj.x, fig->max_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(fig->min_BB_obj.x, fig->max_BB_obj.y, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));

    fig->nv = fig->vertices.size();
    fig->render = GL_TRIANGLE_FAN;

}

void INIT_PIANO(Figura* fig)
{
    fig->vertices.clear();

    fig->vertices.push_back(vec3(-0.5, -0.5, 0.0));
    fig->colors.push_back(vec4(0.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(0.5,-0.5, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(0.5, 0.5, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->vertices.push_back(vec3(-0.5, 0.5, 0.0));
    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));

    fig->nv = fig->vertices.size();
    fig->render = GL_TRIANGLE_FAN;


     
 }




void INIT_CUPOLA_MACCHINA(Curva* curva) {
    float* t;
    float step_t;
    int i;
    Dati dati[1000];
    FILE* file = fopen("cupola_macchina.txt", "r");

    if (file == NULL) {
        perror("Impossibile aprire il file");
    }

    int riga = 0;
    while (fscanf(file, "%f %f %f", &dati[riga].x, &dati[riga].y, &dati[riga].z) == 3) {
        riga++;

        if (riga >= 1000) {
            printf("Troppe righe nel file. L'array dati   stato completamente riempito.\n");
            break;
        }
    }

    fclose(file);


    for (int i = 0; i < riga; i++) {
        curva->CP.push_back(vec3(dati[i].x, dati[i].y, dati[i].z));
        curva->colCP.push_back(vec4(0.0, 0.0, 0.0, 1.0));
        curva->Derivata.push_back(vec3(0.0, 0.0, 0.0));
    }
    curva->ncp = curva->CP.size();

    t = new float[curva->CP.size()];
    step_t = 1.0 / (curva->CP.size() - 1);
    for (i = 0; i < curva->CP.size(); i++)
        t[i] = (float)i * step_t;

    t[curva->CP.size()] = 1.0;
    vec3 centro = vec3(0.0, -0.2, 0.0);
    vec4 color_top = vec4(0.0, 0.4, 1.0, 0.5);
    vec4 color_bot = vec4(0.0, 0.9, 1.0, 0.5);
    CostruisciHermite(t, curva, centro, color_top, color_bot);

    curva->nv = curva->vertices.size();
    curva->render = GL_TRIANGLE_FAN;

}




void INIT_CORPO_MACCHINA(Curva* curva) {
    float* t;
    float step_t;
    int i;
    Dati dati[1000];
    FILE* file = fopen("corpo_macchina.txt", "r");

    if (file == NULL) {
        perror("Impossibile aprire il file");
    }

    int riga = 0;
    while (fscanf(file, "%f %f %f", &dati[riga].x, &dati[riga].y, &dati[riga].z) == 3) {
        riga++;

        if (riga >= 1000) {
            printf("Troppe righe nel file. L'array dati   stato completamente riempito.\n");
            break;
        }
    }

    fclose(file);

    for (int i = 0; i < riga; i++) {
        curva->CP.push_back(vec3(dati[i].x, dati[i].y, dati[i].z));
        curva->colCP.push_back(vec4(0.0, 0.0, 0.0, 1.0));
        curva->Derivata.push_back(vec3(0.0, 0.0, 0.0));
    }
    curva->ncp = curva->CP.size();

    t = new float[curva->CP.size()];
    step_t = 1.0 / (curva->CP.size() - 1);
    for (i = 0; i < curva->CP.size(); i++)
        t[i] = (float)i * step_t;

    t[curva->CP.size()] = 1.0;
    vec3 centro = vec3(-0.01, 0.2, 0.0);
    vec4 color_top = vec4(0.8, 0.0, 0.0, 1.0);
    vec4 color_bot = vec4(1.0, 0.0, 0.0, 1.0);
    CostruisciHermite(t, curva, centro, color_top, color_bot);

    // Calcola la bounding box dell'oggetto (opzionale, ma utile per ottimizzare il rendering)
    findBB(curva);
    curva->vertices.push_back(vec3(curva->min_BB_obj.x, curva->min_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    curva->vertices.push_back(vec3(curva->max_BB_obj.x, curva->min_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    curva->vertices.push_back(vec3(curva->max_BB_obj.x, curva->max_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    curva->vertices.push_back(vec3(curva->min_BB_obj.x, curva->max_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));

    curva->nv = curva->vertices.size();
    curva->render = GL_TRIANGLE_FAN;

}




void INIT_RUOTA_MACCHINA(Curva* curva) {
    float* t;
    float step_t;
    int i;
    Dati dati[1000];
    FILE* file = fopen("ruota_macchina.txt", "r");

    if (file == NULL) {
        perror("Impossibile aprire il file");
    }

    int riga = 0;
    while (fscanf(file, "%f %f %f", &dati[riga].x, &dati[riga].y, &dati[riga].z) == 3) {
        riga++;

        if (riga >= 1000) {
            printf("Troppe righe nel file. L'array dati   stato completamente riempito.\n");
            break;
        }
    }

    fclose(file);

    for (int i = 0; i < riga; i++) {
        curva->CP.push_back(vec3(dati[i].x, dati[i].y, dati[i].z));
        curva->colCP.push_back(vec4(0.0, 0.0, 0.0, 1.0));
        curva->Derivata.push_back(vec3(0.0, 0.0, 0.0));
    }
    curva->ncp = curva->CP.size();

    t = new float[curva->CP.size()];
    step_t = 1.0 / (curva->CP.size() - 1);
    for (i = 0; i < curva->CP.size(); i++)
        t[i] = (float)i * step_t;

    t[curva->CP.size()] = 1.0;
    vec3 centro = vec3(-0.2, 0.2, 0.0);
    vec4 color_top = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 color_bot = vec4(0.0, 0.0, 0.0, 1.0);
    CostruisciHermite(t, curva, centro, color_top, color_bot);

    // Calcola la bounding box dell'oggetto (opzionale, ma utile per ottimizzare il rendering)
    findBB(curva);
    curva->vertices.push_back(vec3(curva->min_BB_obj.x, curva->min_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    curva->vertices.push_back(vec3(curva->max_BB_obj.x, curva->min_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    curva->vertices.push_back(vec3(curva->max_BB_obj.x, curva->max_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    curva->vertices.push_back(vec3(curva->min_BB_obj.x, curva->max_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));

    curva->nv = curva->vertices.size();
    curva->render = GL_TRIANGLE_FAN;

}




void INIT_PROIETTILE(Curva* curva) {
    float* t;
    float step_t;
    int i;
    Dati dati[1000];
    FILE* file = fopen("proiettile.txt", "r");

    if (file == NULL) {
        perror("Impossibile aprire il file");
    }

    int riga = 0;
    while (fscanf(file, "%f %f %f", &dati[riga].x, &dati[riga].y, &dati[riga].z) == 3) {
        riga++;

        if (riga >= 1000) {
            printf("Troppe righe nel file. L'array dati   stato completamente riempito.\n");
            break;
        }
    }

    fclose(file);

    for (int i = 0; i < riga; i++) {
        curva->CP.push_back(vec3(dati[i].x, dati[i].y, dati[i].z));
        curva->colCP.push_back(vec4(0.0, 0.0, 0.0, 1.0));
        curva->Derivata.push_back(vec3(0.0, 0.0, 0.0));
    }
    curva->ncp = curva->CP.size();

    t = new float[curva->CP.size()];
    step_t = 1.0 / (curva->CP.size() - 1);
    for (i = 0; i < curva->CP.size(); i++)
        t[i] = (float)i * step_t;

    t[curva->CP.size()] = 1.0;
    vec3 centro = vec3(0.0, 0.0, 0.0);
    vec4 color_top = vec4(1.0, 0.5, 0.0, 1.0);
    vec4 color_bot = vec4(1.0, 0.8, 0.0, 1.0);
    CostruisciHermite(t, curva, centro, color_top, color_bot);

    // Calcola la bounding box dell'oggetto (opzionale, ma utile per ottimizzare il rendering)
    findBB(curva);
    curva->vertices.push_back(vec3(curva->min_BB_obj.x, curva->min_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    curva->vertices.push_back(vec3(curva->max_BB_obj.x, curva->min_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    curva->vertices.push_back(vec3(curva->max_BB_obj.x, curva->max_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    curva->vertices.push_back(vec3(curva->min_BB_obj.x, curva->max_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));

    curva->nv = curva->vertices.size();
    curva->render = GL_TRIANGLE_FAN;

}




void INIT_MACCHIA_FANGO(Curva* curva) {
    float* t;
    float step_t;
    int i;
    Dati dati[1000];
    FILE* file = fopen("macchia_fango.txt", "r");

    if (file == NULL) {
        perror("Impossibile aprire il file");
    }

    int riga = 0;
    while (fscanf(file, "%f %f %f", &dati[riga].x, &dati[riga].y, &dati[riga].z) == 3) {
        riga++;

        if (riga >= 1000) {
            printf("Troppe righe nel file. L'array dati   stato completamente riempito.\n");
            break;
        }
    }

    fclose(file);

    for (int i = 0; i < riga; i++) {
        curva->CP.push_back(vec3(dati[i].x, dati[i].y, dati[i].z));
        curva->colCP.push_back(vec4(0.0, 0.0, 0.0, 1.0));
        curva->Derivata.push_back(vec3(0.0, 0.0, 0.0));
    }
    curva->ncp = curva->CP.size();

    t = new float[curva->CP.size()];
    step_t = 1.0 / (curva->CP.size() - 1);
    for (i = 0; i < curva->CP.size(); i++)
        t[i] = (float)i * step_t;

    t[curva->CP.size()] = 1.0;
    vec3 centro = vec3(0.0, 0.0, 0.0);
    vec4 color_top = vec4(0.3, 0.0, 0.0, 1.0);
    vec4 color_bot = vec4(0.5, 0.0, 0.0, 1.0);
    CostruisciHermite(t, curva, centro, color_top, color_bot);

    // Calcola la bounding box dell'oggetto (opzionale, ma utile per ottimizzare il rendering)
    findBB(curva);
    curva->vertices.push_back(vec3(curva->min_BB_obj.x, curva->min_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    curva->vertices.push_back(vec3(curva->max_BB_obj.x, curva->min_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    curva->vertices.push_back(vec3(curva->max_BB_obj.x, curva->max_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    curva->vertices.push_back(vec3(curva->min_BB_obj.x, curva->max_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));

    curva->nv = curva->vertices.size();
    curva->render = GL_TRIANGLE_FAN;

}




void INIT_BUCO_STRADA(Curva* curva) {
    float* t;
    float step_t;
    int i;
    Dati dati[1000];
    FILE* file = fopen("buco_strada.txt", "r");

    if (file == NULL) {
        perror("Impossibile aprire il file");
    }

    int riga = 0;
    while (fscanf(file, "%f %f %f", &dati[riga].x, &dati[riga].y, &dati[riga].z) == 3) {
        riga++;

        if (riga >= 1000) {
            printf("Troppe righe nel file. L'array dati   stato completamente riempito.\n");
            break;
        }
    }

    fclose(file);

    for (int i = 0; i < riga; i++) {
        curva->CP.push_back(vec3(dati[i].x, dati[i].y, dati[i].z));
        curva->colCP.push_back(vec4(0.0, 0.0, 0.0, 1.0));
        curva->Derivata.push_back(vec3(0.0, 0.0, 0.0));
    }
    curva->ncp = curva->CP.size();

    t = new float[curva->CP.size()];
    step_t = 1.0 / (curva->CP.size() - 1);
    for (i = 0; i < curva->CP.size(); i++)
        t[i] = (float)i * step_t;

    t[curva->CP.size()] = 1.0;
    vec3 centro = vec3(0.0, 0.0, 0.0);
    vec4 color_top = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 color_bot = vec4(0.4, 0.4, 0.4, 1.0);
    CostruisciHermite(t, curva, centro, color_top, color_bot);

    // Calcola la bounding box dell'oggetto (opzionale, ma utile per ottimizzare il rendering)
    findBB(curva);
    curva->vertices.push_back(vec3(curva->min_BB_obj.x, curva->min_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    curva->vertices.push_back(vec3(curva->max_BB_obj.x, curva->min_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    curva->vertices.push_back(vec3(curva->max_BB_obj.x, curva->max_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    curva->vertices.push_back(vec3(curva->min_BB_obj.x, curva->max_BB_obj.y, 0.0));
    curva->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));

    curva->nv = curva->vertices.size();
    curva->render = GL_TRIANGLE_FAN;

}