#ifndef _MEM_H_
#define _MEM_H_

#include "../cpu/types.h"

void memory_copy(u8 *source, u8 *dest, int nbytes);
void memory_set(u8 *dest, u8 val, u32 len);

// Malloc
u32 kmalloc(u32 size, int align, u32 *phys_addr);

#endif /* _MEM_H_ */