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

// Funkcja sprawdzająca kolizję między paletką a piłką
bool collisionTestPaddleBall(Paddle& paddle, Ball& ball)
{
    if (!isIntersecting1(paddle, ball))
        return false;

    ball.update(paddle);
    return true;
}

// Funkcja sprawdzająca kolizję między blokiem a piłką
bool collisionTestBlockBall(Block& block, Ball& ball, vector<Buff>& buffs)
{
    if (!isIntersecting1(block, ball))
        return false;

    // Obliczanie nakładania się piłki z blokiem
    float overlapLeft{ ball.right() - block.left() };
    float overlapRight{ block.right() - ball.left() };
    float overlapTop{ ball.bottom() - block.top() };
    float overlapBottom{ block.bottom() - ball.top() };

    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
    float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

    // Aktualizacja kierunku ruchu piłki w zależności od kolizji
    if (abs(minOverlapX) < abs(minOverlapY))
    {
        ballFromLeft ? ball.moveLeft() : ball.moveRight();
    }
    else
    {
        ballFromTop ? ball.moveUp() : ball.moveDown();
    }

    Vector2f blockPosition = block.getPosition();
    block.destroy();

    // 25% szans na spawnienie buffa
    if (rand() % 4 == 0)
    {
        BuffType type = static_cast<BuffType>(rand() % static_cast<int>(BuffType::ScoreMultiplier) + 1); // Losowanie typu buffa
        std::cout << static_cast<int>(type) << std::endl;
        buffs.emplace_back(blockPosition.x, blockPosition.y, type); // Dodanie buffa do wektora
    }

    return true;
}

// Funkcja sprawdzająca kolizję między buffem a paletką
bool collisionTestBuffPaddle(Buff& buff, Paddle& paddle, Ball& ball, bool& reverseControls, float& paddleSpeedMultiplier, float& scoreMultiplier)
{
    if (!isIntersecting1(buff, paddle))
        return false;

    buff.activate(paddle, ball, reverseControls, paddleSpeedMultiplier, scoreMultiplier);
    return true;
}

// Funkcja sprawdzająca, czy gra się skończyła (piłka spadła poniżej dolnej krawędzi)
bool isGameOver1(Ball& ball)
{
    return ball.bottom() >= 850;
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

// Funkcja startowa poziomu 1
int Poziom1::Start()
{
    // Inicjalizacja obiektów gry
    Ball ball(550, 425);
    Paddle paddle(400, 790);
    RenderWindow window(VideoMode(1100, 850), "Arcanoid - Poziom 1");

    // Ustawienia okna gry
    window.setFramerateLimit(80);
    Event event;
    unsigned blocksX{ 8 }, blocksY{ 6 }, blockWidth{ 70 }, blockHeight{ 30 };
    vector<Block> blocks;
    vector<Buff> buffs;
    int numberOfBlocks = blocksX * blocksY;
    bool reverseControls = false;
    float paddleSpeedMultiplier = 1.0f;
    float scoreMultiplier = 1.0f;

    // Ładowanie tekstury dla bloków
    Texture blockTexture;
    blockTexture.loadFromFile("Textury/platforma.png");

    // Tworzenie bloków
    for (unsigned i = 0; i < blocksY; i++)
    {
        for (unsigned j = 0; j < blocksX; j++)
        {
            Block block((j + 1) * (blockWidth + 50), (i + 1) * (blockHeight + 25), blockWidth, blockHeight);
            block.getShape().setTexture(&blockTexture); // Użyj metody getShape
            blocks.push_back(block);
        }
    }

    // Ładowanie tekstur
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

    // Ładowanie dźwięków
    SoundBuffer buffer;
    buffer.loadFromFile("Audio/level1Audio.wav");
    Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    // Główna pętla gry
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

        // Aktualizacja stanu paletki i piłki
        paddle.update();
        ball.update(paddle);

        // Sprawdzenie, czy gra się skończyła
        if (isGameOver1(ball))
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

        // Sprawdzenie kolizji piłki z paletką
        if (collisionTestPaddleBall(paddle, ball))
        {
            // Kolizja z paletką
        }

        // Sprawdzenie kolizji piłki z blokami
        for (auto& block : blocks)
        {
            if (collisionTestBlockBall(block, ball, buffs))
            {
                numberOfBlocks--;
                break;
            }
        }

        // Usunięcie zniszczonych bloków
        auto iterator = remove_if(begin(blocks), end(blocks), [](Block& block) { return block.isDestroyed(); });
        blocks.erase(iterator, end(blocks));

        // Sprawdzenie, czy wszystkie bloki zostały zniszczone
        if (numberOfBlocks == 0)
        {
            sound.stop();
            window.close();
            return 2;
        }

        // Aktualizacja i rysowanie buffów
        for (auto it = buffs.begin(); it != buffs.end();)
        {
            it->fall();
            window.draw(*it);

            if (collisionTestBuffPaddle(*it, paddle, ball, reverseControls, paddleSpeedMultiplier, scoreMultiplier))
            {
                it = buffs.erase(it); // Usuń buff po aktywacji
            }
            else
            {
                ++it;
            }
        }

        // Usunięcie buffów, które spadły poniżej dolnej krawędzi
        buffs.erase(remove_if(buffs.begin(), buffs.end(), [](Buff& buff) {
            buff.updateEffect();
            return buff.top() > 850;
            }), buffs.end());

        // Resetowanie efektów buffów, które się skończyły
        for (auto it = buffs.begin(); it != buffs.end();)
        {
            if (it->isEffectEnded())
            {
                it->resetEffect(paddle, ball, reverseControls, paddleSpeedMultiplier, scoreMultiplier);
                it = buffs.erase(it);
            }
            else
            {
                ++it;
            }
        }

        // Aktualizacja prędkości paletki
        paddle.setVelocity(paddle.getVelocity() * paddleSpeedMultiplier);

        // Rysowanie obiektów gry
        window.draw(ball);
        window.draw(paddle);

        for (auto& block : blocks)
        {
            window.draw(block);
        }

        window.display();
    }
    return 0;
}
