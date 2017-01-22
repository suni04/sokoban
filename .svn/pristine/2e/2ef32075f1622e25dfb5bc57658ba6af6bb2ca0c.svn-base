#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <SDL_image.h>

//menuhoz szukseges kepek
static SDL_Surface *background;
SDL_Surface *newgame;
SDL_Surface *ranking;
SDL_Surface *qexit;
SDL_Surface *newgame_c;
SDL_Surface *ranking_c;
SDL_Surface *exit_c;

int cursor_pos = 0;     //jelzi hogy melyik gombon allunk epp


void menu_loop(SDL_Surface *screen, int *game, int *ranking, int *quit){
    SDL_Event event;
    drawbuttons(screen, cursor_pos);
        if(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym){
                        case SDLK_DOWN:{
                            //lefele megy a menupontok kozott, kiveve ha a legalson allunk eppen
                            if(cursor_pos < 2){
                                cursor_pos++;
                                drawbuttons(screen, cursor_pos);
                            }
                            break;
                        }
                        case SDLK_UP: {
                            //felfele megy a menupontok kozott, kiveve ha a legfelson allunk eppen
                            if(cursor_pos > 0){
                                cursor_pos--;
                                drawbuttons(screen, cursor_pos);
                            }
                            break;
                        }
                        case SDLK_RETURN:
                        case SDLK_KP_ENTER:{
                            //enterre abba a menupontba lep amilyik eppen ki van valasztva
                            switch(cursor_pos){
                                case 0: {
                                    *game = 1;
                                    break;
                                }
                                case 1: {
                                    *ranking = 1;
                                    break;
                                }
                                case 2: {
                                    *quit = 1;
                                    break;
                                }
                            }
                            break;
                        }
                        default: break;
                    }

                }
            }
        }

    }

void loadmenu(){
    //Szukseges kepek betoltese
    background = IMG_Load("pic/menu.png");
    newgame = IMG_Load("pic/newgame.png");
    ranking = IMG_Load("pic/rank.png");
    qexit = IMG_Load("pic/exit.png");
    newgame_c = IMG_Load("pic/newgame_c.png");
    ranking_c = IMG_Load("pic/rank_c.png");
    exit_c = IMG_Load("pic/exit_c.png");
    if(background == NULL || newgame == NULL || ranking == NULL || qexit == NULL || newgame_c == NULL || ranking_c == NULL || exit_c == NULL){
        fprintf(stderr, "Nem sikerült betölteni a menühöz a képeket!\n");
        exit(2);
    }
}

void drawbuttons(SDL_Surface *screen, int cursor_pos){
    //Kepernyo bal oldalatol val tav
    int d_edge = 15;
    //Gombok kozotti tav
    int d_buttons = 82;
    //Kepernyo felso szeletol valo tav
    int d_top_edge = 130;

    /*Gombok koordinatai*/
    SDL_Rect r_newgame = {d_edge,d_top_edge,0,0};
    SDL_Rect r_ranking = {d_edge,d_top_edge + d_buttons,0,0};
    SDL_Rect r_exit = {d_edge, d_top_edge + 2*d_buttons,0,0};

    SDL_Rect bg = {0,0,0,0};
    SDL_BlitSurface(background, NULL, screen, &bg);

    /*Amelyik gombon all epp oda masik kepet rak*/
    switch(cursor_pos){
        case 0: {
            SDL_BlitSurface(newgame_c, NULL, screen, &r_newgame);
            SDL_BlitSurface(ranking, NULL, screen, &r_ranking);
            SDL_BlitSurface(qexit, NULL, screen, &r_exit);
            break;
        }
        case 1: {
            SDL_BlitSurface(newgame, NULL, screen, &r_newgame);
            SDL_BlitSurface(ranking_c, NULL, screen, &r_ranking);
            SDL_BlitSurface(qexit, NULL, screen, &r_exit);
            break;
        }
        case 2: {
            SDL_BlitSurface(newgame, NULL, screen, &r_newgame);
            SDL_BlitSurface(ranking, NULL, screen, &r_ranking);
            SDL_BlitSurface(exit_c, NULL, screen, &r_exit);
            break;
        }
    }
    SDL_Flip(screen);
}

void freemenu(){
    SDL_FreeSurface(newgame);
    SDL_FreeSurface(ranking);
    SDL_FreeSurface(qexit);
    SDL_FreeSurface(newgame_c);
    SDL_FreeSurface(ranking_c);
    SDL_FreeSurface(exit_c);
}
