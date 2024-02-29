/*
 * File:   sensor.c
 * Author: USER
 *
 * Created on 9 de Novembro de 2023, 10:20
 */

#include <stdio.h>
#include <float.h>

#include "teds4.h"

#include <stdint.h> 
#include <string.h>

#include <xc.h>


#define _XTAL_FREQ 32000000


void define_METATEDS(void);
void define_TCTEDS(void);
void identify_NCAP_cmd(void);
void send_METATEDS(void);
void send_TCTEDS(uint8_t); 

void send_VALUE(uint8_t); 

//int getch(void);


//char get_char;

//create the structs for the Meta TEDS and for the TransducerChannels TEDS for 2 channels
struct METATEDS_TEMPLATE METATED;
struct TRANSDUCERCHANNEL_TEDS_TEMPLATE TCTEDS1;
struct TRANSDUCERCHANNEL_TEDS_TEMPLATE TCTEDS2;
struct TRANSDUCERCHANNEL_TEDS_TEMPLATE TCTEDS3;

//declaration of global variables and functions
void config7(void);
void LED5_ON(void);
void LED5_OFF(void);
void LED6_ON(void);
void LED6_OFF(void);
void __interrupt() int_handler(void); 
int parcel_lsb;
int parcel_msb;
int* comando2;   // pointer, faz o array

int contagem ;//Adcicionei  indice é do a
int comando[6];// Adicionei  a[6]
char get_char;


void putch(char);
int getch( void);





void main(void) {
    
    config7();
   
    define_METATEDS();
    
    define_TCTEDS();
   

    //PORTA=0b01000000;
    
    
    
    while (1) { 
        ;
  //Lembrar do free
    }
    //return;
}




void putch(char byte) //this function is required for the printf. It tells printf where to put the data. In this case, its to TX1REG
{
    
    while (PIR3bits.TX1IF == 0) {  
        ;
    }
    // Q: WHERE DO WE PUT A BYTE WHEN WE WANT TO SEND IT VIA UART?
    TX1REG = byte; /* transmit a character to Serial IO */
    
    
    //PORTA=0b01000000;

    //wait until it is sent
    while (PIR3bits.TX1IF == 0) {
        ;
    }
    
}
int getch(void )   //this function gets the received char from XXXXXX
{
    get_char= RC1REG;
    
    /// ver se acrecento aqui  
    
    return 0;
}




void define_METATEDS(void) {
    uint8_t array1[] = {3, 4, 0, 1, 0, 1};   // TEDS ID (nao mudei nada)
    memcpy(METATED.TEDSID, array1, 6);
    uint8_t array2[] = {4, 10, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4}; // UUID
    memcpy(METATED.UUID, array2, 12);
    uint8_t array3[] = {13, 2, 0, 3};  // MAX CHANNELS -> 3 pk é 1 sensor; 2 leds(atuadores)
    memcpy(METATED.MAXCHAN, array3, 4);

    return;
}

