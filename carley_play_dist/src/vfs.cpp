#include "vfs.h"
#include "kernel.h"
#include <string.h>

static vfs_fd_t fd_table[MAX_FDS];

void vfs_init(void)
{
    memset(fd_table, 0, sizeof(fd_table));
}

int open(const char *pathname, int flags, ...)
{
    for(int i = 0; i < MAX_FDS; i++) {
        if(!fd_table[i].active) {
            if(fat32_open(pathname, &fd_table[i].fat_file) == 0) {
                fd_table[i].active = 1;
                fd_table[i].cursor = 0;
                return i;
            }
            break;
        }
    }
    return -1;
}

int close(int fd)
{
    if(fd >= 0 && fd < MAX_FDS) fd_table[fd].active = 0;
    return 0;
}

long read(int fd, void *buf, size_t count)
{
    if(fd < 0 || fd >= MAX_FDS || !fd_table[fd].active) return -1;

    int bytes = fat32_read(&fd_table[fd].fat_file, fd_table[fd].cursor, count, (uint8_t*)buf);
    fd_table[fd].cursor += bytes;
    return bytes;
}
