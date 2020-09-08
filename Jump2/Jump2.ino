#include <Arduboy2.h>

Arduboy2 arduboy;

constexpr float initVelocity[5] = { 0, 0.25, 0.5, 1, 2 };

float velocity;

float maxJumpHeight;

float charX, charY;

bool jumping = false;
bool falling = false;

void setup()
{
    arduboy.begin();

    charX = 64;
    charY = 62;

    maxJumpHeight = 50;

    velocity = initVelocity[0];
}

void loop()
{
    if(!arduboy.nextFrame()) return;
    arduboy.pollButtons();

    arduboy.clear();

    arduboy.drawPixel(charX, charY);

    if(charY >= 62)
    {
        charY = 62;
        velocity = initVelocity[0];
        jumping = false;
        falling = false;
    }

    if(velocity >= 0.25 && velocity <= 2) falling = true;

    if(arduboy.justPressed(UP_BUTTON) && charY > 0 && !jumping)
    {
        velocity = -initVelocity[3];
        jumping = true;
    }

    if(arduboy.pressed(RIGHT_BUTTON) && charX < 126) charX += 1;
    if(arduboy.pressed(LEFT_BUTTON) && charX > 2) charX -= 1;

    if(jumping && charY < maxJumpHeight) velocity = initVelocity[3];
    if(jumping && charY == maxJumpHeight + 5) velocity = initVelocity[2];

    if(jumping && charY == maxJumpHeight + 5) velocity = -initVelocity[2];
    if(jumping && charY == maxJumpHeight + 10) velocity = -initVelocity[3];

    charY += velocity;

    arduboy.setCursor(0, 0);
    arduboy.print(F("Y:"));
    arduboy.print(charY);
    
    arduboy.print(F("X:"));
    arduboy.print(charX);

    arduboy.print(F("V:"));
    arduboy.print(velocity);

    arduboy.setCursor(0, 10);
    arduboy.print(F("Jump:"));
    if(!jumping) arduboy.print(F("False"));
    else arduboy.print(F("True"));

    arduboy.setCursor(0, 20);
    arduboy.print(F("Fall:"));
    if(!falling) arduboy.print(F("False"));
    else arduboy.print(F("True"));

    arduboy.display();
}