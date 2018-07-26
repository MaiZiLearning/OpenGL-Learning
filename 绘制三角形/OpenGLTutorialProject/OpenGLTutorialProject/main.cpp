#include <iostream>
//#include "GL/glew.h"
//#include "Display.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Shader.h"

//窗口大小改变时调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//键盘输入时调用
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main(int argc,char **argv)
{
	//初始化GLFW
	glfwInit();
	//配置
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	//OpenGL 主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	//OpenGL 子版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		//使用OpenGL 核心模式
	//创建GLFW 窗口
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();	//释放资源
		return -1;
	}
	//通知GLFW将我们窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);		

	//初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//注册回调函数 (窗口大小改变时调用)
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader ourShader("3.3.shader.vs", "3.3.shader.fs");

	// 设置顶点数据(和缓冲区)，配置顶点属性
	// ------------------------------------------------------------------
	float vertices[] = {
		 // 位置				//颜色
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // 右下
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // 左下
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // 顶部
	};

	unsigned int VAO;		//顶点数组对象ID
	unsigned int VBO;		//顶点缓冲对象ID
	
	glGenVertexArrays(1, &VAO);		//生成顶点数组对象
	glGenBuffers(1, &VBO);			//生成顶点缓冲对象
	// 1. 绑定VAO
	glBindVertexArray(VAO);
	//2. 绑定VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//3. 把顶点数组复制到缓冲中供OpenGL使用
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//4. 设置顶点属性指针
	//位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//4.解除绑定
	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	//渲染循环
	while (!glfwWindowShouldClose(window))
	{
		//监测键盘输入
		processInput(window);

		//清屏
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//清屏颜色
		glClear(GL_COLOR_BUFFER_BIT);

		//激活着色器
		ourShader.use();
		//平移
		float offset = 0.5f;
		ourShader.setFloat("xOffset", offset);
		
		// draw our first triangle
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// 检查并调用事件，交换缓冲
		glfwPollEvents();		//检查触发事件
		glfwSwapBuffers(window);//交换颜色缓冲,绘制缓存内容

	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//释放资源
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
	//调整视口区域
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	//ESC 退出键
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
