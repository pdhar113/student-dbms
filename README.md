# Student Database Management System

A simple command-line student database implemented in C. It stores student records in a singly linked list and supports adding, displaying, searching, updating, and deleting records. Registration numbers are auto-generated from department code, enrollment year, and roll number.

**Features**
- Add student with name, roll, department (core/ai/ds/iot), year, and CGPA
- Auto-generate registration number: DEPT + YEAR + ROLL
- Display all records interactively
- Search, update, and delete individual records
- Delete all records on exit

**Files**
- `management.c` — main program source

**Build**
Requires a C compiler (GCC/Clang). Example (Windows with MinGW or WSL, or Linux/macOS):

```bash
gcc -o management management.c
```

**Run**

```bash
./management    # Linux/macOS/WSL
management.exe  # Windows (MinGW)
```

**Usage**
Run the program and choose from the menu (1–5) to interact with the database. Enter `0` to exit; the program clears all in-memory records on exit.

**Notes & Tips**
- Input is basic; follow prompts exactly (e.g., department values: `core`, `ai`, `ds`, `iot`).
- Registration numbers are formatted without separators (e.g., `CS2024101`).
- Data is stored only in memory — add persistence if you need to keep records between runs.

**License**
Unlicensed — add a license if you plan to share or reuse this project.
