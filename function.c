
//
//  function.c
//  Vehicle Control system
//
//  Created by Youssef on 01/10/2023.


#include "function.h"
#include <stdio.h>
#include <string.h>

#define WITH_ENGINE_TEMP_CONTROLLER 1

ui16 Engine_state;
ui16 AC;
ui16 Vehicle_Speed;
ui16 current_room_temp;
ui16 E_T_C_S;
ui16 current_engine_temp;

void displayVehicleState(ui16 Engine_state, ui16 AC, ui16 Vehicle_Speed, ui16 current_room_temp, ui16 E_T_C_S, ui16 current_engine_temp);
void Ask_the_user(void);
void on_vehicle_engine(void);
void off_vehicle_engine(void);

//===================================================

void displayVehicleState(ui16 Engine_state, ui16 AC, ui16 Vehicle_Speed, ui16 current_room_temp, ui16 E_T_C_S, ui16 current_engine_temp)
{
    printf("       Current Vehicle State :   \n");
    printf(" - Engine state: %s\n", Engine_state ? "ON" : "OFF");
    printf(" - AC: %s\n", AC ? "ON" : "OFF");
    printf(" - Vehicle Speed: %hu km/hr\n", Vehicle_Speed);
    printf(" - Room Temperature: %hu\n", current_room_temp);
    printf(" - Engine Temperature Controller State: %s\n", E_T_C_S ? "ON" : "OFF");
    printf(" - Engine Temperature: %hu\n", current_engine_temp);
    printf("\n");
}

//================== Ask_the_user ===================

void Ask_the_user(void)
{
    char input;

    while (1)
    {

        printf(" - [a] Turn on the vehicle engine\n");
        printf(" - [b] Turn off the vehicle engine\n");
        printf(" - [c] Quit the system\n\n");

        printf(" - What do you need?  :  ");
        scanf(" %c", &input);

        switch (input)
        {
        case 'a':
        {
            on_vehicle_engine();
            break;
        }
        case 'b':
        {
            off_vehicle_engine();
            break;
        }
        case 'c':
        {
            ui16 check;
            printf("Do you really want to exit? [1]Yes , [2]No ");
            scanf("%hu", &check);
            if (1 == check)
            {
                printf(" - Thank you for using the system :) \n");
                return;
            }
            break;
        }
        default:
        {
            printf(" - Invalid choice. Please try again \n");
            break;
        }
        } //switch


    } //while
}

//================== [1] on_vehicle_engine ===================

void on_vehicle_engine(void) // (((((
{
    si8 light_color;
    char input;
    Engine_state = 1;

    printf(" ==============================================\n");
    printf(" ============ ON Vehicle Engine  =============\n");
    printf(" ==============================================\n\n");

    printf(" -----------  Sensors set menu  -----------\n\n");
    printf(" - [a] Turn off the engine\n");
    printf(" - [b] Set the traffic light color.\n");
    printf(" - [c] Set the room temperature\n");
    printf(" - [d] Set the engine temperature\n\n");
    printf(" - Enter your choice: ");
    scanf(" %c", &input);

    while (1)
    {

        switch (input)
        {

        case 'a':
        {
            if (Engine_state == 1)
            {
                off_vehicle_engine();
                break;
            }
            else
            {
                printf("The engine is already turned off.\n\n");
                break;
            }
        }
        case 'b':
        {
            printf("Enter the traffic light color (G/O/R): ");
            scanf(" %c", &light_color);

            switch (light_color)
            {
            case 'G':
                {
                    Vehicle_Speed = 100;
                    break;
                }

            case 'O':
                {
                    Vehicle_Speed = 30;
                    break;
                }
            case 'R':
                {
                    Vehicle_Speed = 30;
                    break;
                }

            default:
                {
                    printf("Invalid Traffic Light Color.\n");
                    break;
                }
            } // switch
            break;
        }
        case 'c':
        {
            printf("Enter the room temperature: ");
            scanf("%hu", &current_room_temp);

            if (current_room_temp < 10 || current_room_temp > 30)
            {
                AC = 1;
                current_room_temp = 20;
            }
            break;
        }
        case 'd':
        {
            printf("Enter the engine temperature: ");
            scanf("%hu", &current_engine_temp);
#if WITH_ENGINE_TEMP_CONTROLLER
                if (current_engine_temp < 100 || current_engine_temp>150 )
                {
                    E_T_C_S = 1;
                    current_room_temp = 125 ;
                }
                else
                {
                    E_T_C_S = 0;
                }
#endif
                break ; // **
            }

//            if (current_engine_temp < 100 || current_engine_temp > 150)
//            {
//                printf("Invalid engine temperature.\n");
//            }

            break;

        default:
        {
            printf("Invalid choice. Please try again\n");
            break;
        }

        } //switch

        if (Vehicle_Speed == 30 )
        {

            if (AC == 0 )
            { AC = 1 ;
                current_room_temp =  (current_room_temp * (5/4)) + 1 ;  // =    current_room_temp =* (5/4) + 1
            }
#if WITH_ENGINE_TEMP_CONTROLLER

            if (E_T_C_S == 0)
            {   E_T_C_S = 1 ;
                current_engine_temp =( current_engine_temp * (5/4)) + 1 ;
            }
#endif

        }

        displayVehicleState(Engine_state, AC, Vehicle_Speed, current_room_temp, E_T_C_S, current_engine_temp);

        printf(" -----------  Sensors set menu  -----------\n\n");
        printf(" - [a] Turn off the engine\n");
        printf(" - [b] Set the traffic light color.\n");
        printf(" - [c] Set the room temperature\n");
        printf(" - [d] Set the engine temperature\n\n");
        printf(" - Enter your choice: ");
        scanf(" %c", &input);

    } //while

} //on_vehicle_engine

//================== [2] off_vehicle_engine ===================

void off_vehicle_engine(void)
{
    Engine_state = 0;
    AC = 0;
    Vehicle_Speed = 0;
    current_room_temp = 0;
    E_T_C_S = 0;
    current_engine_temp = 0;

    printf(" ==============================================\n");
    printf(" ============ OFF Vehicle Engine  ============\n");
    printf(" ==============================================\n\n");

    displayVehicleState(Engine_state, AC, Vehicle_Speed, current_room_temp, E_T_C_S, current_engine_temp);
}


/*
 
 */
