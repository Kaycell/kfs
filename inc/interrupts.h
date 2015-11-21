#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

struct regs
{
    unsigned int ds; /* data segment */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss; /* pushed by processor */
};

void interrupts_init(void);

#endif


