# Collisions

A C++ particle collision simulation built with SFML. The project renders a 2D window filled with circular particles, updates their movement each frame, and resolves elastic collisions between particles and the window boundaries.

## Features

- 2D particle simulation using `sf::CircleShape`
- Elastic collision response between particles
- Boundary collision handling against the render window
- Configurable particle count, particle size, velocity, acceleration, and window size
- Visual Studio solution configured for Debug and Release builds
- SFML headers and libraries included locally in the repository

## Preview

The app opens an `800x600` SFML window and displays particles moving and colliding in real time.

## Requirements

- Windows
- Visual Studio 2022
- MSVC toolset `v143`
- Windows 10 SDK

SFML is already vendored in this repository:

- Headers: `include/SFML/`
- Libraries: `lib/`
- Runtime DLLs: `x64/Debug/` and `x64/Release/`

## Getting Started

1. Clone the repository.

   ```bash
   git clone <repository-url>
   cd collisions
   ```

2. Open the solution in Visual Studio.

   ```text
   collisions.sln
   ```

3. Select a build configuration.

   Recommended:

   ```text
   Release | x64
   ```

4. Build and run the project from Visual Studio.

   ```text
   Build > Build Solution
   Debug > Start Without Debugging
   ```

## Running a Built Executable

Prebuilt outputs may exist under:

```text
x64/Debug/collisions.exe
x64/Release/collisions.exe
```

Run the executable from its output folder so the required SFML DLLs can be found beside it.

## Project Structure

```text
.
|-- collisions.sln
|-- collisions/
|   |-- collisions.cpp
|   `-- collisions.vcxproj
|-- include/
|   `-- SFML/
|-- lib/
|   `-- *.lib
`-- x64/
    |-- Debug/
    `-- Release/
```

## Configuration

Most simulation values are currently set near the top of `main()` in `collisions/collisions.cpp`:

```cpp
Vector2f window_size = Vector2f(800, 600);
int framerate = 60;
int no_of_particles = 1000;
int max_particle_size = 10;
int min_particle_size = 10;
Vector2f particle_velocity = Vector2f(250, 250);
Vector2f particle_acceleration = Vector2f(0, 0);
```

Adjust these values and rebuild to change the simulation behavior.

## Known Limitations

- Fast particles can tunnel through other particles or walls.
- Collision checks currently use a simple pairwise approach, which does not scale well to very large particle counts.
- The boundary is currently the display window; custom boundary shapes are not implemented yet.
- Initial particle placement has basic spacing, but very small particles can still spawn inside larger particles in some cases.

## Roadmap

- Add continuous collision detection to reduce tunneling.
- Add broad-phase collision detection for better performance.
- Support custom simulation boundaries such as circles, rectangles, and polygons.
- Improve spawn placement so particles never start overlapped.

## License

No license file is included yet. Add a license before publishing or reusing this project publicly.
