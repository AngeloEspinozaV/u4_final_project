/*
 * File:          u4_exam_Espinoza_Angelo.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */
/* WEBOTS LIBRARIES */
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/keyboard.h>
#include <webots/distance_sensor.h>
#include <webots/position_sensor.h>

/* C LIBRARIES */
#include <stdio.h>

#define TIME_STEP 64
#define MAX_BITS 1660

#define VELOCITY_MANUAL 2
#define VELOCITY_AUTONOMOUS 3
#define DISTANCE_OBSTACLE 17

#define PI 3.141592

/* PROTOFUNCTIONS */
float bitsToCentimeters(float centimeters);

void manual(int key, WbDeviceTag motor_1, WbDeviceTag motor_2,
            WbDeviceTag motor_3, WbDeviceTag motor_4);

void autonomous(WbDeviceTag motor_1, WbDeviceTag motor_2,
                WbDeviceTag motor_3, WbDeviceTag motor_4,
                WbDeviceTag distance_sensor1, WbDeviceTag distance_sensor,
                WbDeviceTag position_sensor1, WbDeviceTag position_sensor2,
                float desired_centimeters);

void stopRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag motor_3,
               WbDeviceTag motor_4);
void moveForwardRobotAutonomous(WbDeviceTag motor_1, WbDeviceTag motor_2,
                                WbDeviceTag motor_3, WbDeviceTag motor_4);
void moveForwardRobotManual(WbDeviceTag motor_1, WbDeviceTag motor_2,
                            WbDeviceTag motor_3, WbDeviceTag motor_4);

void moveBackwardRobot(WbDeviceTag motor_1, WbDeviceTag motor_2,
                       WbDeviceTag motor_3, WbDeviceTag motor_4);
void moveLeftRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag
                   motor_3, WbDeviceTag motor_4);

void moveRightRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag
                    motor_3, WbDeviceTag motor_4);

void turnLeftRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag
                   motor_3, WbDeviceTag motor_4);

void turnRightRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag
                    motor_3, WbDeviceTag motor_4);

float revolutionToRadians(float radians);

/* STATES */
enum {
    AUTONOMOUS,
    MANUAL
};

/* GLOBAL VARIABLES */
double ds_left_value;
double ds_right_value;

double ps_left_value;
double ps_right_value;

int flag = 0;

int main(int argc, char **argv) {

    wb_robot_init();

   /* IMPORTING MOTORS */
    WbDeviceTag motor_1 = wb_robot_get_device("motor1");
    WbDeviceTag motor_2 = wb_robot_get_device("motor2");
    WbDeviceTag motor_3 = wb_robot_get_device("motor3");
    WbDeviceTag motor_4 = wb_robot_get_device("motor4");

    /* IMPORTING DISTANCE SENSORS */
    WbDeviceTag distance_sensor1 = wb_robot_get_device("distance_sensor1");
    WbDeviceTag distance_sensor2 = wb_robot_get_device("distance_sensor2");

    /* IMPORTING POSITION SENSORS */
    WbDeviceTag position_sensor1 = wb_robot_get_device("position_sensor1");
    WbDeviceTag position_sensor2 = wb_robot_get_device("position_sensor2");


    /* ENABLING DISTANCE SENSORS */
    wb_distance_sensor_enable(distance_sensor1, TIME_STEP);
    wb_distance_sensor_enable(distance_sensor2, TIME_STEP);

    /* ENABLING POSITION SENSORS */
    wb_position_sensor_enable(position_sensor1, TIME_STEP);
    wb_position_sensor_enable(position_sensor2, TIME_STEP);

   /* ENABLING THE KEYBOARD */
    wb_keyboard_enable(TIME_STEP);

   /* VARIABLES */
    int key;
    int robot_status = 0;
    float desired_centimeters = bitsToCentimeters(DISTANCE_OBSTACLE);

    while (wb_robot_step(TIME_STEP) != -1) {

        key = wb_keyboard_get_key();

        if (key == 'W') {
            robot_status = MANUAL;
            printf("MANUAL MODE ACTIVATED\n");
        } else if (key == 'G') {
            robot_status = AUTONOMOUS;
            printf("AUTONOMOUS MODE ACTIVATED\n");
        } else {
            stopRobot(motor_1, motor_2, motor_3, motor_4);
        }

        switch (robot_status) {
            case MANUAL:
                manual(key, motor_1, motor_2, motor_3, motor_4);
                break;
            case AUTONOMOUS:
                autonomous(motor_1, motor_2, motor_3, motor_4,distance_sensor1,
                           distance_sensor2, position_sensor1, position_sensor2,
                           desired_centimeters);
                break;
        }
    };

    wb_robot_cleanup();
    return 0;
}

