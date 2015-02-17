//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// height and width of paddle
#define PADDLE_H 10
#define PADDLE_W 60

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
GLabel initLives(GWindow window);
void updateLives(GWindow window, GLabel livesLabel, int lives);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;
    GLabel livesLabel = initLives(window);

    // number of points initially
    int points = 0;
    
    // initial velocity
    double velocity_v = drand48() + 2;
    double velocity_h = (drand48() - 0.5) * 3;
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // move circle along x-axis
        move(ball, velocity_h, velocity_v);

        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocity_h = -velocity_h;
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            velocity_h = -velocity_h;
        }
        
        //bounce off top of window
        else if (getY(ball)<=0)
        {
            velocity_v = -velocity_v;
            
        }

        //hit bottom of window
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            
            setLocation(ball, WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS);
            velocity_v = drand48() + 2;
            velocity_h = (drand48() - 0.5) * 3;
            lives--;
            updateLives(window, livesLabel, lives);
            waitForClick();
        }
        
        
        //check for collision with objects
        GObject object = detectCollision(window, ball);
        
        if (object == paddle)
            {
                velocity_v = -velocity_v * (1 + drand48() / 20);
            }
        
        //if ball collides with brick, change direction and remove brick
        if ((object != NULL) && object != paddle)
        {
            if (strcmp(getType(object), "GRect") == 0)
            {
                velocity_v = -velocity_v;
                removeGWindow(window, object);
                bricks--;
                points = points + 1 * (60 - bricks) / 5;
                updateScoreboard(window, label, points);
            }
        }        
        
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);
        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows cursor's horizontal location
                double x = getX(event) - getWidth(paddle) / 2;
                setLocation(paddle, x, HEIGHT-100);
            }
        }
        
        
         // linger before moving again
        pause(10);
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int gap = 7;
    int brick_h = 10;
    int brick_w = (WIDTH - gap * (COLS +1) ) / COLS;
    
    //grid is COLS by ROWS in size
    for (int j = 0; j < ROWS; j++)
        {
        for (int i = 0; i < COLS; i++)
            {    
                GRect brick = newGRect( gap * (i + 1) + i * brick_w , 40 + j * (brick_h + gap), brick_w, brick_h);
                setColor(brick, "RED");
                setFilled(brick, true);
                add(window, brick);
            }
        }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS, 2 * RADIUS, 2 * RADIUS);
    setColor(ball, "GREEN");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect((WIDTH-PADDLE_W)/2 , HEIGHT-100, PADDLE_W, PADDLE_H);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    //printf("paddle made\n");
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-36");
    setColor(label, "LIGHTGRAY");
    add(window, label);
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Instantiates, configures, and returns label for lives.
 */
GLabel initLives(GWindow window)
{
    // initiate with LIVES number of lives
    GLabel livesLabel = newGLabel("");
    char s[12];
    sprintf(s, "Lives: %i", LIVES);
    setLabel(livesLabel, s);
    setFont(livesLabel, "SansSerif-20");
    add(window, livesLabel);
    
    // center label in top of window
    double x = (getWidth(window) - getWidth(livesLabel)) / 2;
    setLocation(livesLabel, x, 20);
    return livesLabel;
}

/**
 * Updates lives label, keeping it centered in window.
 */
void updateLives(GWindow window, GLabel livesLabel, int lives)
{
    // update label
    char s[12];
    sprintf(s, "Lives: %i", lives);
    setLabel(livesLabel, s);

    // center label in top of window
    double x = (getWidth(window) - getWidth(livesLabel)) / 2;
    //double y = (getHeight(window) - getHeight(livesLabel)) / 2;
    setLocation(livesLabel, x, 20);
}



/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }
    
    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