void define_TCTEDS(void) {
    //TCTEDS1 - TEDS DO TRANSDUCER CHANNEL 1 - SENSOR
    uint8_t array1[] = {3, 4, 0, 3, 0, 1}; //   ID
    memcpy(TCTEDS1.TEDSID, array1, 6);
    uint8_t array2[] = {11, 1, 0}; // CHANNEL TYPE -- SENSOR
    memcpy(TCTEDS1.CHANNEL_TYPE, array2, 3);
    uint8_t array3[] = {12, 10, 0, 128, 128, 132, 130, 122, 126, 128, 128, 128};
    
    // 2: 128 PK NAO TEMOS RADIANOS
    // 3: 128 //
    // 4: o resto é igual pk é volts e ja esta em volts
    memcpy(TCTEDS1.UNITS, array3, 12);
    uint8_t array4[] = {13, 1, 0}; // low
    memcpy(TCTEDS1.LOW_RANGE_LIMIT, array4, 3);
    uint8_t array5[] = {14, 1, 5}; // hight
    memcpy(TCTEDS1.HIGH_RANGE_LIMIT, array5, 3);
    uint8_t array6[] = {40, 1, 0}; // data model
    memcpy(TCTEDS1.DATA_MODEL, array6, 3);
    uint8_t array7[] = {41, 1, 1};// model lenght
    memcpy(TCTEDS1.DATA_MODEL_LENGTH, array7, 3);
    uint8_t array8[] = {42, 1, 8};
    memcpy(TCTEDS1.MODEL_SIG_BITS, array8, 3);
    
    
    //TCTEDS2 - TEDS DO TRANSDUCER CHANNEL 2 - atuador 1
    uint8_t array9[] = {3, 4, 0, 3, 0, 1}; //   ID
    memcpy(TCTEDS2.TEDSID, array9, 6);
    //memcpy(TCTEDS3.TEDSID, array9, 6);
    uint8_t array10[] = {11, 1, 1}; // CHANNEL TYPE -- led5
    memcpy(TCTEDS2.CHANNEL_TYPE, array10, 3);
   // memcpy(TCTEDS3.CHANNEL_TYPE, array10, 3);
    uint8_t array11[] = {12, 10, 0, 128, 128, 132, 130, 122, 126, 128, 128, 128};
  
    memcpy(TCTEDS2.UNITS, array11, 12);
    //memcpy(TCTEDS3.UNITS, array11, 12);
    uint8_t array12[] = {13, 1, 0}; // low nao sei se fica a 0 tbm
    memcpy(TCTEDS2.LOW_RANGE_LIMIT, array12, 3);
   // memcpy(TCTEDS3.LOW_RANGE_LIMIT, array12, 3);
    uint8_t array13[] = {14, 1, 5}; // hight
    memcpy(TCTEDS2.HIGH_RANGE_LIMIT, array13, 3);
   // memcpy(TCTEDS3.HIGH_RANGE_LIMIT, array13, 3);
    uint8_t array14[] = {40, 1,0}; // data model
    memcpy(TCTEDS2.DATA_MODEL, array14, 3);
   // memcpy(TCTEDS3.DATA_MODEL, array14, 3);
    uint8_t array15[] = {41, 1, 1};// model lenght
    memcpy(TCTEDS2.DATA_MODEL_LENGTH, array15, 3);
   // memcpy(TCTEDS3.DATA_MODEL_LENGTH, array15, 3);
    uint8_t array16[] = {42, 1, 8};
    memcpy(TCTEDS2.MODEL_SIG_BITS, array16, 3);
  //  memcpy(TCTEDS3.MODEL_SIG_BITS, array16, 3);
    
    //TCTEDS3=TCTEDS2;

    
    
    //TCTEDS2 - TEDS DO TRANSDUCER CHANNEL 3 - atuador 3
    uint8_t array17[] = {3, 4, 0, 3, 0, 1}; //   ID
    memcpy(TCTEDS3.TEDSID, array17, 6);
    uint8_t array18[] = {11, 1, 1}; // CHANNEL TYPE -- led5
    memcpy(TCTEDS3.CHANNEL_TYPE, array18, 3);
    uint8_t array19[] = {12, 10, 0, 128, 128, 132, 130, 122, 126, 128, 128, 128};
  
    memcpy(TCTEDS3.UNITS, array19, 12);
    uint8_t array20[] = {13, 1, 0}; // low nao sei se fica a 0 tbm
    memcpy(TCTEDS3.LOW_RANGE_LIMIT, array20, 3);
    uint8_t array21[] = {14, 1, 5}; // hight
    memcpy(TCTEDS3.HIGH_RANGE_LIMIT, array21, 3);
    uint8_t array22[] = {40, 1,0}; // data model
    memcpy(TCTEDS3.DATA_MODEL, array22, 3);
    uint8_t array23[] = {41, 1, 1};// model lenght
    memcpy(TCTEDS3.DATA_MODEL_LENGTH, array23, 3);
    uint8_t array24[] = {42, 1, 8};
    memcpy(TCTEDS3.MODEL_SIG_BITS, array24, 3);
    //define others TCTEDS you need here


    return;
}

