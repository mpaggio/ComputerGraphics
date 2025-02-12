#pragma once
#include "lib.h"
#include "strutture.h"
void modifyModelMatrix(vec3 translation_vector, vec3 rotation_vector, GLfloat angle, GLfloat scale_factor);
void update_ancora(Mesh* mesh);
void normalizeModel(std::vector<MeshObj>& Model3D);
void clear_objModel(vector<MeshObj>* Model3D);
void getUniform();
void findBV(Mesh* fig);
void updateBB(Mesh* mesh);
void updateBB2(Mesh* mesh);
bool checkCollision(vec3 cameraPosition, Mesh* mesh);
