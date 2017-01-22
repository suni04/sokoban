#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "game.h"
#include "main.h"

const int tile_size = 32;   //egy mezo merete (pixelben)
const int ponyphases = 4;   //poni fazisainak szama
const int deltaphase = 8;   //fazisok kozotti eltolodas (pixelben)
const int screen_w = 480;   //kepernyo szelessege
const int screen_h = 480;   //kepernyo magassaga

//Poni fazisaihoz tartozo kepek helyet tarolo tombok
SDL_Rect right[4];
SDL_Rect down[4];
SDL_Rect left[4];
SDL_Rect up[4];

//jatekhoz szukseges kepek
SDL_Surface *pony;
static SDL_Surface *background;
SDL_Surface *tile;
SDL_Surface *ground;
SDL_Surface *target;
SDL_Surface *box;
SDL_Surface *counter;

static  SDL_Color black = {0,0,0};  //szin
static TTF_Font *font;              //betutipus

//a karakter aktualis adatait tarolja
typedef struct {
    int x,y;            //aktualis koordinatai
    int dirx, diry;     //merre tart eppen
    int phase;          //melyik fazisban van
    int steps;          //hany lepest tett meg a palyan
} charstate;

void fontinit(){
    //betutipus betoltese
    TTF_Init();
    font = TTF_OpenFont("LSANSD.ttf", 20);
    if (!font) {
        fprintf(stderr, "Nem sikerult betölteni a betutipust! %s\n", TTF_GetError());
        exit(2);
    }
}

void loadimages() {
    //szukseges kepek betoltese
    pony = IMG_Load("pic/pony.png");
    background = IMG_Load("pic/bg.png");
    tile = IMG_Load("pic/tile.png");
    ground = IMG_Load("pic/floor.png");
    target = IMG_Load("pic/target.png");
    box = IMG_Load("pic/box.png");

    if (pony == NULL || tile == NULL || ground == NULL || target == NULL || background == NULL || box == NULL){
        fprintf(stderr, "Nem sikerült betölteni a játékhoz a képeket!\n");
        exit(3);
    }
}

void loadlevel(koor *charpos, lab *lab, int level){
    int i;
    FILE *f;
    char filepath[20];
    koor bp;

    //aktualis palya eleresi utvonala
    sprintf(filepath, "levels/level%d.txt", level+1);

    //fajl megnyitasa
    f = fopen(filepath,"rt");
    if (f == NULL){
        fprintf(stderr, "Nem sikerült megnyitni a fájlt!");
        exit(3);
    }
    //beolvasas: dobozok szama a palyan
    fscanf(f, "%d", &lab->numofbox);

    //a dobozok poziciojanak tarolasahoz szukseges tomb lefoglalasa
    lab->boxpos = (koor *) malloc(lab->numofbox*sizeof(koor)); //tömb lefoglalása
    if (lab->boxpos == NULL) {
        printf("Nem sikerült memóriát foglalni!\n");
        exit(2);
    }
    //beolvasas: dobozok pozicioja
    for (i = 0; i < lab->numofbox; i++){
        fscanf(f, "%d", &bp.x);
        fscanf(f, "%d", &bp.y);
        lab->boxpos[i] = bp;
    }

    //beolvasas: karakter pozicioja
    fscanf(f, "%d", &charpos->x);
    fscanf(f, "%d", &charpos->y);

    //beolvasas: labirintus merete
    fscanf(f, "%d", &lab->level_w);
    fscanf(f, "%d", &lab->level_h);

    //a labirintus tarolasahoz szukseges tomb lefoglalasa
    lab->map = (char *)malloc(lab->level_w*lab->level_h*sizeof(char));//lefoglalás
    if (lab->map == NULL) {
        printf("Nem sikerült memóriát foglalni!\n");
        exit(2);
    }

    //beolvasás: labirintus
    char pos;
    i = 0;
    while (i < lab->level_w*lab->level_h){
        fscanf(f, "%c", &pos);
        if (pos != '\n'){
            lab->map[i] = pos;
            i++;
        }
    }
    fclose(f);
}

