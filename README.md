# Rabbit Fox Island

Semester Project for COSC 40703: High Performance and Parallel Computing

## Description

Once upon a time there was an island populated only by rabbits, foxes, and vegetation. The island (conveniently enough) was the exact shape of a chessboard. Some local geographers have even drawn gridlines the serve to divide the island into 64 squares to facilitate their demographic studies on the populations of each inhabitant.

## Build and Run

To build the project, run the following commands in the main directory containing CMakeLists.txt:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

To run the project, run the following command in the build directory:

```bash
./RabbitFoxIsland
```

## Idea

- Have a 2D grid (vector of 8 vectors with 8 values) representing each square on the island.
- 3 options
  - Processor 0 handles all border squares, remaining 6 processors handle each row of squares.
  - Processor 0 handles all border squares, remaining 6 processors handle each column of squares.
  - processor 0 handles all border squares, remaining 36 processors handle each square.
- Using option 1 for now.
- Each processor will have a 2D grid (vector of 8 vectors with 8 values) representing the squares it is responsible for.
- Have a square class that does calculations and holds the values of the square.
- Have a rabbit struct that holds the values of the rabbit.
- Have a fox struct that holds the values of the fox.
- Have a vegetation struct that holds the values of the vegetation.
- Have a function that initializes the island with rabbits, foxes, and vegetation.
- Have a function that updates the island based on the rules of the game.
- Have a function that prints the island.

## Authors

- [Aaryan Dehade](https://github.com/dehadeaaryan)
- [Mann Patel](https://github.com/Mann1562)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
