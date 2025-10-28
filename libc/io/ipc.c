#include <ipc.h>

bool register_ipc_port(uint16_t port) {
	return _syscall1(28, port);
}

bool deregister_ipc_port(uint16_t port) {
	return _syscall1(29, port);
}

uint8_t transfer_ipc(uint16_t port, void *data, size_t size) {
	return _syscall3(31, port, (uint32_t)data, size);
}

size_t receive_ipc_size(uint16_t port) {
	return _syscall1(30, port);
}

uint8_t receive_ipc(uint16_t port, void *data) {
	return _syscall2(32, port, (uint32_t)data);
}

void waitipc(int32_t port) {
	_syscall1(33, port);
}
