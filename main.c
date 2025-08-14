#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>

#define BOARD_SIZE 8
#define TILE_SIZE 60

int main(int argc, char* argv[]) {
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, BOARD_SIZE*TILE_SIZE, BOARD_SIZE*TILE_SIZE, 0);

    if(win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, 0);

    // ボードの描画
    for(int y=0; y<BOARD_SIZE; y++) {
        for(int x=0; x<BOARD_SIZE; x++) {
            if((x+y)%2==0) {
                SDL_SetRenderDrawColor(renderer, 240, 217, 181, 255); //白
            }
            else {
                SDL_SetRenderDrawColor(renderer, 181, 136, 99, 255); //黒
            }
            SDL_Rect rect = {x*TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    //駒
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect black_piece = {0*TILE_SIZE+10, 1*TILE_SIZE+10, TILE_SIZE-20, TILE_SIZE-20};
    SDL_RenderFillRect(renderer, &black_piece);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect white_piece = {0*TILE_SIZE+10, 6*TILE_SIZE+10, TILE_SIZE-20, TILE_SIZE-20};
    SDL_RenderFillRect(renderer, &white_piece);

    SDL_RenderPresent(renderer);
    SDL_Delay(3000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
