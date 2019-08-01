#include "project.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

char my_string[100]=" ";
char my_string_cpy[100]=" ";
uint32 mi_edad=21;
int i=-1;
char my_char=' ';

int my_flag=0;
int count=0;

#define TAM 100


//Declarando funciones///
void try_show(char string[]);
float Distance_sensor();


///////////Function/////////////
#define RADIUS_WHEELS 0.04
#define MAX_VELOCITY 10.4719
#define PI 3.141592


/* Global Variables */
float circunference = 0;
float meters_traveled = 0;
float resolution = 0.3141;
float angular_position = 0;

float my_meters=0, my_angular=0;

/* Protofunctions */
float metersTraveled(float radius);
float angularPosition(void);
void Encoder(float* my_meters, float* my_angular);

/* Variables dependientes a las protos */

int read_D0 = 0;
int counter = 0;
int _flag = 0;
char str1[100];

//////////////////////////////////////////////

char string[TAM]="Hola mundo"; //Variable string para imprimir
float my_value=0;              // variable que contiene el valro flotante.

///////////////////////////////



void Uart_GetString();
void my_split();





#define true 1


int max_period=299;
void wheel_velocity(int percent,char y);
void wheel2_velocity(int percent,char y);
void wheel3_velocity(int percent,char y);
void wheel4_velocity(int percent,char y);

//Variables to my split in c//
char cad[] = "Luis,Rafa,Angelo";
const char separador = ',';
char* ptr = cad;
char list[10][10]={" ",
				   " ",
				   " "};
int k=0;
int flag=1;


////////////////////////////////

////////////Teclas////////////
int int_key=0;

enum direction{
    arriba=259,
    abajo=258,
    derecha=261,
    izquierda=260,
    quiet=0
};
char a='u',b='u',c='u',d='u'; //Variables para la velocidad de el carro


char state=' ';


int main(void)
{
    CyGlobalIntEnable;
    UART_Enable();
    UART_Start();
    UART2_Enable();
    UART2_Start();
    Timer_Start(); //Inicia el Timer
    
    //Estar  pwm//
    PWM_Enable(); PWM2_Enable(); PWM3_Enable(); PWM4_Enable(); 
    PWM_Start();  PWM2_Start();  PWM3_Start(); PWM4_Start();
    PWM_WritePeriod(max_period); PWM2_WritePeriod(max_period); PWM3_WritePeriod(max_period); PWM4_WritePeriod(max_period);

    
    //Velocidad de la llanta//
    //wheel_velocity(100,'u');
    //wheel2_velocity(100,'u');
    
    enum direction key_pressed=quiet;    
    
    
    
    for(;;)
    {
        //Leyendo el teclado//
        state=UART_GetChar();
        
        //my_value=Distance_sensor(); //Lee el sensor        
        //sprintf(string,"Obstaculo a %.2f cm... for ", my_value); // Convierte el entero a string
        //try_show(string); // Muestra el string en pantalla
            
        
        if(state=='r'){
            LED_Write(1u);
            UART_PutString("OK\n");
            
             
            
            //Uart_GetString();
            
            //CyDelay(1000);
            //while(my_flag==0){
/////////////////////////////////////////////////////////
            while(1){
                //UART_PutString("Hola\n");
                my_char=UART_GetChar();
                count++;              
                if(count>=300){
                    break;    
                }
                
                if(my_char=='#'){
                    break;   
                }
                if(my_char!=' '){
                    strcat(my_string,&my_char);
                }
                //UART_PutString(my_string);
                CyDelay(10);
                //UART_PutChar(0xC);
                //CyDelay(100);
            }
////////////////////////////////////////////////////////////////
            
            strcpy(my_string_cpy,my_string);
            ptr=my_string;
            ptr = strtok(my_string_cpy,",");
            while (ptr) {
    		
    		    //printf("\n%s",ptr);
    		    strcpy(list[k],ptr);
    		    ptr=strtok(NULL,",");
    		    //
    		    k++;
    	    }
            k=0;
/////////////////////////////////////////////////////////////////////////////////////////
            
            
            //my_split();
            
            if(strcmp(my_string_cpy," $PSOC")==0 || strcmp(my_string_cpy,"$PSOC")==0){
            //if(strncmp(list[0]," $PSOC")==0 || strcmp(list[0],"$PSOC")==0){
                //UART_PutString("Prendido\n");
                //UART_PutString(list[1]);
                CyDelay(10);
                
                //Velocidad de la llanta//
                wheel_velocity(atoi(list[2]),list[1][0]);
                wheel2_velocity(atoi(list[4]),list[3][0]);
                wheel3_velocity(atoi(list[6]),list[5][0]);
                wheel4_velocity(atoi(list[8]),list[7][0]);
                //my_value=Distance_sensor();
                
                LED_Write(1u);
                CyDelay(10);
            }
            strcpy(my_string,""); strcpy(list[0],""); strcpy(list[1],""); strcpy(list[2],""); strcpy(ptr,"");
            strcpy(my_string,"");
            //state= UART_GetChar();
            //UART_PutChar(0xC);
            //UART_PutString("DONE\n");
            state=' ';
            count=0;
            
            
            CyDelay(10);
            Encoder(&my_meters, &my_angular); ///////
                //UART_PutString("Hola mundo");
                
            //}
            
        }


                
        
        else{
            
            //my_value=Distance_sensor(); //Lee el sensor    
            //sprintf(string,"Obstaculo a %.2f cm... else", my_value); // Convierte el entero a string
            //try_show(string); // Muestra el string en pantalla
            
            count++;
            LED_Write(0u);
            if(count>=350){
                //my_value=Distance_sensor(); //Lee el sensor        
                //sprintf(string,"Obstaculo a %.2f cm if count", my_value); // Convierte el entero a string
                //try_show(string); // Muestra el string en pantalla
            
                //LED_Write(0u);
                wheel_velocity(0,'d');
                wheel2_velocity(0,'d');
                wheel3_velocity(0,'d');
                wheel4_velocity(0,'d');
                CyDelay(10);
            }
        }
        
        CyDelay(10);


    }
}

