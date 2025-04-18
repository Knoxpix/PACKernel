
#include <libkern/libkern.h>
#include <mach/mach_types.h>

void kernel_secret() {
    IOLog("[KEXT] secret from kernel called!\n");
}

kern_return_t PACKernel_start(kmod_info_t * ki, void *d) {
    void (*fn)() = kernel_secret;

    // ใน kernel PAC จะถูก enforce จริง
    fn();

    return KERN_SUCCESS;
}

kern_return_t PACKernel_stop(kmod_info_t *ki, void *d) {
    IOLog("[KEXT] Unloaded\n");
    return KERN_SUCCESS;
}
