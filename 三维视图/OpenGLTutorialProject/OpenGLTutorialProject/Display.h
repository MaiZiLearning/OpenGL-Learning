#pragma once
#include <string>
#include <SDL2\SDL.h>
class Display
{
public:
	Display(int width,int height,std::string& title);
	~Display();

public:
	void Update();
	bool isClosed();
	void clear(float r, float g, float b, float a);

private:
	SDL_Window * m_pWindow;		//SDL ´°¿ÚÖ¸Õë
	SDL_GLContext	m_glContext;
	bool m_bIsClosed;
};

