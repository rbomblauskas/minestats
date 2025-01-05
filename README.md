# Minestats

This module analyses Minesweeper matches saved in CSV format, and generates `leaderboard.html`, `matches.html` and individual match pages.

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
Run in `generator` directory:
```bash
# Generate both matches and leaderboard
./gen <matches.csv> <output_directory>

# Generate matches only
./gen -m <matches.csv> <output_location>

# Generate leaderboard only
./gen -l <matches.csv> <output_location>
```