void loadponystates (){
    int i;
    //Jobbra
    for (i = 0; i < ponyphases; i++) {
        right[i].x = i*tile_size;
        right[i].y = 0*tile_size;
        right[i].w = right[i].h = tile_size;
    }

    //Lefele
    for(i=0;i<4;i++){
        down[i].x = i*tile_size;
        down[i].y = 1*tile_size;
        down[i].w = down[i].h = tile_size;
    }
    //Balra
    for(i=0;i<4;i++){
        left[i].x = i*tile_size;
        left[i].y = 2*tile_size;
        left[i].w = left[i].h = tile_size;
    }
    //Felfele
    for (i=0;i<4;i++){
        up[i].x = i*tile_size;
        up[i].y = 3*tile_size;
        up[i].w = up[i].h = tile_size;
    }

}

void drawcounter(SDL_Surface *screen, int steps){
    //palyan megtett lepesek szamanak kirajzolasa
    char counter_s[10];
    sprintf(counter_s, "%d", steps);
    counter = TTF_RenderUTF8_Blended(font, counter_s, black);
    SDL_Rect dest = {8,0,0,0};
    SDL_BlitSurface(counter, NULL, screen, &dest);
    SDL_FreeSurface(counter);
}

void drawpony (SDL_Surface *screen, lab *lab, charstate *ponystate){
    //poni kirajzolasa a kepernyore
    int i,x,y;
    //mozgas kozbeni aktualis koordinatai
    x = (screen_w - lab->level_w*tile_size)/2 + ponystate->x*tile_size + deltaphase * ponystate->dirx * ponystate->phase;
    y = (screen_h - lab->level_h*tile_size)/2 + ponystate->y*tile_size + deltaphase * ponystate->diry * ponystate->phase;
    SDL_Rect dest = {x, y, 0,0};
    SDL_Rect *rect;
    switch (ponystate->dirx) {
        case -1: rect = left; break;
        case 1: rect = right; break;
        default: switch (ponystate->diry) {
            case -1: rect = up; break;
            default: rect = down; break;
        }
    }
    SDL_BlitSurface(pony, &rect[ponystate->phase], screen, &dest);
}

void drawbox (SDL_Surface *screen, lab *lab, koor boxpos, charstate *ponystate, int push){
    //doboz kirajzolasa a kepernyore
    int x,y;
    //ha egyhelyben van a doboz
    if(push == 0){
        x = (screen_h - lab->level_w*tile_size)/2 + boxpos.x*tile_size;
        y = (screen_w - lab->level_h*tile_size)/2 + boxpos.y*tile_size;
        SDL_Rect dest = {x,y,0,0};
        SDL_BlitSurface(box, NULL, screen, &dest);
    }
    //ha epp mozgasban van a doboz
    else {
        x = (screen_h - lab->level_w*tile_size)/2 + boxpos.x*tile_size + deltaphase * ponystate->dirx * ponystate->phase;
        y = (screen_w - lab->level_h*tile_size)/2 + boxpos.y*tile_size + deltaphase * ponystate->diry * ponystate->phase;
        SDL_Rect dest = {x,y,0,0};
        SDL_BlitSurface(box, NULL, screen, &dest);
    }
}

void drawmap(SDL_Surface *screen, lab *lab, charstate *ponystate, int push, int which){
    //kirajzolja a jatekot
    int x,y,i;
    SDL_BlitSurface(background, NULL, screen, NULL);

    //vegig megy a palyat tarolo tombon es kirajzolja a mezoket
    for (i = 0; i < lab->level_w * lab->level_h; i++){
        x = (screen_w - lab->level_w*tile_size)/2 + i%lab->level_w*tile_size;
        y = (screen_h - lab->level_h*tile_size)/2 + i/lab->level_w*tile_size;
        SDL_Rect dest = {x,y,0,0};

        if (lab->map[i] == '#')
            SDL_BlitSurface(tile, NULL, screen, &dest);
        if (lab->map[i] == '.')
            SDL_BlitSurface(floor, NULL, screen, &dest);
        if(lab->map[i] == 'T')
            SDL_BlitSurface(target, NULL, screen, &dest);
    }
    //szamlalo
    drawcounter(screen, ponystate->steps);
    //poni
    drawpony(screen, lab, ponystate);
    //dobozok
    for(i = 0; i < lab->numofbox; i++){
        drawbox(screen, lab, lab->boxpos[i], ponystate, push && which == i);
    }
    SDL_Flip(screen);
}

