#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include "Crosshair.h"
#include "Enemigo.h"
#include "Inocente.h"
#include "Objetivo.h"
#include "SistemaPuntaje.h"
#include "Escenario.h"

using namespace sf;
using namespace std;

//Esta clase representa a Game con sus respectivos metodos
class Game {

private:
    int alto;
    int ancho;
    RenderWindow* wnd;
    Crosshair* crosshair;
    Enemigo* enemigo;
    Inocente* inocente;
    SistemaPuntaje* sistemPuntaje;
    Escenario* escene;
    Time timerMax;
    Time timer;
    Clock clock;
    bool objetivoVisible;

    //Proceso de eventos
    void procesarEventos(Event& evt) {
        switch (evt.type) {
            case Event::Closed:
                wnd->close();
                break;
            case Event::MouseMoved:
                crosshair->apuntar((float)evt.mouseMove.x, (float)evt.mouseMove.y);
                break;
            case Event::MouseButtonPressed:
                if (evt.mouseButton.button == Mouse::Button::Left) {
                    disparar();
                }
        }
    }

    //Dibujar objetos del juego
    void dibujarJuego() {
        escene->dibujar(wnd);
        sistemPuntaje->dibujar(wnd);

        if (objetivoVisible) {

            enemigo->dibujar(wnd);
        }
        else {
            inocente->dibujar(wnd);
        }

        sistemPuntaje->dibujarDamage(wnd);
        crosshair->dibujar(wnd);

    }

    //Actualizacion del juego
    void actualizarJuego() {
        Time elapsedTime = clock.restart();
        Time tempDisparoEnemigo = seconds(2.0f);
        timer -= elapsedTime;
        sistemPuntaje->actualizar();

        if (!sistemPuntaje->gameOver()) {
            if (timer <= sf::Time::Zero) {
                if (!objetivoVisible) {
                    resetTimer();
                }
            }
            else if (timer <= tempDisparoEnemigo) {
                if (objetivoVisible) {
                    cout << "El enemigo te ha disparado!" << endl;
                    sistemPuntaje->disparoRecibido();
                    resetTimer();
                }
            }
        }

        sistemPuntaje->HUD();
        
    }

    //Metodo que permite disparar a un objetivo
    void disparar() {
        Vector2f crosshairPos = crosshair->getPos();

        if (!sistemPuntaje->gameOver()) {
            if (objetivoVisible) {
                if (enemigo->enLimites(crosshairPos.x, crosshairPos.y)) {
                    cout << "Disparo a objetivo exito" << endl;
                    sistemPuntaje->disparoEfectivo();
                    resetTimer();
                }           
            }
            else {
                if (inocente->enLimites(crosshairPos.x, crosshairPos.y)) {
                    cout << "Error: le Diste a un Inocente" << endl;            
                    sistemPuntaje->disparoFallido();
                    resetTimer();
                }
            }
        }
    }

    //Metodo que resetea el tiempo de aparicion de objetivos
    //Eleccion de objetivo de forma aleatoria(Enemigo/inocente)
    void resetTimer() {
        timer = timerMax;
        objetivoVisible = rand() % 2 == 0; 
        enemigo->reset();
        inocente->reset();
    
        if (objetivoVisible) {
            enemigo->posicionAleatoria();
        }
        else {
            inocente->posicionAleatoria();
            
        }
    }

public:

    Game(String titulo) {
        ancho = 1024;
        alto = 768;
        wnd = new RenderWindow(VideoMode(ancho, alto, 32), titulo);
        wnd->setMouseCursorVisible(false);
        wnd->setFramerateLimit(60);
        crosshair = new Crosshair();
        enemigo = new Enemigo();
        inocente = new Inocente();
        sistemPuntaje = new SistemaPuntaje();
        escene = new Escenario();
        srand(static_cast<unsigned>(time(nullptr)));
        // Configurar el temporizador
        timerMax = seconds(3.f); // 3 segundos
        resetTimer();
    }

    ~Game() {
        delete wnd;  
        delete crosshair;
        delete enemigo;
        delete inocente;
        delete sistemPuntaje;
        delete escene;
    }
    
    //Ejecucion del juego
    void ejecutar() {
        Event evt;

        while (wnd->isOpen()) {
            while (wnd->pollEvent(evt))
                procesarEventos(evt);

            actualizarJuego();
            wnd->clear();
            dibujarJuego();
            wnd->display();
        }
    }

};