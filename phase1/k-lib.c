// k-lib.c, 159

#include "k-include.h"
#include "k-type.h"
#include "k-data.h"

// clear DRAM data block, zero-fill it
void Bzero(char *p, int bytes) {
   memcpy(p, 0, bytes);
}

int QisEmpty(q_t *p) { // return 1 if empty, else 0
   return p->size == 0;
}

int QisFull(q_t *p) { // return 1 if full, else 0
   return p->size == Q_SIZE;
}

// Dequeue, 1st # in queue; if queue empty, return -1
// Move rest to front by a notch, set empty spaces -1
int DeQ(q_t *p) { // return -1 if q[] is empty

   int i, x;

   if(QisEmpty(p)) {
      return -1;
   }

   x = p->q[0];

   p->size--;

   for(i = 0; i < p->size-1; i++){
      p->q[i] = p->q[i+1];
   }

   return x;

}

// If not full, enqueue # to tail slot in queue.
void EnQ(int to_add, q_t *p) {
   if(QisFull(p)) {
      cons_printf("Panic: queue is full, cannot EnQ!\n");
   }
   else {
      p->q[p->size] = to_add;
      p->size++;
   }
}

