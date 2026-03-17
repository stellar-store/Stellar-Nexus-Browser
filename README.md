# Stellar-Nexus-Browser
Navegador Web Ligero escrit0 en C++ y QT del navegador web enfocada en la ligeresa y la modernidad. Es el navegador web  principal del ecosistema Stellar, tiene soporte para pestañas, historial, marcadores,traductor, descargas y configuración.


Es desarrollado, empaquetado y distribuido por GBonachea bajo B&R.Corp y ART Ripoll (art.ripoll@aol.com)

<img width="1366" height="731" alt="stellar" src="https://github.com/user-attachments/assets/9c0ced6f-e899-457e-89aa-9096214f30f1" />
## Dependencias

| Package | Ubuntu/Debian | Fedora/RHEL |
|---------|--------------|-------------|
| Qt6 Base | `qt6-base-dev` | `qt6-qtbase-devel` |
| Qt6 WebEngine | `qt6-webengine-dev` | `qt6-qtwebengine-devel` |
| CMake | `cmake` | `cmake` |
| Build tools | `build-essential` | `gcc-c++ make` |

### Ubuntu / Debian

```bash
sudo apt update
sudo apt install qt6-webengine-dev qt6-base-dev cmake build-essential
```

If Qt6 is unavailable, Qt5 also works:

```bash
sudo apt install qtwebengine5-dev qt5-default cmake build-essential
```

### Fedora / RHEL

```bash
sudo dnf install qt6-qtwebengine-devel qt6-qtbase-devel cmake gcc-c++
```

### Arch Linux

```bash
sudo pacman -S qt6-webengine cmake base-devel
```

---

## Build & Run

```bash
chmod +x run.sh
./run.sh

# O simplemente (si ya tiene dependencias instaladas):
chmod +x build.sh
./build.sh

# Ejecutar
./build/stellar

# Abrir una URL directamente
./build/stellar https://example.com
```

---
## Keyboard Shortcuts

| Shortcut | Action |
|----------|--------|
| `Ctrl+T` | New tab |
| `Ctrl+W` | Close current tab |
| `Ctrl+L` | Focus URL bar |
| `Ctrl+D` | Bookmark current page |
| `Ctrl+B` | Show bookmarks |
| `Ctrl+H` | Show history |
| `Ctrl+J` | Show downloads |
| `Ctrl+,` | Open settings |
| `Ctrl+R` / `F5` | Reload |
| `Alt+Left` | Back |
| `Alt+Right` | Forward |
| `F11` | Toggle fullscreen |
| `Ctrl+Tab` | Next tab |
| `Ctrl+Shift+Tab` | Previous tab |

---
