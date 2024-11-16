#pragma once
#include "lib.h"
#include "ShaderMaker.h"
#include "strutture.h" 
#include "inizializzazioni.h"
#include "init_geometrie.h"
#include "gestione_interazioni.h"
#include "Utilities.h"
#include "Gui.h"

#define PI 3.14159265358979323


// ....................... VARIABILI GLOBALI .......................
bool car_swing = false, is_player_invincible = false;
extern bool show_bounding_boxes, game_end, isTransitioning, isRoadTransitioning, first_time_clicking;

extern int  height, width, playerPoints;

float angolo, angoloMouse, theta, randomTime1 = randomTime(), randomTime2 = randomTime(), randomTime3 = randomTime();
float invincibilityTimer = 0.0;
extern float r, g, b;
extern double mousex, mousey;
extern float speed, deltaTime;
extern float w_update, h_update, speed;

double timeCarSwing = 0;

extern unsigned int MatProjS, MatModelS, MatProj, MatModel, vec_resS, loc_time, loc_deltaTime;
extern unsigned int programId_text;
extern unsigned int VAO_Text, VBO_Text;

extern mat4 Projection;
extern vec2 resolution;
extern vector<float> timerFig;
extern vector<Figura> Scena;

extern Figura background;
extern Curva cupola_macchina, corpo_macchina, ruota_macchina, scudo;
extern Curva proiettile, macchia_fango, buco_strada, cannone, bersaglio;

extern GLint loc_speed, loc_resolution;
extern GLFWwindow* window;

// .................................................................





void render(float currentFrame, int frame) {

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
    buco_strada.timerFig += deltaTime;
    if (buco_strada.position.y < 0 && buco_strada.timerFig >= randomTime1) {
        buco_strada.position = randomPosition(width, height);
        buco_strada.timerFig = 0.0f;
        randomTime1 = randomTime();
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
    macchia_fango.timerFig += deltaTime;
    if (macchia_fango.position.y < 0 && macchia_fango.timerFig >= randomTime2) {
        macchia_fango.position = randomPosition(width, height);
        while (fabs(macchia_fango.position.x - buco_strada.position.x) < 100.0f) {
            macchia_fango.position = randomPosition(width, height);
        }
        macchia_fango.timerFig = 0.0f;
        randomTime2 = randomTime();
    }
    macchia_fango.Model = translate(macchia_fango.Model, vec3(macchia_fango.position.x, macchia_fango.position.y, 0.0));
    macchia_fango.Model = scale(macchia_fango.Model, vec3(90.0, 90.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(macchia_fango.Model));
    glBindVertexArray(macchia_fango.VAO);
    updateBB(&macchia_fango);
    glDrawArrays(macchia_fango.render, 0, macchia_fango.nv - 4);
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, macchia_fango.nv - 4, 4);



    // BERSAGLIO
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    bersaglio.Model = mat4(1.0);
    bersaglio.timerFig += deltaTime;
    if (bersaglio.timerFig >= 1.5f) {
        bersaglio.timerFig = 0.0f;
        bersaglio.position = randomPositionForTarget(width, height);
    };
    bersaglio.Model = translate(bersaglio.Model, vec3(bersaglio.position.x, bersaglio.position.y, 0.0));
    bersaglio.Model = scale(bersaglio.Model, vec3(180.0, 180.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(bersaglio.Model));
    glBindVertexArray(bersaglio.VAO);
    updateBB(&bersaglio);
    glDrawArrays(bersaglio.render, 0, bersaglio.nv - 4);
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, bersaglio.nv - 4, 4);



    // SCUDO
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    scudo.Model = mat4(1.0);
    scudo.position.y -= 0.4f;
    scudo.timerFig += deltaTime;
    if (scudo.timerFig >= randomTime3 && scudo.position.y > height + 200.0) {
        scudo.timerFig = 0.0f;
        scudo.position = randomPositionForTarget(width, height);
        randomTime3 = randomTime() * 2;
    };
    if (scudo.position.y < -200) {
        scudo.timerFig = 0.0;
        scudo.position = randomPosition(width, height);
        scudo.position.y += 1000.0;
    }
    scudo.Model = translate(scudo.Model, vec3(scudo.position.x, scudo.position.y, 0.0));
    scudo.Model = scale(scudo.Model, vec3(80.0, 80.0, 1.0));
    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(scudo.Model));
    glBindVertexArray(scudo.VAO);
    updateBB(&scudo);
    glDrawArrays(scudo.render, 0, scudo.nv - 4);
    if (show_bounding_boxes)
        glDrawArrays(GL_LINE_LOOP, scudo.nv - 4, 4);




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
        proiettile.position.x -= cos(theta - PI/2);
        proiettile.position.y -= sin(theta - PI/2);

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

    if (checkCollision(corpo_macchina, buco_strada) && !is_player_invincible) {
        game_end = true;
    }
    if (checkCollision(corpo_macchina, macchia_fango) && !is_player_invincible) {
        car_swing = true;
        timeCarSwing = glfwGetTime();
    }
    if (checkCollision(proiettile, bersaglio)) {
        playerPoints += 1;
        proiettile.isalive = false;
        proiettile.position.y = 0.0;
        proiettile.position.x = 0.0;
        first_time_clicking = true;
        bersaglio.timerFig = 0.0f;
        bersaglio.position = randomPositionForTarget(width, height);
    }
    if (checkCollision(corpo_macchina, scudo)) {
        is_player_invincible = true;
        invincibilityTimer = 0.0;
        scudo.timerFig = 0.0f;
        scudo.position = randomPosition(width, height);
        scudo.position.y += 1000.0;
    }

    if (is_player_invincible && invincibilityTimer >= 3.0) {
        is_player_invincible = false;
        invincibilityTimer = 0.0;
    }
    else if (is_player_invincible && invincibilityTimer < 3.0) {
        invincibilityTimer += deltaTime;
    }
}