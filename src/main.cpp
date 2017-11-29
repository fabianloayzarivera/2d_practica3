#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION


#include <glfw3.h>
#include <stb_image.h>
#include <font.h>
#include <Vec2.h>
#include <list>
#include <random>

using namespace std;

struct FontObj {
	Font *font;
	const char* text;
	float textWidth;
	float textHeight;
	int speed;
	float xPos;
	float yPos;
	float r;
	float g;
	float b;

};

FontObj generateFont(int screenWidth, int screenHeight, const char* text);
std::vector<const char *> fontFilenames;
std::random_device rd;
std::mt19937 rng(rd());
std::vector<FontObj> fontObjs;
std::vector<Font*> fonts;
int fontFilesAmount;
int main() {

	

	// Inicializamos GLFW
	if (!glfwInit()) {
		cout << "Error: No se ha podido inicializar GLFW" << endl;
		return -1;
	}
	atexit(glfwTerminate);
	// Creamos la ventana
	glfwWindowHint(GLFW_RESIZABLE, false);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Programacion 2D", nullptr, nullptr);
	if (!window) {
		cout << "Error: No se ha podido crear la ventana" << endl;
		return -1;
	}
	// Activamos contexto de OpenGL
	glfwMakeContextCurrent(window);
	// Inicializamos LiteGFX
	lgfx_setup2d(800, 600);

		
	// Bucle principal
	fontFilenames.push_back("./data/first.ttf");
	fontFilenames.push_back("./data/longshot.ttf");
	fontFilenames.push_back("./data/mexican.ttf");
	fontFilenames.push_back("./data/boom.ttf");
	fontFilenames.push_back("./data/blacklist.ttf");


	int min = 10;
	int max = 150;	
	std::uniform_int_distribution<int> uni(min, max); 	
	fontFilesAmount = fontFilenames.size();	
	std::uniform_int_distribution<int> frand(0, fontFilesAmount -1);
	for (int i = 0; i < fontFilesAmount; i++) {
		int randSize = uni(rng);
		int randFont = frand(rng);
		//const char* file = fontFilenames.at(randFont);
		const char* file = fontFilenames.at(i);
		fonts.push_back(Font::load(file, static_cast<float>(randSize)));
	}
	const char* text = "Hello World!";
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
		float random = (float)rand() / (float)(RAND_MAX / 100);
		if (random < 1){
			fontObjs.push_back(generateFont(screenWidth, screenHeight, text));
		}

		lgfx_clearcolorbuffer(0, 0, 0);
		for (auto obj = fontObjs.begin(); obj != fontObjs.end();)
		{   
			lgfx_setcolor((*obj).r, (*obj).g, (*obj).b, 1);			
			(*obj).font->draw((*obj).text, Vec2((*obj).xPos, (*obj).yPos));
			(*obj).xPos -= (*obj).speed * deltaTime;
			if ((*obj).xPos < ((*obj).textWidth * -1)) {
				//delete(obj);
				obj = fontObjs.erase(obj);
			}
			else {
				++obj;
			}						
		}		
		cout << "Size: " << (fontObjs.size()) << endl;

		// Actualizamos ventana y eventos
		glfwSwapBuffers(window);
		glfwPollEvents();


	}

	for (auto obj = fontObjs.begin(); obj != fontObjs.end();) {
		//delete(*obj);
		obj = fontObjs.erase(obj);
	}
	fontObjs.clear();
	for (auto obj = fonts.begin(); obj != fonts.end();) {
		delete(*obj);
		obj = fonts.erase(obj);
	}
	fonts.clear();
	return 0;
}

FontObj generateFont(int screenWidth, int screenHeight, const char* text) {
	FontObj *obj = new FontObj();
	obj->text = text;

	std::uniform_int_distribution<int> fon(0, fontFilesAmount-1);
	int randFont = fon(rng);
	obj->font = fonts.at(randFont);

	Vec2 textSize = obj->font->getTextSize(text);
	obj->textWidth = textSize.x;
	obj->textHeight = textSize.y;

	std::uniform_int_distribution<int> spd(20, 200);
	int speed = spd(rng);
	obj->speed = speed;
	obj->xPos = screenWidth;

	std::uniform_int_distribution<int> uni(0, screenHeight);
	int randY = uni(rng);
	obj->yPos = static_cast<float>(randY);

	float randomR = (float)rand() / (float)(RAND_MAX / 1);
	obj->r = randomR;
	float randomG = (float)rand() / (float)(RAND_MAX / 1);
	obj->g = randomG;
	float randomB = (float)rand() / (float)(RAND_MAX / 1);
	obj->b = randomB;
	return *obj;


}
