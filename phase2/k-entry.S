// k-entry.S, entries to kernel services, build process trapframe

#include "k-const.h"
#include <spede/machine/asmacros.h> // do not use/include "spede.h"
#define K_STACK_SIZE (PROC_STACK_SIZE * 8) // kernel has 32KB stack

.comm k_stack, K_STACK_SIZE, 1      // declare kernel stack space (16K x 1B)
.text

// load proc trapframe to run it
ENTRY(Loader) // loads proc trapframe to run it
   movl 4(%esp), %ebx
   movl %ebx, %esp
   popa
   add $4, %esp // (add $4 to %esp -- skip 'entry_id' in trapframe) <-- !!!
   iret


ENTRY(TimerEntry)
   pushl $TIMER_INTR
   jmp PreKernel


ENTRY(GetPidEntry)
   pushl $GETPID_CALL
   jmp PreKernel


ENTRY(SleepEntry)
   pushl $SLEEP_CALL
   jmp PreKernel


ENTRY(ShowCharEntry)
   pushl $SHOWCHAR_CALL
   jmp PreKernel


PreKernel: // build rest of trapframe, switch stack, pass arg, call Kernel
   pusha   // push all: eax ecx edx ebx esp ebp esi edi
   movl %esp, %ebx          // copy esp
   movw $0x10, %ax          // put 16 to ax
   mov %ax, %ds             // set kernel data segment registers ds
   mov %ax, %es             // set kernel data segment registers es
   leal k_stack + K_STACK_SIZE, %esp  // set esp to top of kernel stack
   pushl %ebx               // push (proc TF addr) there
   cld                      // clear direction flag bit
   call CNAME(Kernel)       // call Kernel code
