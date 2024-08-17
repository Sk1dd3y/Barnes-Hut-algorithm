#include <SDL2/SDL.h>
//#include "particle.h"
#include "auxfunc.h"

// Window dimensions

void render_object(SDL_Renderer *renderer, struct Node *node, int num_objects, int n) {

      // Render all particles in the node

    for (int i = 0; i < node->num_particles; i++) {
        SDL_SetRenderDrawColor(renderer, 0, node->particles[i].vel.x * 255, node->particles[i].vel.y * 255, 255);
        SDL_Rect rect = {node->particles[i].pos.x, node->particles[i].pos.y, node->particles[i].mass, node->particles[i].mass};
        SDL_RenderFillRect(renderer, &rect);
    }

    // Recursively render subnodes
    for (int i = 0; i < node->no_subnodes; i++) {
        if (node->subnodes[i] != NULL) {
	  render_object(renderer, node->subnodes[i], node->num_particles, n);
        }
    }
}

void render_particle(struct Node* node, SDL_Renderer* renderer) {
  
  SDL_Rect particle_rect;
  particle_rect.w = 2; // width of the particle
  particle_rect.h = 2; // height of the particle
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0); // set color of the particles to blue
  for(int i = 0; i < node->num_particles; i++) {
    particle_rect.x = node->particles[i].pos.x - particle_rect.w/2; // x position of the top-left corner of the particle
    particle_rect.y = node->particles[i].pos.y - particle_rect.h/2; // y position of the top-left corner of the particle
    SDL_RenderFillRect(renderer, &particle_rect); // draw the particle
  } 
}

void render_tree(struct Node* node, SDL_Renderer* renderer) {

  // Render the current node as a square
  SDL_Rect rect;

  rect.w = node->dim + 1;   // width of the square
  rect.h = node->dim + 1;   // height of the square
  rect.x = node->pos.x-node->dim/2; // x position of the top-left corner of the square
  rect.y = node->pos.y-node->dim/2; // y position of the top-left corner of the square

  SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255); // set color of the square to white
  SDL_RenderDrawRect(renderer, &rect);                 // draw the square


  // Render the subnodes recursively
  if(node->no_subnodes) {
    for(int i = 0; i < node->no_subnodes; i++) {
    //if(node->subnodes[i] != NULL) {
      render_tree(node->subnodes[i], renderer);
    }
  }
}

