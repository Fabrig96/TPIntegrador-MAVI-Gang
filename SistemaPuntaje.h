#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>

//Clase que representa al Sistema de Puntaje y sus respectivos metodos
class SistemaPuntaje {

private:

	Texture damageTx;
	Sprite  damageSp;
	Texture logoWildtx;
	Sprite logoWildSp;
	Font fuente;
	Text labelPuntaje;
	Text labelEnemigosElim;
	Text labelVidasRestant;
	Text puntajeH;
	Text enemigosElim;
	Text vidaRestant;
	Text resultadoTitle;
	int enemigosAbatidos;
	int inocentesAbatidos;
	int vidaTotal;
	int puntaje;
	bool finished;

	Clock tiempoDisparoEnemigo;

public:

	SistemaPuntaje() {

		vidaTotal = 3;
		enemigosAbatidos = 0;
		inocentesAbatidos = 0;
		puntaje = 0;
		finished = false;

		if (!logoWildtx.loadFromFile("Assets/wildlogo.png")) {
			cerr << "Error al cargar logo" << endl;
		}

		logoWildSp.setTexture(logoWildtx);
		logoWildSp.setScale(0.35f, 0.35f);
		logoWildSp.setOrigin(damageTx.getSize().x / 2.0f, damageTx.getSize().y / 2.0f);
		
		if (!fuente.loadFromFile("Assets/RobotoCondensed-Bold.ttf")) {
			cerr << "Error al cargar la fuente" << endl;
		}

		labelPuntaje.setFont(fuente);
		labelPuntaje.setString("Puntaje: ");
		labelPuntaje.setCharacterSize(40);
		labelPuntaje.setFillColor(Color::Green);
		labelPuntaje.setPosition(-100, -100);
		labelEnemigosElim.setFont(fuente);
		labelEnemigosElim.setString("Enemigos abatidos: ");
		labelEnemigosElim.setCharacterSize(40);
		labelEnemigosElim.setFillColor(Color::Green);
		labelVidasRestant.setFont(fuente);
		labelVidasRestant.setString("Vidas restantes: ");
		labelVidasRestant.setCharacterSize(40);
		labelVidasRestant.setFillColor(Color::Green);

		puntajeH.setFont(fuente);
		puntajeH.setString(to_string(puntaje));
		puntajeH.setCharacterSize(40);
		puntajeH.setFillColor(Color::Cyan);
		puntajeH.setPosition(-100, -100);
		enemigosElim.setFont(fuente);
		enemigosElim.setString(to_string(enemigosAbatidos));
		enemigosElim.setCharacterSize(40);
		enemigosElim.setFillColor(Color::Cyan);
		vidaRestant.setFont(fuente);
		vidaRestant.setString(to_string(vidaTotal));
		vidaRestant.setCharacterSize(40);
		vidaRestant.setFillColor(Color::Cyan);

		damageTx.loadFromFile("Assets/shotyou.png");
		damageSp.setTexture(damageTx);
		damageSp.setScale(0.35f, 0.35f);
		damageSp.setOrigin(damageTx.getSize().x / 2.0f, damageTx.getSize().y / 2.0f);
		damageSp.setPosition(-100, -100);

		resultadoTitle.setFont(fuente);
		resultadoTitle.setCharacterSize(60);
		resultadoTitle.setFillColor(Color::Yellow);
		resultadoTitle.setPosition(-100, -100);


	}

	//Setea el HUD de enemigos eliminados y vidas restantes
	void HUD() {
		
		logoWildSp.setPosition(120, 560);
		labelEnemigosElim.setPosition(570, 580);
		labelVidasRestant.setPosition(570, 660);
		enemigosElim.setPosition(885, 580);
		vidaRestant.setPosition(885, 660);
	}

	//Aumenta puntaje y enemigos eliminados por medio de un disparo efectivo
	void disparoEfectivo() {
		enemigosAbatidos += 1;
		puntaje = enemigosAbatidos - (inocentesAbatidos * 10);
		puntajeH.setString(to_string(puntaje));
		enemigosElim.setString(to_string(enemigosAbatidos));
		cout << "Puntaje: " << puntaje << endl;
	}

	//Disminuye la cantidad de vidas por disparar a inocente
	void disparoFallido() {
		vidaTotal -= 1;
		inocentesAbatidos += 1;
		puntaje = enemigosAbatidos - (inocentesAbatidos * 10);
		puntajeH.setString(to_string(puntaje));
		vidaRestant.setString(to_string(vidaTotal));
		cout << "Puntaje: " << puntaje << endl;
		cout << "Vida: " << vidaTotal << endl;
	}

	//Disminuye vida restante al recibir disparo
	void disparoRecibido() {
		vidaTotal -= 1;
		vidaRestant.setString(to_string(vidaTotal));
		damageSp.setPosition(1024 / 2.0f, 768 / 4.0f);
		cout << "Vida: " << vidaTotal << endl;
	}

	//Verificar si finaliza el juego y setear HUD game over
	bool gameOver() {
		resultadoTitle.setPosition(360, 600);
		
		
		if (vidaTotal == 0) {
			cout << "GAME OVER" << endl;
			resultadoTitle.setString("GAME OVER!");
			labelPuntaje.setPosition(400, 680);
			puntajeH.setPosition(540, 680);
			finished = true;
		}

		return finished;
	}

	//Dibujar HUD sistema de puntaje
	void dibujar(RenderWindow* wnd) {

		if (!gameOver()) {
			wnd->draw(labelEnemigosElim);
			wnd->draw(labelVidasRestant);			
			wnd->draw(enemigosElim);
			wnd->draw(vidaRestant);
			wnd->draw(logoWildSp);
		}
		wnd->draw(resultadoTitle);
		wnd->draw(labelPuntaje);
		wnd->draw(puntajeH);
	}

	//Actualizar sprite de danio recibido
	void actualizar() {

		if (tiempoDisparoEnemigo.getElapsedTime().asSeconds() > 1.0) {
			tiempoDisparoEnemigo.restart();
			damageSp.setPosition(-100, -100);
		}
	}

	//Dibujar sprite de danio
	void dibujarDamage(RenderWindow* wnd) {
		wnd->draw(damageSp);
	}

};