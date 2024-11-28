#pragma once

#include "lib.h"
#include "strutture.h"


extern int selected_obj;
extern vector<Mesh> Scena;

void modifyModelMatrix(vec3 translation_vector, vec3 rotation_vector, GLfloat angle, GLfloat scale_factor)
{
	//ricordare che mat4(1) costruisce una matrice identità di ordine 4
	vec3 traslModel;
	mat4 aa;
	aa= Scena[selected_obj].Model;
	
	// Estrazione della traslazione corrente :
	//Viene estratta la componente di traslazione dalla matrice di modellazione corrente dell'oggetto selezionato (l'ultima colonna della matrice di
	// Modellazione dell'oggetto selezionato.
	// Questa informazione è necessaria per centrare l'oggetto prima di applicare le trasformazioni di scala e rotazione.

	traslModel = glm::vec3(aa[3][0], aa[3][1], aa[3][2]);
	
	//Traslazione: Viene creata una matrice di traslazione che sposta l'oggetto in base al vettore di traslazione fornito.

	mat4 traslation = glm::translate(glm::mat4(1), translation_vector);

	

	//Per scalare intorno al centro dell'oggetto, lo traslo nell'origine, lo scalo e poi lo riposizono nella sua posizione memorizzata
	//in traslModel
	//Viene creata una matrice di traslazione temporanea per spostare l'oggetto nell'origine.
	// Viene applicata la scala all'oggetto nell'origine.
	// Viene creata una matrice di traslazione inversa per riportare l'oggetto nella sua posizione originale.

	mat4 scala= glm::translate(glm::mat4(1), traslModel);
	scala =scale(scala, glm::vec3(scale_factor, scale_factor, scale_factor));
	scala = translate(scala, -traslModel);


	//Per ruotare intorno al centro dell'oggetto, lo traslo nell'origine, ruoto e poi lo riposizono nella sua posizione memorizzata
	//in traslModel

	//Analogamente alla scala, viene creata una matrice di traslazione temporanea per centrare l'oggetto, 
	// una matrice di rotazione e infine una matrice di traslazione inversa per riportare l'oggetto nella sua posizione originale.
	
	mat4 rotation= glm::translate(glm::mat4(1), traslModel);
	rotation = glm::rotate(rotation, angle, rotation_vector);
	rotation = glm::translate(rotation, -traslModel);
	 

	//Le matrici di traslazione, rotazione e scala vengono moltiplicate nell'ordine corretto (traslazione, rotazione, scala) 
	// e premoltiplicate alla matrice di modellazione corrente dell'oggetto selezionato.
	// Questo aggiorna la matrice di modellazione dell'oggetto selezionato  con le nuove trasformazioni.
	if (selected_obj < 0) return;
	   Scena[selected_obj].Model = traslation*rotation * scala*Scena[selected_obj].Model;

}

void update_ancora(Mesh* mesh )
{
	mesh->ancora_world = mesh->ancora_obj;
	mesh->ancora_world = mesh->Model * mesh->ancora_world;

}

void clear_objModel(vector<MeshObj> * Model3D){
	int i;
	for (i = 0; i < Model3D->size(); i++)
{
	Model3D->at(i).vertices.clear();
	Model3D->at(i).colors.clear();
	Model3D->at(i).normals.clear();
	Model3D->at(i).indices.clear();
}
}
