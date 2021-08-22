#ifndef _IPC_H
#define _IPC_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <sys.h>

bool register_ipc_port(uint16_t port);
bool deregister_ipc_port(uint16_t port);
uint8_t transfer_ipc(uint16_t port, void *data, size_t size);
size_t receive_ipc_size(uint16_t port);
uint8_t receive_ipc(uint16_t port, void *data);
void waitipc(int32_t port);

#endif
