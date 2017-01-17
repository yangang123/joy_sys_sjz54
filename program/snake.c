


#include "snake.h"






xdata char snake[CONST_SNAKE_LEN];
xdata char cgram[32];
xdata char snake_tail;







// input : snake header pointer
// format : ccc_lllll, coloumx3_linex5
void SnakeHeadDir(char *sh, char *hd)
{
    // up & downt
    if (((*sh) & 0x1F) == 0x00)         // top, left
    {
        hd[0] = ((*sh) & 0xE0) | 0x0F;
        hd[1] = ((*sh) & 0xE0) | 0x01;
    }
    else if (((*sh) & 0x1F) == 0x10)    // top, right
    {
        hd[0] = ((*sh) & 0xE0) | 0x1F;
        hd[1] = ((*sh) & 0xE0) | 0x11;
    }
    else if (((*sh) & 0x1F) == 0x0F)    // bottom, left
    {
        hd[0] = ((*sh) & 0xE0) | 0x0E;
        hd[1] = ((*sh) & 0xE0) | 0x00;
    }
    else if (((*sh) & 0x1F) == 0x1F)    // bottom, right
    {
        hd[0] = ((*sh) & 0xE0) | 0x1E;
        hd[1] = ((*sh) & 0xE0) | 0x10;
    }
    else                                // middle line
    {
        hd[0] = ((*sh) - 1);
        hd[1] = ((*sh) + 1);
    }


    // left & right
    if (((*sh) & 0xE0) == 0x00)
    {
        if (((*sh) & 0x10))             // left high
        {
            hd[2] = (0x80 | ((*sh) & 0x0F));
            hd[3] = (0x20 | ((*sh) & 0x1F));
        }
        else                            // left low
        {
            hd[2] = (0x90 | ((*sh) & 0x1F));
            hd[3] = (0x20 | ((*sh) & 0x1F));
        }
    }
    else if (((*sh) & 0xE0) == 0x80)
    {
        if (((*sh) & 0x10))             // right high
        {
            hd[2] = (0x60 | ((*sh) & 0x1F));
            hd[3] = (0x00 | ((*sh) & 0x0F));
        }
        else                            // right low
        {
            hd[2] = (0x60 | ((*sh) & 0x1F));
            hd[3] = (0x10 | ((*sh) & 0x1F));
        }
    }
    else                                // middle coloum
    {
        hd[2] = (*sh) - 0x20;
        hd[3] = (*sh) + 0x20;
    }
}





// head: *(snake + 0)
// tail: *(snake + slen)
void SnakeMove (char *snake, char dir)
{
    unsigned char i, j, sd[4], tmp;


    // get dirs
    SnakeHeadDir (snake, sd);


    // remove none use dir
    for (i = 0; i < 4; i++)
        for (j = 0; j < CONST_SNAKE_LEN; j++)
            if (sd[i] == snake[j])
                sd[i] = 0xFF;
    i = snake[1] & 0x03;    // random
    j = snake[CONST_SNAKE_LEN - 1] & 0x03;
    tmp = sd[j];
    sd[j] = sd[i];
    sd[i] = tmp;


    // choose header
    j = dir;
    for (i = 0; i < 4; i++)
    {
        tmp = sd[j];
        if (tmp != 0xFF)
            break;
        if (j == 3)
            j = 0;
        else
            j++;
    }


    // move snake body
    for (i = (CONST_SNAKE_LEN - 1); i != 0; i--)
        snake[i] = snake[i - 1];
    snake[0] = tmp;

}





void SnakeLcdRefresh (char *snake_tail, char *snake_head, char *pcgram)
{
    unsigned char line, col, i, tmp;
    unsigned char x;

    x = *snake_tail;




    // display new header
    if ((*snake_head) != 0xFF)
    {
        tmp     = 0x10;
        line    = (*snake_head) & 0x1F;
        col     = ((*snake_head) & 0xE0) >> 5;      // 移位后补充的是1
        col     = col & 0x07;
        for (i = 0; i < col; i++)
        {
            tmp = tmp >> 1;
            tmp = tmp & 0x7F;
        }
        pcgram[line] |= tmp;

        if (line < 8)
            LcdWriteOneCGRAM (CONST_SNAKE_RAM0, (pcgram + 0));
        else if (line < 16)
            LcdWriteOneCGRAM (CONST_SNAKE_RAM1, (pcgram + 8));
        else if (line < 24)
            LcdWriteOneCGRAM (CONST_SNAKE_RAM2, (pcgram + 16));
        else
            LcdWriteOneCGRAM (CONST_SNAKE_RAM3, (pcgram + 24));
    }




    // clear tial
    //if ((*snake_tail) != 0xE0)
    if (x != 0xFF)
    {
        tmp     = 0xEF;
        line    = (*snake_tail) & 0x1F;
        col     = ((*snake_tail) & 0xE0) >> 5;
        col     = col & 0x07;
        for (i = 0; i < col; i++)
        {
            tmp = tmp >> 1;
            tmp = tmp | 0x80;
        }
        pcgram[line] &= tmp;

        if (line < 8)
            LcdWriteOneCGRAM (CONST_SNAKE_RAM0, (pcgram + 0));
        else if (line < 16)
            LcdWriteOneCGRAM (CONST_SNAKE_RAM1, (pcgram + 8));
        else if (line < 24)
            LcdWriteOneCGRAM (CONST_SNAKE_RAM2, (pcgram + 16));
        else
            LcdWriteOneCGRAM (CONST_SNAKE_RAM3, (pcgram + 24));
    }
}




void SnakeInit (char *snake, char *pcgram)
{
    unsigned char i;

    // init snake
    for (i = 0; i < CONST_SNAKE_LEN; i++)
        snake[i] = 0xFF;

    // init CGRAM
    for (i = 0; i < 32; i++)
        pcgram[i] = 0;

    // init display
    LcdWriteOneCGRAM (CONST_SNAKE_RAM0, (pcgram + 0));
    LcdWriteOneCGRAM (CONST_SNAKE_RAM1, (pcgram + 8));
    LcdWriteOneCGRAM (CONST_SNAKE_RAM2, (pcgram + 16));
    LcdWriteOneCGRAM (CONST_SNAKE_RAM3, (pcgram + 24));
}


