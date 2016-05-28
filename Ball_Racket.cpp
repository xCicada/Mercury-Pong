//
// Created by Adonis on 16/04/2014.
//

using namespace sf;

// Detect collision between a ball and a racket
bool collisionBR(const CircleShape& ball, const RectangleShape& racket) // BR means Ball Racket
{
    FloatRect r1 = ball.getGlobalBounds();
    FloatRect r2 = racket.getGlobalBounds();

    return r1.intersects(r2);
}



// Detect collision between 2 balls
bool collisionBB(const CircleShape& ball, const CircleShape& ball2) // BB means Ball Ball
{
    FloatRect r1 = ball.getGlobalBounds();
    FloatRect r2 = ball2.getGlobalBounds();

    return r1.intersects(r2);
}



// Set the speed limit for the ball
void speedLimit(Vector2f& move, const int nbBall)
{
    unsigned short int max;

    if(nbBall > 2)
        max = 10;
    else
        max = 30;

    if(move.x > 0)
    {
        if(move.x > max)
            move.x = max;
        else if(move.x < 5)
            move.x = 5;
    }
    else
    {
        if(move.x > -5)
            move.x = -5;
        else if(move.x < -max)
            move.x = -max;
    }

    if(move.y > max)
        move.y = max;
    else if(move.y < -max)
        move.y = -max;
}



// Set the ball's trajectory
void trajectory(float& moveY, const CircleShape& ball, const RectangleShape& racket)
{
    moveY = ball.getPosition().y - racket.getPosition().y;
}



// Set the first ball's direction
void startDirection(Vector2f& move)
{
    switch(rand()%4)
    {
        case 0:
            move.x = 5, move.y = 5;
            break;

        case 1:
            move.x = -5, move.y = 5;
            break;

        case 2:
            move.x = 5, move.y = -5;
            break;

        case 3:
            move.x = -5, move.y = -5;
            break;
    }
}



// Set the racket's position when it collides with a wall
void wallCollision(sf::RectangleShape& racket)
{
    if(racket.getPosition().y < racket.getSize().y/2)
        racket.setPosition(racket.getPosition().x, racket.getSize().y/2);
    else if(racket.getPosition().y > SCREEN_HEIGHT-racket.getSize().y/2)
        racket.setPosition(racket.getPosition().x, SCREEN_HEIGHT-racket.getSize().y/2);
}