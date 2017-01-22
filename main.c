#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include "menu.h"
#include "game.h"
#include "ranking.h"

#define SCREEN_W 480
#define SCREEN_H 480

const int numlevels = 5;

int main(int argc, char *argv[]) {
    SDL_Surface *screen;          //kepernyo
    SDL_Event event;              //esemeny
    koor charpos;                 //a karakter pozicioja
    lab lab1;                     //a labirintus adatai
    scoreboard sb[numlevels];     //az eredmenyek
    int game = 0;                 //igaz, ha jatekban vagyunk
    int ranking = 0;              //igaz, ha a rangsort nezzuk
    int quit = 0;                 //igaz, ha kilepes van
    int level;                    //aktualis palya szama
    int result;                   //elert pontszam
    int i;

    /* SDL inicializalasa �s ablak megnyit�sa */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen=SDL_SetVideoMode(SCREEN_W, SCREEN_H, 0, SDL_ANYFORMAT);
    if (!screen) {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
    }
    SDL_WM_SetCaption("Fluttershy SOKOBAN", "Fluttershy SOKOBAN");

    /*Kepek + betut�pus betotese*/
    loadimages();       //j�t�khoz sz�ks�ges k�pek bet�lt�se
    loadponystates();   //a p�ni anim�ci�j�hoz sz�ks�ges k�pr�szek elt�rol�sa
    loadmenu();         //a men�h�z tartoz� k�pek bet�lt�se
    loadranking(sb);      //a rangsorhoz tartoz� k�pek bet�lt�se
    fontinit();         //bet�t�pus bet�lt�se
    fontinit_r();

    //Program ciklus
    while (!quit){
        //Menu
        SDL_EnableKeyRepeat(0,0);
        menu_loop(screen, &game, &ranking, &quit);

        /*J�t�k ciklus*/
        level = 0;
        while(game){
            SDL_EnableKeyRepeat(1,60);
            //Adott p�lya bet�lt�se
            loadlevel(&charpos, &lab1, level);
            //Ha sikerult vegig vinni a palyat akkor eredmeny eltarolasa
            if (game_event_loop(screen, &charpos, &lab1, &game, &result)){
                saveranking(sb, result, level);
                //Ha nincs tobb palya, az elsore ugras
                if (level == numlevels - 1)
                    game = 0;
                //Amugy kovetkezo palya
                else
                    level++;
            }
        }
        /*Rangsor*/
        while(ranking){
            ranking_loop(screen, &ranking, sb);
        }
    }

    /*Lefoglalt dolgok felszabad�t�sa*/
    free(lab1.boxpos);
    free(lab1.map);
    for (i = 0; i < numlevels; i++)
        free(sb[i].scores);
    SDL_FreeSurface(screen);
    freegame();
    freemenu();
    freeranking();

    /* Ablak bez�r�sa */
    SDL_Quit();

    return 0;
}
