
#include <stdio.h>
#include <stdint.h>

// จำลองการลงลายเซ็น pointer ด้วย XOR
uintptr_t fake_pac_sign(uintptr_t ptr, uintptr_t context) {
    return ptr ^ context;
}

// จำลองการตรวจสอบลายเซ็น (authenticate)
uintptr_t fake_pac_auth(uintptr_t ptr, uintptr_t context) {
    return ptr ^ context;
}

// ฟังก์ชันเป้าหมาย
void secret() {
    printf("[+] เรียกใช้งาน secret() สำเร็จ!\n");
}

int main() {
    uintptr_t context = 0xCAFEBABEDEADBEEF; // สมมติ context สำหรับลงลายเซ็น

    // สร้าง pointer แบบธรรมดา
    void (*original_ptr)() = secret;
    printf("[*] Original pointer: %p\n", original_ptr);

    // Sign pointer ด้วยฟังก์ชันจำลอง
    uintptr_t signed_ptr = fake_pac_sign((uintptr_t)original_ptr, context);
    printf("[*] Signed pointer (PAC): 0x%lx\n", signed_ptr);

    // Authenticate ก่อนใช้งาน
    uintptr_t verified_ptr = fake_pac_auth(signed_ptr, context);
    printf("[*] Verified pointer: %p\n", (void *)verified_ptr);

    // เรียกใช้งาน pointer ที่ผ่านการตรวจสอบ
    void (*final_fn)() = (void (*)())verified_ptr;
    final_fn();

    return 0;
}
