#include "sim.h"

int main() {
  simInit();
  app();
  simKill();
  return 0;
}
