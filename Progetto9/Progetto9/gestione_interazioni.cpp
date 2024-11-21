#pragma once
#include "lib.h"
#include "strutture.h"
#include "gestione_interazioni.h"
#include "gestione_telecamera.h"
#include "ImGui/imgui.h"
#include "enum.h"
#include "utilities.h"
extern GLFWwindow* window;
extern mat4 Projection;
extern int height, width;
extern PerspectiveSetup SetupProspettiva;
extern ViewSetup SetupTelecamera;
extern mat4 View;
extern float w_up, h_up;
extern bool flagAncora;
 
string stringa_asse, Operazione;

int last_mouse_pos_X, last_mouse_pos_Y;
float Theta=-89.0;
float Phi=0.0;
bool moving_trackball = false;
bool isNavigationMode = false;
 
extern int selected_obj;
extern vector<Mesh> Scena;
float raggio_sfera = 1.0;
float amount = .05;
vec3 asse;

void cursor_position_callback(GLFWwindow* window, double xposIn, double yposIn) {
    

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    float xoffset, yoffset;
    float alfa = 0.05; //serve ridimensionare l'offset tra due posizioni successive del mosue
    ypos = height - ypos;

    float center_x = width / 2.0f;
    float center_y = height / 2.0f;

     
     xoffset = xpos - center_x;
     yoffset = ypos - center_y;
    
    if (isNavigationMode&&!moving_trackball)
    {
        //Aggiorna gli angoli di rotazione orizzontale(Theta) e verticale(Phi) in base agli offset calcolati.
        // L'angolo Theta controlla la rotazione attorno all'asse y, mentre Phi controlla la rotazione attorno all'asse x.
        // To DO
        Theta += xoffset;
        Phi += yoffset;

        // Facciamo si' che l'angolo di Phi vari tra -89 e 89, evitando così di capovolgere la telecamera.
        // To DO
        if (Phi > 89.0f) {
            Phi = 89.0f;
        }
        if (Phi < -89.0f) {
            Phi = -89.0f;
        }
            
        //Calcola le coordinate x, y e z di un punto sulla sfera unitaria,  utilizzando gli angoli Theta e Phi convertiti in radianti.
        // Questo punto rappresenta la direzione in cui punta la telecamera.
        //To DO 
        vec3 front;
        front.x = cos(radians(Theta)) * cos(radians(Phi));
        front.y = sin(radians(Phi));
        front.z = sin(radians(Theta)) * cos(radians(Phi));


        //Normalizza la direzione per ottenere un vettore unitario che rappresenta la nuova direzione della telecamera.
        //To DO
        SetupTelecamera.direction = normalize(front);
        SetupTelecamera.target = SetupTelecamera.position + SetupTelecamera.direction;    //aggiorno il punto in cui guarda la telecamera
            
        //Disabilita il cursore del mouse per evitare che si muova fuori dalla finestra durante la navigazione.
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        
        //Riposiziona il cursore al centro della finestra per mantenere una navigazione fluida.
        glfwSetCursorPos(window, (int)center_x, (int)center_y);
            

    }
    if (moving_trackball==true && !isNavigationMode)
       {
        
        float velocity = 10.0;

        // Recupera la posizione sul trackball del mouse attuale e la posizione precedente

        vec3 destination = getTrackBallPoint(xpos, ypos);
        vec3 origin = getTrackBallPoint(last_mouse_pos_X, last_mouse_pos_Y);
        float dx, dy, dz;

        //Calcola lo spostamento del mouse dx,dy,dz

         // Calcola l'angolo di rotazione (approssimato)
             

            // Calcola l'asse di rotazione
           

            // Recupera il vettore direzione della telecamera
            

            // Ruota il vettore direzione 
            

            // Aggiorna la posizione della telecamera
            

            // Aggiorna la posizione del mouse precedente
        last_mouse_pos_X = xpos;
        last_mouse_pos_Y = ypos;
        }
 
        last_mouse_pos_X = xpos; last_mouse_pos_Y = ypos;

     

    }


