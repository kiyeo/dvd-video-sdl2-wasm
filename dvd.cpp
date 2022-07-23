#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
EM_JS(int, canvas_get_width, (), {
  canvas.width = window.innerWidth;
  return window.innerWidth;
});

EM_JS(int, canvas_get_height, (), {
  canvas.height = window.innerHeight;
  return window.innerHeight;
});

int SCREEN_HEIGHT = canvas_get_height();
int SCREEN_WIDTH = canvas_get_width();
#else
int SCREEN_HEIGHT = 1920;
int SCREEN_WIDTH = 1080;
#endif

SDL_Window *WINDOW = NULL;
SDL_Renderer *RENDERER = NULL;
SDL_Surface *TMPSURFACE = NULL;
SDL_Texture *TEX = NULL;
SDL_Rect DVDsrcR, DVDdestR;
int DVD_xvel, DVD_yvel;
bool isRunning = false;
int fps = 60;
const int frameDelay = 1000 / fps;
Uint32 frameStart;
int frameTime;
int speed = 4;

void collision() {
  if (DVDdestR.x + DVDdestR.w >= SCREEN_WIDTH) {
    DVD_xvel = -1;
  }
  if (DVDdestR.x <= 0) {
    DVD_xvel = 1;
  }
  if (DVDdestR.y <= 0) {
    DVD_yvel = 1;
  }
  if (DVDdestR.y + DVDdestR.h >= SCREEN_HEIGHT) {
    DVD_yvel = -1;
  }
}

void draw() {
  SDL_RenderClear(RENDERER);
  SDL_RenderCopy(RENDERER, TEX, NULL, &DVDdestR);
  SDL_RenderPresent(RENDERER);
}

void load_texture() {
  RENDERER = SDL_CreateRenderer(WINDOW, -1, 0);
  TMPSURFACE = IMG_Load("dvd-video.png");
  TEX = SDL_CreateTextureFromSurface(RENDERER, TMPSURFACE);
  SDL_FreeSurface(TMPSURFACE);
}

void main_loop() {
  frameStart = SDL_GetTicks();

  draw();
  collision();

  frameTime = SDL_GetTicks() - frameStart;

  if (frameTime < frameDelay) {
    SDL_Delay(frameDelay - frameTime);
  }

  DVDdestR.x += DVD_xvel * speed / 2;
  DVDdestR.y += DVD_yvel * speed / 2;
}

void close() {
  SDL_DestroyTexture(TEX);
  SDL_DestroyRenderer(RENDERER);
  SDL_DestroyWindow(WINDOW);
  SDL_Quit();
#ifdef __EMSCRIPTEN__
  emscripten_cancel_main_loop();
#endif
}

bool init(void) {
  SDL_Init(SDL_INIT_VIDEO);
  WINDOW = SDL_CreateWindow("DVD Video", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                            SDL_WINDOW_RESIZABLE);
  isRunning = true;
  return true;
}

int main() {
  if (init()) {
    load_texture();

    DVDdestR.w = 340;
    DVDdestR.h = 150;
    DVDdestR.x = SCREEN_WIDTH / 2;
    DVDdestR.y = SCREEN_HEIGHT / 2 - DVDdestR.h / 2;

    DVD_xvel = DVD_yvel = 1;
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, 1);
#endif
#ifndef __EMSCRIPTEN__
    while (isRunning)
      main_loop();
#endif
  } else
    return -1;
  close();
  return 0;
}
