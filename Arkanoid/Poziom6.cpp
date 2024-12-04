/** \file Poziom6.h
* Odpowiada za szosty poziom
*/
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "MainMenu.h"
#include "Poziom6.h"
#include <windows.h>
#include <cstdlib>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;
/// Szablon klasy
/**
* Funkcja z 2 argumentami szablonowymi, uniwersalna funckja, pozwoli nam sprawdza� kolizje miedzy roznymi obiektami
* Zwraca dana krawedz obiektu w pixelach
*/
template <class T1, class T2> bool isIntersecting6(T1& A, T2& B)
{
    return A.right() >= B.left() && A.left() <= B.right() && A.bottom() >= B.top() && A.top() <= B.bottom();
}
/// collisionTest6
/**
* Funckja z dwoma parametrami sprawdzajaca kolizje paletki i pileczki
* Sprawdza czy oba obiekty na siebie nachodza
* Zabawa grawitacja, losujemy w jaki sposob ma sie odbic pileczka od paletki
*/
bool collisionTest6(Paddle& paddle, Ball& ball)
{
    if (!isIntersecting6(paddle, ball))
        return false;

    ball.update(paddle); // Wywo�anie funkcji update z obiektem Paddle
    return true;

}
/// collisionTest6
/**
* Funckja z dwoma parametrami sprawdzajaca kolizje bloku i pileczki
* Sprawdza czy oba obiekty na siebie nachodza
* Przy odpowiednim warunku zniszcz blok
* Zmienne float z dwoma metodami klasy
* Instrukcja warunkowa, sprawdza w jaki sposob powinna odbic sie pilka
*/
bool collisionTest6(Block& block, Ball& ball)
{
    if (!isIntersecting6(block, ball))
        return false;

    block.destroy();

    float overlapLeft{ ball.right() - block.left() };
    float overlapRight{ block.right() - ball.left() };

    float overlapTop{ ball.bottom() - block.top() };
    float overlapBottom{ block.bottom() - ball.top() };

    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
    float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

    if (abs(minOverlapX) < abs(minOverlapY))
    {
        ballFromLeft ? ball.moveLeft() : ball.moveRight();
    }
    else
    {
        srand(time(NULL));
        int liczba = (rand() % 3) + 1;
        switch (liczba)
        {
        case 1:
            ballFromTop ? ball.moveUp() : ball.moveDown();
            break;
        case 2:
            ballFromTop ? ball.moveUpLeft() : ball.moveDownRight();
            break;
        case 3:
            ballFromTop ? ball.moveUpRight() : ball.moveDownLeft();
            break;
        }
    }
}
/// isGameOver6
/**
* Instrukcja warunkowa, sprawdza czy pilka spadla na dol planszy
*/
bool isGameOver6(Ball& ball)
{
    if (ball.bottom() >= 850) // Sprawd�, czy pi�ka znajduje si� poni�ej dolnej kraw�dzi okna
    {
        return true;
    }
    else
    {
        return false;
    }
}


