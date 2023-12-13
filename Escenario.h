#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

//Clase que representa al Escenario de fondo del juego
class Escenario {

	Texture escenario_tex;
	Sprite escenario_sprite;

public:

	Escenario() {

		escenario_tex.loadFromFile("Assets/frame.png");
		escenario_sprite.setTexture(escenario_tex);
		escenario_sprite.setScale(1.0f, 0.9f);
		escenario_sprite.setOrigin(escenario_tex.getSize().x / 2.0f, escenario_tex.getSize().y / 2.0f);

	}

	//Dibujar Escenario
	void dibujar(RenderWindow* wnd) {
		escenario_sprite.setPosition(1024 / 2.0f, 768 / 2.6f);
		wnd->draw(escenario_sprite);
	}

};