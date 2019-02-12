.include "xc.inc"

.text ;BP (put the following data in ROM(program memory))

; This is a library, thus it can *not* contain a _main function: the C file will
; deine main().  However, we
; we will need a .global statement to make available ASM functions to C code.
; All functions utilized outside of this file will need to have a leading 
; underscore (_) and be included in a comment delimited list below.
.global _write_0, _write_1, _delay_100_micro, _delay_1_milli
   
_delay_100_micro:
    ;1600 cycles total
    repeat #1593
    nop
    return
    
_delay_1_milli:
    ;16000 cycles total
    repeat #15993
    nop
    return
    
;1.25microsecond period, 20 cycles
;assume starting low
_write_0:
    ;0.2us-0.5us
    inc LATA
    repeat #3
    nop
    clr LATA
    ;0.65us-0.95us
    repeat #6
    nop
    return

;1.25us period, 20 cycles
_write_1:
    ;0.55us-0.85us
    inc LATA
    repeat #8
    nop
    clr LATA
    ;0.45us-0.75us
    nop
    nop
    return
    


