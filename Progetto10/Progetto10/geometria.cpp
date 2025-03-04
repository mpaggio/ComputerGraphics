#include "Strutture.h"
#include "Lib.h"
#include "inizializzazioni.h"


void crea_cubo(Mesh* mesh)
{

	mesh->vertices.push_back(vec3(-1.0, -1.0, 1.0));
	mesh->colors.push_back(vec4(1.0, 0.0, 0.0, 0.5));
	mesh->vertices.push_back(vec3(1.0, -1.0, 1.0));
	mesh->colors.push_back(vec4(0.0, 1.0, 0.0, 0.5));
	mesh->vertices.push_back(vec3(1.0, 1.0, 1.0));
	mesh->colors.push_back(vec4(0.0, 0.0, 1.0, 0.5));
	mesh->vertices.push_back(vec3(-1.0, 1.0, 1.0));
	mesh->colors.push_back(vec4(1.0, 0.0, 1.0, 0.5));
	// back
	mesh->vertices.push_back(vec3(-1.0, -1.0, -1.0));
	mesh->colors.push_back(vec4(1.0, 1.0, 1.0, 0.5));
	mesh->vertices.push_back(vec3(1.0, -1.0, -1.0));
	mesh->colors.push_back(vec4(1.0, 1.0, 1.0, 0.5));
	mesh->vertices.push_back(vec3(1.0, 1.0, -1.0));
	mesh->colors.push_back(vec4(1.0, 1.0, 1.0, 0.5));
	mesh->vertices.push_back(vec3(-1.0, 1.0, -1.0));
	mesh->colors.push_back(vec4(1.0, 1.0, 1.0, 0.5));

	
	
	mesh->vertices.push_back(vec3(0.0, 0.0, 0.0));
	mesh->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));
	mesh->ancora_obj = (vec4(0.0, 0.0, 0.0, 1.0));

	mesh->indices.push_back(0); mesh->indices.push_back(1); mesh->indices.push_back(2);
	mesh->indices.push_back(2); mesh->indices.push_back(3); mesh->indices.push_back(0);
	mesh->indices.push_back(1); mesh->indices.push_back(5); mesh->indices.push_back(6);
	mesh->indices.push_back(6); mesh->indices.push_back(2); mesh->indices.push_back(1);
	mesh->indices.push_back(7); mesh->indices.push_back(6); mesh->indices.push_back(5);
	mesh->indices.push_back(5); mesh->indices.push_back(4); mesh->indices.push_back(7);
	mesh->indices.push_back(4); mesh->indices.push_back(0); mesh->indices.push_back(3);
	mesh->indices.push_back(3); mesh->indices.push_back(7); mesh->indices.push_back(4);
	mesh->indices.push_back(4); mesh->indices.push_back(5); mesh->indices.push_back(1);
	mesh->indices.push_back(1); mesh->indices.push_back(0); mesh->indices.push_back(4);
	mesh->indices.push_back(3); mesh->indices.push_back(2); mesh->indices.push_back(6);
	mesh->indices.push_back(6); mesh->indices.push_back(7); mesh->indices.push_back(3);

	mesh->normals.push_back(normalize(vec3(0, 0, 1)));
	mesh->normals.push_back(normalize(vec3(0, 0, 1)));
	mesh->normals.push_back(normalize(vec3(0, 0, 1)));
	mesh->normals.push_back(normalize(vec3(0, 0, 1)));
	mesh->normals.push_back(normalize(vec3(0, 0, -1)));
	mesh->normals.push_back(normalize(vec3(0, 0, -1)));
	mesh->normals.push_back(normalize(vec3(0, 0, -1)));
	mesh->normals.push_back(normalize(vec3(0, 0, -1)));
	int nv = mesh->vertices.size();
 
	mesh->indices.push_back(nv-1);


}
void crea_piramide(Mesh* mesh)
{
	mesh->vertices.push_back(vec3(-1.0, 0.0, 1.0));
	mesh->colors.push_back(vec4(1.0, 0.0, 0.0, 0.5));
	mesh->vertices.push_back(vec3(1.0, 0.0,  1.0));
	mesh->colors.push_back(vec4(0.0, 1.0, 0.0, 0.5));
	mesh->vertices.push_back(vec3(1.0, 0.0, -1.0));
	mesh->colors.push_back(vec4(0.0, 0.0, 1.0, 0.5));
	mesh->vertices.push_back(vec3(-1.0,  0.0,  -1.0));
	mesh->colors.push_back(vec4(1.0, 1.0, 0.0, 0.5));
	// Apice piramide
	mesh->vertices.push_back(vec3(0.0,1.0,0.0));
	mesh->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));


	

	mesh->indices.push_back(0); mesh->indices.push_back(1); mesh->indices.push_back(2);
	mesh->indices.push_back(0); mesh->indices.push_back(2); mesh->indices.push_back(3);

	mesh->indices.push_back(0); mesh->indices.push_back(4); mesh->indices.push_back(3);
	mesh->indices.push_back(0); mesh->indices.push_back(1); mesh->indices.push_back(4);

	mesh->indices.push_back(3); mesh->indices.push_back(2); mesh->indices.push_back(4);
	mesh->indices.push_back(1); mesh->indices.push_back(2); mesh->indices.push_back(4);

	mesh->vertices.push_back(vec3(0.0,0.3, 0.0));
	mesh->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));
	mesh->ancora_obj = (vec4(0.0, 0.3, 0.0, 1.0));


	for (int i = 0; i < mesh->vertices.size(); i++)
		mesh->normals.push_back(vec3(0.0));

	int nv = mesh->vertices.size();
	mesh->indices.push_back(nv-1);

}
void crea_piano(Mesh* mesh, vec4 colore)
{

	mesh->vertices.push_back(vec3(-0.5, 0.0, 0.5));
	mesh->colors.push_back(colore);
	mesh->vertices.push_back(vec3(0.5, 0.0, 0.5));
	mesh->colors.push_back(colore);
	mesh->vertices.push_back(vec3(0.5, 0.0, -0.5));
	mesh->colors.push_back(colore);
	mesh->vertices.push_back(vec3(-0.5, 0.0, -0.5));
	mesh->colors.push_back(colore);

	mesh->indices.push_back(0); mesh->indices.push_back(1); mesh->indices.push_back(2);
	mesh->indices.push_back(0); mesh->indices.push_back(2); mesh->indices.push_back(3);

	mesh->normals.push_back(vec3(0.0, 1.0, 0.0));
	mesh->normals.push_back(vec3(0.0, 1.0, 0.0));
	mesh->normals.push_back(vec3(0.0, 1.0, 0.0));
	mesh->normals.push_back(vec3(0.0, 1.0, 0.0));

	mesh->vertices.push_back(vec3(0.0, 0.0, 0.0));  //Memorizzo come ultimo vertice l'ancora per poterla visualizzare
	mesh->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
	mesh->ancora_obj = (vec4(0.0, 0.0, 0.0, 1.0));  //memorizzo l'ancora nel campo ancora_obj
	 
	int nv = mesh->vertices.size();
	mesh->indices.push_back(nv-1);
}

