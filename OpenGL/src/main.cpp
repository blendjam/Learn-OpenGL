#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core/Shader.h"
#include "Core/Texture.h"
#include "Core/Camera.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#define TORAD(x) glm::radians(x)

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void DrawTwoScaledUpContainers();

glm::mat4 identityMat(1.0f);
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
glm::vec3 lightPos(1.0f, 1.0f, 2.0f);
float lightspeed = 2.5f;
bool firstMouse = true;
float lastX, lastY;

float deltaTime = 0.0f;
float lastTime = 0.0f;

static float f = 0;
bool show_demo_window = false;

GLFWwindow* window;

void OpenGLInit()
{
	if (!glfwInit()) return;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Triangle", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to make window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return;
	}
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_move_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
}

int main(void)
{
	OpenGLInit();
	//float cube[] = {
	//-0.5f, -0.5f, -0.5f,
	// 0.5f, -0.5f, -0.5f,
	// 0.5f,  0.5f, -0.5f,
	// 0.5f,  0.5f, -0.5f,
	//-0.5f,  0.5f, -0.5f,
	//-0.5f, -0.5f, -0.5f,

	//-0.5f, -0.5f,  0.5f,
	// 0.5f, -0.5f,  0.5f,
	// 0.5f,  0.5f,  0.5f,
	// 0.5f,  0.5f,  0.5f,
	//-0.5f,  0.5f,  0.5f,
	//-0.5f, -0.5f,  0.5f,

	//-0.5f,  0.5f,  0.5f,
	//-0.5f,  0.5f, -0.5f,
	//-0.5f, -0.5f, -0.5f,
	//-0.5f, -0.5f, -0.5f,
	//-0.5f, -0.5f,  0.5f,
	//-0.5f,  0.5f,  0.5f,

	// 0.5f,  0.5f,  0.5f,
	// 0.5f,  0.5f, -0.5f,
	// 0.5f, -0.5f, -0.5f,
	// 0.5f, -0.5f, -0.5f,
	// 0.5f, -0.5f,  0.5f,
	// 0.5f,  0.5f,  0.5f,

	//-0.5f, -0.5f, -0.5f,
	// 0.5f, -0.5f, -0.5f,
	// 0.5f, -0.5f,  0.5f,
	// 0.5f, -0.5f,  0.5f,
	//-0.5f, -0.5f,  0.5f,
	//-0.5f, -0.5f, -0.5f,

	//-0.5f,  0.5f, -0.5f,
	// 0.5f,  0.5f, -0.5f,
	// 0.5f,  0.5f,  0.5f,
	// 0.5f,  0.5f,  0.5f,
	//-0.5f,  0.5f,  0.5f,
	//-0.5f,  0.5f, -0.5f,
	//};
	float cube[] = {
		//Vertices            //Normals
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	unsigned int VBO, cubeVAO;
	// Generate Buffers and Vertex Arrays
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	//Binding
	glBindVertexArray(cubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

	//Telling OpenGL about the layout of your verteices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));


	//Light Box
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);

	//Configuring the shader
	Shader colorShader("res/shaders/color.vert", "res/shaders/color.frag");
	Shader lightShader("res/shaders/light.vert", "res/shaders/light.frag");
	Shader outlineShader("res/shaders/color.vert", "res/shaders/outline.frag");


	//----ImGui
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
	//----

	float colors[3] = { 0.0f, 1.0f, 0.0f };
	glm::vec3 objColor(1.0f, 0.5f, 0.31f);
	glm::vec3 lightColor(1.0f);
	while (!glfwWindowShouldClose(window))
	{

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//-----Deltatime Calculation --------
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		//----------
		processInput(window);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		//-----------Stencil----------
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		//----------Draw Object---------
		int time = glfwGetTime();
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
		colorShader.use();
		colorShader.setVec("light.ambient", ambientColor);
		colorShader.setVec("light.diffuse", diffuseColor);
		colorShader.setVec("light.specular", glm::vec3(1.0f));
		colorShader.setVec("light.position", lightPos);
		colorShader.setVec("viewPos", camera.Position);
		colorShader.setVec("material.ambient", objColor);
		colorShader.setVec("material.diffuse", objColor);
		colorShader.setVec("material.specular", glm::vec3(0.5f));
		colorShader.setFloat("material.shininess", 32.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(TORAD(camera.Zoom), (float)(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);
		glm::mat4 model(1.0f);
		colorShader.setMatrix("view", view);
		colorShader.setMatrix("projection", projection);
		colorShader.setMatrix("model", model);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//--------Draw Light-------
		lightShader.use();
		lightShader.setMatrix("view", view);
		lightShader.setMatrix("projection", projection);
		model = glm::translate(identityMat, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader.setMatrix("model", model);
		lightShader.setVec("lightColor", lightColor);
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//Draw scaled up shapes
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00); // disable writing to the stencil buffer
		glDisable(GL_DEPTH_TEST);
		outlineShader.use();
		DrawTwoScaledUpContainers();
		//------Imgui-------
		if (show_demo_window)
		{

			static int counter = 0;
			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

			ImGui::SliderFloat("Slideme", &f, 0, 10);
			ImGui::ColorEdit3("clear color", colors); // Edit 3 floats representing a color
			if (ImGui::Button("Click Me"))
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		//----------

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//Clearing the memory
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &cubeVAO);

	//imgui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	float angle = (float)glfwGetTime();

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
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		show_demo_window = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		show_demo_window = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		lightPos.x += lightspeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		lightPos.x -= lightspeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		lightPos.y += lightspeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		lightPos.y -= lightspeed * deltaTime;
	lightPos.x += sin(angle) * deltaTime;
	lightPos.y += cos(angle) * deltaTime;
}


void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	camera.ProcessMouseMovement(xoffset, yoffset, true);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void DrawTwoScaledUpContainers()
{

}
