
# PACKernel – macOS Kernel Extension (KEXT) PAC Demo

⚠️ This project is for educational purposes. It demonstrates calling a function through a pointer in kernel space, where PAC (Pointer Authentication Codes) are enforced by Apple Silicon hardware.

## 💻 Requirements

- macOS Monterey or earlier (macOS 12.x or lower)
- Apple Silicon (M1/M2/M3)
- Xcode 13.x or 14.x with KEXT support
- System Integrity Protection (SIP) **partially disabled** (optional)

## 📦 Project Structure

- `PACKernel.c` – Main kernel logic that demonstrates pointer execution
- `Info.plist` – Kernel extension metadata

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
