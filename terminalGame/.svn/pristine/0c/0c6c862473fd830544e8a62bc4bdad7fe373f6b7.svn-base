#ifndef _HT_H_
#define _HT_H_

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#define WIDTH  12
#define HEIGHT 22

typedef enum {
    I = 0,
    J,
    L,
    O,
    S,
    T,
    Z
} blockShape;

typedef struct htPos
{
    int x;
    int y;
} htPos;

typedef struct htBlock
{
    blockShape      mShape;
    htPos           mPosition;
    int             mRotation;
    htPos           mFill[4];
    int             mIsEnded;
    pthread_mutex_t mMtx;
} htBlock;

extern int      gQuit;
extern char     gBackground[HEIGHT][WIDTH];
extern htBlock  gBlock;
extern char     gForeground[HEIGHT][WIDTH];

#endif
