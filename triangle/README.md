# Triangles
I've implemented the algorithm that detects the intersection of triangles (and all corner cases such as points and line segments).
You can find algorithm in "Geometric Tools for Computer Graphics", Philip J. Schneider, David H. Eberly, 11.5.4 section.
## Build
```
mkdir build
cd build
cmake .. [-DTEST=ON]
cmake --build .
./triangles
``` 
## Input
Enter the number of triangles and then points for each triangle, for example:
```
./triangles
6
1 0 0 0 1 0 0 0 1
0 0 0 1 1 1 0 0 2
3 4 5 5 6 7 3 8 9
5 3 2 2 -2 1 2 2 0
5 5 5 2 2 -3 2 2 2
3 3 3 2 2 1 4 2 1
```
```
1
2
4
5
6

```
## Output
The program displays the number of triangles that have at least one intersection with some other triangles.