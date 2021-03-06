#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

typedef struct {
    int x, y;
} koor;

typedef struct {
    int level_w, level_h;   //palya szelessege, magassaga
    char *map;              //palyat tartalmaza tomb
    int numofbox;           //palyan talalhato dobozok szama
    koor *boxpos;           //dobozok aktualis poziciojat tartalmazo tomb
} lab;

void fontinit();
void loadimages();
void loadponystates();
void loadlevel(koor *charpos, lab *lab, int level);
int game_event_loop (SDL_Surface *screen, koor *charpos, lab *lab, int *game, int *result);
void freegame();

#endif // GAME_H_INCLUDED
