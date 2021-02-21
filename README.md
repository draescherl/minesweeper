# Minesweeper


## Compilation
To compile this program, all you need to do is run these commands :
```bash
make prepare
make
```
You only need to run the preparation once.


## Execution
To run this program, from the working directory, type :
```bash
./minesweeper
```
It is strongly recommended having your terminal maximized to play this game.


## Clean up
To remove the contents of the `bin/` directory, run :
```bash
make clean
```

To remove everything that is not source code, run :
```bash
make mrproper
```
This will delete the compiled program and the `doc/`, `bin/` and `save/` directories as well as all their contents. <br>
Note: If you run `mrproper`, make sure to run `prepare` again next time you compile.


## Create documentation
To generate the doxygen documentation, run :
```bash
make doc
```
This will generate a brand new `Doxyfile`, modify a few config lines, create the documentation in the `doc/` directory and delete the `Doxyfile`.


## Help
You can get a summary of these commands by typing : 
```bash
make usage
```