void crea_piano_suddiviso(Mesh* mesh, vec4 colore)
{

	int N = 32;

	int i, j;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			mesh->vertices.push_back(vec3(-0.5+(float)i / N, 0.0, -0.5+(float)j / N));
			mesh->colors.push_back(colore);
			mesh->normals.push_back(vec3(0.0, 1.0, 0.0));
		}
	}
	int cont = -1;


	

	for (i = 0; i <= pow(N, 2) - (N + 1); i++) {

		j = i % (N);

		if (j != N - 1)
		{
			mesh->indices.push_back(i);
			mesh->indices.push_back(i + 1);
			mesh->indices.push_back(i + N );

			mesh->indices.push_back(i + N + 1);
			mesh->indices.push_back(i+1);
			mesh->indices.push_back(i + N);
		}
		

	}
 

	
	mesh->vertices.push_back(vec3(0.0, 0.0, 0.0));
	mesh->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));
	mesh->ancora_obj = (vec4(0.0, 0.0, 0.0, 1.0));
	mesh->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));
	int nv = mesh->vertices.size();
	mesh->indices.push_back(nv-1);

 

}

void crea_sfera(Mesh* mesh, vec4 colore)
{
	vec3 centro = vec3(0.0, 0.0, 0.0);
	vec3 raggio = vec3(1.0, 1.0, 1.0);

	int Stacks = 30;  //numero di suddivisioni sull'asse y
	int Slices = 30;  // numero di suddivisioni sull'asse x

	//Calc The Vertices

	//Stacks= suddivisioni lungo l'asse y
	for (int i = 0; i <= Stacks; ++i) {

		float V = i / (float)Stacks;
		float phi = V * pi <float>();

		// Loop Through Slices suddivisioni lungo l'asse x
		for (int j = 0; j <= Slices; ++j) {

			float U = j / (float)Slices;
			float theta = U * (pi <float>() * 2);

			// Calc The Vertex Positions
			float x = centro.x + raggio.x * (cosf(theta) * sinf(phi));
			float y = centro.y + raggio.y * cosf(phi);
			float z = centro.z + raggio.z * sinf(theta) * sinf(phi);

			mesh->vertices.push_back(vec3(x, y, z)),
			mesh->colors.push_back(colore);

			//Normale nel vertice
			mesh->normals.push_back(vec3(x, y, z));

		}
	}

	// Calc The Index Positions
	for (int i = 0; i < Slices * Stacks + Slices; ++i) {

		mesh->indices.push_back(i);
		mesh->indices.push_back(i + Slices + 1);
		mesh->indices.push_back(i + Slices);


		mesh->indices.push_back(i + Slices + 1);
		mesh->indices.push_back(i);
		mesh->indices.push_back(i + 1);
	}

	mesh->vertices.push_back(vec3(0.0, 0.0, 0.0));
	mesh->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));

	mesh->ancora_obj = (vec4(0.0, 0.0, 0.0, 1.0));

	int nv = mesh->vertices.size();
	mesh->indices.push_back(nv-1);


}

