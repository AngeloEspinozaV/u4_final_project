#ifndef CONTROL
#define CONTROL

extern float control(float reference_velocity, float velocity, float ui, float up,
              float kp, float ki,float error,float last_error);

#endif
