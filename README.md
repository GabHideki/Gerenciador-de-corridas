# Race Management System (Terminal)

Hi, this is my first project at UTFPR.  
This project is a terminal-based race management system developed in C, designed to manage athletes, training sessions, and race competitions.

---

## Overview

The system simulates the organization of a race event, allowing the user to:

- Register athletes (manually or automatically)
- Perform training sessions
- Classify competitors
- Manage a final competition
- Display rankings and statistics

---

## Features

### Athlete Management
- Register athletes with:
  - Name
  - Country
  - Gender
  - Birth date
- Validation of all input data
- Automatic random athlete generation

---

### Training System
- Manual or automatic training input
- Stores multiple times per athlete
- Identifies best performance

---

### Classification
- Selects top 8 competitors based on performance
- Sorting system based on time

---

### Final Competition
- Define competition name and date
- Insert final times
- Generate final ranking:
  - Gold
  - Silver
  - Bronze

---

### Data Visualization
- List all competitors
- Filter by:
  - Country
  - Gender
- Show oldest athletes
- Display zodiac signs:
  - List of signs per athlete
  - Percentage distribution chart (text-based)

---

## Concepts Used

This project applies core programming concepts:

- Structs (`struct`)
- Modularization (functions)
- Arrays and data manipulation
- Sorting algorithms
- Input validation
- Menu-driven interface
- Random data generation (`rand()`)

---

## System Rules

- Maximum of 100 athletes
- Only athletes 45+ years old (based on July 31, 2024)
- Allowed countries:
  - Brazil
  - USA
  - England
  - Jamaica
  - Saudi Arabia
- Only top 8 athletes advance to final competition

---

## How to Run

### Compile
```bash
gcc main.c -o race
````
### Execute

````bash
./race
````

### Project Structure

````bash
main.c   # Main source code (single-file implementation)
````

## Known Limitations

- Uses global variables (`controle`)
- Input handling may have edge cases (`scanf` + `fgets`)
- Single-file structure (not modularized into multiple files)

---

## Future Improvements

- Remove global variables
- Split into multiple `.c` and `.h` files
- Improve input handling
- Add file persistence (save/load data)
- Enhance terminal interface

---

## Author

Gabriel Hideki  
Software Engineering Student at UTFPR

---

## License

This project is for academic purposes.
