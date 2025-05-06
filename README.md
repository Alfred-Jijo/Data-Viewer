# Data-Viewer

---

## Building and Running the Project

This project uses a `Makefile` to build and run a mixed C++ and C codebase.

### Build the Project

To compile the project in **debug** mode (default):

```bash
make
```

The compiled binary will be located at:

```
out/debug/data-viewer
```

### Run the Program

After building, you can run the program with:

```bash
make run
```

### Clean the Build

To remove compiled files and the output directory:

```bash
make clean
```

### Build in Release Mode

For an optimized build, use the `BUILD=release` flag:

```bash
make BUILD=release
```

Output binary will be in:

```
out/release/data-viewer
```

### Optional Customization

You can override compilers or install prefix (not used yet):

```bash
make CXX=clang++ CC=clang PREFIX=/usr/local
```

---