
# Benchmarking Lua's GC

Course assignment in DOCS CS60203 (Design and Optimization of Computer Systems)
An assignment to understand the source code of Lua scripting language written in c and performance analysis of its Garbage Collector using tools like valgrind and perf command.

## Installation

First clone lua's git repository and build it using the steps given on https://www.lua.org/download.html

```bash
  cd lua-version-name
  git clone <current repository>
  python -m venv venv
  source venv/bin/activate
  pip install gprof2dot
```


now to actually generate the graphs, use 

```bash
chmod +x script.sh
./script.sh
```
    