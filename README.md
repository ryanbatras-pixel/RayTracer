# Raytracer

A simple raytracer written in C++.

Inspired by: [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)

This project renders a red sphere on top of a blue-white gradient background and writes the image in PPM format.

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/raytracer > image.ppm
```

On Windows with a multi-config CMake generator, the executable may be inside `build/Debug` or `build/Release`:

```powershell
.\build\Release\raytracer.exe > image.ppm
```

## Project Structure

```text
.
|-- CMakeLists.txt
|-- README.md
`-- src
    |-- ray.h
    |-- raytracer.cpp
    `-- vector.h
```