float bitsToCentimeters(float centimeters) {
    return (MAX_BITS*centimeters)/(500);
}

void stopRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag motor_3,
               WbDeviceTag motor_4) {
    wb_motor_set_velocity(motor_1, 0);
    wb_motor_set_velocity(motor_2, 0);
    wb_motor_set_velocity(motor_3, 0);
    wb_motor_set_velocity(motor_4, 0);
}

void moveForwardRobotAutonomous(WbDeviceTag motor_1, WbDeviceTag motor_2,
                                WbDeviceTag motor_3, WbDeviceTag motor_4){
    wb_motor_set_velocity(motor_1, VELOCITY_AUTONOMOUS);
    wb_motor_set_velocity(motor_2, VELOCITY_AUTONOMOUS);
    wb_motor_set_velocity(motor_3, VELOCITY_AUTONOMOUS);
    wb_motor_set_velocity(motor_4, VELOCITY_AUTONOMOUS);
}

void moveForwardRobotManual(WbDeviceTag motor_1, WbDeviceTag motor_2,
                            WbDeviceTag motor_3, WbDeviceTag motor_4) {
    wb_motor_set_velocity(motor_1, VELOCITY_MANUAL);
    wb_motor_set_velocity(motor_2, VELOCITY_MANUAL);
    wb_motor_set_velocity(motor_3, VELOCITY_MANUAL);
    wb_motor_set_velocity(motor_4, VELOCITY_MANUAL);
}

void moveBackwardRobot(WbDeviceTag motor_1, WbDeviceTag motor_2,
                       WbDeviceTag motor_3, WbDeviceTag motor_4) {
    wb_motor_set_velocity(motor_1, -VELOCITY_MANUAL);
    wb_motor_set_velocity(motor_2, -VELOCITY_MANUAL);
    wb_motor_set_velocity(motor_3, -VELOCITY_MANUAL);
    wb_motor_set_velocity(motor_4, -VELOCITY_MANUAL);
}

void moveLeftRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag
                   motor_3, WbDeviceTag motor_4) {
    wb_motor_set_velocity(motor_1, -VELOCITY_MANUAL);
    wb_motor_set_velocity(motor_2, VELOCITY_MANUAL);
    wb_motor_set_velocity(motor_3, VELOCITY_MANUAL);
    wb_motor_set_velocity(motor_4, -VELOCITY_MANUAL);
}

void moveRightRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag
                    motor_3, WbDeviceTag motor_4) {
    wb_motor_set_velocity(motor_1, VELOCITY_MANUAL);
    wb_motor_set_velocity(motor_2, -VELOCITY_MANUAL);
    wb_motor_set_velocity(motor_3, -VELOCITY_MANUAL);
    wb_motor_set_velocity(motor_4, VELOCITY_MANUAL);
}

void turnLeftRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag
                   motor_3, WbDeviceTag motor_4) {
    wb_motor_set_velocity(motor_1, -VELOCITY_MANUAL);
    wb_motor_set_velocity(motor_2, VELOCITY_MANUAL);
    wb_motor_set_velocity(motor_3, -VELOCITY_MANUAL);
    wb_motor_set_velocity(motor_4, VELOCITY_MANUAL);
}

void turnRightRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag
                    motor_3, WbDeviceTag motor_4) {
    wb_motor_set_velocity(motor_1, VELOCITY_MANUAL);
    wb_motor_set_velocity(motor_2, -VELOCITY_MANUAL);
    wb_motor_set_velocity(motor_3, VELOCITY_MANUAL);
    wb_motor_set_velocity(motor_4, -VELOCITY_MANUAL);
}

float revolutionToRadians(float radians) {
    int integer_part;
    float result;
    float decimal_part;
    float turns;

    integer_part = radians/(2*PI);
    decimal_part = radians/(2*PI);

    turns = decimal_part - integer_part;

    result = turns * (2*PI);

    return result;
}

