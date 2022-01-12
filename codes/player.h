class Player
{
public:
    sf::Texture t2;
    sf::Sprite s2;
    int life;
    float moveSpeed;
    sf::Vector2f velocity;
    sf::RectangleShape rectangle;
    bool hit;
    friend class Game;
    Player();
    void checkPosition();
    void rectPosition();
};
Player::Player():moveSpeed(1.f)
{
    life = 3;
    hit = false;
    std::string fileName = "resources/Newbike4.png";
    t2.loadFromFile(fileName, sf::IntRect(30,370,450,740));
    s2.setTexture(t2);
    s2.setPosition(sf::Vector2f(200,275));
    rectangle.setSize(sf::Vector2f(220, 25));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(5);
    rectangle.setPosition(400, 600);
}
void Player::checkPosition()
{
    if(s2.getGlobalBounds().left < 0)
        s2.setPosition(0, s2.getPosition().y);
    if(s2.getGlobalBounds().left + s2.getGlobalBounds().width > 2950)
        s2.setPosition(2950 - s2.getGlobalBounds().width, s2.getPosition().y);
    if(s2.getPosition().y < 275)
        s2.setPosition(s2.getPosition().x, 275);
    if(s2.getGlobalBounds().top + s2.getGlobalBounds().height > 1250)
        s2.setPosition(s2.getPosition().x, 1250 - s2.getGlobalBounds().height);
}
void Player::rectPosition()
{
    if(rectangle.getGlobalBounds().left < 0)
        rectangle.setPosition(0, rectangle.getPosition().y);
    if(rectangle.getGlobalBounds().left + rectangle.getGlobalBounds().width > 2950)
        rectangle.setPosition(2950 - rectangle.getGlobalBounds().width, rectangle.getPosition().y);
    if(rectangle.getPosition().y < 600)
        rectangle.setPosition(rectangle.getPosition().x, 600);
    if(rectangle.getGlobalBounds().top + rectangle.getGlobalBounds().height > 1200)
        rectangle.setPosition(rectangle.getPosition().x, 1200 - rectangle.getGlobalBounds().height);
}