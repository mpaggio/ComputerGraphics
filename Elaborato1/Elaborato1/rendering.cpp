#pragma once
#include "lib.h"
#include "ShaderMaker.h"
#include "strutture.h" 
#include "inizializzazioni.h"
#include "init_geometrie.h"
#include "gestione_interazioni.h"
#include "Utilities.h"
#include "Gui.h"


// ....................... VARIABILI GLOBALI .......................
double timeCarSwing = 0;
extern int  height, width;

float angolo, angoloMouse, theta;
extern float r, g, b;
extern double mousex, mousey;
extern float speed, deltaTime;
extern float w_update, h_update, speed;

extern unsigned int MatProjS, MatModelS, MatProj, MatModel, vec_resS, loc_time, loc_deltaTime;
extern unsigned int programId_text;
extern unsigned int VAO_Text, VBO_Text;
extern GLint loc_speed, loc_resolution;

bool car_swing = false;
extern bool show_bounding_boxes, game_end, isTransitioning, isRoadTransitioning;

extern mat4 Projection;
extern vec2 resolution;
extern vector<float> timerFig;
extern vector<Figura> Scena;

extern Figura background;
extern Curva cupola_macchina, corpo_macchina, ruota_macchina, proiettile, macchia_fango, buco_strada, cannone;