void crea_toro(Mesh* mesh, vec4 colore)
{
	int Stacks = 30;  //numero di suddivisioni sull'asse x
	int Slices = 30;  // numero di suddivisioni sull'asse y
	float R = 1, r = 0.5;
	float s, t;


	//Calc The Vertices
	for (int i = 0; i <= Stacks; ++i) {

		float V = i / (float)Stacks;
		float phi = V * glm::pi <float>() * 2;

		// Loop Through Slices
		for (int j = 0; j <= Slices; ++j) {

			float U = j / (float)Slices;
			float theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			float x = (R + r * cosf(phi)) * cosf(theta);
			float y = r * sinf(phi);
			float z = (R + r * cosf(phi)) * sinf(theta);


			// Push Back Vertex Data
			mesh->vertices.push_back(vec3(x, y, z));
			mesh->colors.push_back(colore);
			//Normale nel vertice
			mesh->normals.push_back(vec3(normalize(vec3(sin(phi) * cos(theta), cos(phi), sin(theta) * sin(phi)))));


		}
	}

	// Calc The Index Positions
	for (int i = 0; i < Slices * Stacks + Slices; ++i) {

		mesh->indices.push_back(i);
		mesh->indices.push_back(i + Slices + 1);
		mesh->indices.push_back(i + Slices);


		mesh->indices.push_back(i + Slices + 1);
		mesh->indices.push_back(i);
		mesh->indices.push_back(i + 1);
	}
	mesh->vertices.push_back(vec3(0.0, 0.0, 0.0));
	mesh->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));

	mesh->ancora_obj = (vec4(0.0, 0.0, 0.0, 1.0));

	int nv = mesh->vertices.size();
	mesh->indices.push_back(nv - 1);

}

void crea_cono(Mesh* mesh, vec4 colore)
{
	int Stacks = 30;  //numero di suddivisioni sull'asse x
	int Slices = 30;  // numero di suddivisioni sull'asse y
	float s, t;


	//Calc The Vertices
	for (int i = 0; i <= Stacks; ++i) {

		float V = i / (float)Stacks;
		float h = V;

		// Loop Through Slices
		for (int j = 0; j <= Slices; ++j) {

			float U = j / (float)Slices;
			float theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			float x = h * cosf(theta);
			float y = h;
			float z = h * sinf(theta);


			// Push Back Vertex Data
			mesh->vertices.push_back(vec3(x, y, z));
			mesh->colors.push_back(colore);
			//Normale nel vertice
			mesh->normals.push_back(normalize(vec3(cos(theta) / sqrt(2.0f), -1 / sqrt(2.0f), sin(theta) / sqrt(2.0f))));

		}
	}

	// Calc The Index Positions
	for (int i = 0; i < Slices * Stacks + Slices; ++i) {

		mesh->indices.push_back(i);
		mesh->indices.push_back(i + Slices + 1);
		mesh->indices.push_back(i + Slices);


		mesh->indices.push_back(i + Slices + 1);
		mesh->indices.push_back(i);
		mesh->indices.push_back(i + 1);
	}

	mesh->ancora_obj = (vec4(0.0, 0.0, 0.0, 1.0));

}
void crea_cilindro(Mesh* mesh, vec4 colore)
{
	int Stacks = 30;  //numero di suddivisioni sull'asse x
	int Slices = 30;  // numero di suddivisioni sull'asse y

	float s, t;
	//Calc The Vertices
	for (int i = 0; i <= Stacks; ++i) {

		float V = i / (float)Stacks;
		float h = V;

		// Loop Through Slices
		for (int j = 0; j <= Slices; ++j) {

			float U = j / (float)Slices;
			float theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			float x = cosf(theta);
			float y = h;
			float z = sinf(theta);


			// Push Back Vertex Data
			mesh->vertices.push_back(vec3(x, y, z));
			mesh->colors.push_back(colore);
			mesh->normals.push_back(vec3(normalize(vec3(cos(theta), 0, sin(theta)))));
		}
	}

	// Calc The Index Positions
	for (int i = 0; i < Slices * Stacks + Slices; ++i) {

		mesh->indices.push_back(i);
		mesh->indices.push_back(i + Slices + 1);
		mesh->indices.push_back(i + Slices);


		mesh->indices.push_back(i + Slices + 1);
		mesh->indices.push_back(i);
		mesh->indices.push_back(i + 1);
	}

	mesh->ancora_obj = (vec4(0.0, 0.0, 0.0, 1.0));

}


