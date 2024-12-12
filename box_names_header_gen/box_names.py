#!/usr/bin/env python3
import csv


# Generate header file for box names
with open('./box_names.csv', 'r') as f:
    reader = csv.reader(f)
    # Skip header
    next(reader)
    atoms = []
    for row in reader:
        atom = row[0]

        # The ISO 14996-12 document displays duplicate atom names
        # but with different levels
        # Add to cache to avoid duplicate atom names
        if atom in atoms:
            continue

        atoms.append(atom)
        indent_lvl = int(row[1])
        indent = "  " * indent_lvl
        print(f"{indent}#define ATOM_{atom.upper()} \"{atom}\"")
