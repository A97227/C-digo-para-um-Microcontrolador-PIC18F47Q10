#include <xc.inc>
    
GLOBAL _int_handler, _identify_NCAP_cmd
    
PSECT intcode 
    
#define parcel_lsb 0
#define parcel_msb 0
    
    
_int_handler:
    
    
    BANKSEL PIR0
    
    BTFSC PIR0, 5 ;tava a 0 antes
    
    GOTO _timer0_int_handler
    
    BANKSEL PIR1
    
    BTFSC PIR1, 0
    
    GOTO _adc_int_handler 
    
    
    BANKSEL PIR3
    BTFSC PIR3,5 ;check if the EUSART1 RX flag is set. If so, go to the C function _getch. If not, skip.  
    CALL _identify_NCAP_cmd
    
    
    RETFIE 

_timer0_int_handler:
    Banksel ADCON0
    
    BSF ADCON0, 0
    
 
    BANKSEL PIR0
    BCF PIR0, 5
    
    
    
    RETFIE
    
_adc_int_handler:
    
    
;    BANKSEL ADRESH   ; registro do resultado, quando faz  a conversão vai para
    ;AQUI ; H--> HIGHEST
    
    
;    MOVFF ADRESH, parcel_msb 
;    
;    BANKSEL ADRESL
;    
;    MOVFF ADRESL, parcel_lsb
;    
;    
;    BANKSEL TX1REG
;   
;    MOVFF parcel_lsb, TX1REG
    
    
    BANKSEL PIR1
    
    BCF PIR1, 0
    
    RETFIE
    
    
    
    
    
    
