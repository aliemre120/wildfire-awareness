# Wildfire Awareness & Reporting (C + SQLite)
> TR Bu proje, orman yangını farkındalığını artırmak ve basit bir SQLite tabanlı sistemle yangın raporlamasını kolaylaştırmak amacıyla geliştirilmiştir.
> EN This project has been developed to raise awareness about forest fires and to facilitate fire reporting with a simple SQLite-based system.

A bilingual (TR/EN) console app to **estimate wildfire risk**, **report new fires**, **mark extinguished fires**, and **list active/all fires** using a local **SQLite** database.

https://github.com/aliemre120/wildfire-awareness

---

## ✨ Features
- **Language menu (TR/EN)**
- **Risk prediction** based on temperature & humidity
- **Report new wildfire** (writes to SQLite DB)
- **Mark fire as extinguished**
- **List active** and **list all** reported wildfires
- Simple, portable C codebase (no frameworks)

## 📁 Project Structure
```
.
├─ main.c               # CLI and language menus
├─ risk.c / risk.h      # Risk matrix & awareness text
├─ db.c / db.h          # SQLite operations (init/insert/update/select)
├─ wildfire.db          # SQLite database file (auto-created if missing)
└─ wildfire_new.exe     # (Optional) Prebuilt Windows binary (use Releases instead)
```

> **Tip:** Prefer publishing binaries via **GitHub Releases** instead of committing large `.exe` files to main. Keep `wildfire.db` empty or add a **seed script** below.

---

## 🧰 Requirements
- **SQLite** (runtime + headers)
- **gcc/clang** toolchain

### Windows (MSYS2/MinGW) quick start
1. Install [MSYS2](https://www.msys2.org/) and open *MSYS2 MinGW x64* shell.
2. Install packages:
   ```bash
   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-pkg-config mingw-w64-x86_64-sqlite3
   ```
3. Build:
   ```bash
   gcc main.c db.c risk.c -o wildfire -Wall -Wextra -O2 $(pkg-config --cflags --libs sqlite3)
   ```
4. Run:
   ```bash
   ./wildfire
   ```

### Linux (Debian/Ubuntu)
```bash
sudo apt update
sudo apt install build-essential pkg-config libsqlite3-dev
gcc main.c db.c risk.c -o wildfire -Wall -Wextra -O2 $(pkg-config --cflags --libs sqlite3)
./wildfire
```

### macOS (Homebrew)
```bash
brew install sqlite pkg-config
gcc main.c db.c risk.c -o wildfire -Wall -Wextra -O2 $(pkg-config --cflags --libs sqlite3)
./wildfire
```

---

## ▶️ Usage (CLI)
On launch, choose a language:
```
1. Türkçe
2. English
3. Exit/Cikis
```
Then the main menu provides:
- (1) Learn about wildfires & actions
- (2) Risk prediction
- (3) Report a new wildfire
- (4) Report an extinguished wildfire
- (5) View reported current wildfires
- (6) View all reported wildfires
- (7) Back to language menu
- (8) Exit

---

## 🗄️ Database
Schema is created automatically on first run:
```sql
CREATE TABLE IF NOT EXISTS fires (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  datetime TEXT NOT NULL,
  location TEXT NOT NULL,
  status TEXT NOT NULL CHECK(status IN('active','extinguished'))
);
```

### Seed examples
You can prefill sample data with the app (menu 3) or via SQLite:
```sql
INSERT INTO fires(datetime, location, status) VALUES
('2025-07-20 15:30','İzmir/Bornova','active'),
('2025-07-21 11:05','Muğla/Menteşe','extinguished');
```

---

## 📸 Screenshots / GIF
Add console screenshots or a short demo **GIF**:
- Record with **ShareX** (Windows) / **OBS** / **QuickTime** (macOS).
- Convert to GIF (ShareX) or `ffmpeg`:
  ```bash
  ffmpeg -i demo.mp4 -vf "fps=12,scale=960:-1:flags=lanczos" -loop 0 demo.gif
  ```
- Place in `assets/` and embed here.

---

## 📦 Releases
1. Create a **tag** (e.g. `v1.0.0`).
2. Build binaries locally.
3. Upload `wildfire_new.exe` (include `sqlite3.dll` if needed) to **GitHub Releases**.

---

## 🧪 Testing ideas
- Insert multiple fires and list active/all.
- Try marking the same ID extinguished twice (second call should be no-op).
- Input validation around menus and temperature/humidity ranges.

 **GitHub Topics:** `c`, `sqlite`, `console-app`, `wildfire`, `disaster-tech`, `bilingual`, `cli`

---

## 🛡️ License
This project is licensed under the **MIT License** (see `LICENSE`).


## 🤝 Contributing
PRs and issues are welcome. For larger changes, please open an issue first to discuss.

---

## 📧 Contact
- LinkedIn: [Ali Emre Yılmaz](https://www.linkedin.com/in/ali-emre-y%C4%B1lmaz-96510a34b/)
- Email: aliemreyilmaz120@gmail.com
