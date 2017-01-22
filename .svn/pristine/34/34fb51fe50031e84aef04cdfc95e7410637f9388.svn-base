#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "main.h"
#include "ranking.h"

static SDL_Surface *background;
static SDL_Color black = {0,0,0};
static TTF_Font *font1;
static TTF_Font *font2;
SDL_Surface *text;

extern int numlevels;       //palyak szama
const int maxnumscore = 3;  //maximum eltarolt eredmeny egy palyan

void ranking_loop(SDL_Surface *screen, int *ranking, scoreboard sb[]){
    //kirajzolja az eredmenyeket
    SDL_Event event;
    drawranking(screen, sb);
    if(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_KEYDOWN: {
                switch(event.key.keysym.sym){
                    case SDLK_q:{
                        *ranking = 0;
                        break;
                    }
                    default: break;
                }
            }
        }
    }
}

void fontinit_r(){
    //betutipus betoltese
    TTF_Init();
    font1 = TTF_OpenFont("comic.ttf", 35);
    font2 = TTF_OpenFont("comic.ttf", 20);
    if (!font1 || !font2) {
        fprintf(stderr, "Nem sikerult betölteni a betutipust! %s\n", TTF_GetError());
        exit(2);
    }
}

void drawranking(SDL_Surface *screen, scoreboard sb[]){
    int i,j;
    char num[30];
    //Hatter kirajzolasa
    SDL_BlitSurface(background, NULL, screen, NULL);

    //Cim kirajzolasa
    text = TTF_RenderUTF8_Blended(font1, "Eredm\xC3\xA9nyek", black);
    SDL_Rect dest = {145,15,0,0};
    SDL_BlitSurface(text, NULL, screen, &dest);

    //Eredmenyek kirajzolasa
    for(i = 0; i < numlevels; i++){
        //Palya sorszamok kirajzolasa
        sprintf(num, "%d.p\xC3\xA1lya", i+1);
        text = TTF_RenderUTF8_Blended(font2, num, black);
        SDL_Rect dest = {15,100+i*50,0,0};
        SDL_BlitSurface(text, NULL, screen, &dest);

        //Eredmenyek kirajzolasa
        for (j = 0; j < sb[i].numofscore; j++){
            sprintf(num, "%d   ",sb[i].scores[j]);
            text = TTF_RenderUTF8_Blended(font2, num, black);
            SDL_Rect dest = {90+j*50,100+i*50,0,0};
            SDL_BlitSurface(text, NULL, screen, &dest);
        }
    }

    SDL_FreeSurface(text);
    SDL_Flip(screen);
}

void loadranking(scoreboard *sb){
    //hatter betoltese
    background = IMG_Load("pic/ranking_bg.png");

    if(background == NULL){
        fprintf(stderr, "Nem sikerült betölteni a rangsorhoz a képeket!\n");
        exit(3);
    }

    //Fajl betoltese
    FILE *f;
    int i,j;
    f = fopen("ranking/ranking.txt", "rt");
    //ha nem letezik a fajl akkor letrehozza és feltolti 0-val az eredmenyek szamat
    if(f == NULL){
        for (i = 0; i < numlevels; i++) {
            sb[i].numofscore = 0;
            sb[i].scores = NULL;
        }
    }
    //eredmenyek betoltese a fajlbol
    else{
        for (i = 0; i < numlevels; i++){
            fscanf(f, "%d", &sb[i].numofscore);
            sb[i].scores = (int *) malloc(sb[i].numofscore*sizeof(int));
            for(j = 0; j < sb[i].numofscore; j++){
                fscanf(f, "%d", &sb[i].scores[j]);
            }
        }
        fclose(f);  //fajl bezarasa
    }
}

void saveranking(scoreboard *sb, int result, int level){
    //elmenti az elert eredmenyt
    FILE *f;
    int i, j;
    for(i = 0; i < sb[level].numofscore && result >= sb[level].scores[i]; i++){
        //megkeresi az uj eredmeny helyet
    }
    if(i < maxnumscore){
        if(sb[level].numofscore < maxnumscore) {
            sb[level].numofscore++;
            sb[level].scores = realloc(sb[level].scores, sb[level].numofscore * sizeof(int));
        }
        //az eredmenyt beszurja az i-edik helyre, a tobbi elem hatraleptetesével
        for(j = sb[level].numofscore-1; j > i; j--){
            sb[level].scores[j] = sb[level].scores[j-1];
        }
        sb[level].scores[i] = result;

        //uj rangsor fajlbairasa
        f = fopen("ranking/ranking.txt", "wt");
        if(f == NULL)
            fprintf(stderr, "Nem sikerult létrehozni a ranking.txt-t");
        else{
            for(i = 0; i < numlevels; i++){
                fprintf(f, "%d", sb[i].numofscore);
                for(j = 0; j < sb[i].numofscore; j++)
                    fprintf(f, " %d", sb[i].scores[j]);
                fprintf(f, "\n");
            }
            fclose(f);  //fajl bezarasa
        }
    }
}

void freeranking(){
    //hasznalt kepek felszabaditasa
    SDL_FreeSurface(background);
}
