#include <SDL2/SDL.h>
#include <stdio.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

// 現在のゲーム (0=将棋, 1=チェス, 2=囲碁)
int current_game = 0;

void draw_board(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // --- ボタン描画 ---
    SDL_Rect shogiBtn = {10, 10, 80, 30};
    SDL_Rect chessBtn = {100, 10, 80, 30};
    SDL_Rect igoBtn   = {190, 10, 80, 30};

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &shogiBtn);
    SDL_RenderFillRect(renderer, &chessBtn);
    SDL_RenderFillRect(renderer, &igoBtn);

    // 枠線
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &shogiBtn);
    SDL_RenderDrawRect(renderer, &chessBtn);
    SDL_RenderDrawRect(renderer, &igoBtn);

    // --- 盤面描画 ---
    int offsetY = 60;
    int size = 40; // マスの大きさ
    int grid = (current_game == 0 ? 9 : (current_game == 1 ? 8 : 9)); // 将棋=9, チェス=8, 囲碁(簡易)=9

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i <= grid; i++) {
        SDL_RenderDrawLine(renderer, 50, offsetY + i * size, 50 + grid * size, offsetY + i * size); // 横線
        SDL_RenderDrawLine(renderer, 50 + i * size, offsetY, 50 + i * size, offsetY + grid * size); // 縦線
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Board Game Hub",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int quit = 0;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x;
                int y = e.button.y;

                if (y >= 10 && y <= 40) {
                    if (x >= 10 && x <= 90) current_game = 0; // 将棋
                    if (x >= 100 && x <= 180) current_game = 1; // チェス
                    if (x >= 190 && x <= 270) current_game = 2; // 囲碁
                }
            }
        }

        draw_board(renderer);
        SDL_Delay(16); // 60fps程度
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

