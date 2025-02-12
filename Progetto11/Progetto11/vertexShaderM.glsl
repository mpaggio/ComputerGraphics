#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec4 aColor; // the color variable has attribute position 1
layout(location = 2) in vec3 vertexNormal;  //Attributo normale 2
layout (location =3 ) in vec2 coord_st; // Attributo texture
  
// output a color to the fragment shader
out vec4 ourColor;

//Variabili di tipo uniform, rimane la stessa per ogni vertice della primitiva e viene passata dall'esterno
uniform mat4 Projection;
uniform mat4 Model;
uniform mat4 View;
uniform vec3 ViewPos;
uniform float time;

//Struttura per la gestione di un punto luce
struct PointLight {
	vec3 position;
	vec3 color;
	float power;
};

// Luce numero 1
uniform PointLight light;
// Luce numero 2
uniform PointLight light2;

//Struttura per la gestione di un materiale
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform int sceltaShader;
uniform Material material;

float strenght = 0.1;
 
out vec2 frag_coord;

void main()
{
//Trasformazione dei vertici dalle coordinate nel sistema di riferimento dell'oggetto (apos), al sistema di riferimento del mondo (premoltiplicazione 
// per Model) e successivamente proiettate nel cubo di centro l'origine e lato lungo 2, con x,y,z che variano tra -1 ed 1- (premoltiplicazione 
//per la matrice Projection)
    ourColor = aColor; // set ourColor to the input color we got from the vertex data

    if (sceltaShader==0)
        gl_Position = Projection*View*Model*vec4(aPos, 1.0);
    
    if (sceltaShader == 1 || sceltaShader == 4 || sceltaShader == 3 ) //Interpolative Shading Phong
    {
        gl_Position = Projection * View * Model * vec4(aPos, 1.0);

        //Trasformare le coordinate del vertice da elaborare (aPos) in coordinate di vista
        vec4 eyePosition = View * Model * vec4(aPos, 1.0);

        //Trasformiamo la posizione della luce nelle coordinate di vista
        vec4 eyeLightPos1 = View * vec4(light.position, 1.0);
        vec4 eyeLightPos2 = View * vec4(light2.position, 1.0);

        //trasformare le normali nel vertice in esame nel sistema di coordinate di vista
        vec3 N = normalize(transpose(inverse(mat3(View * Model))) * vertexNormal);

        //Calcoliamo la direzione di vista 
        vec3 V = normalize(ViewPos - eyePosition.xyz);

        //Calcoliamo la direzione della luce L e la direzione riflessione R per ciascuna luce presente
        vec3 L1 = normalize((eyeLightPos1 - eyePosition).xyz);
        vec3 R1 = reflect(-L1, N);
        vec3 L2 = normalize((eyeLightPos2 - eyePosition).xyz);
        vec3 R2 = reflect(-L2, N);

        //Illuminazione data dalla luce 1
        vec3 ambient1 = strenght * light.power * material.ambient;
        float coseno_angolo_theta1 = max(dot(L1, N), 0);
        vec3 diffuse1 = light.power * light.color * coseno_angolo_theta1 * material.diffuse;
        float coseno_angolo_alfa1 = pow(max(dot(V, R1), 0), material.shininess);
        vec3 specular1 = light.power * light.color * coseno_angolo_alfa1 * material.specular;

        //Illuminazione data dalla luce 2
        vec3 ambient2 = strenght * light2.power * material.ambient;
        float coseno_angolo_theta2 = max(dot(L2, N), 0);
        vec3 diffuse2 = light2.power * light2.color * coseno_angolo_theta2 * material.diffuse;
        float coseno_angolo_alfa2 = pow(max(dot(V, R2), 0), material.shininess);
        vec3 specular2 = light2.power * light2.color * coseno_angolo_alfa2 * material.specular;

        // Somma dei contributi di entrambe le luci
        vec3 totalAmbient = ambient1 + ambient2;
        vec3 totalDiffuse = diffuse1 + diffuse2;
        vec3 totalSpecular = specular1 + specular2;

        ourColor = vec4(totalAmbient + totalDiffuse + totalSpecular, 1.0);

        frag_coord = coord_st;
    }

    if (sceltaShader == 2) //Interpolative Shading Blinn-Phong
    {
        gl_Position = Projection * View * Model * vec4(aPos, 1.0);

        //Trasformare le coordinate del vertice da elaborare (aPos) in coordinate di vista
        vec4 eyePosition = View * Model * vec4(aPos, 1.0);

        //Trasformiamo la posizione delle luci nelle coordinate di vista
        vec4 eyeLightPos1 = View * vec4(light.position, 1.0);
        vec4 eyeLightPos2 = View * vec4(light2.position, 1.0);

        //trasformare le normali nel vertice in esame nel sistema di coordinate di vista
        vec3 N = normalize(transpose(inverse(mat3(View * Model))) * vertexNormal);

        //Calcoliamo la direzione di vista
        vec3 V = normalize(ViewPos - eyePosition.xyz);

        //Calcoliamo la direzione della luce L e dell'halfway vector H per ogni luce presente
        vec3 L1 = normalize((eyeLightPos1 - eyePosition).xyz);
        vec3 H1 = normalize(L1+V);
        vec3 L2 = normalize((eyeLightPos2 - eyePosition).xyz);
        vec3 H2 = normalize(L2+V);

        //Contributo della luce numero 1
        vec3 ambient1 = strenght * light.power * material.ambient;
        float coseno_angolo_theta1 = max(dot(L1, N), 0);
        vec3 diffuse1 = light.power * light.color * coseno_angolo_theta1 * material.diffuse;
        float coseno_angolo_beta1 = pow(max(dot(H1, N), 0), material.shininess);
        vec3 specular1 = light.power * light.color * coseno_angolo_beta1 * material.specular;

        //Contributo della luce numero 2
        vec3 ambient2 = strenght * light2.power * material.ambient;
        float coseno_angolo_theta2 = max(dot(L2, N), 0);
        vec3 diffuse2 = light2.power * light2.color * coseno_angolo_theta2 * material.diffuse;
        float coseno_angolo_beta2 = pow(max(dot(H2, N), 0), material.shininess);
        vec3 specular2 = light2.power * light2.color * coseno_angolo_beta2 * material.specular;

        // Somma dei contributi di entrambe le luci
        vec3 totalAmbient = ambient1 + ambient2;
        vec3 totalDiffuse = diffuse1 + diffuse2;
        vec3 totalSpecular = specular1 + specular2;

        ourColor = vec4(totalAmbient + totalDiffuse + totalSpecular, 1.0);
        frag_coord = coord_st;
    }
    
    // SLIDING FLOOR
    if (sceltaShader == 5){
        vec4 v = vec4(aPos, 1);
        // Originariamentoe ---> v.y = (sin(80.0*v.x + time) * cos(8.5 * v.y + time) * 0.1);
        gl_Position = Projection * View * Model * v;
        frag_coord = coord_st;
        frag_coord.y -= time*0.1;
    }
    
    // BANDIERA
    if (sceltaShader == 6){
        vec4 v = vec4(aPos, 1);
        float offset = 0.3 * sin(0.5 * time + 5.0 * v.x);
        v.z = v.z + offset;
        gl_Position = Projection * View * Model * v;
        frag_coord = coord_st;
    }

}  

