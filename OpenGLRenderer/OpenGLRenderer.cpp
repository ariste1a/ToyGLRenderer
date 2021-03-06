// OpenGLRenderer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <cstdlib>
#include <string>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "shader.h"
#include "mesh.h"
#include "model.h"
#include "Camera.h"
#pragma comment(lib, "opengl32.lib")
//bool DoTheImportThing(const std::string& pFile)
//{
//	// Create an instance of the Importer class
//	Assimp::Importer importer;
//	// And have it read the given file with some example postprocessing
//	// Usually - if speed is not the most important aspect for you - you'll
//	// probably to request more postprocessing than we do in this example.
//	const aiScene* scene = importer.ReadFile(pFile,
//		aiProcess_CalcTangentSpace |
//		aiProcess_Triangulate |
//		aiProcess_JoinIdenticalVertices |
//		aiProcess_SortByPType);
//	// If the import failed, report it
//	if (!scene)
//	{
//		//DoTheErrorLogging(importer.GetErrorString());
//		std::cout << importer.GetErrorString() << std::endl; 
//		return false;
//	}
//	// Now we can access the file's contents.
//	//DoTheSceneProcessing(scene);
//	// We're done. Everything will be cleaned up by the importer destructor
//	return true;
//}
//
//static void error_callback(int error, const char* description)
//{
//	fprintf(stderr, "Error: %s\n", description);
//}
//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GLFW_TRUE);
//}
//
//int main(void)
//{
//	std::cout << "Hello World!\n";
//	std::string input;
//	std::cin >> input;
//	DoTheImportThing(input);
//
//	// start GL context and O/S window using the GLFW helper library
//	if (!glfwInit()) {
//		fprintf(stderr, "ERROR: could not start GLFW3\n");
//		return 1;
//	}
//
//	// uncomment these lines if on Apple OS X
//	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/
//
//	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
//	if (!window) {
//		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
//		glfwTerminate();
//		return 1;
//	}
//	glfwMakeContextCurrent(window);
//
//	// start GLEW extension handler
//	glewExperimental = GL_TRUE;
//	glewInit();
//
//	// get version info
//	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
//	const GLubyte* version = glGetString(GL_VERSION); // version as a string
//	printf("Renderer: %s\n", renderer);
//	printf("OpenGL version supported %s\n", version);
//
//	// tell GL to only draw onto a pixel if the shape is closer to the viewer
//	glEnable(GL_DEPTH_TEST); // enable depth-testing
//	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
//
//	/* OTHER STUFF GOES HERE NEXT */
//
//	float points[] = {
//	   0.0f,  0.5f,  0.0f,
//	   0.5f, -0.5f,  0.0f,
//	  -0.5f, -0.5f,  0.0f
//	};
//
//	const char* vertex_shader =
//		"#version 400\n"
//		"in vec3 vp;"
//		"void main() {"
//		"  gl_Position = vec4(vp, 1.0);"
//		"}";
//
//	const char* fragment_shader =
//		"#version 400\n"
//		"out vec4 frag_colour;"
//		"void main() {"
//		"  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
//		"}";
//
//	GLuint vbo = 0;
//	glGenBuffers(1, &vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
//
//	GLuint vao = 0;
//	glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//
//	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vs, 1, &vertex_shader, NULL);
//	glCompileShader(vs);
//	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fs, 1, &fragment_shader, NULL);
//	glCompileShader(fs);
//
//	GLuint shader_programm = glCreateProgram();
//	glAttachShader(shader_programm, fs);
//	glAttachShader(shader_programm, vs);
//	glLinkProgram(shader_programm);
//
//
//	while (!glfwWindowShouldClose(window)) {
//		// wipe the drawing surface clear
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glUseProgram(shader_programm);
//		glBindVertexArray(vao);
//		// draw points 0-3 from the currently bound VAO with current in-use shader
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		// update other events like input handling 
//		glfwPollEvents();
//		// put the stuff we've been drawing onto the display
//		glfwSwapBuffers(window);
//	}
//
//	// close GL context and any other GLFW resources
//	glfwTerminate();
//	return 0;
//}


#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	if (!glfwInit()) {
			fprintf(stderr, "ERROR: could not start GLFW3\n");
			return 1;
	}
	/*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	glewInit();
	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader ourShader("shader.vert", "shader.frag");

	// load models
	// -----------
	Model ourModel("box.obj");


	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		ourShader.use();

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);		
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);

		// render the loaded model
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMat4("model", model);
		ourModel.Draw(ourShader);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}