vec3 get_ray_from_mouse(float mouse_x, float mouse_y) {

    vec3 ray_wor = vec3(0.0f,0.0f,0.0f);

    //mouse_y = height - mouse_y;

    //1. Normalizzazione delle coordinate del mouse :

    //Le coordinate del mouse, che sono in pixel, vengono convertite in coordinate normalizzate che vanno da - 1 a 1. Questo permette di lavorare con un sistema di coordinate standard indipendentemente dalla risoluzione dello schermo.
    
    // 2. Creazione di un punto nello spazio di clipping :

    //Viene creato un punto nello spazio di clipping, che è il sistema di coordinate utilizzato dalla pipeline grafica per la proiezione.In questo spazio, il piano vicino ha un valore z di - 1.
    
    
    //3. Trasformazione nello spazio della vista :

    //Il punto nello spazio di clipping viene moltiplicato per l'inversa della matrice di proiezione per ottenere le coordinate nello spazio della vista. Questo spazio è centrato sulla telecamera e rappresenta il mondo visto dagli occhi della telecamera.
      
    //4. Trasformazione nello spazio del mondo :

    //Il punto nello spazio della vista viene moltiplicato per l'inversa della matrice di vista per ottenere le coordinate nello spazio del mondo. Questo è il sistema di coordinate globale della scena.
      
    //5. Calcolo della direzione del raggio :

    //La direzione del raggio viene calcolata sottraendo la posizione della telecamera dal punto nello spazio del mondo.Il vettore risultante viene normalizzato per ottenere un vettore unitario.

     return ray_wor;  //vettore contenente la direzione del raggio in coordinate del mondo
}

/*controlla se un raggio interseca una sfera. In caso negativo, restituisce false. Rigetta
le intersezioni dietro l'origine del raggio, e pone  intersection_distance all'intersezione p iù vicina.
*/

