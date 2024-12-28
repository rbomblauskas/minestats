# Minestats

This module analyses Minesweeper matches saved in CSV format, and generates `leaderboard.html` and `matches.html`

## Installation and Usage Instructions

### System Requirements

- **OS:** Ubuntu 22.04
- **Tools:** `make`, `gcc`
  
Installation:
```bash
sudo apt install build-essential
```
### Dependencies
- `libcsv`

Installation:
```bash
sudo apt install libcsv-dev
```

### Compilation instructions:

Run the `make` command:

```bash
make
```

This will compile an executable file (./gen).