#ifndef STRUCTS_H
#define STRUCTS_H


struct Vector {
  float x, y;
};

struct Particle {
  struct Vector pos, vel;
  int  mass, index;
};

struct Node {
  struct Vector pos, mass_center;
  int dim, no_subnodes, num_particles, index, mass;
  struct Node * subnodes[4];
  struct Node *parent;
  struct Particle *particles;
};

#endif
