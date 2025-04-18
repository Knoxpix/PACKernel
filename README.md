# PACKernel – macOS Kernel Extension (KEXT) PAC Demo

⚠️ This project is for **educational purposes only**. It demonstrates how pointer authentication (PAC) on Apple Silicon (ARM64e) enforces function pointer integrity in kernel space, and how function pointer reuse can simulate potential PAC bypass logic.

---

## 🔐 About Pointer Authentication

Apple Silicon implements [ARMv8.3-A Pointer Authentication (PAC)](https://developer.arm.com/documentation/100690/latest/) to mitigate memory corruption attacks like ROP (Return-Oriented Programming) and JOP (Jump-Oriented Programming).

This kernel extension shows how a function pointer (signed in the kernel with PAC) is safely called, and demonstrates how attackers could *reuse* signed pointers in PAC-related exploitation scenarios.

---

## 🧨 Related CVEs

The logic demonstrated in this PoC is conceptually related to real-world vulnerabilities where PAC was bypassed or misused, including:

- **CVE-2020-27930** – Memory corruption due to PAC misuse in iOS kernel context.
- **CVE-2022-26766** – An attacker with kernel privileges could exploit PAC to execute arbitrary code.
- **CVE-2023-28206** – Found in Apple WebKit, leveraging pointer reuse under specific sandbox evasion cases.
- **CVE-2025-31201** – (🔴 Actively exploited) PAC bypass vulnerability in Apple’s RPAC on macOS and iOS 18, patched in April 2025.

> These CVEs prove that PAC is not a silver bullet; when combined with memory leaks or improperly validated contexts, attackers can reuse signed pointers — just as demonstrated in the logic of this KEXT.

---

## 💻 Requirements

- macOS Monterey or earlier (macOS 12.x or lower)
- Apple Silicon (M1/M2/M3)
- Xcode 13.x or 14.x with KEXT support
- System Integrity Protection (SIP) **partially disabled** (optional)

---

## 📦 Project Structure

- `PACKernel.c` – Kernel logic demonstrating PAC-enforced pointer call
- `Info.plist` – KEXT metadata
- `PACKernel.xcodeproj` – Xcode project for building KEXT

---

## 🔧 Build Instructions

1. Open Terminal
2. Compile the KEXT using:

   ```bash
   sudo xcodebuild -project PACKernel.xcodeproj -target PACKernel -configuration Release
   ```

3. Load the KEXT:

   ```bash
   sudo kextload /path/to/PACKernel.kext
   ```

4. View kernel logs:

   ```bash
   log stream --predicate 'process == "kernel"' --info
   ```

## ❌ Unload the KEXT

```bash
sudo kextunload /path/to/PACKernel.kext
```

## 🧠 Notes

- You must use `IOLog()` instead of `printf()` in kernel space.
- This demo does not bypass PAC but shows how a function pointer is enforced at the hardware level.

---

📚 Educational use only – do not run on production systems.

- PAC helps protect return addresses and function pointers from being tampered with.
- However, attackers can sometimes reuse signed pointers or leak PAC-valid values, bypassing protection.
- This project helps demonstrate that principle safely in a controlled environment.

---

🔬 This KEXT is a safe academic demonstration and does not exploit any vulnerabilities. Use responsibly and only for research or internal testing.


MIT License | Created by Pituphong Yavirach
