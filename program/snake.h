

#ifndef __SNAKE_H__
#define __SNAKE_H__


//******************************************************
//* headers
//******************************************************
#include <lcd1602.h>
//******************************************************




//******************************************************
//******************************************************
//******************************************************
#define CONST_SNAKE_LEN                         6
#define CONST_SNAKE_RAM0                        4
#define CONST_SNAKE_RAM1                        5
#define CONST_SNAKE_RAM2                        6
#define CONST_SNAKE_RAM3                        7
//******************************************************



extern xdata char snake[CONST_SNAKE_LEN];
extern xdata char cgram[32];
extern xdata char snake_tail;







//******************************************************
//******************************************************
//******************************************************
void SnakeHeadDir(char *sh, char *hd);
void SnakeMove (char *snake, char dir);
void SnakeLcdRefresh (char *snake_tail, char *snake_head, char *pcgram);
void SnakeInit (char *snake, char *pcgram);
//******************************************************








#endif
