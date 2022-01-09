class Player
{
public:
    sf::Texture t2;
    sf::Sprite s2;
    int life;
    float moveSpeed;
    sf::Vector2f velocity;
    sf::RectangleShape rectangle;
    friend class Game;
    Player();
    void checkPosition();
    void rectPosition();
};
Player::Player():moveSpeed(1.f)
{
    life = 1;
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
    // std::cout << s2.getPosition().x << std::endl;
    // std::cout << s2.getPosition().y << std::endl;
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