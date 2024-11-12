#pragma once
#include "lib.h"
#include "ShaderMaker.h"
#include "strutture.h" 
#include "inizializzazioni.h"
#include "init_geometrie.h"
#include "gestione_interazioni.h"
#include "Utilities.h"


// ....................... VARIABILI GLOBALI .......................
extern int  height, width;

float angolo;
extern float r, g, b;
extern float speed, targetSpeed, speedTransitionRate, deltaTime;
extern float w_update, h_update, speed;

extern unsigned int MatProjS, MatModelS, MatProj, MatModel, vec_resS, loc_time, loc_deltaTime;
extern unsigned int programId_text;
extern unsigned int VAO_Text, VBO_Text;
extern GLint loc_speed, loc_resolution;

extern bool show_bounding_boxes;

extern mat4 Projection;
extern vec2 resolution;
extern vector<float> timerFig;
extern vector<Figura> Scena;

extern Figura background;
extern Curva cupola_macchina, corpo_macchina, ruota_macchina, proiettile, macchia_fango, buco_strada;

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

    updateSpeed(speed, targetSpeed, speedTransitionRate);
    updateDeltaTime();

    glUniform1f(loc_speed, speed);
    glUniform2f(loc_resolution, w_update, h_update);
    glUniform1f(loc_deltaTime, deltaTime);


    // Lega il Vertex Array Object (VAO) di ogni struttura di tipo Figura memorizzata in Scena
    glBindVertexArray(Scena[0].VAO);

    // Esegue il rendering della struttura specificata
    glDrawArrays(Scena[0].render, 0, Scena[0].nv);

    // Abilita il blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // CUPOLA NAVICELLA
    angolo = cos(radians(float(frame/3))) * 10.0;
    glUseProgram(proiettile.programId);
   
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    cupola_macchina.Model = mat4(1.0);
    cupola_macchina.Model = translate(cupola_macchina.Model, vec3(cupola_macchina.position.x, cupola_macchina.position.y - 150.0, 0.0));

    // CORPO NAVICELLA
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    corpo_macchina.Model = translate(cupola_macchina.Model, vec3(corpo_macchina.position.x, corpo_macchina.position.y, 0.0));
    corpo_macchina.Model = scale(corpo_macchina.Model, vec3(200.0, 200.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(corpo_macchina.Model));
    glBindVertexArray(corpo_macchina.VAO);

    //Update Bounding box del proiettile
    updateBB(&corpo_macchina);

    //disegna il proiettile (nelle utilme 4 posizioni del VBO sono memorizzati i vertici del Bounding Box
    glDrawArrays(corpo_macchina.render, 0, corpo_macchina.nv - 4);
    //disegna il Bounding Box
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, corpo_macchina.nv - 4, 4);



    // RUOTA MACCHINA 1
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    ruota_macchina.Model = translate(cupola_macchina.Model, vec3(ruota_macchina.position.x - 50.0, ruota_macchina.position.y + 80.0, 0.0));
    ruota_macchina.Model = scale(ruota_macchina.Model, vec3(80.0, 80.0, 1.0));
    //ruota_macchina.Model = rotate(ruota_macchina.Model, radians(angolo), vec3(0.0, 0.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(ruota_macchina.Model));
    glBindVertexArray(ruota_macchina.VAO);
    updateBB(&ruota_macchina);
    glDrawArrays(ruota_macchina.render, 0, ruota_macchina.nv - 4);
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, ruota_macchina.nv - 4, 4);

    // RUOTA MACCHINA 2
    ruota_macchina.Model = translate(cupola_macchina.Model, vec3(ruota_macchina.position.x - 50.0, ruota_macchina.position.y - 80.0, 0.0));
    ruota_macchina.Model = scale(ruota_macchina.Model, vec3(80.0, 80.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(ruota_macchina.Model));
    glBindVertexArray(ruota_macchina.VAO);
    updateBB(&ruota_macchina);
    glDrawArrays(ruota_macchina.render, 0, ruota_macchina.nv - 4);
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, ruota_macchina.nv - 4, 4);

    // RUOTA MACCHINA 3
    ruota_macchina.Model = translate(cupola_macchina.Model, vec3(ruota_macchina.position.x + 50.0, ruota_macchina.position.y + 80.0, 0.0));
    ruota_macchina.Model = scale(ruota_macchina.Model, vec3(80.0, 80.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(ruota_macchina.Model));
    glBindVertexArray(ruota_macchina.VAO);
    updateBB(&ruota_macchina);
    glDrawArrays(ruota_macchina.render, 0, ruota_macchina.nv - 4);
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, ruota_macchina.nv - 4, 4);

    // RUOTA MACCHINA 4
    ruota_macchina.Model = translate(cupola_macchina.Model, vec3(ruota_macchina.position.x + 50.0, ruota_macchina.position.y - 80.0, 0.0));
    ruota_macchina.Model = scale(ruota_macchina.Model, vec3(80.0, 80.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(ruota_macchina.Model));
    glBindVertexArray(ruota_macchina.VAO);
    updateBB(&ruota_macchina);
    glDrawArrays(ruota_macchina.render, 0, ruota_macchina.nv - 4);
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, ruota_macchina.nv - 4, 4);



    aggiornaProiettile(&proiettile);
    
    // PROIETTILE
    if (!proiettile.isalive) {
        glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
        proiettile.Model = translate(cupola_macchina.Model, vec3(proiettile.position.x, proiettile.position.y - 60.0, 0.0));
        proiettile.Model = scale(proiettile.Model, vec3(20.0, 20.0, 1.0));
        glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(proiettile.Model));
        glBindVertexArray(proiettile.VAO);
        glDrawArrays(proiettile.render, 0, proiettile.nv - 4);
        if (show_bounding_boxes)
            glDrawArrays(GL_LINE_LOOP, proiettile.nv - 4, 4);
        updateBB(&proiettile);
    }
    else {
        glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
        proiettile.Model = mat4(1.0);
        proiettile.Model = translate(proiettile.Model, vec3(proiettile.position.x, proiettile.position.y - 60.0, 0.0));
        proiettile.Model = scale(proiettile.Model, vec3(20.0, 20.0, 1.0));
        glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(proiettile.Model));
        glBindVertexArray(proiettile.VAO);
        glDrawArrays(proiettile.render, 0, proiettile.nv - 4);
        if (show_bounding_boxes)
            glDrawArrays(GL_LINE_LOOP, proiettile.nv - 4, 4);
        updateBB(&proiettile);
    }
    


    //Aggiorna la matrice di modellazione del player postmoltiplicando per una matrice di scala
    cupola_macchina.Model = scale(cupola_macchina.Model, cupola_macchina.scale);
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(cupola_macchina.Model));
    glBindVertexArray(cupola_macchina.VAO);

    //Fa il rendering del player
    glDrawArrays(cupola_macchina.render, 0, cupola_macchina.nv);
    
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
             



            glUseProgram(proiettile.programId);
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
        if (checkCollision(proiettile, Scena[i])) {
            Scena[i].isalive = false;
        }
    }

}