void manual(int key, WbDeviceTag motor_1, WbDeviceTag motor_2,
            WbDeviceTag motor_3, WbDeviceTag motor_4) {

    switch (key) {
        /* MOVE FORWARD */
        case WB_KEYBOARD_UP:
            moveForwardRobotManual(motor_1, motor_2, motor_3, motor_4);
            break;
        /* MOVE BACKWARD */
        case WB_KEYBOARD_DOWN:
            moveBackwardRobot(motor_1, motor_2,motor_3, motor_4);
            break;
        /* MOVE TO THE LEFT */
        case WB_KEYBOARD_LEFT:
            moveLeftRobot(motor_1, motor_2, motor_3, motor_4);
            break;
        /* MOVE TO THE RIGHT */
        case WB_KEYBOARD_RIGHT:
            moveRightRobot(motor_1, motor_2, motor_3, motor_4);
            break;
        /* TURN TO THE LEFT */
        case 'A':
            turnLeftRobot(motor_1, motor_2, motor_3, motor_4);
            break;
        /* TURN TO THE RIGHT */
        case 'S':
            turnRightRobot(motor_1, motor_2, motor_3, motor_4);
            break;
        default:
            stopRobot(motor_1, motor_2, motor_3, motor_4);
            break;
    }

}

void autonomous(WbDeviceTag motor_1, WbDeviceTag motor_2,
                WbDeviceTag motor_3, WbDeviceTag motor_4,
                WbDeviceTag distance_sensor1, WbDeviceTag distance_sensor2,
                WbDeviceTag position_sensor1, WbDeviceTag position_sensor2,
                float desired_centimeters) {
     // int flag = 0;
     float localVar1;
     float localVar2;
     float var1;
     float var2;

     printf("FLAG %d\n", flag);

     if (flag == 0) {
    /* SETTING POSITION OF THE MOTORS */
     wb_motor_set_position(motor_1, INFINITY);
     wb_motor_set_position(motor_2, INFINITY);
     wb_motor_set_position(motor_3, INFINITY);
     wb_motor_set_position(motor_4, INFINITY);
    }

    ds_left_value = wb_distance_sensor_get_value(distance_sensor1);
    ds_right_value = wb_distance_sensor_get_value(distance_sensor2);

    ps_left_value = wb_position_sensor_get_value(position_sensor1);
    ps_right_value = wb_position_sensor_get_value(position_sensor2);

    // if (ps_left_value >= 2*PI) {
        localVar1 = revolutionToRadians(ps_left_value);
    // }
    // if (ps_right_value >= 2*PI) {
        localVar2 = revolutionToRadians(ps_right_value);
    // }
    var1 =  ps_left_value + (5*PI)/(2*PI);
    var2 =  ps_right_value - (2.5*PI)/(2*PI);

    printf("LEFT VALUE PS: %.4lf, RIGHT VALUE: %.4lf\n",localVar1, localVar2);
    printf("LEFT VALUE PS: %.4lf, RIGHT VALUE: %.4lf\n", ps_left_value, ps_right_value);
    printf("revolutionToRadians: %.4f\n", revolutionToRadians(5*PI));


    if (ds_left_value > desired_centimeters &&
        ds_right_value > desired_centimeters) {
        moveForwardRobotAutonomous(motor_1, motor_2, motor_3, motor_4);
    }
    if (ds_left_value <= desired_centimeters) {
        flag = 1;
        stopRobot(motor_1, motor_2, motor_3, motor_4);
        //turnRightRobot(motor_1, motor_2, motor_3, motor_4);
        printf("BANDERAAAAAAAAAAA\n");
        wb_motor_set_velocity(motor_1, VELOCITY_MANUAL);
        wb_motor_set_position(motor_1, ps_left_value + (5*PI)/(2*PI));
        wb_motor_set_velocity(motor_2, VELOCITY_MANUAL);
        wb_motor_set_position(motor_2, ps_right_value - (2.5*PI)/(2*PI));
        wb_motor_set_velocity(motor_3, VELOCITY_MANUAL);
        wb_motor_set_position(motor_3, ps_left_value + (5*PI)/(2*PI));
        wb_motor_set_velocity(motor_4, VELOCITY_MANUAL);
        wb_motor_set_position(motor_4, ps_right_value - (2.5*PI)/2*PI);
    }
}
