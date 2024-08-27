Sure, I'll walk you through the steps for creating a shared library (dynamic library) instead of a static library. The process involves compiling source files into position-independent code (PIC), creating the shared library, and linking against that shared library in your driver program.

### Step-by-Step Instructions for Shared Library

#### 1. Compile the `.c` Files into Position-Independent Object Files

Shared libraries require position-independent code. You compile the source files with the `-fPIC` flag to generate position-independent code.

```bash
gcc -fPIC -c myadd.c -o myadd.o
gcc -fPIC -c mydiv.c -o mydiv.o
gcc -fPIC -c mymul.c -o mymul.o
gcc -fPIC -c mysub.c -o mysub.o
```

- `-fPIC`: Generates position-independent code suitable for use in shared libraries.

#### 2. Create the Shared Library Using `gcc`

You use `gcc` to create the shared library from the position-independent object files.

```bash
gcc -shared -o libmymath.so myadd.o mydiv.o mymul.o mysub.o
```

- `gcc`: The GNU Compiler Collection command.
- `-shared`: Creates a shared library.
- `-o libmymath.so`: Specifies the name of the shared library file (with `.so` extension).
- `myadd.o`, `mydiv.o`, `mymul.o`, `mysub.o`: The position-independent object files.

#### 3. Use the Shared Library in Your Driver Program

You need to compile `prog1.c` and link it against `libmymath.so`. You'll also need to ensure that the directory containing `libmymath.so` is included in the library search path at runtime.

Change directory to `driver` and run:

```bash
gcc -I../ -o prog1 prog1.c -L../ -lmymath
```

- `-L../`: Adds the parent directory to the list of directories to be searched for libraries at link time.
- `-lmymath`: Links against `libmymath.so`. The `-l` flag is followed by the name of the library without the `lib` prefix and `.so` suffix.

To run the `prog1` executable, you may need to set the `LD_LIBRARY_PATH` environment variable to include the directory where `libmymath.so` is located, so the runtime linker can find it:

```bash
export LD_LIBRARY_PATH=../:$LD_LIBRARY_PATH
./prog1
```

- `LD_LIBRARY_PATH`: An environment variable specifying the directories where the runtime linker should look for dynamic libraries.

### Summary of Compiler and Linker Flags for Shared Libraries

1. **Compiler Flags:**
   - `-fPIC`: Generate position-independent code suitable for shared libraries.

2. **Linker Flags:**
   - `-shared`: Create a shared library.
   - `-L`: Specifies the directory to search for libraries during linking.
   - `-l`: Links against a library. The library name should be provided without the `lib` prefix and `.so` suffix.

### Example Commands

```bash
# Compile source files into position-independent object files
gcc -fPIC -c myadd.c -o myadd.o
gcc -fPIC -c mydiv.c -o mydiv.o
gcc -fPIC -c mymul.c -o mymul.o
gcc -fPIC -c mysub.c -o mysub.o

# Create the shared library
gcc -shared -o libmymath.so myadd.o mydiv.o mymul.o mysub.o

# Compile and link the driver program
cd driver
gcc -I../ -o prog1 prog1.c -L../ -lmymath

# Set the library path and run the executable
export LD_LIBRARY_PATH=../:$LD_LIBRARY_PATH
./prog1
```

Following these steps will let you compile your C source files into position-independent object files, create a shared library, and link your driver program against that shared library. Let me know if you have more questions!