//************ AUXILARY FUNCTIONS ************//

#ifndef AUXFUNC_H
#define AUXFUNC_H

#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <math.h>

//#define N 2050
#define WINDOW_HEIGHT 900
#define WINDOW_WIDTH 900

//Prototypes
void count_particle(struct Node* node);

//Auxfunctions

float generate_rand(){
   return rand()/((float) RAND_MAX + 1);
}

float generate_rand_ex(){
   return 2 * generate_rand() - 1;
}

float sqrd_distance(struct Particle a, struct Particle b) {
  float dx = a.pos.x - b.pos.x;
  float dy = a.pos.y - b.pos.y;
  return((dx*dx) + (dy*dy));
}

float sqrd_distance_far(struct Particle a, struct Node b) {
  float dx = a.pos.x - b.pos.x;
  float dy = a.pos.y - b.pos.y;
  return((dx*dx) + (dy*dy));
}

void print_particles(struct Particle* particles) {
  for (int i = 0; i < sizeof(particles) / 8; i++) {
    printf("Particle %d @ %p:\n", particles[i].index, &particles[i]);
    printf("\tPosition: (%f, %f)\n", particles[i].pos.x, particles[i].pos.y);
    printf("\tVelocity: (%f, %f)\n", particles[i].vel.x, particles[i].vel.y);
    printf("\tMass: %d\n", particles[i].mass);
      }     
}

void print_node(struct Node* node) {
  printf("\nNode: %p\n", node);
    printf("Child of: %p\n", node->parent);
    printf("Position: (%f, %f)\n", node->pos.x, node->pos.y);
    printf("Dimension: %d\n", node->dim);
    printf("Index: %d\n", node->index);
    printf("No. of subnodes: %d\n", node->no_subnodes);
    printf("No. of particles: %d\n", node->num_particles);
    printf("Mass center: (%f, %f)\n", node->mass_center.x, node->mass_center.y);
    printf("Mass: %d\n", node->mass);
    
  // Print the subnodes recursively
  for(int i = 0; i < node->no_subnodes; i++) {
    if(node->subnodes[i] != NULL) {
      print_node(node->subnodes[i]);
    }
  }
}

struct Particle *init_particles(struct Node* node, int n) {
  
  for (int i = 0; i < n; i++) {
    node->particles[i].pos.x = generate_rand()*WINDOW_WIDTH;
    node->particles[i].pos.y = generate_rand()*WINDOW_HEIGHT;
    node->particles[i].vel.x = generate_rand_ex();
    node->particles[i].vel.y = generate_rand_ex();
    node->particles[i].mass = generate_rand();
    node->particles[i].index = i;
    node->num_particles++;
  }
  return 0;
}

struct Node *init_root(float x, float y, int dim, int n) {

  struct Node* node = malloc(sizeof(struct Node));
  node->particles = malloc(n * sizeof(struct Particle));
  
  init_particles(node, n);

  node->dim = dim;
    
  node->pos.x = x;
  node->pos.y = y;

  node->mass_center.x = x;
  node->mass_center.y = y;

  node->no_subnodes = 0;
  node->mass = 0;

  node->num_particles = n;

  return node;
}


struct Node *init_node(float x, float y, int dim, int index, struct Node* parent_node) {

  // Allocate Memory
  // Allocate same amount of memory for particle
  // as parent possesed - this will scale very
  // badly so TODO: use realloc to increase memory
  // based on counted particles
  
  struct Node* node = malloc(sizeof(struct Node));
  //node->particles = malloc(node->parent->num_particles * sizeof(struct Particle*));
  
  node->dim = dim;
    
  node->pos.x = x;
  node->pos.y = y;

  node->mass_center.x = x;
  node->mass_center.y = y;

  node->no_subnodes = 0;
  node->mass = 0;

  node->parent = parent_node;
  node->index = index;

  node->num_particles = 0;
  count_particle(node);

  return node;
}

void init_subnodes(struct Node* node) {

  float dim = ((float) node->dim) / 2.0;

  // The parent node has now subnodes:
  node->no_subnodes = 4;

  for(int i = 0; i < node->no_subnodes; i++) {

      float new_x, new_y;

        switch (i) {
        case 0:
            new_x = node->pos.x - dim/2;
            new_y = node->pos.y - dim/2;
            break;
        case 1:
            new_x = node->pos.x + dim/2;
            new_y = node->pos.y - dim/2;
            break;
        case 2:
            new_x = node->pos.x - dim/2;
            new_y = node->pos.y + dim/2;
            break;
        case 3:
            new_x = node->pos.x + dim/2;
            new_y = node->pos.y + dim/2;
            break;
	}
	node->subnodes[i] = init_node(new_x, new_y, dim, i, node);
    }  
}

int locate_node(struct Node* node, struct Particle particle) {

  // Epsilon to help out with edgecases
  float epsilon = 1e-6;

  if (particle.pos.x < node->pos.x - epsilon) {
    
    if (particle.pos.y < node->pos.y - epsilon) {
      return 0;
      
    } else {
      return 2;
    }
    
  } else if (particle.pos.x > node->pos.x + epsilon) {
    
    if (particle.pos.y < node->pos.y - epsilon) {
      return 1;
      
    } else {
      return 3;
    }
    
  } else {
    return -1; 
  }
}

void count_particle(struct Node* node) {
 
  // Allocate Memory for particles based on parent node
  node->particles = malloc(node->parent->num_particles *  sizeof(struct Particle));

  // Iterate over all particles in the parent node
  // And check if they are also in child node
  for (int i = 0; i < node->parent->num_particles; i++) {
    if (locate_node(node->parent, node->parent->particles[i]) == node->index) {
      node->particles[node->num_particles++] = node->parent->particles[i];
    }
  }
  // Reallocate memory if not full space was used
  if (node->num_particles < node->parent->num_particles) {
    node->particles = realloc(node->particles, node->num_particles * sizeof(struct Particle));
  }
}

void init_tree(struct Node* node, int level, int cutoff) {

  //Check how many particle there are
  //and recursively call init_tree to
  //build branches until num_particles == 1
  
  if(node->num_particles > cutoff) {
    
    init_subnodes(node);
    level++;
    //cutoff++;
     
    for (int i = 0; i < node->no_subnodes; i++) {
      init_tree(node->subnodes[i], level, cutoff);
      }
  }
}
#endif
