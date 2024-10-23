#include "sim.h"

static const uint32_t g_background_color = 0xFF181818;

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

void app() {
  struct Circle circles[10] = {{WIDTH / 2, HEIGHT / 2, 1, 1, 100, 0xFF3CB371},
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
    if (simHandleEvents())
      return;

    simFillScreen(g_background_color);

    size_t circles_size = sizeof(circles) / sizeof(struct Circle);
    for (unsigned idx = 0; idx < circles_size; ++idx) {
      struct Circle *circle = &circles[idx];
      moveCircle(circle);
      if (simDrawCircle(circle))
        return;
    }

    simFlush();
  }
}