bool ray_sphere(vec3 O, vec3 d, vec3 sphere_centre_wor, float sphere_radius, float* intersection_distance) {

    //Funzione che serve a determinare se un raggio(definito da un punto di origine O (posizione della telecamera) e una direzione d intersechi una sfera.
    // In caso affermativo, viene calcolata la distanza dall'origine del raggio al punto di intersezione più vicino.
    
    //Calcoliamo O-C
    vec3 dist_sfera = O - sphere_centre_wor;
    float b = dot(dist_sfera, d);
    float cc = dot(dist_sfera, dist_sfera) - sphere_radius * sphere_radius;

    float delta = b * b - cc;

    if (delta < 0)  //Il raggio non interseca la sfera
        return false;
    //Calcolo i valori di t per cui il raggio interseca la sfera e restituisco il valore dell'intersezione 
    //più vicina all'osservatore (la t più piccola)
    if (delta > 0.0f) {
        //calcola le due intersezioni
        float t_a = -b + sqrt(delta);
        float t_b = -b - sqrt(delta);
        *intersection_distance = t_b;

        //Caso di intersezioni dietro l'osservatore
        if (t_a < 0.0) {
            if (t_b < 0)
                return false;
        }

        return true;
    }
    //Caso in cui il raggio è tangente alla sfera: un interesezione con molteplicità doppia.
    if (delta == 0) {
        float t = -b + sqrt(delta);
        if (t < 0)
            return false;
        *intersection_distance = t;
        return true;
    }

    return false;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    switch (button) {

    case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS)
            moving_trackball = true;
        else
            moving_trackball = false;

        glfwGetCursorPos(window, &xpos, &ypos);


        last_mouse_pos_X = (int)xpos;
        last_mouse_pos_Y = (int)ypos;
        cout << "Last pos x " << last_mouse_pos_X << endl;
        cout << "Last pos y " << last_mouse_pos_Y << endl;
        break;


    case GLFW_MOUSE_BUTTON_MIDDLE:

        //Con il tasto centrale premuto si selezionano gli oggetti nella scena
        if (action == GLFW_PRESS)
        {
             
            glfwGetCursorPos(window, &xpos, &ypos);
            float xmouse = xpos;
            float ymouse = ypos;
     //Per selezionare oggetto
           
            //1) A partire dalla posizione del mouse, si calcola un raggio che parte dalla telecamera e passa attraverso il punto sullo schermo corrispondente al clic del mouse.
              //usando la funzione  get_ray_from_mouse(float mouse_x, float mouse_y)
              // 
            //2) Iterazione sugli oggetti della scena :
            /*
            Per ogni oggetto nella scena :
            Si verifica se il raggio interseca la sfera circoscritta all'oggetto (bounding sphere), usando la funzione
            ray_sphere(vec3 O, vec3 d, vec3 sphere_centre_wor, float sphere_radius, float* intersection_distance)
                Se c'è un'intersezione, si verifica se è l'intersezione più vicina alla telecamera finora trovata.
                Se è l'intersezione più vicina, si memorizza l'indice dell'oggetto selezionato.
                 Se è stato selezionato un oggetto, se ne stampa il nome a schermo.
                */
        }
        break;
    default:
        break;
    }
    
}
 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    // Se il tasto ESCAPE è premuto, chiude la finestra
    switch (key) {
    case GLFW_KEY_ESCAPE:
        if (action == GLFW_PRESS)
            //Imposta a True il flag booleano di chiusura della finestr
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;

    case GLFW_KEY_W:  //Muove la telecamera in avanti
        moveCameraForward();

        break;
    case GLFW_KEY_S:  //Muove la telecamera indietro
        if (mods & GLFW_MOD_SHIFT) {
            OperationMode = SCALING; //Si entra in modalità di operazione scalatura
            Operazione = "SCALATURA";
        }
        else
            moveCameraBack();

        break;

    case GLFW_KEY_A:  //Muove la telecamera a sisnistra
        moveCameraLeft();
        break;

    case GLFW_KEY_D:     //Muove la telecamera a destra
        moveCameraRight();
        break;

    case GLFW_KEY_U:
        if (mods & GLFW_MOD_SHIFT)
            moveCameraDown();   //Se premuto insieme al tasto shift sposta la telecamera in basso
        else
            moveCameraUp();  //Sposta la telecamera in alto


    case GLFW_KEY_T:  //Si entra in modalità di operazione traslazione
        OperationMode = TRASLATING;
        Operazione = "TRASLAZIONE";
        break;

    case GLFW_KEY_R: //Si entra in modalità di operazione rotazione
        OperationMode = ROTATING;
        Operazione = "ROTAZIONE";
        break;

    case GLFW_KEY_X:
        WorkingAxis = X;  //Seleziona l'asse X come asse lungo cui effettuare l'operazione selezionata (tra traslazione, rotazione, scalatura)
        stringa_asse = " Asse X";
        break;
    case GLFW_KEY_Y:
        WorkingAxis = Y;  //Seleziona l'asse Y come asse lungo cui effettuare l'operazione selezionata (tra traslazione, rotazione, scalatura)
        stringa_asse = " Asse Y";
        break;
    case GLFW_KEY_Z:
        WorkingAxis = Z;
        stringa_asse = " Asse Z";  //Seleziona l'asse Z come asse lungo cui effettuare l'operazione selezionata (tra traslazione, rotazione, scalatura)
        break;


    

    default:
        break;
    }
    // Selezione dell'asse per le trasformazioni
    switch (WorkingAxis) {
    case X:	asse = glm::vec3(1.0, 0.0, 0.0);

        break;
    case Y: asse = glm::vec3(0.0, 1.0, 0.0);

        break;
    case Z: asse = glm::vec3(0.0, 0.0, 1.0);

        break;

    default:
        break;

    }


    // I tasti   aggiornano lo spostamento a destra o a sinistra, la rotazione in segno antiorario o in senso orario, la scalatura come amplificazione o diminuizione delle dimensioni



    switch (OperationMode) {

        //la funzione modifyModelMatrix(glm::vec3 translation_vector, glm::vec3 rotation_vector, GLfloat angle, GLfloat scale_factor) 
        // definisce la matrice di modellazione che si vuole postmoltiplicare alla matrice di modellazione dell'oggetto selezionato, per poterlo traslare, ruotare scalare.

    case TRASLATING:
        
        break;
    case ROTATING:

        break;
    case SCALING:


        break;

    }
}
 

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{

    //Imposto la matrice di proiezione per la scena da diegnare
    

    float AspectRatio_mondo = (float)(width) / (float)(height); //Rapporto larghezza altezza di tutto ciò che è nel mondo
    //Se l'aspect ratio del mondo è diversa da quella della finestra devo mappare in modo diverso 
    //per evitare distorsioni del disegno
    if (AspectRatio_mondo > w / h)   //Se ridimensioniamo la larghezza della Viewport
    {
       
        w_up = (float)w;
        h_up = w / AspectRatio_mondo;
    }
    else {  //Se ridimensioniamo la larghezza della viewport oppure se l'aspect ratio tra la finestra del mondo 
        //e la finestra sullo schermo sono uguali
        glViewport(0, 0, h * AspectRatio_mondo, h);
        w_up = h * AspectRatio_mondo;
        h_up = (float)h;
    }
    glViewport(0, 0, w_up, h_up);
}

    
 

vec3 getTrackBallPoint(float x, float y)
{
    //Dalla posizione del mouse al punto proiettato sulla semisfera con centro l'origine e raggio 1

    
    vec3 point;
    

    return normalize(point);
}