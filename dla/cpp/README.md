dla
===

Simulating diffusion-limited aggregation.

Example usage:
```bash
$ simulate -w 256 -h 256 -o data.out [-v]
```
Verbose mode writes the position of each new anchor to stdout, which can take forever if your grid is large.

A Python plotting script (plot.py) is included for convenience; simply run
```bash
$ python plot.py data.out
```
to view a visualization of the final system.
