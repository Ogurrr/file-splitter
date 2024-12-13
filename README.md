# File Splitter & Merger

This project consists of two tools:

1. **File Splitter** – splits a large file into smaller chunks.
2. **File Merger** – merges smaller files back into the original file.

## Description

These tools are useful when working with very large files that need to be divided into smaller pieces for easier transfer or storage. The first program splits the file into smaller chunks of a specified size, and the second allows you to merge those chunks back into a single file.

### File Splitter

This program splits an input file into smaller pieces of a specified size. Each chunk is saved into a separate file.

#### Usage

1. Copy the file you want to split.
2. Run the program, passing the file path and chunk size in bytes. For example:

```bash
./splitter my_large_file.txt 1048576
```
3. To unsplit your file, type:

```bash
./unsplitter my_large_file.txt
```

4. done

## COMPILATION
1. Create build folder, and go to this folder
```bash
mkdir build && cd build
```
2. Run CMake
```bash
cmake .. && make
```
## LICENSE
This project is licensed under the GNU General Public License v3.0.

