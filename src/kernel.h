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

// --- POSIX LITE (Para Motores de Juego) ---
typedef int pid_t;
typedef uint32_t mode_t;
typedef long off_t;

int open(const char *pathname, int flags, ...);
int close(int fd);
long read(int fd, void *buf, size_t count);
long write(int fd, const void *buf, size_t count);
off_t lseek(int fd, off_t offset, int whence);

#ifdef __cplusplus
}
#endif

#endif // KERNEL_H
