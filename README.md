# Minestats

This module analyses Minesweeper matches saved in CSV format, and generates `leaderboard.html`.

Test it here: http://rokoserveris.gw.lt/

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
cd generator
make
```

This will compile an executable file (./gen).

### Usage

To generate the `leaderboard.html` file, simply run (in `generator` directory):
```bash
./gen matches.csv ../frontend/leaderboard.html
```
