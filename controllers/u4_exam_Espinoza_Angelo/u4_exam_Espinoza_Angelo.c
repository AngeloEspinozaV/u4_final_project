/*
 * File:          u4_exam_Espinoza_Angelo.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/keyboard.h>

#define TIME_STEP 64

#define VELOCITY_ROBOT 10


/* PROTOFUNCTIONS */
void stopRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag motor_3,
               WbDeviceTag motor_4);

void moveForwardRobot(WbDeviceTag motor_1, WbDeviceTag motor_2,
                            WbDeviceTag motor_3, WbDeviceTag motor_4);

void moveBackwardRobot(WbDeviceTag motor_1, WbDeviceTag motor_2,
                       WbDeviceTag motor_3, WbDeviceTag motor_4);
void moveLeftRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag
                   motor_3, WbDeviceTag motor_4);

void moveRightRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag
                  motor_3, WbDeviceTag motor_4);

int main(int argc, char **argv)
{

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

   /* ENABLING THE KEYBOARD */
    wb_keyboard_enable(TIME_STEP);

   /* VARIABLES */
    int key;

    while (wb_robot_step(TIME_STEP) != -1) {
        key = wb_keyboard_get_key();

        switch (key) {
            case WB_KEYBOARD_UP:    moveForwardRobot(motor_1, motor_2, motor_3,
                                                     motor_4);
                                    break;
            case WB_KEYBOARD_DOWN:  moveBackwardRobot(motor_1, motor_2,motor_3,
                                                      motor_4);
                                    break;
            case WB_KEYBOARD_LEFT:  moveLeftRobot(motor_1, motor_2, motor_3,
                                                  motor_4);
                                    break;
            case WB_KEYBOARD_RIGHT: moveRightRobot(motor_1, motor_2, motor_3,
                                                   motor_4);
                                    break;
            default:                stopRobot(motor_1, motor_2, motor_3,
                                              motor_4);
                                    break;
        }
    };

    wb_robot_cleanup();
    return 0;
}

void stopRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag motor_3,
               WbDeviceTag motor_4) {
    wb_motor_set_velocity(motor_1, 0);
    wb_motor_set_velocity(motor_2, 0);
    wb_motor_set_velocity(motor_3, 0);
    wb_motor_set_velocity(motor_4, 0);
}

void moveForwardRobot(WbDeviceTag motor_1, WbDeviceTag motor_2,
                      WbDeviceTag motor_3, WbDeviceTag motor_4) {
    wb_motor_set_velocity(motor_1, VELOCITY_ROBOT);
    wb_motor_set_velocity(motor_2, VELOCITY_ROBOT);
    wb_motor_set_velocity(motor_3, VELOCITY_ROBOT);
    wb_motor_set_velocity(motor_4, VELOCITY_ROBOT);
}

void moveBackwardRobot(WbDeviceTag motor_1, WbDeviceTag motor_2,
                       WbDeviceTag motor_3, WbDeviceTag motor_4) {
    wb_motor_set_velocity(motor_1, -VELOCITY_ROBOT);
    wb_motor_set_velocity(motor_2, -VELOCITY_ROBOT);
    wb_motor_set_velocity(motor_3, -VELOCITY_ROBOT);
    wb_motor_set_velocity(motor_4, -VELOCITY_ROBOT);
}

void moveLeftRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag
                   motor_3, WbDeviceTag motor_4) {
    wb_motor_set_velocity(motor_1, VELOCITY_ROBOT);
    wb_motor_set_velocity(motor_2, VELOCITY_ROBOT);
    wb_motor_set_velocity(motor_3, VELOCITY_ROBOT);
    wb_motor_set_velocity(motor_4, VELOCITY_ROBOT);
}
void moveRightRobot(WbDeviceTag motor_1, WbDeviceTag motor_2, WbDeviceTag
                    motor_3, WbDeviceTag motor_4) {
    wb_motor_set_velocity(motor_1, VELOCITY_ROBOT);
    wb_motor_set_velocity(motor_2, VELOCITY_ROBOT);
    wb_motor_set_velocity(motor_3, VELOCITY_ROBOT);
    wb_motor_set_velocity(motor_4, VELOCITY_ROBOT);
}
