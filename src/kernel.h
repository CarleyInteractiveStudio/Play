#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void * malloc(size_t size);
void free(void * ptr);
char * strdup(const char * s);

#ifdef __cplusplus
}
#endif

#endif // KERNEL_H
