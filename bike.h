class Bike
{
private:
    // int animateSpeed ;
    float speedControl ;

public:
    Bike();
    // ~Bike();
    float bikeSpeed();
    void bikeAnimationSpeed(float& speedControler);
    void bikeAccelerating();
    void bikeDecelerating();
    void testbikeAccelerating();
    //bike spped : smooth accelerating 
};

Bike::Bike()
{
    // this -> animatedSpeed = 0.01 ;
    speedControl = 0.01 ;
}
float Bike::bikeSpeed()
{
    return speedControl ;
}
void Bike::testbikeAccelerating()
{
    if(this -> speedControl < 0)
        this -> speedControl = 0;
    else if(this -> speedControl >=0 && this -> speedControl <= 0.05)
        this -> speedControl += 0.003 ;
    else if(this -> speedControl > 0.05 && this -> speedControl <= 0.08) 
        this -> speedControl += 0.004 ;
    else if(this -> speedControl > 0.08 && this -> speedControl <= 0.15)
        this -> speedControl += 0.002 ;
    else if(this -> speedControl >= 0.15 && this -> speedControl <= 0.2)
        this -> speedControl += 0.01 ;
    else if(this -> speedControl > 0.2 )
        this -> speedControl = 0.2 ;
}
void Bike::bikeAccelerating()
{
    if(this -> speedControl < 0)
        this -> speedControl = 0;
    else if(this -> speedControl >=0 && this -> speedControl <= 0.05)
        this -> speedControl += 0.0010 ;
    else if(this -> speedControl > 0.05 && this -> speedControl <= 0.08) 
        this -> speedControl += 0.0017 ;
    else if(this -> speedControl > 0.08 && this -> speedControl <= 0.15)
        this -> speedControl += 0.0030 ;
    else if(this -> speedControl >= 0.15 && this -> speedControl <= 0.2)
        this -> speedControl += 0.01 ;
    else if(this -> speedControl > 0.2 )
        this -> speedControl = 0.2 ;
}
void Bike::bikeDecelerating()
{
    if(this -> speedControl < 0)
        this -> speedControl = 0;
    else if(this -> speedControl >=0 && this -> speedControl <= 0.15)
        this -> speedControl = 0.05 ;
    else if(this -> speedControl >= 0.15 )
        this -> speedControl -= 0.08 ;
}
