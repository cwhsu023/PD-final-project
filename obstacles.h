class Obstacles{
public:
    int posX, posY, c;
    sf::Texture obsTexture;
    sf::Sprite obsSprite;
    sf::CircleShape circle;
    sf::Vector2f velocity;
    Obstacles(int posX, int posY, int speedX, int speedY);
    void setCircle(int x, int y);
    bool collision(Player &player);
    void move(float bikeSpeed);
};
Obstacles::Obstacles(int X, int Y, int speedX, int speedY):c(1)
{
    this->velocity.x = speedX;
    this->velocity.y = speedY;
    this->posX = X;
    this->posY = Y;
    this->obsTexture.loadFromFile("resources/dove.png", sf::IntRect(1300,460,980, 750));
    this->obsSprite.setTexture(this->obsTexture);
    this->obsSprite.setScale(sf::Vector2f(0.15f, 0.15f));
    this->obsSprite.setPosition(sf::Vector2f(posX, posY));
    setCircle(posX, posY+20);
}
void Obstacles::setCircle(int x, int y)
{
    this->circle.setRadius(40);
    this->circle.setFillColor(sf::Color::Transparent);
    this->circle.setOutlineColor(sf::Color::Red);
    this->circle.setOutlineThickness(5);
    this->circle.setPosition(x, y);
}
bool Obstacles::collision(Player &player)
{   
    sf::FloatRect playerBounds = player.rectangle.getGlobalBounds();
    sf::FloatRect obsBounds = this->obsSprite.getGlobalBounds();
    if( playerBounds.intersects(obsBounds))
    {
        std::cout << "撞到鴿子了" << std::endl;
        player.hit = true;
        player.life -= 1;
        std::cout << player.life << std::endl;
        return true;
    }
    return false;
}
void Obstacles::move(float bikeSpeed)
{
    sf::Vector2f speed;
    speed.x = this->velocity.x - bikeSpeed;
    this->obsSprite.move(speed);
    this->circle.move(speed);
}