#include "Paddle.h"

// Konstruktor klasy Paddle
/**
 * @brief Konstruktor klasy Paddle
 *
 * @param t_X Pozycja X paletki
 * @param t_Y Pozycja Y paletki
 */
Paddle::Paddle(float t_X, float t_Y)
{
    shape.setPosition(t_X, t_Y);
    shape.setSize({ this->paddleWidth, this->paddleHeight });
    shape.setFillColor(Color::Green);
    shape.setOrigin(this->paddleWidth / 2.f, this->paddleHeight / 2.f);

    // Załaduj teksturę i ustaw ją dla kształtu paletki
    if (!paddleTexture.loadFromFile("Textury/paletka.png"))
    {
        // Obsłuż błąd ładowania tekstury       
        shape.setFillColor(Color::Red); // Przykładowa obsługa błędu
    }
    else
    {
        shape.setTexture(&paddleTexture);
    }
}

// Destruktor klasy Paddle
/**
 * @brief Destruktor klasy Paddle
 */
Paddle::~Paddle()
{
}

// Metoda rysująca paletkę na ekranie
/**
 * @brief Metoda rysująca paletkę na ekranie
 *
 * @param target Obiekt docelowy do rysowania
 * @param state Stan renderowania
 */
void Paddle::draw(RenderTarget& target, RenderStates state) const
{
    target.draw(this->shape, state);
}

// Metoda aktualizująca stan paletki
/**
 * @brief Metoda aktualizująca stan paletki
 */
void Paddle::update()
{
    shape.move(this->velocity);

    // Sprawdzenie, czy kontrolki są odwrócone
    if (reverseControls)
    {
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) && this->right() < 1100)
        {
            velocity.x = paddleVelocity;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && this->left() > 0)
        {
            velocity.x = -paddleVelocity;
        }
        else
        {
            velocity.x = 0;
        }
    }
    else
    {
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) && this->left() > 0)
        {
            velocity.x = -paddleVelocity;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && this->right() < 1100)
        {
            velocity.x = paddleVelocity;
        }
        else
        {
            velocity.x = 0;
        }
    }
}

// Metoda przesuwająca paletkę w lewo
/**
 * @brief Metoda przesuwająca paletkę w lewo
 */
void Paddle::moveLeft()
{
    velocity.x = -paddleVelocity;
}

// Metoda przesuwająca paletkę w prawo
/**
 * @brief Metoda przesuwająca paletkę w prawo
 */
void Paddle::moveRight()
{
    velocity.x = paddleVelocity;
}

// Metoda ustawiająca odwrócone kontrolki
/**
 * @brief Metoda ustawiająca odwrócone kontrolki
 *
 * @param reverse Flaga określająca, czy kontrolki mają być odwrócone
 */
void Paddle::setReverseControls(bool reverse)
{
    reverseControls = reverse;
}

// Metoda zwracająca lewą krawędź paletki
/**
 * @brief Metoda zwracająca lewą krawędź paletki
 *
 * @return float Lewa krawędź paletki
 */
float Paddle::left() const
{
    return this->shape.getPosition().x - shape.getSize().x / 2.f;
}

// Metoda zwracająca prawą krawędź paletki
/**
 * @brief Metoda zwracająca prawą krawędź paletki
 *
 * @return float Prawa krawędź paletki
 */
float Paddle::right() const
{
    return this->shape.getPosition().x + shape.getSize().x / 2.f;
}

// Metoda zwracająca górną krawędź paletki
/**
 * @brief Metoda zwracająca górną krawędź paletki
 *
 * @return float Górna krawędź paletki
 */
float Paddle::top() const
{
    return this->shape.getPosition().y - shape.getSize().y / 2.f;
}

// Metoda zwracająca dolną krawędź paletki
/**
 * @brief Metoda zwracająca dolną krawędź paletki
 *
 * @return float Dolna krawędź paletki
 */
float Paddle::bottom() const
{
    return this->shape.getPosition().y + shape.getSize().y / 2.f;
}

// Metoda zwracająca pozycję paletki
/**
 * @brief Metoda zwracająca pozycję paletki
 *
 * @return Vector2f Pozycja paletki
 */
Vector2f Paddle::getPosition() const
{
    return shape.getPosition();
}

// Metoda zwracająca prędkość paletki
/**
 * @brief Metoda zwracająca prędkość paletki
 *
 * @return Vector2f Prędkość paletki
 */
Vector2f Paddle::getVelocity() const
{
    return velocity;
}

// Metoda zwracająca szerokość paletki
/**
 * @brief Metoda zwracająca szerokość paletki
 *
 * @return float Szerokość paletki
 */
float Paddle::getWidth() const
{
    return shape.getSize().x;
}

// Metoda zwracająca wysokość paletki
/**
 * @brief Metoda zwracająca wysokość paletki
 *
 * @return float Wysokość paletki
 */
float Paddle::getHeight() const
{
    return shape.getSize().y;
}

// Metoda ustawiająca rozmiar paletki
/**
 * @brief Metoda ustawiająca rozmiar paletki
 *
 * @param size Nowy rozmiar paletki
 */
void Paddle::setSize(const Vector2f& size)
{
    shape.setSize(size);
}

// Metoda ustawiająca prędkość paletki
/**
 * @brief Metoda ustawiająca prędkość paletki
 *
 * @param newVelocity Nowa prędkość paletki
 */
void Paddle::setVelocity(const Vector2f& newVelocity)
{
    velocity = newVelocity;
}