int move(charstate *ponystate, int boxstate[], int dirx, int diry, SDL_Surface *screen, lab *lab){
    int i, j;
    ponystate->dirx = dirx;
    ponystate->diry = diry;
    int x      = ponystate->x + dirx + (ponystate->y+diry)*lab->level_w;
    int xplus1 = ponystate->x + 2*dirx + (ponystate->y+2*diry)*lab->level_w;

    //Doboz
    int push = 0;   //ha a poni epp tolja a dobozt
    int hit = 0;    //ha nem tud a poni tovabb mozogni abba az iranyba
    int which;      //melyik dobozt tolja epp
    int goal = 0;   //hany doboz van epp a celmezon

    //utkozes keresese
    for (i = 0; i < lab->numofbox; i++){
        //ha doboz+fal van elotte
        if(x == boxstate[i] && lab->map[xplus1] == '#')
            hit++;
        //ha ketto doboz van elotte
        for(j = 0; j < lab->numofbox; j++){
            if(x == boxstate[i] && xplus1 == boxstate[j])
                hit++;
        }
        //ha tudja tolni a dobozt
        if(x == boxstate[i] && !hit){
            push++;
            which = i;
        }
    }


    //ha tud mozogni a poni
    if(lab->map[x] != '#' && !hit){
        //noveli a lepesek szamat
        ponystate->steps++;
        //poni fazisainak kirajzolasa
        for (i = 0; i < ponyphases; i++){
            ponystate->phase = i;
            drawmap(screen, lab, ponystate, push, which);
            SDL_Delay(60);
        }
        //doboz kirajzolasa mozgas kozben
        if(push){
            lab->boxpos[which].x += dirx;
            lab->boxpos[which].y += diry;
            boxstate[which] = lab->boxpos[which].x + lab->boxpos[which].y*lab->level_w;
        }

        //fazis alaphelyzetbe allitasa
        ponystate->phase = 0;
        //poni koordinatainak megvaltoztatasa
        ponystate->x += dirx;
        ponystate->y += diry;
    }

    drawmap(screen, lab, ponystate, push, which);
    //ha a doboz helyzete valtozik megnezi hogy vege van-e annak a palyanak
    if(push){
        //megnezi hany doboz van celmezon
        for(j = 0; j < lab->numofbox; j++){
            if(lab->map[boxstate[j]] == 'T')
                goal++;
        }
        //ha az osszes doboz a celmezokon van akkor visszater 1-el
        if(goal == lab->numofbox){
            return 1;
        }
    }
    return 0;
}

int game_event_loop (SDL_Surface *screen, koor *charpos, lab *lab, int *game, int *result){
    const int middle = (screen_w - lab->level_w*tile_size)/2;   //kozepre igazitas
    SDL_Event event;
    int i;
    int win = 0;    //igaz, ha az adott palya teljesitve van
    int loop = 1;   //igaz amig a palyan folyik a jatek
    charstate ponystate = {charpos->x, charpos->y, 0, 1, 0, 0}; //poni kiindulo helyzetenek beallitasa
    int boxstate[lab->numofbox];    //boxpos egydimenzios megfeleloje
    for(i = 0; i < lab->numofbox; i++){
        boxstate[i] = lab->boxpos[i].x + lab->boxpos[i].y*lab->level_w;
    }
    drawmap(screen, lab, &ponystate, 0, 0);
    while (loop) {
        if (SDL_PollEvent(&event)) {
            switch (event.type){
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym){
                        case SDLK_q: {
                            *game = 0;
                            loop = 0;
                            break;
                        }
                        case SDLK_r:{
                            loop = 0;
                            break;
                        }
                        case SDLK_RIGHT: {
                            win = move(&ponystate, boxstate, 1, 0, screen, lab);
                            break;
                        }
                        case SDLK_DOWN: {
                            win = move(&ponystate, boxstate, 0, 1, screen, lab);
                            break;
                        }
                        case SDLK_LEFT: {
                            win = move(&ponystate, boxstate, -1, 0, screen, lab);
                            break;
                        }
                        case SDLK_UP: {
                            win = move(&ponystate, boxstate, 0, -1, screen, lab);
                            break;
                        }
                        default: break;
                    }
                    //ha teljesitva van a palya vege a ciklusnak
                    if(win){
                        loop = 0;
                        *result = ponystate.steps;
                    }
                }
                break;
                default: break;
            }
        }
    }
    return win;
}

void freegame(){
    //a jatekban hasznalt elemek felszabaditasa
    SDL_FreeSurface(pony);
    SDL_FreeSurface(background);
    SDL_FreeSurface(tile);
    SDL_FreeSurface(ground);
    SDL_FreeSurface(target);
    SDL_FreeSurface(box);
}
