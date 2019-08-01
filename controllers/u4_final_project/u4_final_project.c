/*
 * File:          u4_exam_Espinoza_Angelo.c
 * Date:          July 31st, 2019
 * Description:
 * Author:        Angelo Espinoza, Jesus Duarte, Nora Quintal
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

/* MY LIBRARIES */
#include "control.h"

#define TIME_STEP 64
#define MAX_BITS 1660
#define RADIUS_WHEELS 0.04

#define VELOCITY_MANUAL 0.15
#define VELOCITY_AUTONOMOUS 0.2
#define DISTANCE_OBSTACLE 17
#define TURN_RATIO 45

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

float degreesSec2RadSec(void);

float metersSec2RadSec(float meters_per_second);

float linearVelocity(float meters_per_second);

float distanceTraveled(float radius, WbDeviceTag position_sensor1,
                        WbDeviceTag position_sensor2);

void printStuff(WbDeviceTag ds1, WbDeviceTag ds2, WbDeviceTag ps1,
                WbDeviceTag ps2);

/* STATES */
enum {
    AUTONOMOUS,
    MANUAL
};

/* GLOBAL VARIABLES */
int counter_left, counter_right = 0;

double ds_left_value;
double ds_right_value;

double ps_left_value;
double ps_right_value;

float circunference = 0 ;
float distance_traveled = 0;

char *msg1 = "Distance sensor right value:";
char *msg2 = "Distance sensor left value:";
char *msg3 = "Position sensor wheel 1:";
char *msg4 = "Position sensor wheel 2:";
char *msg5 = "Distance traveled";

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
        printStuff(distance_sensor1, distance_sensor2, position_sensor1,
                   position_sensor2);
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
    wb_motor_set_velocity(motor_1, metersSec2RadSec(VELOCITY_AUTONOMOUS));
    wb_motor_set_velocity(motor_2, metersSec2RadSec(VELOCITY_AUTONOMOUS));
    wb_motor_set_velocity(motor_3, metersSec2RadSec(VELOCITY_AUTONOMOUS));
    wb_motor_set_velocity(motor_4, metersSec2RadSec(VELOCITY_AUTONOMOUS));
}

void moveForwardRobotManual(WbDeviceTag motor_1, WbDeviceTag motor_2,
                            WbDeviceTag motor_3, WbDeviceTag motor_4) {
    wb_motor_set_velocity(motor_1, metersSec2RadSec(VELOCITY_MANUAL));
    wb_motor_set_velocity(motor_2, metersSec2RadSec(VELOCITY_MANUAL));
    wb_motor_set_velocity(motor_3, metersSec2RadSec(VELOCITY_MANUAL));
    wb_motor_set_velocity(motor_4, metersSec2RadSec(VELOCITY_MANUAL));
}

void moveBackwardRobot(WbDeviceTag motor_1, WbDeviceTag motor_2,
                       WbDeviceTag motor_3, WbDeviceTag motor_4) {
    wb_motor_set_velocity(motor_1, -metersSec2RadSec(VELOCITY_MANUAL));
    wb_motor_set_velocity(motor_2, -metersSec2RadSec(VELOCITY_MANUAL));
    wb_motor_set_velocity(motor_3, -metersSec2RadSec(VELOCITY_MANUAL));
    wb_motor_set_velocity(motor_4, -metersSec2RadSec(VELOCITY_MANUAL));
}

void moveLeftRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag
                   motor_3, WbDeviceTag motor_4) {
    wb_motor_set_velocity(motor_1, -metersSec2RadSec(VELOCITY_MANUAL));
    wb_motor_set_velocity(motor_2,  metersSec2RadSec(VELOCITY_MANUAL));
    wb_motor_set_velocity(motor_3,  metersSec2RadSec(VELOCITY_MANUAL));
    wb_motor_set_velocity(motor_4, -metersSec2RadSec(VELOCITY_MANUAL));
}

void moveRightRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag
                    motor_3, WbDeviceTag motor_4) {
    wb_motor_set_velocity(motor_1,  metersSec2RadSec(VELOCITY_MANUAL));
    wb_motor_set_velocity(motor_2, -metersSec2RadSec(VELOCITY_MANUAL));
    wb_motor_set_velocity(motor_3, -metersSec2RadSec(VELOCITY_MANUAL));
    wb_motor_set_velocity(motor_4,  metersSec2RadSec(VELOCITY_MANUAL));
}

void turnLeftRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag
                   motor_3, WbDeviceTag motor_4) {
    wb_motor_set_velocity(motor_1, -degreesSec2RadSec());
    wb_motor_set_velocity(motor_2, degreesSec2RadSec());
    wb_motor_set_velocity(motor_3, -degreesSec2RadSec());
    wb_motor_set_velocity(motor_4, degreesSec2RadSec());
}

void turnRightRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag
                    motor_3, WbDeviceTag motor_4) {
    wb_motor_set_velocity(motor_1, degreesSec2RadSec());
    wb_motor_set_velocity(motor_2, -degreesSec2RadSec());
    wb_motor_set_velocity(motor_3, degreesSec2RadSec());
    wb_motor_set_velocity(motor_4, -degreesSec2RadSec());
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

float degreesSec2RadSec(void) {
    float rad_sec;

    rad_sec = TURN_RATIO * 0.017452;

    return rad_sec;
}
float metersSec2RadSec(float meters_per_second) {
    float radians_per_second;

    radians_per_second =  meters_per_second / RADIUS_WHEELS;

    return radians_per_second;
}

float distanceTraveled(float radius, WbDeviceTag position_sensor1,
                       WbDeviceTag position_sensor2) {
    circunference = radius * (2 * PI);

    if (revolutionToRadians(wb_position_sensor_get_value(position_sensor2)) >= 6){
        distance_traveled = distance_traveled + circunference;
    }
    return distance_traveled;
}

void printStuff(WbDeviceTag ds1, WbDeviceTag ds2, WbDeviceTag ps1,
                WbDeviceTag ps2) {
    printf("%s  %.4lf || %s %.4lf || %s %.4lfrad || %s %.4lfrad\n",
    msg1, wb_distance_sensor_get_value(ds1), msg2,
    wb_distance_sensor_get_value(ds2), msg3,
    wb_position_sensor_get_value(ps1), msg4,
    wb_position_sensor_get_value(ps2));
    printf("\t\t\t\t     %s %.2lfm   || %s %.2lfm\n",
    msg1,  wb_distance_sensor_get_value(ds1) * 5/MAX_BITS, msg3,
    wb_distance_sensor_get_value(ds2) * 5/MAX_BITS);
    printf("\t\t\t\t     %s %.2lfm\n", msg5, distanceTraveled(RADIUS_WHEELS,
    ps1, ps2));
}

void manual(int key, WbDeviceTag motor_1, WbDeviceTag motor_2,
            WbDeviceTag motor_3, WbDeviceTag motor_4) {

    switch (key) {
        /* MOVE FORWARD */
        case WB_KEYBOARD_UP:
            moveForwardRobotManual(motor_1, motor_2, motor_3, motor_4);
            printf("Linear Velocity is: %.2fm/s\n", VELOCITY_MANUAL);
            break;
        /* MOVE BACKWARD */
        case WB_KEYBOARD_DOWN:
            moveBackwardRobot(motor_1, motor_2,motor_3, motor_4);
            printf("Linear Velocity is: %.2fm/s\n", VELOCITY_MANUAL);
            break;
        /* MOVE TO THE LEFT */
        case WB_KEYBOARD_LEFT:
            moveLeftRobot(motor_1, motor_2, motor_3, motor_4);
            printf("Linear Velocity is: %.2fm/s\n", VELOCITY_MANUAL);
            break;
        /* MOVE TO THE RIGHT */
        case WB_KEYBOARD_RIGHT:
            moveRightRobot(motor_1, motor_2, motor_3, motor_4);
            printf("Linear Velocity is: %.2fm/s\n", VELOCITY_MANUAL);
            break;
        /* TURN TO THE LEFT */
        case 'A':
            turnLeftRobot(motor_1, motor_2, motor_3, motor_4);
            printf("Degrees/s are: %ddeg/s\n", TURN_RATIO);
            break;
        /* TURN TO THE RIGHT */
        case 'S':
            turnRightRobot(motor_1, motor_2, motor_3, motor_4);
            printf("Degrees/s are: %ddeg/s\n", TURN_RATIO);
            break;
        default:
            stopRobot(motor_1, motor_2, motor_3, motor_4);
            printf("Linear Velocity is: %dm/s\n", 0);
            break;
    }

}

void autonomous(WbDeviceTag motor_1, WbDeviceTag motor_2,
                WbDeviceTag motor_3, WbDeviceTag motor_4,
                WbDeviceTag distance_sensor1, WbDeviceTag distance_sensor2,
                WbDeviceTag position_sensor1, WbDeviceTag position_sensor2,
                float desired_centimeters) {

    /* SETTING POSITION OF THE MOTORS */
     wb_motor_set_position(motor_1, INFINITY);
     wb_motor_set_position(motor_2, INFINITY);
     wb_motor_set_position(motor_3, INFINITY);
     wb_motor_set_position(motor_4, INFINITY);


    ds_left_value = wb_distance_sensor_get_value(distance_sensor1);
    ds_right_value = wb_distance_sensor_get_value(distance_sensor2);

    ps_left_value = wb_position_sensor_get_value(position_sensor1);
    ps_right_value = wb_position_sensor_get_value(position_sensor2);


    if (ds_left_value > desired_centimeters &&
        ds_right_value > desired_centimeters) {
        moveForwardRobotAutonomous(motor_1, motor_2, motor_3, motor_4);
        printf("Linear Velocity is: %.2fm/s\n", VELOCITY_AUTONOMOUS);
    }
    /* AVOID OBSTACLES LEFT */
    if (ds_left_value <= desired_centimeters && ds_left_value
        < ds_right_value) {
        counter_left++;
    }
    if (counter_left >= 1 && counter_left <= 70) {
        turnRightRobot(motor_1, motor_2, motor_3, motor_4);
        printf("Degrees/s are: %ddeg/s\n", TURN_RATIO);
        counter_left++;
    } else {
        counter_left = 0;
    }

    /* AVOID OBSTACLES RIGHT */
    if (ds_right_value < desired_centimeters && ds_right_value
        < ds_left_value) {
        counter_right++;
    }

    if (counter_right >= 1 && counter_right <= 70) {
        turnLeftRobot(motor_1, motor_2, motor_3, motor_4);
        printf("Degrees/s are: %d deg/s\n", TURN_RATIO);
        counter_right++;
    } else {
        counter_right = 0;
    }


}
