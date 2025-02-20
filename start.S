
    .text
    .arm
    .long   0xc0ffebee
    .long   __image_start
    .long   __bss_start
    .long   __bss_end
    .long   __rel_dyn_start
    .long   __rel_dyn_end
    .fill   1024 - 24, 1, 0

    .globl _start

_start:
    push    {r4, lr}

    /* Call main */
    ldr     r0, =main
    blx     r0

    pop     {r4, pc}

/*
 * The location of section
 */
    .align 4
_data_start:
    .long __data_start
_data_end:
    .long __data_end
_bss_start:
    .long __bss_start
_bss_end:
    .long __bss_end
