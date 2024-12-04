/** \file Poziom1.h
* Odpowiada za pierwszy poziom
*/
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ball.h"
#include "Paddle.h"
#include "Block.h"
#include "MainMenu.h"
#include "Poziom1.h"
#include "Buff.h"
#include <windows.h>
#include <cstdlib>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

/// Szablon klasy
/**
* Funkcja z 2 argumentami szablonowymi, uniwersalna funckja, pozwoli nam sprawdzać kolizje miedzy roznymi obiektami
* Zwraca dana krawedz obiektu w pixelach
*/



/// collisionTest1
/**
* Funckja z dwoma parametrami sprawdzajaca kolizje paletki i pileczki
* Sprawdza czy oba obiekty na siebie nachodza
* Zabawa grawitacja, losujemy w jaki sposob ma sie odbic pileczka od paletki
*/
bool collisionTestPaddleBall(Paddle& paddle, Ball& ball)
{
    if (!isIntersecting1(paddle, ball))
        return false;

    ball.update(paddle); // Wywołanie funkcji update z obiektem Paddle
    return true;
}



/// collisionTest1
/**
* Funckja z dwoma parametrami sprawdzajaca kolizje bloku i pileczki
* Sprawdza czy oba obiekty na siebie nachodza
* Przy odpowiednim warunku zniszcz blok
* Zmienne float z dwoma metodami klasy
* Instrukcja warunkowa, sprawdza w jaki sposob powinna odbic sie pilka
*/
bool collisionTestBlockBall(Block& block, Ball& ball, vector<Buff>& buffs)
{
    if (!isIntersecting1(block, ball))
        return false;

    // Sprawdzenie, z której strony nastąpiła kolizja
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
        ballFromTop ? ball.moveUp() : ball.moveDown();
    }

    block.destroy();

    // Generowanie buffów z 25% szansą
    if (rand() % 4 == 0)
    {
        BuffType type = static_cast<BuffType>(rand() % static_cast<int>(BuffType::Count)); // Losowanie typu buffa
        buffs.emplace_back(block.getPosition().x, block.getPosition().y, type);
    }

    return true;
}

bool collisionTestBuffBall(Buff& buff, Ball& ball, Paddle& paddle, bool& reverseControls, float& paddleSpeedMultiplier, int& extraLives, float& scoreMultiplier, RenderWindow& window)
{
    if (!isIntersecting1(buff, ball))
        return false;

    // Zastosuj buff
    switch (buff.getType())
    {
    case BuffType::SpeedUp:
        ball.setVelocity(ball.getVelocity() * 1.5f);
        break;
    case BuffType::SpeedDown:
        ball.setVelocity(ball.getVelocity() * 0.5f);
        break;
    case BuffType::SizeUp:
        paddle.setSize(Vector2f(paddle.getWidth() * 1.5f, paddle.getHeight()));
        break;
    case BuffType::SizeDown:
        paddle.setSize(Vector2f(paddle.getWidth() * 0.5f, paddle.getHeight()));
        break;
    case BuffType::ReverseControls:
        reverseControls = !reverseControls;
        paddle.setReverseControls(reverseControls);
        break;
    case BuffType::BallSpeedUp:
        ball.setVelocity(ball.getVelocity() * 1.2f);
        break;
    case BuffType::PaddleSpeedUp:
        paddleSpeedMultiplier *= 1.2f;
        break;
    case BuffType::ScreenShake:
        // Implementacja trzęsienia ekranu
        window.setView(View(FloatRect(0, 0, 1100, 850)));
        window.setView(View(FloatRect(rand() % 10 - 5, rand() % 10 - 5, 1100, 850)));
        break;
    case BuffType::InvisibleBall:
        ball.setInvisible(true);
        break;
    case BuffType::DoubleBall:
        // Implementacja podwójnej piłki
        break;
    case BuffType::BallSizeUp:
        ball.setRadius(ball.getRadius() * 1.5f);
        break;
    case BuffType::BallSizeDown:
        ball.setRadius(ball.getRadius() * 0.5f);
        break;
    case BuffType::PaddleSpeedDown:
        paddleSpeedMultiplier *= 0.5f;
        break;
    case BuffType::ExtraLife:
        extraLives++;
        break;
    case BuffType::ScoreMultiplier:
        scoreMultiplier *= 2.0f;
        break;
    }

    buff.update(); // Aktualizacja stanu buffa po zastosowaniu
    return true;
}




/// isGameOver1
/**
* Instrukcja warunkowa, sprawdza czy pilka spadla na dol planszy
*/
bool isGameOver1(Ball& ball)
{
    if (ball.bottom() >= 850)
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
int Poziom1::Start()
{
    Ball ball(300, 400);
    Paddle paddle(400, 790);
    RenderWindow window(VideoMode(1100, 850), "Arcanoid - Poziom 1");

    window.setFramerateLimit(80);
    Event event;
    unsigned blocksX{ 8 }, blocksY{ 6 }, blockWidth{ 70 }, blockHeight{ 30 };
    vector<Block> blocks;
    vector<Buff> buffs;
    int numberOfBlocks = blocksX * blocksY;
    bool reverseControls = false;
    float paddleSpeedMultiplier = 1.0f;
    bool invisibleBall = false;
    int extraLives = 3;
    float scoreMultiplier = 1.0f;

    for (int i = 0; i < blocksY; i++)
    {
        for (int j = 0; j < blocksX; j++)
        {
            if ((i + j) % 2 == 0)
            {
                blocks.emplace_back((j + 1) * (blockWidth + 50), (i + 1) * (blockHeight + 25), blockWidth, blockHeight);
            }
        }
    }

    numberOfBlocks /= 2;

    Texture Poziom1;
    Poziom1.loadFromFile("Textury/level1.png");

    Sprite sprite1;
    sprite1.setTexture(Poziom1);

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
    buffer.loadFromFile("Audio/level1Audio.wav");
    Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    while (window.isOpen())
    {
        window.clear();
        window.draw(sprite1);
        window.pollEvent(event);

        if (event.type == Event::Closed)
        {
            window.close();
            break;
        }

        paddle.update();
        ball.update(paddle); // Wywołanie metody update z obiektem Paddle

        if (isGameOver1(ball) == true)
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
            return -1;
        }

        if (collisionTestPaddleBall(paddle, ball))
        {
            // Kolizja z paletką
        }

        for (auto& block : blocks)
        {
            if (collisionTestBlockBall(block, ball, buffs))
            {
                numberOfBlocks--;
                break;
            }
        }

        auto iterator = remove_if(begin(blocks), end(blocks), [](Block& block) { return block.isDestroyed(); });
        blocks.erase(iterator, end(blocks));

        if (numberOfBlocks == 0)
        {
            sound.stop();
            window.close();
            return 2;
        }

        // Aktualizacja i rysowanie buffów
        for (auto& buff : buffs)
        {
            buff.update();
            window.draw(buff);

            if (collisionTestBuffBall(buff, ball, paddle, reverseControls, paddleSpeedMultiplier, extraLives, scoreMultiplier, window))
            {
                // Buff został zastosowany, więc można go usunąć
                buff.update();
            }
        }

        buffs.erase(remove_if(buffs.begin(), buffs.end(), [](Buff& buff) { return !buff.isActive(); }), buffs.end());

        paddle.setVelocity(paddle.getVelocity() * paddleSpeedMultiplier);

        window.draw(ball);
        window.draw(paddle);

        for (auto& block : blocks)
        {
            window.draw(block);
        }

        window.display();
    }
}




