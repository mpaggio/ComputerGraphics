#pragma once
#include "strutture.h"
#include "Utilities.h"
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

    
}

void INIT_HEART(float cx, float cy, float raggiox, float raggioy, Figura* fig)
{
     

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


