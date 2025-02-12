#pragma once

#include "lib.h"
#include "strutture.h"
extern unsigned int programId, programId1, programIdr;

extern int selected_obj;
extern vector<Mesh> Scena;
extern Uniform uniform;
extern LightShaderUniform light_unif;



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
	Model3D->at(i).texCoords.clear();
}
}

void getUniform() {

	uniform.MatProj = glGetUniformLocation(programId, "Projection");
	uniform.MatModel = glGetUniformLocation(programId, "Model");
	uniform.MatView = glGetUniformLocation(programId, "View");
	uniform.loc_time= glGetUniformLocation(programId, "time");
	uniform.loc_sceltaShader = glGetUniformLocation(programId, "sceltaShader");
	uniform.loc_view_pos = glGetUniformLocation(programId, "ViewPos");
	uniform.loc_texture1 = glGetUniformLocation(programId, "id_tex1");
	uniform.loc_texture2 = glGetUniformLocation(programId, "id_tex2");
	//location delle variabili uniformi per la gestione della luce
	light_unif.light_position_pointer = glGetUniformLocation(programId, "light.position");
	light_unif.light_color_pointer = glGetUniformLocation(programId, "light.color");
	light_unif.light_power_pointer = glGetUniformLocation(programId, "light.power");

	//location delle variabili uniformi per la gestione dei materiali
	light_unif.material_ambient = glGetUniformLocation(programId, "material.ambient");
	light_unif.material_diffuse = glGetUniformLocation(programId, "material.diffuse");
	light_unif.material_specular = glGetUniformLocation(programId, "material.specular");
	light_unif.material_shininess = glGetUniformLocation(programId, "material.shininess");

	//location delle variabili uniform per lo skybox
	uniform.MatProjS = glGetUniformLocation(programId1, "Projection");
	uniform.MatViewS = glGetUniformLocation(programId1, "View");
	uniform.loc_skybox = glGetUniformLocation(programId1, "skybox");
	
	uniform.MatModelR = glGetUniformLocation(programIdr, "Model");
	uniform.MatViewR = glGetUniformLocation(programIdr, "View");
	uniform.MatProjR = glGetUniformLocation(programIdr, "Projection");
	uniform.loc_view_posR = glGetUniformLocation(programIdr, "ViewPos");
	uniform.loc_cubemapR = glGetUniformLocation(programIdr, "cubemap");
}


void findBV(Mesh* fig) {
	int n = fig->vertices.size();

	float minx = fig->vertices[0].x;
	float miny = fig->vertices[0].y;
	float minz = fig->vertices[0].z;

	float maxx = fig->vertices[0].x;
	float maxy = fig->vertices[0].y;
	float maxz = fig->vertices[0].z;

	for (int i = 1; i < n; i++) {
		if (fig->vertices[i].x < minx) {
			minx = fig->vertices[i].x;
		}
		if (fig->vertices[i].x > maxx) {
			maxx = fig->vertices[i].x;
		}

		if (fig->vertices[i].y < miny) {
			miny = fig->vertices[i].y;
		}

		if (fig->vertices[i].y > maxy) {
			maxy = fig->vertices[i].y;
		}

		if (fig->vertices[i].z < minz) {
			minz = fig->vertices[i].z;
		}

		if (fig->vertices[i].z > maxz) {
			maxz = fig->vertices[i].z;
		}
	}

	fig->min_BB_obj = vec3(minx, miny, minz);
	fig->max_BB_obj = vec3(maxx, maxy, maxz);
}


void updateBB(Mesh* mesh) {
	mesh->minBB = vec4(mesh->min_BB_obj, 1.0);
	mesh->maxBB = vec4(mesh->max_BB_obj, 1.0);
	mesh->minBB = mesh->Model * mesh->minBB;
	mesh->maxBB = mesh->Model * mesh->maxBB;
}

void updateBB2(Mesh* mesh) {
	// Calcolare la Bounding Box trasformata usando la matrice Model

	// Applica la matrice Model ai vertici per aggiornare minBB e maxBB
	vec4 transformed_min = mesh->Model * vec4(mesh->min_BB_obj, 1.0);
	vec4 transformed_max = mesh->Model * vec4(mesh->max_BB_obj, 1.0);

	// Aggiorna la Bounding Box trasformata
	mesh->minBB = transformed_min;
	mesh->maxBB = transformed_max;

	// Per ogni vertice della mesh, dobbiamo trovare i minimi e massimi estremi
	// Risulta più efficace ripetere il calcolo dell'BB trasformato basandoci su tutti i vertici
	for (size_t i = 0; i < mesh->vertices.size(); ++i) {
		// Trasformiamo il vertice e aggiorniamo la BB
		vec4 transformed_vertex = mesh->Model * vec4(mesh->vertices[i], 1.0);

		// Aggiorna i limiti della Bounding Box
		mesh->minBB.x = std::min(mesh->minBB.x, transformed_vertex.x);
		mesh->minBB.y = std::min(mesh->minBB.y, transformed_vertex.y);
		mesh->minBB.z = std::min(mesh->minBB.z, transformed_vertex.z);

		mesh->maxBB.x = std::max(mesh->maxBB.x, transformed_vertex.x);
		mesh->maxBB.y = std::max(mesh->maxBB.y, transformed_vertex.y);
		mesh->maxBB.z = std::max(mesh->maxBB.z, transformed_vertex.z);
	}
}

bool checkCollision(vec3 cameraPosition, Mesh* mesh) {
	bool collisionX = cameraPosition.x >= mesh->minBB.x - 5.0f && cameraPosition.x <= mesh->maxBB.x + 5.0f;
	bool collisionY = cameraPosition.y >= mesh->minBB.y - 5.0f && cameraPosition.y <= mesh->maxBB.y + 5.0f;
	bool collisionZ = cameraPosition.z >= mesh->minBB.z - 5.0f && cameraPosition.z <= mesh->maxBB.z + 5.0f;
	return collisionX && collisionY && collisionZ;
}