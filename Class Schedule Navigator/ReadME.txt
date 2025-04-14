Class Schedule Navigator
========================

Description
-----------
Class Schedule Navigator is a C-based application designed to help students manage their daily class schedules and navigate between campus locations efficiently. It provides functionalities to view the day's schedule and determine the optimal time and route to leave for the next class.

Features
--------
- View today's schedule with subject names, timings, and locations.
- Identify the next class based on the current time.
- Calculate the shortest path between campus locations using Dijkstra's algorithm.
- Provide real-time updates on whether you are early, late, or on time for your next class.

How It Works
------------
1. **Graph Representation**: The campus is represented as a graph where nodes are locations and edges are paths with weights (time in minutes).
2. **Dijkstra's Algorithm**: Used to compute the shortest path between two locations.
3. **Linked List for Schedule**: Each day's schedule is stored as a linked list for efficient traversal and management.

Usage Instructions
------------------
1. Compile the program using any C compiler:
2. Run the program:
3. Choose an option from the menu:
- Press `1` to view today's schedule.
- Press `2` to check when to leave for your next class.

Input Details
-------------
- For schedule viewing:
- The program automatically fetches today's schedule based on the system date.
- For navigation:
- Enter your current location by selecting from a list of predefined campus spots (e.g., PRP = 1, SJT = 2, etc.).

Output Examples
---------------
- **Schedule View**:

- **Class Navigation**:

Campus Locations Mapping
------------------------
| Code | Location          |
|------|-------------------|
| 1    | PRP              |
| 2    | SJT              |
| 3    | N-Block          |
| ...  | ...              |
| 13   | Outside VIT      |

Dependencies
------------
This program uses standard C libraries such as:
- `<stdio.h>` for input/output operations.
- `<stdlib.h>` for memory management.
- `<time.h>` for fetching system time and date.
- `<string.h>` for string manipulation.
- `<math.h>` for mathematical calculations.

Future Enhancements
-------------------
- Add a graphical user interface (GUI) for easier interaction.
- Support dynamic addition of classes and locations.
- Integrate with GPS or real-time location tracking.

Author Information
------------------
Developed by a Computer Science student specializing in AI/ML.

License
-------
This project is open-source and distributed under the MIT License.
