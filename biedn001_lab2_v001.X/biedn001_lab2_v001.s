.include "xc.inc"          ; required "boiler-plate" (BP)

;the next two lines set up the actual chip for operation - required
config __CONFIG2, POSCMOD_EC & I2C1SEL_SEC & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSECME & FNOSC_FRCPLL & SOSCSEL_LPSOSC & WUTSEL_FST & IESO_OFF
config __CONFIG1, WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & BKBUG_ON & GWRP_ON & GCP_ON & JTAGEN_OFF

    .bss        ; put the following labels in RAM
counter:
    .space 2    ; a variable that takes two bytes (we won?t use
                ; it for now, but put here to make this a generic
                ; template to be used later).
stack:
    .space  32  ; this will be our stack area, needed for func calls

.text           ; BP (put the following data in ROM(program memory))

write_bit_stream:
    ;2 for function call
    repeat #14 ;1 cycle
    nop ;n + 1 cycles
    clr LATA ;1 cycle
    repeat #29
    nop
    inc LATA
    return ;3 for return

delay_100_micro:
    ;1600 cycles total
    repeat #1593
    nop
    return
    
delay_1_milli:
    ;16000 cycles total
    repeat #15993
    nop
    return
    
;1.25microsecond period, 20 cycles
;assume starting low
write_0:
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
write_1:
    ;0.55us-0.85us
    inc LATA
    repeat #8
    nop
    clr LATA
    ;0.45us-0.75us
    nop
    nop
    return
    
;because we are using the C compiler to assemble our code, we need a "_main" label
;somewhere. (There's a link step that looks for it.)
.global _main               ;BP
_main:
    bclr    CLKDIV,#8                 ;BP
    nop
    ;; --- Begin your program below here ---
    MOV #0x9FFF, W0
    MOV W0, AD1PCFG
    
    MOV #0b1111111111111110, W0
    MOV W0, TRISA
    
    ;reset, 50us
    clr LATA
    repeat #798
    nop
 
    ;8 green, 8 red, 8 blue
    ;red: 80
    call write_0
    call write_0
    call write_0
    call write_0
    call write_0
    call write_0
    call write_0
    call write_1
    ;green: 00
    call write_0
    call write_0
    call write_0
    call write_0
    call write_0
    call write_0
    call write_0
    call write_1
    ;blue: 80
    call write_0
    call write_0
    call write_0
    call write_0
    call write_0
    call write_0
    call write_0
    call write_0
    
    foreverLoop:
    bra foreverLoop
    .end




