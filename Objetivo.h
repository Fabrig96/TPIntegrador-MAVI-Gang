#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

//Esta clase representa a un Objetivo con sus respectivos metodos
class Objetivo {

private:

    Sprite sprite;
    Texture texture;
    Sprite sprite2;
    Texture texture2;
    Sprite sprite3;
    Texture texture3;
    Clock clock;
    Time timer;
    Time timerMax;
    int ventana;
    bool vivo;
    vector<sf::Vector2f> windowPositions;
    int posicionAnterior;

    int generarPosicionNoConsecutiva(int posicionAnterior, int rango) {
        int nuevaPosicion;

        do {
            nuevaPosicion = rand() % rango;
        } while (nuevaPosicion == posicionAnterior);

        return nuevaPosicion;
    }

public:

    Objetivo(const string& texturePath, const string& texturePath2, const string& texturePath3, const vector<Vector2f>& positions)
        : windowPositions(positions), ventana(0) {

        texture.loadFromFile(texturePath);
        sprite.setTexture(texture);
        sprite.setScale(1.0f, 0.9f);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);

        texture2.loadFromFile(texturePath2);
        sprite2.setTexture(texture2);
        sprite2.setScale(1.0f, 0.9f);
        sprite2.setOrigin(texture2.getSize().x / 2.0f, texture2.getSize().y / 2.0f);

        texture3.loadFromFile(texturePath3);
        sprite3.setTexture(texture3);
        sprite3.setScale(1.0f, 0.9f);
        sprite3.setOrigin(texture3.getSize().x / 2.0f, texture3.getSize().y / 2.0f);

        vivo = true;
        posicionAnterior = -1;

    }

    //Dibujar objetivo
    void dibujar(RenderWindow* wnd) {
        if (ventana == 1) {
            wnd->draw(sprite2);
        }
        else if (ventana == 2) {
            wnd->draw(sprite);
        }
        else if (ventana == 3) {
            wnd->draw(sprite3);
        }
    }

    //Posicionar de forma aleatoria el objetivo en diferentes ventanas
    void posicionAleatoria() {
        int rango = windowPositions.size();
        int posIndex = generarPosicionNoConsecutiva(posicionAnterior, rango);

        if (posIndex == 0 || posIndex == 1) {
            sprite2.setPosition(windowPositions[posIndex]);
            ventana = 1;
        }
        else if (posIndex == 2 || posIndex == 3) {
            sprite.setPosition(windowPositions[posIndex]);
            ventana = 2;
        }
        else if (posIndex == 4) {
            sprite3.setPosition(windowPositions[posIndex]);     
            ventana = 3;
        }

        posicionAnterior = posIndex;
    }

    //Resetar a un objetivo 
    void reset() {
        sprite.setPosition(-1, -1);
        sprite2.setPosition(-1, -1);
        sprite3.setPosition(-1, -1);
        vivo = false;
    }

    //Verificar si objetivo esta dentro de una coordenada x, y
    bool enLimites(float x, float y) {
        FloatRect limits1 = sprite.getGlobalBounds();
        FloatRect limits2 = sprite2.getGlobalBounds();
        FloatRect limits3 = sprite3.getGlobalBounds();

        if (limits1.contains(x, y)) {
            return true;
        }
        else if (limits2.contains(x, y)) {
            return true;
        }
        else if (limits3.contains(x, y)) {
            return true;
        }

        return false;
    } 
   
};