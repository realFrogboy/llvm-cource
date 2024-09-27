#include <assert.h>

#include "sim.h"

static const unsigned WIDTH = 960;
static const unsigned HEIGHT = 720;
static const unsigned N_CIRCLES = 10;
static const unsigned DELAY = 10;

static SDL_Window *g_window;
static SDL_Renderer *g_renderer;

struct Circle {
  int x;
  int y;
  int dx;
  int dy;
  int radius;
  uint32_t color;
};

static void moveCircle(struct Circle *circle) {
  int x = circle->x + circle->dx;
  if (x - circle->radius < 0 || x + circle->radius >= WIDTH)
    circle->dx *= -1;
  else
    circle->x = x;

  int y = circle->y + circle->dy;
  if (y - circle->radius < 0 || y + circle->radius >= HEIGHT)
    circle->dy *= -1;
  else
    circle->y = y;
}

static int SDL_RenderFillCircle(const struct Circle *circle) {
  int offsetx = 0;
  int offsety = circle->radius;
  int d = circle->radius - 1;
  int status = 0;

  uint32_t color = circle->color;
  uint8_t a = color >> 24;
  uint8_t r = (color >> 16) & 0xFF;
  uint8_t g = (color >> 8) & 0xFF;
  uint8_t b = color & 0xFF;
  if (SDL_SetRenderDrawColor(g_renderer, r, g, b, a) < 0) {
    fprintf(stderr, "%s(): couldn't set color %s\n", __FUNCTION__,
            SDL_GetError());
    return 1;
  }

  while (offsety >= offsetx) {
    int x = circle->x;
    int y = circle->y;

    status += SDL_RenderDrawLine(g_renderer, x - offsety, y + offsetx,
                                 x + offsety, y + offsetx);
    status += SDL_RenderDrawLine(g_renderer, x - offsetx, y + offsety,
                                 x + offsetx, y + offsety);
    status += SDL_RenderDrawLine(g_renderer, x - offsetx, y - offsety,
                                 x + offsetx, y - offsety);
    status += SDL_RenderDrawLine(g_renderer, x - offsety, y - offsetx,
                                 x + offsety, y - offsetx);

    if (status < 0) {
      fprintf(stderr, "%s(): couldn't draw line %s\n", __FUNCTION__,
              SDL_GetError());
      return 1;
    }

    if (d >= 2 * offsetx) {
      d -= 2 * offsetx + 1;
      offsetx += 1;
    } else if (d < 2 * (circle->radius - offsety)) {
      d += 2 * offsety - 1;
      offsety -= 1;
    } else {
      d += 2 * (offsety - offsetx - 1);
      offsety -= 1;
      offsetx += 1;
    }
  }

  return 0;
}

void simInit() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "%s(): could not initialize sdl2: %s\n", __FUNCTION__,
            SDL_GetError());
    return;
  }

  g_window = SDL_CreateWindow("aboba", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                              SDL_WINDOW_SHOWN);
  if (!g_window) {
    fprintf(stderr, "%s(): could not create window: %s\n", __FUNCTION__,
            SDL_GetError());
    return;
  }

  g_renderer = SDL_CreateRenderer(g_window, -1, 0);
  if (!g_renderer)
    fprintf(stderr, "%s(): couldn't create renderer: %s\n", __FUNCTION__,
            SDL_GetError());
}

void draw() {

  struct Circle circles[N_CIRCLES] = {
      {WIDTH / 2, HEIGHT / 2, 1, 1, 100, 0xFF3CB371},
      {WIDTH / 2, HEIGHT / 2, 2, 3, 50, 0xFFFFA500},
      {WIDTH / 2, HEIGHT / 2, -4, -1, 75, 0xFF6A5ACD},
      {WIDTH / 2, HEIGHT / 2, -3, 4, 25, 0xFFEE82EE},
      {WIDTH / 2, HEIGHT / 2, -1, 3, 40, 0xFFFF4499},
      {WIDTH / 2, HEIGHT / 2, 4, 5, 65, 0xFFFFDC99},
      {WIDTH / 2, HEIGHT / 2, -5, 3, 98, 0xFF00C2FF},
      {WIDTH / 2, HEIGHT / 2, -4, -6, 32, 0xFF8AEA90},
      {WIDTH / 2, HEIGHT / 2, -3, 2, 55, 0xFFEA9C8A},
      {WIDTH / 2, HEIGHT / 2, -2, 3, 77, 0xFFEE1A1A}};

  for (;;) {
    SDL_PumpEvents();
    if (SDL_HasEvent(SDL_QUIT) == SDL_TRUE)
      return;

    SDL_SetRenderDrawColor(g_renderer, 0x18, 0x18, 0x18, 0x00);
    SDL_RenderFillRect(g_renderer, NULL);

    for (unsigned idx = 0; idx < N_CIRCLES; ++idx) {
      struct Circle *circle = &circles[idx];
      moveCircle(circle);
      if (SDL_RenderFillCircle(circle))
        return;
    }

    SDL_RenderPresent(g_renderer);
    SDL_Delay(DELAY);
  }
}

void simFin() {
  SDL_DestroyRenderer(g_renderer);
  SDL_DestroyWindow(g_window);
  SDL_Quit();
}