void identify_NCAP_cmd(void) { 

    contagem=0;
   
        
    while (contagem < 6){  // é 6 pk tem pelo menos 6 valores de array nas querry do PIC
            
        //PORTA=0b01000000;  
        //PORTA=0b01000000; 
         
        if (PIR3bits.RC1IF==1){
            
            getch();
            //PORTA=0b00000000; 
                
            comando[contagem] = get_char;   // tinha colocado getch(); 
                
                
                //PIR3bits.RC1IF==0; // 0 ou 1 o mudou tava a 0
            
            
            contagem++; 
                
                
        } 
            
    }
    contagem=0;
    if (comando[4]!=0 || comando[5]!=0){  // 4 most significant bit do leght ; 5 least significant bit  da leght 
    
        int* comando2 = (int*)malloc(((int)comando[4]*256) + ((int)comando[5])); // malloc encontra espaço onde se pode guardar
        while(contagem<(comando[4]*256+comando[5])){
            if ( PIR3bits.RC1IF==1){   
                getch();
                comando2[contagem] = get_char; // mudei istotava get_char
                //PIR3bits.RC1IF==0; // o mjudou tava a 0
                contagem++;
                
            
            
        }
    
    //VERIFY WHAT COMMAND WAS RECEIVED FROM THE NCAP AND DECIDE WHAT TO DO       
}
    
    // METATEDS
    if(comando[2] == 1  && comando[3] == 2 && comando[0]==0 && comando[1]==0 && comando[4]==0 && comando[5]==2 && comando2[0]==1 && comando2[1]==0){//Query TEDS
           
        
        send_METATEDS();
        return;
    }
    // TC TEDS DE TDS OS CANAIS 
    else if( comando[2] == 1  && comando[3] == 2 && comando[0]==0 && comando[1]==1  && comando[4]==0 && comando[5]==2 && comando2[0]==3 && comando2[1]==0){
        //Query TEDS

                send_TCTEDS(1);
                return;
                
     }
    else if( comando[2] == 1  && comando[3] == 2 && comando[0]==0 && comando[1]==2  && comando[4]==0 && comando[5]==2 && comando2[0]==3 && comando2[1]==0){
        //Query TEDS

                send_TCTEDS(2);
                return;
                
    }
        
    else if( comando[2] == 1  && comando[3] == 2 && comando[0]==0 && comando[1]==3  && comando[4]==0 && comando[5]==2 && comando2[0]==3 && comando2[1]==0){
        //Query TEDS

                send_TCTEDS(3);
                return;
                
    }
    // LER !!!!!!!!!!!!!!!!111
    else if(comando[0]==0 && comando[1]>=1 && comando[1]<=3 && comando[2]==3 && comando[3]==1 && comando[4]==0 && comando[5]==1 && comando2[0]==0) {
        send_VALUE(comando[1]);
        
        return;
    
    }      


 // WRITE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11  NOS ATUADORES!!!!!!!!1
    else if ( comando[0]==0  && comando[1]==2 && comando[2] == 3 && comando[3]==2 && comando[4]== 0 && comando[5]==2  && comando2[0]==0 && comando2[1]==1  ){ //Transducer operating set   // comando class 
//                send_VALUE(1); //ACHO QUE É 1comando[3] == 2 && comando[2] //Write
            
            putch(1);
            putch(0);
            putch(0);
            LED5_ON();
    }
    else if (comando[0]==0  && comando[1]==2 && comando[2] == 3 && comando[3]==2 && comando[4]== 0 && comando[5]==2  && comando2[0]==0 && comando2[1]==0 ){
                putch(1);
                putch(0);
                putch(0);
                LED5_OFF();
                }
            
    else if (comando[0]==0  && comando[1]==3 && comando[2] == 3 && comando[3]==2 && comando[4]== 0 && comando[5]==2  && comando2[0]==0 && comando2[1]==1 ){
                
                    putch(1);
                    putch(0);
                    putch(0);
                    LED6_ON();
                }
    else if (comando[0]==0  && comando[1]==3 && comando[2] == 3 && comando[3]==2 && comando[4]== 0 && comando[5]==2  && comando2[0]==0 && comando2[1]==0 ){
                
                    putch(1);
                    putch(0);
                    putch(0);
                    LED6_OFF();
                }
                
                    //mensagem de erro
            
        
    
    else{
        putch(0);
        putch(0);
        putch(0);
    }
    

//Não é na flag que vai mandar é aqui
    
    //VERIFY WHAT COMMAND WAS RECEIVED FROM THE NCAP AND DECIDE WHAT TO DO

    free(comando2);
    return;
}
}


