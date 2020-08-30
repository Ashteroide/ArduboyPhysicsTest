#include <Arduboy2.h>

Arduboy2 arduboy;

constexpr int initVelocityY[3] = { 1, 0, -1 };

int velocityY;

int charX, charY;
int maxJumpHeight;

bool jumping = false;

void setup()
{
    arduboy.begin();

    charX = 20;
    charY = 61;

    maxJumpHeight = 10;

    velocityY = initVelocityY[1];
}

void loop()
{
    if(!arduboy.nextFrame()) return;
    arduboy.pollButtons();

    arduboy.clear();

    arduboy.drawPixel(charX, charY);
    if(arduboy.pressed(RIGHT_BUTTON) && charX < 126) charX += 1;
    if(arduboy.pressed(LEFT_BUTTON) && charX > 0) charX -= 1;

    if(charY >= 62)
    {
        jumping = false;
        charY = 62;
    }

    if(arduboy.justPressed(UP_BUTTON) && charY > 0 && !jumping)
    {
        velocityY = initVelocityY[2];
        jumping = true;
    }
    if(charY < maxJumpHeight) velocityY = initVelocityY[0];

    charY += velocityY;

    arduboy.setCursor(0, 0);
    arduboy.print(charX);
    arduboy.print(F(","));
    arduboy.print(charY);

    arduboy.display();
}