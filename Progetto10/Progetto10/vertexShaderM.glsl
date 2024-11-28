#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec4 aColor; // the color variable has attribute position 1
layout(location = 2) in vec3 vertexNormal;  //Attributo normale 2

  
out vec4 ourColor; // output a color to the fragment shader
uniform mat4 Projection;  //vARIABILE DI TIPO uniform, rimane la stessa per ogni vertice della primitiva e viene passata dall'esterno
uniform mat4 Model;
uniform mat4 View;
uniform vec3 ViewPos;
//Struttura per la gestione di un punto luce
struct PointLight {
	vec3 position;
	vec3 color;
	float power;
};
//definizione di una variabile uniform che ha la struttura PointLight
uniform PointLight light;

//Struttura per la gestione di un materiale

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform int sceltaShader;

//Variabile uniorme
uniform Material material;

float strenght = 0.1;

void main()
{
//Trasformazione dei vertici dalle coordinate nel sistema di riferimento dell'oggetto (apos), al sistema di riferimento del mondo (premoltiplicazione 
// per Model) e successivamente proiettate nel cubo di centro l'origine e lato lungo 2, con x,y,z che variano tra -1 ed 1- (premoltiplicazione 
//per la matrice Projection)
    ourColor = aColor; // set ourColor to the input color we got from the vertex data
    
    if (sceltaShader==0)
        gl_Position = Projection*View*Model*vec4(aPos, 1.0);
    
    if (sceltaShader==1) {   // Interpola shading
        gl_Position = Projection*View*Model*vec4(aPos, 1.0);
        
        // Trasformare le coordinate del vertice da elaborare (aPos) in coordinate di vista
        vec4 eyePosition = View * Model * vec4(aPos, 1.0);

        // Trasformare la posizione della luce nel sistema di coordinate di vista
        vec4 eyeLightPos = View * vec4(light.position, 1.0);
    
        // Trasformare le normali nel vertice in esame, nel sistema di riferimento di vista
        vec3 N = normalize(transpose(inverse(mat3(View * Model))) * vertexNormal);

        vec3 V = normalize(ViewPos - eyePosition.xyz);
        vec3 L = normalize((eyeLightPos - eyePosition).xyz);
    
        // Costruire la direzione riflessa di L rispetto alla normale N
        vec3 R = normalize(reflect(-L, N));

        // Componente ambientale:
        vec3 ambiente = strenght * light.power * material.ambient;

        // Componente diffusa:
        float cos_theta = max(dot(L, N), 0);
        vec3 diffuse = light.power * light.color * cos_theta * material.diffuse;

        // Componente speculare:
        float cos_alpha = pow(max(dot(V, R), 0), material.shininess);
        vec3 specular = light.power * light.color * cos_alpha * material.specular;

        ourColor = vec4(ambiente + diffuse + specular, 1.0);

    }
  
}  