void send_METATEDS(void) {

    putch(1);
    putch(0);
    putch(22);
    for (int i = 0; i < 6; i++) {
        putch(METATED.TEDSID[i]);
    }
    for (int j = 0; j < 12; j++) {
        putch(METATED.UUID[j]);
    }
    for (int k = 0; k < 4; k++) {
        putch(METATED.MAXCHAN[k]);
    }
    return;
}


void send_TCTEDS(uint8_t channel) {
    if (channel == 1) {
        putch(1);
        putch(0);
        putch(36);

        for (int i = 0; i < 6; i++) {
            putch(TCTEDS1.TEDSID[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS1.CHANNEL_TYPE[i]);
        }
        for (int i = 0; i < 12; i++) {
            putch(TCTEDS1.UNITS[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS1.LOW_RANGE_LIMIT[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS1.HIGH_RANGE_LIMIT[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS1.DATA_MODEL[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS1.DATA_MODEL_LENGTH[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS1.MODEL_SIG_BITS[i]);
        }
    } 
    
     // acrecentei isto e mais a funçao de baixo

    

    // fazer isto para o LED5 e LED6
    else if (channel == 2) {
        putch(1);
        putch(0);
        putch(36);

        for (int i = 0; i < 6; i++) {
            putch(TCTEDS2.TEDSID[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS2.CHANNEL_TYPE[i]);
        }
        for (int i = 0; i < 12; i++) {
            putch(TCTEDS2.UNITS[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS2.LOW_RANGE_LIMIT[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS2.HIGH_RANGE_LIMIT[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS2.DATA_MODEL[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS2.DATA_MODEL_LENGTH[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS2.MODEL_SIG_BITS[i]);
        }
        
    }
    
    
    else if (channel == 3) {
        putch(1);
        putch(0);
        putch(36);

        for (int i = 0; i < 6; i++) {
            putch(TCTEDS3.TEDSID[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS3.CHANNEL_TYPE[i]);
        }
        for (int i = 0; i < 12; i++) {
            putch(TCTEDS3.UNITS[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS3.LOW_RANGE_LIMIT[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS3.HIGH_RANGE_LIMIT[i]);
        }
       
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS3.DATA_MODEL[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS3.DATA_MODEL_LENGTH[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS3.MODEL_SIG_BITS[i]);
        }
        
    }
    //the same procedure for other channel TEDS
    
    
    return;
}


void send_VALUE(uint8_t channel){
    if(channel == 1){
        putch(1);
        putch(0);
        putch(1);
        
        ADCON0bits.ADGO=1; //ADC conversion cycle in progress. Setting this bit starts an ADC conversion cycle. 
        while (PIR1bits.ADIF==0) { //espera até que a ADIF flag seja ativada, indicando que a conversão está completa
          ;
        }
        putch(ADRESH); //ADC Result Register bits
        
        
        putch(ADRESL); //ADC Result Register bits
        
        
        
    
    }
    
    
    else if (channel == 2){
        putch(1);
        putch(0);
        putch(1);
        
        putch(RA5);
        
        
    }
    
    else if (channel == 3){
        putch(1);
        putch(0);
        putch(1);
        putch(RA6); 
    
    }
  
    return; 
}

    
