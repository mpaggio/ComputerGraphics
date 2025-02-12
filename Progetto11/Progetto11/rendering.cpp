#pragma once
#include "strutture.h"
#include "lib.h"
#include "utilities.h"

extern float clear_color[3];
extern mat4 Projection;

extern bool flagWf;
extern bool flagAncora;
extern bool flagBV;
extern ViewSetup SetupTelecamera;
extern PerspectiveSetup SetupProspettiva;
extern mat4 View, projection;
extern vector<Mesh> Scena;
extern vector<vector<MeshObj>> ScenaObj;
extern Mesh sky;
extern vector<MaterialObj> materials;
extern point_light light, light2;
 
extern unsigned int programId, programId1, programIdr;
 
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void rendering(float currentFrame,Uniform uniform, LightShaderUniform light_unif, LightShaderUniform light_unif2, vector<int>texture,  int cubemapTexture) {
   
    int i, k;
    glClearColor(clear_color[0], clear_color[1], clear_color[2], 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Imposto la matrice di proiezione per la scena da disegnare
    Projection = perspective(radians(SetupProspettiva.fovY), SetupProspettiva.aspect, SetupProspettiva.near_plane, SetupProspettiva.far_plane);

    //Costruisco la matrice di Vista che applicata ai vertici in coordinate del mondo li trasforma nel sistema di riferimento della camera.
    View = lookAt(vec3(SetupTelecamera.position), vec3(SetupTelecamera.target), vec3(SetupTelecamera.upVector));
    
    // GESTIONE CUBEMAP
    glDepthMask(GL_FALSE);
    glUseProgram(programId1);
    glUniform1i(glGetUniformLocation(programId1, "skybox"), 0);
    glUniformMatrix4fv(uniform.MatProjS, 1, GL_FALSE, value_ptr(Projection));
    glUniformMatrix4fv(uniform.MatViewS, 1, GL_FALSE, value_ptr(View));
    glBindVertexArray(sky.VAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawElements(GL_TRIANGLES, sky.indices.size() * sizeof(GLuint), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);


  
    glUseProgram(programId);
    
    //Passo al Vertex Shader il puntatore alla matrice View
    glUniformMatrix4fv(uniform.MatView, 1, GL_FALSE, value_ptr(View));
    //La matrice di proiezione che mappa il volume di vista in coordinate NDC
    glUniformMatrix4fv(uniform.MatProj, 1, GL_FALSE, value_ptr(Projection));
    glUniform1f(uniform.loc_time, currentFrame);

    //flagWf: se true viene fatta la visualizzazione wireframe
    if (flagWf == true)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Ottenere le location per la luce 1
    light_unif.light_position_pointer = glGetUniformLocation(programId, "light.position");
    light_unif.light_color_pointer = glGetUniformLocation(programId, "light.color");
    light_unif.light_power_pointer = glGetUniformLocation(programId, "light.power");

    // Ottenere le location per la luce 2
    light_unif2.light_position_pointer = glGetUniformLocation(programId, "light2.position");
    light_unif2.light_color_pointer = glGetUniformLocation(programId, "light2.color");
    light_unif2.light_power_pointer = glGetUniformLocation(programId, "light2.power");

    // Passo allo shader i parametri della prima luce (light)
    glUniform3f(light_unif.light_position_pointer, light.position.x, light.position.y, light.position.z);
    glUniform3f(light_unif.light_color_pointer, light.color.r, light.color.g, light.color.b);
    glUniform1f(light_unif.light_power_pointer, light.power);

    // Passo allo shader i parametri della seconda luce (light2)
    glUniform3f(light_unif2.light_position_pointer, light2.position.x, light2.position.y, light2.position.z);
    glUniform3f(light_unif2.light_color_pointer, light2.color.r, light2.color.g, light2.color.b);
    glUniform1f(light_unif2.light_power_pointer, light2.power);

    //Passo allo shader il puntatore alla posizione della camera
    glUniform3f(uniform.loc_view_pos, SetupTelecamera.position.x, SetupTelecamera.position.y, SetupTelecamera.position.z);

    for (i = 0; i < Scena.size(); i++) {

        update_ancora(&Scena[i]);
        glUniformMatrix4fv(uniform.MatModel, 1, GL_FALSE, value_ptr(Scena[i].Model));
        glBindVertexArray(Scena[i].VAO);

        glUniform1i(uniform.loc_sceltaShader, Scena[i].sceltaShader);

        glUniform3fv(light_unif.material_ambient, 1, glm::value_ptr(materials[Scena[i].material].ambient));
        glUniform3fv(light_unif.material_diffuse, 1, glm::value_ptr(materials[Scena[i].material].diffuse));
        glUniform3fv(light_unif.material_specular, 1, glm::value_ptr(materials[Scena[i].material].specular));
        glUniform1f(light_unif.material_shininess, materials[Scena[i].material].shininess);
        
      
        if (i == Piano) {
            glUniform1i(uniform.loc_texture1, 0);
            glBindTexture(GL_TEXTURE_2D, texture[strada]);
        }
        else if (i == Drappo) {
            glUniform1i(uniform.loc_texture1, 0);
            glBindTexture(GL_TEXTURE_2D, texture[bandiera_ita]);
        }
        else if (i == Asta) {
            glUniform1i(uniform.loc_texture1, 0);
            glBindTexture(GL_TEXTURE_2D, texture[cemento]);
        }
        else {
            glUniform1i(uniform.loc_texture1, 0);
            glBindTexture(GL_TEXTURE_2D, texture[cemento]);
        }

        
        if (flagAncora) {
            glPointSize(15.0);
            int ind = Scena[i].indices.size() - 1;
            glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, BUFFER_OFFSET(ind * sizeof(GLuint)));
        }

        glDrawElements(GL_TRIANGLES, (Scena[i].indices.size() - 1) * sizeof(GLuint), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    //Rendering della ScenaObj
    for (i = 0; i < ScenaObj.size(); i++) {
        for (int k = 0; k < ScenaObj[i].size(); k++) {

            update_ancora(&ScenaObj[i][k]);

            glUniformMatrix4fv(uniform.MatModel, 1, GL_FALSE, value_ptr(ScenaObj[i][k].Model));
            glUniform1i(uniform.loc_sceltaShader, ScenaObj[i][k].sceltaShader);

            //Passo allo shader il puntatore ai materiali
            glUniform3fv(light_unif.material_ambient, 1, value_ptr(ScenaObj[i][k].materiale.ambient));
            glUniform3fv(light_unif.material_diffuse, 1, value_ptr(ScenaObj[i][k].materiale.diffuse));
            glUniform3fv(light_unif.material_specular, 1, value_ptr(ScenaObj[i][k].materiale.specular));
            glUniform1f(light_unif.material_shininess, ScenaObj[i][k].materiale.shininess);
            
            glBindVertexArray(ScenaObj[i][k].VAO);

            glDrawElements(GL_TRIANGLES, (ScenaObj[i][k].indices.size()) * sizeof(GLuint), GL_UNSIGNED_INT, 0);

            glBindVertexArray(0);
        }
    }
}

