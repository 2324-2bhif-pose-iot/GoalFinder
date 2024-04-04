#include <GoalfinderApp.h>

GoalfinderApp gf;

void setup() {
    gf.Init();
}

void loop() {
  gf.Process();
}