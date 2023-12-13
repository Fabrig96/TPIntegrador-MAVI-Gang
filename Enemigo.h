#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Objetivo.h"

using namespace sf;
using namespace std;

//Esta clase representa a un Enemigo que hereda de Objetivo
class Enemigo : public Objetivo {

public:


    Enemigo() : Objetivo("Assets/enemigo1Vent.png", "Assets/enemigo2Vent.png","Assets/enemigo2Puer.png",
                { {243, 143}, {788, 143}, {212, 394}, {802, 394},{512,411} }) {}


};