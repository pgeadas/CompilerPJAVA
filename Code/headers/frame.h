#ifndef PJAVA_FRAME_H
#define PJAVA_FRAME_H

typedef struct _frame {
    struct _frame *parent;    // frame pointer - caller function
    void *locals[64];         // local variables address space
    void *outgoing[32];       // address space for arguments of called functions
    char *frame_buffer;       // used to store concat e println content
    int return_address;       // caller function address
} frame;

#endif
