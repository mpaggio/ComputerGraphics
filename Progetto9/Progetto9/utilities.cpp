#pragma once

#include "lib.h"
#include "strutture.h"


extern int selected_obj;
extern vector<Mesh> Scena;

void modifyModelMatrix(vec3 translation_vector, vec3 rotation_vector, GLfloat angle, GLfloat scale_factor)
{
	//ricordare che mat4(1) costruisce una matrice identità di ordine 4
	mat4 traslation = glm::translate(glm::mat4(1), translation_vector);
	mat4 scale = glm::scale(glm::mat4(1), glm::vec3(scale_factor, scale_factor, scale_factor));
	mat4 rotation = glm::rotate(glm::mat4(1), angle, rotation_vector);

	//Modifica la matrice di Modellazione dell'oggetto della scena selezionato postmolitplicando per le matrici scale*rotarion*traslation

	if (selected_obj < 0) return;

 

}

void update_ancora(Mesh* mesh )
{

	 

}