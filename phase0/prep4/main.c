//*********************************************************************
// NAME: Ryan Kozak
//
// main.c of 159, phase 0, prep 4, Timer Interrupt
//*********************************************************************


#include <spede/flames.h>
#include <spede/machine/io.h>
#include <spede/machine/proc_reg.h>
#include <spede/machine/seg.h>
#include <spede/machine/pic.h>
#include <spede/time.h> // From service.c

#define VID_MASK 0x0f00     // foreground bright white, background black.
#define TIMER_INTR 32       // TIMER_INTR constant identifier.
#define PIC_MASK 0x21       // Programmable Interrupt Controller I/O.
#define MASK ~0x01          // Mask for Programmagle Interrupt Controller.
#define PIC_CONTROL 0x20    // Programmable Interrupt Controller I/O.
#define TIMER_DONE 0x60     // Sent to PIC control when timer intr service done.

__BEGIN_DECLS
extern void TimerEntry(void);
void TimerCode(void);
__END_DECLS



void TimerCode() {
  
  static int count = 0;

  count++;

  cons_putchar('.');

  outportb(PIC_CONTROL, TIMER_DONE);

}



int main() {
 
  char ch;
  struct i386_gate *intr_table;

  intr_table = get_idt_base();

  fill_gate(&intr_table[TIMER_INTR], (int)TimerEntry, get_cs(), ACC_INTR_GATE, 0);

  outportb(PIC_MASK, MASK);

  asm("sti");

  while(1) {
    if( cons_kbhit() ) {
      ch = cons_getchar();
      if(ch=='b') {
        breakpoint();
      }
      else{
        cons_printf("thanks for pressing a key\n");
      }
    }  
  }

  return 0;
}
