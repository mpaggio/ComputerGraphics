#include "lib.h"
#include "strutture.h"
#include "utilities.h"

extern GLFWwindow* window;
extern mat4 Projection;
extern int height, width;
 
extern ViewSetup SetupTelecamera;
extern PerspectiveSetup SetupProspettiva;
extern float cameraSpeed;

extern vector<Mesh> Scena;
extern vector<vector<MeshObj>> ScenaObj;

vec3 slide_vector;

bool checkPosition(vec3 position) {
	for (int i = 0; i < Scena.size() - 1; i++) {
		if (checkCollision(position, &Scena[i])) {
			return false;
		}
	}
	for (int i = 0; i < ScenaObj.size(); i++) {
		for (int j = 0; j < ScenaObj[i].size(); j++) {
			if (checkCollision(position, &ScenaObj[i][j])) {
				return false;
			}
		}
	}
	return true;
}

void moveCameraForward()
{
	cout << SetupTelecamera.direction.b << ", " << SetupTelecamera.direction.g << endl;
	SetupTelecamera.direction= SetupTelecamera.target - SetupTelecamera.position;
	if (checkPosition(SetupTelecamera.position + SetupTelecamera.direction * cameraSpeed)) {
		SetupTelecamera.position += SetupTelecamera.direction * cameraSpeed;
		SetupTelecamera.target = SetupTelecamera.position + SetupTelecamera.direction;
	}
}

void moveCameraBack()
{
	SetupTelecamera.direction = SetupTelecamera.target - SetupTelecamera.position;
	if (checkPosition(SetupTelecamera.position - SetupTelecamera.direction * cameraSpeed)) {
		SetupTelecamera.position -= SetupTelecamera.direction * cameraSpeed;
		SetupTelecamera.target = SetupTelecamera.position + SetupTelecamera.direction;
	}
}

void moveCameraLeft()
{
	SetupTelecamera.direction = SetupTelecamera.target - SetupTelecamera.position;
	slide_vector = cross(SetupTelecamera.direction, vec3(SetupTelecamera.upVector)) * cameraSpeed;
	if (checkPosition(SetupTelecamera.position - slide_vector)) {
		SetupTelecamera.position -= slide_vector;
		SetupTelecamera.target -= slide_vector;
	}
}

void moveCameraRight()
{
	SetupTelecamera.direction = SetupTelecamera.target - SetupTelecamera.position;
	slide_vector = cross(SetupTelecamera.direction, vec3(SetupTelecamera.upVector)) * cameraSpeed;
	if (checkPosition(SetupTelecamera.position + slide_vector)) {
		SetupTelecamera.position += slide_vector;
		SetupTelecamera.target += slide_vector;
	}
}

void moveCameraUp()
{
	SetupTelecamera.direction = SetupTelecamera.target - SetupTelecamera.position;
	slide_vector=normalize(cross(SetupTelecamera.direction, SetupTelecamera.upVector));
	vec3 upDirection = cross(SetupTelecamera.direction, slide_vector) * cameraSpeed;
	if (checkPosition(SetupTelecamera.position - upDirection)) {
		SetupTelecamera.position -= upDirection;
		SetupTelecamera.target -= upDirection;
	}
}

void moveCameraDown()
{
	SetupTelecamera.direction = SetupTelecamera.target - SetupTelecamera.position;
	slide_vector = normalize(cross(SetupTelecamera.direction, vec3(SetupTelecamera.upVector)));
	vec3 upDirection = cross(SetupTelecamera.direction, slide_vector) * cameraSpeed;
	if (checkPosition(SetupTelecamera.position + upDirection)) {
		SetupTelecamera.position += upDirection;
		SetupTelecamera.target += upDirection;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{ 
	if (yoffset < 0)
		SetupProspettiva.fovY +=1; //Rotella del mouse indietro
	 else
		SetupProspettiva.fovY -= 1;  //Rotella del mouse in avanti

}