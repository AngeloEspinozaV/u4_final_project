#include "control.h"
#include <stdlib.h>
#include <time.h>

float control(float reference_velocity, float velocity, float ui, float up,
              float kp, float ki,float error,float last_error) {
  srand(time(NULL));
  kp = rand()%10;
  ki = 0.15;
  error = reference_velocity - velocity;
  up = kp * error;
  last_error = last_error + error;
  ui = ki * last_error;
  return up + ui;
}
