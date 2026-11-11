# Apache Log Analysis

A C++ coursework CLI that reads Apache access logs, reports the ten most requested resources, and exports a Graphviz graph of transitions from referrers to requested pages.

## Build and try it

Use G++ and Make on Linux or WSL. From the repository root:

```bash
make -C bin
./bin/analog mini_log.log
./bin/analog -e -g navigation.dot mini_log.log
```

`-e` excludes static assets, `-t 14` filters by hour and `-g navigation.dot` exports a graph. To render the graph, install Graphviz and run `dot -Tsvg navigation.dot -o navigation.svg`. See the existing manual with `man -l Manuel`.

`bin/Lecture.cpp` reads and filters the log. `bin/Graphe.cpp` aggregates request counts and writes the graph. After building, run the command-line fixtures with `(cd Tests && bash mktest.sh)`.
