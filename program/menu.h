#ifndef __MENU_H__
#define __MENU_H__

#include "ds12c887.h"
#include "lcd1602.h"
#include "joy_sys.h"




//*****************************************************************
// Éµº¢×ÓµÄ²Ëµ¥
//*****************************************************************
struct MenuItem {
    unsigned char MenuCount;
    char *DisplayString;
    void (*Subs)();
    struct MenuItem *ChildrenMenu;
    struct MenuItem *ParentMenu;
};
//*****************************************************************









//*****************************************************************
// Menu Variables
//*****************************************************************
extern data unsigned char menu_point;
extern data unsigned char menu_start;
extern data unsigned char menu_choose;
extern data unsigned char menu_max;
extern data struct MenuItem (*pMenu);


extern code struct MenuItem MainMenu[4];
extern code struct MenuItem SetSystem[5];
//*****************************************************************












//*****************************************************************
// Menu Functions
//*****************************************************************
void NullSubs (void);
void MenuSetTime (void);
void MenuSetDate (void);
void MenuShow (void);
void MenuInit (void);
void MenuRefresh (void);
void About (void);
void SetTimeout (void);

//*****************************************************************







#endif
