#include "Display.h"
#include "GL/glew.h"
#include <iostream>


Display::Display(int width, int height, std::string& title)
{
	//初始化SDL 窗口
	SDL_Init(SDL_INIT_EVERYTHING);

	//设置窗口属性
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//创建SDL 窗口
	m_pWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	//
	m_glContext = SDL_GL_CreateContext(m_pWindow);


	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		std::cerr << "Glew Init failure" << std::endl; 
	}

	m_bIsClosed = false;

}

Display::~Display()
{
	//退出SDL
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();

}

bool Display::isClosed()
{
	return m_bIsClosed;
}

void Display::Update()
{
	SDL_GL_SwapWindow(m_pWindow);
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			m_bIsClosed = true;
		}
	}


}

void Display::clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);

}
