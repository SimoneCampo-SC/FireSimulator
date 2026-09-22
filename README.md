# Fire Simulator

A console-based forest-fire simulation written in object-oriented C++, modelling probabilistic fire propagation across a grid with optional moisture and wind effects.

The project explores simulation logic, custom data structures, dynamic memory, object-oriented design and file-based reporting.

## How it works

The simulation represents a forest as a 21 × 21 grid.

The outer cells form the forest boundary, while the internal cells contain `Tree` objects. A burning tree is placed at the centre of the forest when the simulation begins.

Each simulation round is processed as a discrete timestep:

1. trees already burning at the beginning of the round are identified;
2. each burning tree attempts to ignite its north, south, east and west neighbours;
3. ignition is determined probabilistically;
4. the trees that were burning at the beginning of the round are consumed;
5. forest state and statistics are updated.

Newly ignited trees therefore begin propagating fire from the following timestep rather than during the same round.

## Environmental effects

The simulation can optionally enable moisture and wind effects.

### Soil moisture

When environmental effects are enabled, trees can be assigned either dry or moist soil.

Base ignition probability:

- dry tree — 60%
- moist tree — 40%

### Wind

A wind direction is selected from north, south, east or west, with a randomly generated speed between 10 and 35 km/h.

When fire spreads in the same direction as the wind, the wind speed is added to the ignition probability.

This produces a maximum ignition probability of:

- 95% for dry trees;
- 75% for moist trees.

## Data structures and design

The simulation uses a 2D array to represent the visual state of the forest while the underlying `Tree` objects are maintained in a custom singly linked list.

The main components are:

- `Forest` — manages the grid, fire propagation and simulation statistics;
- `Tree` — represents tree state, moisture and ignition probability;
- `ListOfTrees` — custom linked-list implementation used to manage active trees;
- `Wind` — models wind direction and speed;
- `Program` — handles user interaction and statistics reporting.

`Forest`, `Wind` and `ListOfTrees` use a Singleton-style design so that one shared instance is maintained during a simulation.

## Forest states

The console representation uses:

| Symbol | State |
| --- | --- |
| `0` | Forest boundary |
| `&` | Tree with dry soil |
| `@` | Tree with moist soil |
| `#` | Burning tree |
| ` ` | Consumed tree |

## Statistics

When the simulation ends, statistics are written to `statistics.txt`.

Depending on the selected mode, the report includes information such as:

- number of simulation rounds;
- total, live and consumed trees;
- burning trees;
- dry and moist tree counts;
- wind direction and speed.

The generated statistics file is excluded from version control.

## Building

An Xcode project is included in the repository.

The simulator can also be compiled directly with a C++ compiler from the repository root:

```bash
g++ -std=c++11 "Fire Simulator/"*.cpp -o fire-simulator
