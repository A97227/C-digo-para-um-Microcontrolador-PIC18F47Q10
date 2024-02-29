
#include <xc.inc>
    
Global _LED6_ON, _LED6_OFF, _LED5_ON, _LED5_OFF

    
PSECT intcode
    
    
    
_LED5_ON:
    BANKSEL LATA
    
    BSF LATA, 5
    RETURN
_LED5_OFF:
    BANKSEL LATA
    BCF LATA, 5
    RETURN
    
_LED6_ON:
    BANKSEL LATA
    BSF LATA, 6
    RETURN
    
_LED6_OFF:
    BANKSEL LATA
    BCF LATA, 6
    RETURN 

