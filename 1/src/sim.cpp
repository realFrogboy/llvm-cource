#include <stdio.h>

#include "sim.h"

static const unsigned g_delay = 10;

static SDL_Window *g_window;
static SDL_Renderer *g_renderer;

static void color2rgba(uint32_t color, uint8_t *r, uint8_t *g, uint8_t *b,
                       uint8_t *a) {
  *a = color >> 24;
  *r = (color >> 16) & 0xFF;
  *g = (color >> 8) & 0xFF;
  *b = color & 0xFF;
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

void simFillScreen(const uint32_t color) {
  uint8_t r, g, b, a;
  color2rgba(color, &r, &g, &b, &a);
  SDL_SetRenderDrawColor(g_renderer, r, g, b, a);
  SDL_RenderFillRect(g_renderer, NULL);
}

int simDrawCircle(const struct Circle *circle) {
  int offsetx = 0;
  int offsety = circle->radius;
  int d = circle->radius - 1;
  int status = 0;

  uint8_t r, g, b, a;
  color2rgba(circle->color, &r, &g, &b, &a);
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

void simFlush() {
  SDL_RenderPresent(g_renderer);
  SDL_Delay(g_delay);
}

int simHandleEvents() {
  SDL_PumpEvents();
  return (SDL_HasEvent(SDL_QUIT) == SDL_TRUE) ? 1 : 0;
}

void simKill() {
  SDL_DestroyRenderer(g_renderer);
  SDL_DestroyWindow(g_window);
  SDL_Quit();
}
