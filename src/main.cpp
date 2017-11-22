#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <stb_image.h>
#include <font.h>
#include <Vec2.h>
using namespace std;


int main() {
	// Inicializamos GLFW
	if (!glfwInit()) {
		cout << "Error: No se ha podido inicializar GLFW" << endl;
		return -1;
	}
	atexit(glfwTerminate);

	// Creamos la ventana
	glfwWindowHint(GLFW_RESIZABLE, true);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Programacion 2D", nullptr, nullptr);
	if (!window) {
		cout << "Error: No se ha podido crear la ventana" << endl;
		return -1;
	}

	// Activamos contexto de OpenGL
	glfwMakeContextCurrent(window);

	// Inicializamos LiteGFX

	lgfx_setup2d(800, 600);

	Font::load("./data/boom.ttf", 3);




	// Bucle principal
	double xposMouse;
	double yposMouse;
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		// Actualizamos delta
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// Actualizamos tamaño de ventana
		int screenWidth, screenHeight;
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
		lgfx_setviewport(0, 0, screenWidth, screenHeight);


		// Actualizacion de logica del programa
		glfwGetCursorPos(window, &xposMouse, &yposMouse);

		Vec2 *mousePos = new Vec2(xposMouse, yposMouse);

		
		lgfx_setcolor(1, 1, 1, 1);





		// Actualizamos ventana y eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
		delete(mousePos);

	}

	return 0;
}