#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED

typedef struct{
    int numofscore; //eredmenyek szama
    int *scores;    //eredmenyeket tartalmazo tomb
} scoreboard;

void ranking_loop(SDL_Surface *screen, int *ranking, scoreboard sb[]);
void fontinit_r();
void loadranking(scoreboard *sb);
void saveranking(scoreboard *sb, int result, int level);
void freeranking();

#endif // RANKING_H_INCLUDED