/// Start
/**
* Obiekt klasy o dwoch parametrach
* Obiekt klasy o dwoch parametrach
* Stworzenie okna window
* Ustalenie limitu klatek na sekunde
* Stworzenie eventu
* Stworzenie zawartosci bloczkow, okreslaja ich liczbe i wielkosc
* Stworzenie wektora obiektu klasy
* Implementacja liczby blokow
* Petla for rysujaca blocki na ekranie
* Stworzenie tekstur i dodanie kilku tekstur tla
* Stworzenie obiektu klasy do rysowania obrazu na ekranie
* Ustawienie rozmiaru tla
* Buforowanie dzwieku oraz jego implementacja
* Wlaczenie muzyki
* Petla while, ktora dziala tylko przy wlaczonym oknie menu
* Wyczyszczenie okna, narysowanie obrazu na ekranie, dodanie opcji odpowiadajacej za funkcjonalnosc okna
* Warunek sprawdzajacy czy okno zostalo zamkniete
* Wywolanie funkcji update oraz collisionTest dla pilki i paletki\
* Warunek, ktory sprawdza czy gra zostala przegrana
* Zatrzymanie muzyki, wylaczenie okna
* Stworzenie nowego okna
* Buforowanie nowych dzwiekow i ich implementacja
* Dodanie opoznienia dzwieku i wlaczenie go
* Petla while sprawdza czy nowe okno jest otwarte
* Stworzenie eventu
* Petla while sprawdza czy nowy event jest wlaczony - jesli nie to wylacza okno, jesli jest to czekaj na przycisk i wylacz okno
* Wyczysc ekran, narysuj tlo i wyswietl
* Zwroc wartosc -1
* Petla for, dla ktorej argumentow automatycznie jest przypisany typ
* Warunek, ktory sprawdza kolizje bloku i pileczki, jesli nastapi zmniejsza liczbe blokow
* Automatyczny iterator, usuwa blok w przypadku spelnienia warunku
* Warunek sprawdza czy liczba blokow jest rowna zero
* Otworz nowe okno z tlem i komunikatem
* Zwroc wartosc 2
* Narysuj na ekranie pilke, paletke i bloki
*/
int Poziom6::Start()
{
    Ball ball(300, 400);
    Paddle paddle(400, 790);
    RenderWindow window(VideoMode(1100, 850), "Arcanoid - Poziom 6");
    window.setFramerateLimit(60);
    Event event;

    RectangleShape tloPrzegrana;
    tloPrzegrana.setSize(Vector2f(1100, 850));
    Texture mainPrzegrana;
    mainPrzegrana.loadFromFile("Textury/przegrana.png");
    tloPrzegrana.setTexture(&mainPrzegrana);

    RectangleShape tloWygrana;
    tloWygrana.setSize(Vector2f(1100, 850));
    Texture mainWygrana;
    mainWygrana.loadFromFile("Textury/wygrana.png");
    tloWygrana.setTexture(&mainWygrana);

    Sprite sprite11;
    Sprite sprite111;
    SoundBuffer buffer;
    buffer.loadFromFile("Audio/level6Audio.wav");
    Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    window.setFramerateLimit(80); // Frame rate pozwala na zwi�kszenie tempa rozgrywki w tym pr�dko�ci pi�ki czy paletki
    unsigned blocksX{ 8 }, blocksY{ 6 }, blockWidth{ 70 }, blockHeight{ 30 };
    vector<Block> blocks;
    int numberOfBlocks = blocksX * blocksY;
    int destroyedBlocks = 0; // Licznik zniszczonych blok�w
    bool isFlipped = false; // Flaga odwr�cenia ekranu

    for (int i = 0; i < blocksY; i++)
    {
        for (int j = 0; j < blocksX; j++)
        {
            // Tworzenie bloku tylko na co drugim polu
            if ((i + j) % 2 == 0)  // co drugie pole tworzy blok, reszta jest pusta
            {
                blocks.emplace_back((j + 1) * (blockWidth + 50), (i + 1) * (blockHeight + 25), blockWidth, blockHeight);
            }
        }
    }

    Texture Poziom6;
    Poziom6.loadFromFile("Textury/level6.png");
    Sprite sprite6;
    sprite6.setTexture(Poziom6);

    // Utw�rz widok
    View view = window.getDefaultView();

    while (window.isOpen())
    {
        window.clear();
        window.setView(view); // Ustaw widok
        window.draw(sprite6);
        window.pollEvent(event);

        if (event.type == Event::Closed)
        {
            window.close();
            break;
        }

        paddle.update();
        ball.update(paddle); // Przekazanie obiektu Paddle do funkcji update

        if (isGameOver6(ball) == true)
        {
            sound.stop();
            window.close();
            RenderWindow Super(VideoMode(1100, 850), "Przegrana");
            SoundBuffer bufferL;
            bufferL.loadFromFile("Audio/koniecAudio.wav");
            Sound soundL;
            soundL.setBuffer(bufferL);
            soundL.setPlayingOffset(sf::seconds(10.f));
            soundL.play();
            while (Super.isOpen())
            {
                Event aevent;
                while (Super.pollEvent(aevent))
                {
                    if (aevent.type == Event::Closed)
                    {
                        Super.close();
                    }
                    if (aevent.type == Event::KeyPressed)
                    {
                        if (aevent.key.code == Keyboard::Escape)
                        {
                            Super.close();
                        }
                    }
                }
                Super.clear();
                Super.draw(tloPrzegrana);
                Super.display();
            }
            exit(1);
            return 0;
        }

        for (auto& block : blocks)
        {
            if (collisionTest6(block, ball))
            {
                numberOfBlocks--;
                destroyedBlocks++; // Zwi�ksz licznik zniszczonych blok�w
                break;
            }
        }

        auto iterator = remove_if(begin(blocks), end(blocks), [](Block& block) {return block.isDestroyed(); });
        blocks.erase(iterator, end(blocks));

        // Sprawd�, czy liczba zniszczonych blok�w osi�gn�a 10, i odwr�� widok
        if (destroyedBlocks >= 10 && !isFlipped)
        {
            view.setCenter(view.getSize() / 2.0f);
            view.setRotation(180.0f); // Obr�� widok o 180 stopni
            isFlipped = true; // Ustaw flag� odwr�cenia ekranu
        }

        if (numberOfBlocks == 0)
        {
            sound.stop();
            window.close();
            RenderWindow Super(VideoMode(1100, 850), "Wygrana");
            SoundBuffer bufferW;
            bufferW.loadFromFile("Audio/wygranaAudio.wav");
            Sound soundW;
            soundW.setBuffer(bufferW);
            soundW.play();

            while (Super.isOpen())
            {
                Event aevent;
                while (Super.pollEvent(aevent))
                {
                    if (aevent.type == Event::Closed)
                    {
                        Super.close();
                    }
                    if (aevent.type == Event::KeyPressed)
                    {
                        if (aevent.key.code == Keyboard::Escape)
                        {
                            Super.close();
                        }
                    }
                }
                Super.clear();
                Super.draw(tloWygrana);
                Super.display();
            }
            return 7;
        }

        window.draw(ball);
        window.draw(paddle);

        for (auto& block : blocks)
        {
            window.draw(block);
        }

        window.display();
    }
}







