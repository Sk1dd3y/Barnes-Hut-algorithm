# Barnes-Hut-Algorithm
## Introduction
Simple training project to create a quadtree structure in C and renderer the result with SDL2
## Usage

To compile you need SDL2 and math librarys installed.
Simply run:

gcc test.c -out output -lm -lSDL

Two command line parameter can be used.
First one is an int to specify number of particles
Second one is a cutoff for how deep the quadtree should be generated.
The cut off is usually set to one, so the quadtree will generate until only one particle is within each of the smallest branches.
However due to Kernel limitations when it comes to the stack(?) and the recursive nature of this implementation this would only work to up to ~2000 particles.
For a higher number of particles you would have to increase the cutoff.

