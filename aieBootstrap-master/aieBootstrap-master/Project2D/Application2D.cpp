#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <iostream>

Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	int i1 = 45;
	int result = (i1 << 2) & 0b111000;
	std::cout << result << std::endl;

	m_2dRenderer = new aie::Renderer2D();

	//Loads an image
	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	//Positions the transform near the centre
	m_matrix3.setIdentity();
	m_shipPos = { getWindowWidth() / 2.f, getWindowHeight() / 2.f };
	//m_matrix3[2] = { getWindowWidth() / 2.f, getWindowHeight() / 2.f,1 };
	m_matrix3.setTranslate(m_shipPos);
	m_font = new aie::Font("./font/consolas.ttf", 32);
	
	m_timer = 0;

	return true;
}

void Application2D::shutdown() {
	
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	//m_matrix3.rotateZ(deltaTime);
	//m_shipPos.x += deltaTime * 30;
	//m_matrix3.setTranslate(m_shipPos);

	// input example
	aie::Input* input = aie::Input::getInstance();

	// Update the camera position using the arrow keys
	float camPosX;
	float camPosY;
	m_2dRenderer->getCameraPos(camPosX, camPosY);

	if (input->isKeyDown(aie::INPUT_KEY_UP))
		camPosY += 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		camPosY -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		camPosX -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		camPosX += 500.0f * deltaTime;

	m_2dRenderer->setCameraPos(camPosX, camPosY);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	//// demonstrate animation
	//m_2dRenderer->setUVRect(int(m_timer) % 8 / 8.0f, 0, 1.f / 8, 1.f / 8);
	//m_2dRenderer->drawSprite(m_texture, 200, 200, 100, 100);

	// demonstrate spinning sprite
	m_2dRenderer->setUVRect(0,0,1,1);
	m_2dRenderer->drawSprite(m_shipTexture, 600, 400, 0, 0, m_timer, 1);

	//// draw a thin line
	//m_2dRenderer->setRenderColour(1, 0, 1, 1);
	//m_2dRenderer->drawLine(300, 300, 600, 400, 2, 1);

	//// draw a moving purple circle
	//m_2dRenderer->setRenderColour(1, 0, 1, 1);
	//m_2dRenderer->drawCircle(sin(m_timer) * 100 + 600, 150, 50);

	//// draw a rotating red box
	//m_2dRenderer->setRenderColour(1, 0, 0, 1);
	//m_2dRenderer->drawBox(600, 500, 60, 20, m_timer);

	//// draw a slightly rotated sprite with no texture, coloured yellow
	//m_2dRenderer->setRenderColour(1, 1, 0, 1);
	//m_2dRenderer->drawSprite(nullptr, 400, 400, 50, 50, 3.14159f * 0.25f, 1);
	
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}