extern GLFWwindow* window;

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




    // CUPOLA MACCHINA
    angolo = cos(radians(float(frame/3))) * 10.0;
    glUseProgram(proiettile.programId);
   
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    cupola_macchina.Model = mat4(1.0);
    cupola_macchina.Model = translate(cupola_macchina.Model, vec3(cupola_macchina.position.x, cupola_macchina.position.y - 150.0, 0.0));
    if (car_swing) {
        cupola_macchina.Model = rotate(cupola_macchina.Model, radians(angolo), vec3(0.0, 0.0, 1.0));
    }
    if (glfwGetTime() - timeCarSwing >= 2.0) {
        car_swing = false;
    }




    // BUCO STRADA
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    buco_strada.Model = mat4(1.0);
    buco_strada.position.y -= 0.4f;
    if (buco_strada.position.y < 0) {
        buco_strada.position = randomPosition(width, height);
    }
    buco_strada.Model = translate(buco_strada.Model, vec3(buco_strada.position.x, buco_strada.position.y, 0.0));
    buco_strada.Model = scale(buco_strada.Model, vec3(120.0, 120.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(buco_strada.Model));
    glBindVertexArray(buco_strada.VAO);
    updateBB(&buco_strada);
    glDrawArrays(buco_strada.render, 0, buco_strada.nv - 4);
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, buco_strada.nv - 4, 4);



    // MACCHIA FANGO
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    macchia_fango.Model = mat4(1.0);
    macchia_fango.position.y -= 0.4f;
    if (macchia_fango.position.y < 0) {
        macchia_fango.position = randomPosition(width, height);
        while (fabs(macchia_fango.position.x - buco_strada.position.x) < 100.0f) {
            macchia_fango.position = randomPosition(width, height);
        }
    }
    macchia_fango.Model = translate(macchia_fango.Model, vec3(macchia_fango.position.x, macchia_fango.position.y, 0.0));
    macchia_fango.Model = scale(macchia_fango.Model, vec3(90.0, 90.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(macchia_fango.Model));
    glBindVertexArray(macchia_fango.VAO);
    updateBB(&macchia_fango);
    glDrawArrays(macchia_fango.render, 0, macchia_fango.nv - 4);
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, macchia_fango.nv - 4, 4);




    // CORPO MACCHINA
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    corpo_macchina.Model = translate(cupola_macchina.Model, vec3(corpo_macchina.position.x, corpo_macchina.position.y, 0.0));
    corpo_macchina.Model = scale(corpo_macchina.Model, vec3(140.0, 140.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(corpo_macchina.Model));
    glBindVertexArray(corpo_macchina.VAO);
    updateBB(&corpo_macchina);
    glDrawArrays(corpo_macchina.render, 0, corpo_macchina.nv - 4);
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, corpo_macchina.nv - 4, 4);



    // CANNONE
    /* Sottraggo il valore corrispondente a 90° in radianti(poiche l'angolo sarebbe rispetto al verso positivo di x
       ma qui serve rispetto al verso positivo di y. */
    angoloMouse = atan2(mousey - cannone.position.y, mousex - cannone.position.x) - 1.571;
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    cannone.Model = mat4(1.0);
    cannone.position = cupola_macchina.position;
    cannone.Model = translate(cannone.Model, vec3(cannone.position.x, cannone.position.y - 150.0, 0.0));
    cannone.Model = rotate(cannone.Model, angoloMouse, vec3(0.0, 0.0, 1.0));
    cannone.Model = scale(cannone.Model, vec3(40.0, 60.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(cannone.Model));
    glBindVertexArray(cannone.VAO);
    updateBB(&cannone);
    glDrawArrays(cannone.render, 0, cannone.nv - 4);
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, cannone.nv - 4, 4);



    // RUOTA MACCHINA 1
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    ruota_macchina.Model = translate(cupola_macchina.Model, vec3(ruota_macchina.position.x - 40.0, ruota_macchina.position.y + 60.0, 0.0));
    ruota_macchina.Model = scale(ruota_macchina.Model, vec3(80.0, 80.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(ruota_macchina.Model));
    glBindVertexArray(ruota_macchina.VAO);
    updateBB(&ruota_macchina);
    glDrawArrays(ruota_macchina.render, 0, ruota_macchina.nv - 4);
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, ruota_macchina.nv - 4, 4);

    // RUOTA MACCHINA 2
    ruota_macchina.Model = translate(cupola_macchina.Model, vec3(ruota_macchina.position.x - 40.0, ruota_macchina.position.y - 60.0, 0.0));
    ruota_macchina.Model = scale(ruota_macchina.Model, vec3(80.0, 80.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(ruota_macchina.Model));
    glBindVertexArray(ruota_macchina.VAO);
    updateBB(&ruota_macchina);
    glDrawArrays(ruota_macchina.render, 0, ruota_macchina.nv - 4);
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, ruota_macchina.nv - 4, 4);

    // RUOTA MACCHINA 3
    ruota_macchina.Model = translate(cupola_macchina.Model, vec3(ruota_macchina.position.x + 40.0, ruota_macchina.position.y + 60.0, 0.0));
    ruota_macchina.Model = scale(ruota_macchina.Model, vec3(80.0, 80.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(ruota_macchina.Model));
    glBindVertexArray(ruota_macchina.VAO);
    updateBB(&ruota_macchina);
    glDrawArrays(ruota_macchina.render, 0, ruota_macchina.nv - 4);
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, ruota_macchina.nv - 4, 4);

    // RUOTA MACCHINA 4
    ruota_macchina.Model = translate(cupola_macchina.Model, vec3(ruota_macchina.position.x + 40.0, ruota_macchina.position.y - 60.0, 0.0));
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
        theta = angoloMouse;
        glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
        proiettile.Model = mat4(1.0);
        proiettile.position.x = cannone.position.x;
        proiettile.position.y = cannone.position.y;
        proiettile.Model = translate(proiettile.Model, vec3(proiettile.position.x, proiettile.position.y - 150.0, 0.0));
        proiettile.Model = rotate(proiettile.Model, angoloMouse, vec3(0.0, 0.0, 1.0));
        proiettile.Model = scale(proiettile.Model, vec3(20.0, 20.0, 1.0));
        glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(proiettile.Model));
        glBindVertexArray(proiettile.VAO);
        glDrawArrays(proiettile.render, 0, proiettile.nv - 4);
        if (show_bounding_boxes)
            glDrawArrays(GL_LINE_LOOP, proiettile.nv - 4, 4);
        updateBB(&proiettile);
    }
    else {
        proiettile.position.x -= cos(theta - 1.571);
        proiettile.position.y -= sin(theta - 1.571);

        glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
        proiettile.Model = mat4(1.0);
        proiettile.Model = translate(proiettile.Model, vec3(proiettile.position.x, proiettile.position.y - 150.0, 0.0));
        proiettile.Model = rotate(proiettile.Model, theta, vec3(0.0, 0.0, 1.0));
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

    if (checkCollision(corpo_macchina, buco_strada)) {
        game_end = true;
    }
    if (checkCollision(corpo_macchina, macchia_fango)) {
        car_swing = true;
        timeCarSwing = glfwGetTime();
    }
}