#pragma once
#include "lib.h"
#include "ShaderMaker.h"
#include "strutture.h" 
#include "inizializzazioni.h"
#include "init_geometrie.h"
#include "gestione_interazioni.h"
#include "Utilities.h"
 

extern float r, g, b;
extern unsigned int MatProjS, MatModelS, MatProj, MatModel, vec_resS, loc_time,loc_numberOfClouds;
extern mat4 Projection;
extern vec2 resolution;
extern float angolo;
extern int  height, width, nClouds;
extern float deltaTime;
extern unsigned int programId_text;
extern unsigned int VAO_Text, VBO_Text;
extern  vector<float> timerFig;
extern vector<Figura> Scena;

extern bool show_bounding_boxes;
extern Figura background;
extern Curva player, proiettile;

float angolo_barca;
void render(float currentFrame, int frame) {
    int n_deleted = 0;
    int i;
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
     


    glUseProgram(Scena[0].progamId);
    Scena[0].Model = mat4(1.0);
    Scena[0].Model = scale(Scena[0].Model, background.scale);
    
    glUniformMatrix4fv(MatProjS, 1, GL_FALSE, value_ptr(Projection));
    glUniformMatrix4fv(MatModelS, 1, GL_FALSE, value_ptr(Scena[0].Model));
    glUniform2fv(vec_resS, 1, value_ptr(resolution));
    glUniform1f(loc_time, currentFrame);
    glUniform1i(loc_numberOfClouds, nClouds);
    //Questa istruzione "lega" o "attiva" il Vertex Array Object (VAO) di ogni struttura di tipo Figura memorizzata nel vector Scena .
    glBindVertexArray(Scena[0].VAO);
    //Fa il rendering della struttura i-esima
    glDrawArrays(Scena[0].render, 0, Scena[0].nv);

     
    //Disegna il player
    angolo_barca = cos(radians(float(frame))) * 10.0;
    glUseProgram(Scena[1].progamId);
   
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    player.Model = mat4(1.0);
    player.Model = translate(player.Model, vec3(player.position.x, player.position.y, 0.0));
    player.Model = rotate(player.Model, radians(angolo_barca), vec3(0.0, 0.0, 1.0));

    //La posizione dle proiettile viene aggiornata facendo pressione sulla barra spaziatrice
    aggiornaProiettile(&proiettile);
    
    //Disegna il proiettile
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    //Aggiornamento della matrice di modellazione del proiettile: viene inizializzata alla matrice di modellazione del player e poi aggiornata in seguito alla pressione della barra spaziatrice
    proiettile.Model = translate(player.Model, vec3(proiettile.position.x + 20.0, proiettile.position.y + 20.0, 0.0));
    proiettile.Model = scale(proiettile.Model, vec3(20.0, 20.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(proiettile.Model));
    glBindVertexArray(proiettile.VAO);

    //Update Bounding box del proiettile

    updateBB(&proiettile);

    glBindVertexArray(proiettile.VAO);
    //disegna il proiettile (nelle utilme 4 posizioni del VBO sono memorizzati i vertici del Bounding Box
    glDrawArrays(proiettile.render, 0, proiettile.nv - 4);
    //disegna il Bounding Box
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, proiettile.nv - 4, 4);
  

    //Aggiorna la matrice di modellazione del player postmoltiplicando per una matrice di scala
    player.Model = scale(player.Model, player.scale);
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(player.Model));
    glBindVertexArray(player.VAO);

    //Fa il rendering del player
    glDrawArrays(player.render, 0, player.nv);
    
    //Disegna le shape animate
    for (i = 1; i < Scena.size(); i++) {
        //Rendering della shape se non è entrata in collisione con il proiettile
        if (Scena[i].isalive == true)
        {
            //Aggiornamento della posizione in maniera casuale
         
             Scena[i].timerFig += deltaTime;
             if (Scena[i].timerFig >= 1.0f) { // Aggiorna ogni 1 second0
                Scena[i].timerFig = 0.0f;
                Scena[i].position = randomPosition(width, height);
            };
             



            glUseProgram(Scena[i].progamId);
            glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));

            Scena[i].Model = mat4(1.0);
            Scena[i].Model = translate(Scena[i].Model, vec3(Scena[i].position.x, Scena[i].position.y, 1.0));
            Scena[i].Model = scale(Scena[i].Model, Scena[i].scale);

            //update Bounding Box
            updateBB(&Scena[i]);


            glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Scena[i].Model));
            glBindVertexArray(Scena[i].VAO);
            //renderizza la shape
            glDrawArrays(Scena[i].render, 0, Scena[i].nv - 4);
            //renderizza il bounding box
            if (show_bounding_boxes)
                glDrawArrays(GL_LINE_LOOP, Scena[i].nv - 4, 4);
        }
    }
    
   
    glUseProgram(Scena[1].progamId);

    //Verifica se c'è collisione tra le shape della scena ed il proiettile
    for (i = 1; i < Scena.size(); i++) {
        if (checkCollision(proiettile, Scena[i]))
            Scena[i].isalive = false;
    }

    

}