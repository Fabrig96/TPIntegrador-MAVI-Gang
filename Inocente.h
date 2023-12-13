#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Objetivo.h"

using namespace sf;
using namespace std;

//Esta clase representa a un Inocente que hereda de Objetivo
class Inocente : public Objetivo {

public:

    Inocente() : Objetivo("Assets/inocenteVentBton.png","Assets/inocenteVentTop.png","Assets/inocentePuer.png",
                { {243, 143}, {788, 143}, {212, 394}, {802, 394},{512,411} }) {}

};
