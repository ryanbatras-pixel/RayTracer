RayTracer-CPP

A CPU-based ray tracer written in modern C++ that generates photorealistic images by simulating the behavior of light rays in a 3D scene.

Overview

This project was created to explore the fundamentals of computer graphics and rendering. Instead of relying on graphics APIs such as OpenGL or DirectX, every pixel is computed manually using ray tracing techniques.

The renderer supports multiple material types, reflections, refractions, soft shadows, depth of field, and emissive lighting to produce realistic images from mathematically defined scenes.

Example Output

Features
Ray-sphere intersection calculations
Diffuse (Lambertian) materials
Metallic surfaces with adjustable roughness
Glass materials with realistic refraction
Emissive light sources
Recursive ray bouncing
Anti-aliasing through multi-sampling
Depth of field simulation
Multithreaded rendering using C++ threads
Procedural scene generation
Technical Concepts Implemented
Ray Tracing

For every pixel, rays are cast from the virtual camera into the scene. The renderer determines which object each ray intersects and calculates the resulting color based on material properties and lighting.

Materials

Three physically-inspired material models are implemented:

Lambertian — matte surfaces that scatter light diffusely
Metal — reflective surfaces with configurable roughness
Dielectric — transparent materials such as glass that support refraction
Recursive Light Transport

When a ray hits an object, secondary rays are generated to simulate reflection and refraction. This process is repeated recursively to approximate realistic light behavior.

Depth of Field

The camera supports aperture-based sampling, producing realistic background blur similar to a real camera lens.

Parallel Rendering

Rendering is distributed across available CPU cores using C++ multithreading, significantly reducing image generation time.

Project Structure
src/
├── main.cpp          # Program entry point
├── camera.h          # Camera and rendering system
├── ray.h             # Ray mathematics
├── vec3.h            # Vector operations
├── hittable.h        # Object intersection framework
├── sphere.h          # Sphere primitives
├── material.h        # Material implementations
├── scene.h           # Scene generation
└── rtweekend.h       # Utility functions
How It Works
A virtual camera generates rays through every pixel.
Rays are tested against objects in the scene.
Material properties determine how rays scatter.
Additional rays are recursively traced.
Color contributions are accumulated.
The final image is written as a PPM file.
Building
Requirements
C++17 or newer
g++ compiler
Compile
g++ -std=c++17 -O2 src/main.cpp -o raytracer
Run
./raytracer

The rendered image will be saved as:

render.ppm
What I Learned

Through this project I gained practical experience with:

3D vector mathematics
Geometric intersection algorithms
Recursive algorithms
Physically-based rendering concepts
Multithreaded programming
Performance optimization in C++
Future Improvements
Triangle mesh support
OBJ model loading
Bounding Volume Hierarchies (BVH)
Texture mapping
HDR environment lighting
Progressive rendering preview
GPU acceleration
References

The project was inspired by concepts presented in the book:

📖 Ray Tracing in One Weekend

while extending the implementation with custom scene generation, multithreading, emissive lighting, and camera effects.
