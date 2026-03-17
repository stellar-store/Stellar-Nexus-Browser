# ⬡ Stellar Nexus Browser

A modern, minimal web browser built with C++ and Qt — featuring a distinctive dark interface with accent color theming, multi-tab support, and a clean monospace aesthetic.

---

## Features

| Feature | Details |
|---------|---------|
| **Multi-tab** | Custom-drawn tab bar with close buttons, middle-click to close |
| **Navigation** | Back, Forward, Reload, Home buttons |
| **Smart URL bar** | Detects URLs vs search queries automatically |
| **Bookmarks** | Add, view, search, and open bookmarks |
| **Downloads** | File download manager with progress |
| **History** | Browsing history with search and clear |
| **Settings** | Dark/light mode, accent color picker, search engine, privacy |
| **Home page** | Custom live clock home page with search integration |
| **Keyboard shortcuts** | Full shortcut support (see below) |

---

## Dependencies

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

## Customization

All settings are persisted via `QSettings` (stored in `~/.config/StellarBrowser/`).

- **Accent color** — any color from the palette or a custom picker
- **Dark / Light mode** — toggle in Settings → Appearance
- **Search engine** — DuckDuckGo, Google, Bing, Startpage, Brave, Ecosia
- **Home page** — set to any URL or keep `nexus://home`

---

## Architecture

```
Nexus/
├── CMakeLists.txt          # Build configuration
├── build.sh                # Build helper script
├── src/
│   ├── main.cpp            # Entry point
│   ├── mainwindow.*        # Main window orchestrator
│   ├── tabbar.*            # Custom-drawn tab bar
│   ├── navbar.*            # Navigation bar + URL input
│   ├── browserpage.*       # WebEngine view wrapper + home page
│   ├── bookmarkmanager.*   # Bookmark storage + dialog
│   ├── downloadmanager.*   # Download handling + dialog
│   ├── historymanager.*    # History storage + dialog
│   └── settingsdialog.*    # Settings UI
└── resources/
    └── resources.qrc
```

---

## License

MIT — free to use, modify, and distribute.
