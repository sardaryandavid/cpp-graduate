# LFU Cache
I've implemented lfu cache. Algorithm description you can find in the [article](http://dhruvbird.com/lfu.pdf).

# Build
```
mkdir build
cd build
cmake ..
cmake --build .
```
If you want to add tests
```
cmake .. -DTEST=ON
```
If you want to add comparation with belady
```
cmake .. -DBENCH=ON
```

# Input
Enter cache size, elem num (n) and then n elements \
For example:
```
$ ./lfu
2 6 1 2 1 2 1 2
4
```