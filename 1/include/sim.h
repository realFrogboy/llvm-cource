#include "SDL.h"

static const unsigned WIDTH = 960;
static const unsigned HEIGHT = 720;

struct Circle {
  int x;
  int y;
  int dx;
  int dy;
  int radius;
  uint32_t color;
};

void simInit();
void simFillScreen(const uint32_t color);
int simDrawCircle(const struct Circle *circle);
void simFlush();
int simHandleEvents();
void simKill();

void app();
