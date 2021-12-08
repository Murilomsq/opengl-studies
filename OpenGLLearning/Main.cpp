#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main() {

	//Initialize GLFW
	glfwInit();



	//Tell GLFW what version of OpenGL we are using
	// 3.3 in this case
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Tell GLFW we are using the core profile (modern functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f
	};

	GLuint indices[] =
	{
		0, 3, 5, //Lower left
		3, 2, 4, //Lower Right
		5, 4, 1 //Upper
	};


	// Creating an instance of a window
	GLFWwindow* window = glfwCreateWindow(800, 800, "Zebra", NULL, NULL);

	//Error checking
	if (window == NULL) {
		std::cout << "Failed tp create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Make the window the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport that OpenGL will use in the window
	// x,y = [0 0, 800 800]
	glViewport(0, 0, 800, 800);

	// Creating Vertex Shader Object and getting its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	// Compile the Vertex Shader
	glCompileShader(vertexShader);
	

	// Creating Fragment Shader Object and getting its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Vertex Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Fragment Shader
	glCompileShader(fragmentShader);

	// Creating shader program and keeping its ref
	GLuint shaderProgram = glCreateProgram();

	//Attaching Vertex and Fragment Shader to their shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Attaching shaders int the object program
	glLinkProgram(shaderProgram);

	// Delete useless shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Creating reference containers for the Vertex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO, EBO;

	//Generating VAO and VBO and EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	//Binding EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Get the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Get indices to EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Configuring Vertex Attribute so OpenGL knows how to deal with the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// Enabling VertexAttribute so OpenGL knows how to use it
	glEnableVertexAttribArray(0);

	// Bind both VBO and VAO to 0 so that we don't accidentally modify them
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);




	// Specify the background color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Cleaning the back buffer and assigning the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap back and front buffers
	glfwSwapBuffers(window);
	
	
	//Main whileLoop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows how to use it
		glBindVertexArray(VAO);
		// Draw The Triangles
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		// Update OpenGL main functions (display, reshape, etc)
		glfwPollEvents();
	}
	// Deleting the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// Deleting the window before exiting the program
	glfwDestroyWindow(window);
	// Terminating GLFW before exiting the program
	glfwTerminate();
	return 0;
}