// opengl-template.cpp: Defines the entry point for the application.
//

#include "opengl-template.h"

constexpr int width = 2560;
constexpr int height = 1080;

int main()
{
	assert(glfwInit());

	GLFWwindow* window = glfwCreateWindow(width, height, "Hello Triangle", nullptr, nullptr);
	assert(window);

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	assert(glewInit() == GLEW_OK);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	ImGui::StyleColorsLight();

	void framebuffer_size_callback(GLFWwindow * window, int width, int height);
	{
		glViewport(0, 0, width, height);
	}

	static float f0 = 0.0f, f1 = 2.0f, f2 = 3.0f;


	GLint gl_major_version = 0;
	GLint gl_minor_version = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &gl_major_version);
	glGetIntegerv(GL_MINOR_VERSION, &gl_minor_version);

	std::cout << "OpenGl Version: " << gl_major_version << "." << gl_minor_version << std::endl;
	std::cout << "OpenGl Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGl Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	std::array<glm::vec3, 3> Vertices = {
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(0.0f, 0.5f, 0.0f)
	};

	constexpr auto model_matrix = glm::identity<glm::mat4>();

	constexpr glm::vec3 eye{ 0, -5, 10 };
	constexpr glm::vec3 center{ 0, 0, 0 };
	constexpr glm::vec3 up{ 0, 1, 0 };

	const glm::mat4 view_matrix = lookAt(eye, center, up);

	constexpr float fov = glm::radians(45.0f);
	constexpr float aspect = static_cast<float>(width) / static_cast<float>(height);
	constexpr float near = 0.001f;
	constexpr float far = 1000.0f;

	const glm::mat4 projection_matrix = glm::perspective(fov, aspect, near, far);

	const glm::mat4 mvp = projection_matrix * view_matrix * model_matrix;

	for (glm::vec3& vertex : Vertices)
	{
		glm::vec4 projected_vertex = mvp * glm::vec4(vertex, 1.0f);
		projected_vertex /= projected_vertex.w;
		vertex = projected_vertex;
	}

	GLuint vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices.data(), GL_STATIC_DRAW);


	while (!glfwWindowShouldClose(window))
	{

		glViewport(0, 0, width, height);
		glClearColor(f0, 0.584f, 0.659f, 1.0f);

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);


		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Properties");
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();

	return 0;
}