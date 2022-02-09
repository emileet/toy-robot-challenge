# Toy Robot Challenge

An application to simulate a toy robot moving on a square table top.

## Description

The application is a simulation of a toy robot moving on a square table top, of dimensions 5 units x 5 units. There are no other obstructions on the table surface. The robot is free to roam around the surface of the table, but must be prevented from falling to destruction. Any movement that would result in the robot falling from the table must be prevented, however further valid movement commands must still be allowed.

## Dependencies

* CMake (>=3.12)
* GoogleTest (1.11.0)

## Instructions

### Building

```shell
cmake -B build
cmake --build build
```

### Running

```shell
./build/TestToyRobot # unit tests
./build/ToyRobot      # main application
```

### Commands

| Command | Action |
| ------ | ------ |
| **PLACE X,Y,FACING** | Places the robot at the given X,Y,(NORTH,SOUTH,EAST,WEST) values |
| **MOVE** | Moves the robot 1 unit in the direction it's facing |
| **LEFT** | Rotates the robot 90degrees to the left |
| **RIGHT** | Rotate the robot 90degrees to the right |
| **REPORT** | Announces the X,Y,Facing values of the robot |
| **EXIT** | Quits the application |

## Notes

- This project was developed for linux, where CMake and GoogleTest can be retrieved with your distributions respective package manager
- If you can't use GoogleTest, remove the last four lines from `CMakeLists.txt`
- This project was built successfully with GCC 11.1.0
