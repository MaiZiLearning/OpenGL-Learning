#include <iostream>
//#include "GL/glew.h"
//#include "Display.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Shader.h"

//���ڴ�С�ı�ʱ����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//��������ʱ����
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main(int argc,char **argv)
{
	//��ʼ��GLFW
	glfwInit();
	//����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	//OpenGL ���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	//OpenGL �Ӱ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		//ʹ��OpenGL ����ģʽ
	//����GLFW ����
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();	//�ͷ���Դ
		return -1;
	}
	//֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);		

	//��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//ע��ص����� (���ڴ�С�ı�ʱ����)
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader ourShader("3.3.shader.vs", "3.3.shader.fs");

	// ���ö�������(�ͻ�����)�����ö�������
	// ------------------------------------------------------------------
	float vertices[] = {
		 // λ��				//��ɫ
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // ����
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // ����
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // ����
	};

	unsigned int VAO;		//�����������ID
	unsigned int VBO;		//���㻺�����ID
	
	glGenVertexArrays(1, &VAO);		//���ɶ����������
	glGenBuffers(1, &VBO);			//���ɶ��㻺�����
	// 1. ��VAO
	glBindVertexArray(VAO);
	//2. ��VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//3. �Ѷ������鸴�Ƶ������й�OpenGLʹ��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//4. ���ö�������ָ��
	//λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//4.�����
	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		//����������
		processInput(window);

		//����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//������ɫ
		glClear(GL_COLOR_BUFFER_BIT);

		//������ɫ��
		ourShader.use();
		//ƽ��
		float offset = 0.5f;
		ourShader.setFloat("xOffset", offset);
		
		// draw our first triangle
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// ��鲢�����¼�����������
		glfwPollEvents();		//��鴥���¼�
		glfwSwapBuffers(window);//������ɫ����,���ƻ�������

	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//�ͷ���Դ
	glfwTerminate();	




	///*Display display(800,600,std::string("test"));
	//while (!display.isClosed())
	//{
	//display.clear(0.0f,0.15f,0.3f,1.0f);
	//display.Update();
	//}
	//*/
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//�����ӿ�����
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	//ESC �˳���
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