void wheel_velocity(int percent,char y){
    int x=(max_period*percent)/100;
    if(y=='u'){
        PWM_WriteCompare1(x);
        PWM_WriteCompare2(0);
    }
    else if(y=='d'){
        PWM_WriteCompare2(x);
        PWM_WriteCompare1(0);
    }
}
void wheel2_velocity(int percent,char y){
    int x=(max_period*percent)/100;
    if(y=='u'){
        PWM2_WriteCompare1(x);
        PWM2_WriteCompare2(0);
    }
    else if(y=='d'){
        PWM2_WriteCompare2(x);
        PWM2_WriteCompare1(0);
    }
}
void wheel3_velocity(int percent,char y){
    int x=(max_period*percent)/100;
    if(y=='u'){
        PWM3_WriteCompare1(x);
        PWM3_WriteCompare2(0);
    }
    else if(y=='d'){
        PWM3_WriteCompare2(x);
        PWM3_WriteCompare1(0);
    }
}
void wheel4_velocity(int percent,char y){
    int x=(max_period*percent)/100;
    if(y=='u'){
        PWM4_WriteCompare1(x);
        PWM4_WriteCompare2(0);
    }
    else if(y=='d'){
        PWM4_WriteCompare2(x);
        PWM4_WriteCompare1(0);
    }
}

void Uart_GetString(){
    while(1){
        //UART_PutString("Hola\n");
        my_char=UART_GetChar();
        count++;              
        if(count>=300){
            break;    
        }
        
        if(my_char=='#'){
            break;   
        }
        if(my_char!=' '){
            strcat(my_string,&my_char);
        }
        //UART_PutString(my_string);
        CyDelay(10);
        //UART_PutChar(0xC);
        //CyDelay(100);
    }
    
}

void my_split(){
    strcpy(my_string_cpy,my_string);
    ptr=my_string;
    ptr = strtok(my_string_cpy,",");
    while (ptr) {
	
	    //printf("\n%s",ptr);
	    strcpy(list[k],ptr);
	    ptr=strtok(NULL,",");
	    //
	    k++;
    }
    k=0;   
    
}
void try_show(char string[]){ // Pasale el string completo
    UART2_PutString(string); 
    CyDelay(500);
    UART2_PutChar(0xC);
}

float Distance_sensor(){
    
    int value_counter=0;
    float distancia=0;
    int state=0; //Lee el estado de echo//
    state=Echo_Read();
    
    //sprintf(string,"Hoy es %d",day);  //Convierte el entero en string//
    //try_show(string);
    
    
    while(Echo_Read()==0){
        Trigger_out_Write(1);
        CyDelay(10u);
        Trigger_out_Write(0);
        CyDelay(1);
    }
    while(Echo_Read()==1){
     //Wait
        //try_show("estoy aqui");    
    }
    
    value_counter=65536-Timer_ReadCounter();
    //Ya que el counter cuenta desendente
    //hay que restarle para obtener el acendente.
    distancia=value_counter/58.0; //igual a centrimos aplicando el datasheet//
    return distancia;   
}
///////////////////////////7
float metersTraveled(float radius) {
    circunference = (2 * PI)*(radius);
    meters_traveled = meters_traveled + circunference;
    return meters_traveled;
}
float angularPosition(void) {
    angular_position = angular_position + resolution;
    return angular_position;
}
void Encoder(float* my_meters, float* my_angular){
    
    read_D0 = D0_Read();
    
    if(read_D0 == 0 && _flag == 1){
        _flag = 0;
    }
        
    if (read_D0 == 1 && _flag == 0){
        _flag = 1;
        counter++;    
        *my_angular=angularPosition();
        if (counter == 20) {
            *my_meters=metersTraveled(RADIUS_WHEELS);
            counter = 0;  
        }   
    }
}
