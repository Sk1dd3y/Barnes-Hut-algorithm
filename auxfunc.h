//************ AUXILARY FUNCTIONS ************//

#ifndef AUXFUNC_H
#define AUXFUNC_H

#include "structs.h"
#define N 5
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
  for (int i = 0; i < N; i++) {
    printf("Particle %d:\n", particles[i].index);
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
  return particles;
}

struct Node *init_root(float x, float y, int dim) {
  
  struct Node* node = malloc(sizeof(struct Node));
  node->particles = malloc(N * sizeof(struct Particle));

  init_particles(node, N);

  node->dim = dim;
    
  node->pos.x = x;
  node->pos.y = y;

  node->mass_center.x = x;
  node->mass_center.y = y;

  node->no_subnodes = 0;
  node->mass = 0;

  node->num_particles = N;

  return node;
}

struct Node *init_node(float x, float y, int dim, int index, struct Node* parent_node) {
  
  struct Node* node = malloc(sizeof(struct Node));

  node->dim = dim;
    
  node->pos.x = x;
  node->pos.y = y;

  node->mass_center.x = x;
  node->mass_center.y = y;

  node->no_subnodes = 0;
  node->mass = 0;

  node->parent = parent_node;
  node->index = index;
  
  printf("[DEBUG] init_node...");
  count_particle(node);

  return node;
}

void init_subnode(struct Node* node) {



  float dim = ((float) node->dim) / 2.0;
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

int locate_node(struct Node* node, struct Particle* particle) {

  //Determine which subnode to add based on the root node
  //checking the position relative to the center of root node and
  //returning the corresponding number of the subnode

  printf("[DEBUG] locating particle...");

  if(particle->pos.x < node->pos.x) {
    if(particle->pos.y > node->pos.y)
      return 3;
    else
      return 2;
  }

  if(particle->pos.x > node->pos.x) {
    if(particle->pos.y > node->pos.y)
      return 1;
    else
      return 0;
  }
  return -1;
}

void count_particle(struct Node* node) {

  printf("[DEBUG] Particle counting...");
  for(int i = 0; i < node->parent->num_particles; i++)
    if(locate_node(node->parent, node->parent->particles[i]) == node->index)
      node->num_particles++;
}

void init_tree(struct Node* node, int no_particles) {

  if(node->num_particles > 1) {
    init_subnode(node);
    init_subnode(node->subnodes[1]);
  }
}
#endif


