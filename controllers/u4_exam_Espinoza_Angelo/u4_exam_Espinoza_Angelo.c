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

/* C LIBRARIES */
#include <stdio.h>

#define TIME_STEP 64
#define MAX_BITS 1660

#define VELOCITY_MANUAL 3
#define VELOCITY_AUTONOMOUS 3
#define DISTANCE_OBSTACLE 17


/* PROTOFUNCTIONS */
float bitsToCentimeters(float centimeters);

void manual(int key, WbDeviceTag motor_1, WbDeviceTag motor_2,
            WbDeviceTag motor_3, WbDeviceTag motor_4);

void autonomous(WbDeviceTag motor_1, WbDeviceTag motor_2,
                WbDeviceTag motor_3, WbDeviceTag motor_4,
                WbDeviceTag distance_sensor, float desired_centimeters);

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


/* STATES */
enum {
    AUTONOMOUS,
    MANUAL
};

/* GLOBAL VARIABLES */
double distance_sensor_value;

int main(int argc, char **argv) {

    wb_robot_init();

   /* IMPORTING MOTORS */
    WbDeviceTag motor_1 = wb_robot_get_device("motor1");
    WbDeviceTag motor_2 = wb_robot_get_device("motor2");
    WbDeviceTag motor_3 = wb_robot_get_device("motor3");
    WbDeviceTag motor_4 = wb_robot_get_device("motor4");

   /* SETTING POSITION OF THE MOTORS */
    wb_motor_set_position(motor_1, INFINITY);
    wb_motor_set_position(motor_2, INFINITY);
    wb_motor_set_position(motor_3, INFINITY);
    wb_motor_set_position(motor_4, INFINITY);

    /* IMPORTING DISTANCE SENSORS */
    WbDeviceTag distance_sensor = wb_robot_get_device("distance_sensor");

    /* ENABLING DISTANCE SENSORS */
    wb_distance_sensor_enable(distance_sensor, TIME_STEP);

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

        }
        else if (key == 'G') {
            robot_status = AUTONOMOUS;
            printf("AUTONOMOUS MODE ACTIVATED\n");
        }
        else {
            stopRobot(motor_1, motor_2, motor_3, motor_4);
        }

        switch (robot_status) {
            case MANUAL:     manual(key, motor_1, motor_2, motor_3, motor_4);
                             break;
            case AUTONOMOUS: autonomous(motor_1, motor_2, motor_3, motor_4,
                                        distance_sensor, desired_centimeters);
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

void manual(int key, WbDeviceTag motor_1, WbDeviceTag motor_2,
            WbDeviceTag motor_3, WbDeviceTag motor_4) {

    switch (key) {
        /* MOVE FORWARD */
        case WB_KEYBOARD_UP:    moveForwardRobotManual(motor_1, motor_2, motor_3,
                                                       motor_4);
                                break;
        /* MOVE BACKWARD */
        case WB_KEYBOARD_DOWN:  moveBackwardRobot(motor_1, motor_2,motor_3,
                                                  motor_4);
                                break;
        /* MOVE TO THE LEFT */
        case WB_KEYBOARD_LEFT:  moveLeftRobot(motor_1, motor_2, motor_3,
                                              motor_4);
                                break;
        /* MOVE TO THE RIGHT */
        case WB_KEYBOARD_RIGHT: moveRightRobot(motor_1, motor_2, motor_3,
                                               motor_4);
                                break;
        /* TURN TO THE LEFT */
        case 'A':               turnLeftRobot(motor_1, motor_2, motor_3,
                                              motor_4);
                                break;
        /* TURN TO THE RIGHT */
        case 'S':               turnRightRobot(motor_1, motor_2, motor_3,
                                               motor_4);
                                break;
        default:                stopRobot(motor_1, motor_2, motor_3,
                                          motor_4);
                                break;
    }

}

void autonomous(WbDeviceTag motor_1, WbDeviceTag motor_2,
                WbDeviceTag motor_3, WbDeviceTag motor_4,
                WbDeviceTag distance_sensor, float desired_centimeters) {

    /* READING VALUES */
    distance_sensor_value = wb_distance_sensor_get_value(distance_sensor);

    if (distance_sensor_value > desired_centimeters) {
        moveForwardRobotAutonomous(motor_1, motor_2, motor_3, motor_4);
    }
    else if (distance_sensor <= desired_centimeters) {
        stopRobot(motor_1, motor_2, motor_3, motor_4);
    }
}
