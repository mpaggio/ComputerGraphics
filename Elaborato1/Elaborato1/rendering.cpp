#pragma once
#include "lib.h"
#include "ShaderMaker.h"
#include "strutture.h" 
#include "inizializzazioni.h"
#include "init_geometrie.h"
#include "gestione_interazioni.h"
#include "Utilities.h"


// ....................... VARIABILI GLOBALI .......................
extern int  height, width, nClouds;

float angolo_player;
extern float r, g, b;
extern float angolo;
extern float deltaTime;

extern unsigned int MatProjS, MatModelS, MatProj, MatModel, vec_resS, loc_time,loc_numberOfClouds;
extern unsigned int programId_text;
extern unsigned int VAO_Text, VBO_Text;

extern bool show_bounding_boxes;

extern mat4 Projection;
extern vec2 resolution;
extern vector<float> timerFig;
extern vector<Figura> Scena;

extern Figura background, sfera_di_energia;
extern Curva  corpo_navicella, cupola_navicella, asteroide, alieno;

// .................................................................





void render(float currentFrame, int frame) {

    int n_deleted = 0;
    int i;
    
    
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(Scena[0].programId);
    Scena[0].Model = mat4(1.0);
    Scena[0].Model = scale(Scena[0].Model, background.scale);
    
    glUniformMatrix4fv(MatProjS, 1, GL_FALSE, value_ptr(Projection));
    glUniformMatrix4fv(MatModelS, 1, GL_FALSE, value_ptr(Scena[0].Model));
    glUniform2fv(vec_resS, 1, value_ptr(resolution));
    glUniform1f(loc_time, currentFrame);
    glUniform1i(loc_numberOfClouds, nClouds);

    // Lega il Vertex Array Object (VAO) di ogni struttura di tipo Figura memorizzata in Scena
    glBindVertexArray(Scena[0].VAO);

    // Esegue il rendering della struttura specificata
    glDrawArrays(Scena[0].render, 0, Scena[0].nv);

    // Abilita il blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // CUPOLA NAVICELLA
    angolo_player = cos(radians(float(frame/3))) * 10.0;
    glUseProgram(Scena[1].programId);
   
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    cupola_navicella.Model = mat4(1.0);
    cupola_navicella.Model = translate(cupola_navicella.Model, vec3(cupola_navicella.position.x, cupola_navicella.position.y, 0.0));
    cupola_navicella.Model = rotate(cupola_navicella.Model, radians(angolo_player), vec3(0.0, 0.0, 1.0));

    // CORPO NAVICELLA
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    corpo_navicella.Model = translate(cupola_navicella.Model, vec3(corpo_navicella.position.x, corpo_navicella.position.y - 20.0, 0.0));
    corpo_navicella.Model = scale(corpo_navicella.Model, vec3(180.0, 180.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(corpo_navicella.Model));
    glBindVertexArray(corpo_navicella.VAO);

    //Update Bounding box del proiettile
    updateBB(&corpo_navicella);

    //disegna il proiettile (nelle utilme 4 posizioni del VBO sono memorizzati i vertici del Bounding Box
    glDrawArrays(corpo_navicella.render, 0, corpo_navicella.nv - 4);
    //disegna il Bounding Box
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, corpo_navicella.nv - 4, 4);



    // ALIENO
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    alieno.Model = translate(cupola_navicella.Model, vec3(alieno.position.x, alieno.position.y, 0.0));
    alieno.Model = scale(alieno.Model, vec3(90.0, 90.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(alieno.Model));
    glBindVertexArray(alieno.VAO);

    //Update Bounding box del proiettile
    updateBB(&alieno);

    //disegna il proiettile (nelle utilme 4 posizioni del VBO sono memorizzati i vertici del Bounding Box
    glDrawArrays(alieno.render, 0, alieno.nv - 4);
    //disegna il Bounding Box
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, alieno.nv - 4, 4);

    aggiornaProiettile(&sfera_di_energia);
    cout << "SFERA" << sfera_di_energia.position.x << ", " << sfera_di_energia.position.y << endl;
    cout << "CUPOLA" << cupola_navicella.position.x << ", " << cupola_navicella.position.y << endl;

    // SFERA DI ENERGIA
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    sfera_di_energia.Model = translate(cupola_navicella.Model, vec3(sfera_di_energia.position.x, sfera_di_energia.position.y - 60.0, 0.0));
    sfera_di_energia.Model = scale(sfera_di_energia.Model, vec3(20.0, 20.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(sfera_di_energia.Model));
    glBindVertexArray(sfera_di_energia.VAO);
    //disegna il proiettile (nelle utilme 4 posizioni del VBO sono memorizzati i vertici del Bounding Box
    glDrawArrays(sfera_di_energia.render, 0, sfera_di_energia.nv - 4);
    //disegna il Bounding Boxs
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, sfera_di_energia.nv - 4, 4);

    //Update Bounding box del proiettile
    updateBB(&sfera_di_energia);


    //Aggiorna la matrice di modellazione del player postmoltiplicando per una matrice di scala
    cupola_navicella.Model = scale(cupola_navicella.Model, cupola_navicella.scale);
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(cupola_navicella.Model));
    glBindVertexArray(cupola_navicella.VAO);

    //Fa il rendering del player
    glDrawArrays(cupola_navicella.render, 0, cupola_navicella.nv);
    
    //Disegna le shape animate
    for (i = 1; i < Scena.size(); i++) {
        
        //Rendering della shape se non è entrata in collisione con il proiettile
        if (Scena[i].isalive == true)
        {
            //Aggiornamento della posizione in maniera casuale
            Scena[i].timerFig += deltaTime;

            // Aggiorna ogni 1 secondo e mezzo
            if (Scena[i].timerFig >= 1.5f) {
                Scena[i].timerFig = 0.0f;
                Scena[i].position = randomPosition(width, height);
            };
             



            glUseProgram(Scena[i].programId);
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

    //Verifica se c'è collisione tra le shape della scena ed il proiettile
    for (i = 1; i < Scena.size(); i++) {
        if (checkCollision(sfera_di_energia, Scena[i])) {
            Scena[i].isalive = false;
        }
    }

}