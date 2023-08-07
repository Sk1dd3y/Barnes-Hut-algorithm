#include <SDL2/SDL.h>
#include "particle.h"
#include "auxfunc.h"

// Window dimensions

void render_object(SDL_Renderer *renderer, object *objects, int num_objects) {
    // Render all objects in the array
 
    for (int i = 0; i < num_objects; i++) {
      SDL_SetRenderDrawColor(renderer, 0, objects[i].vx*255, objects[i].vy*255, 255);
      SDL_Rect rect = {objects[i].px, objects[i].py, objects[i].m, objects[i].m};
      SDL_RenderFillRect(renderer, &rect);
    }
}

void render_particle(struct Node* node, SDL_Renderer* renderer) {
  
  SDL_Rect particle_rect;
  particle_rect.w = 5; // width of the particle
  particle_rect.h = 5; // height of the particle
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0); // set color of the particles to blue
  for(int i = 0; i < N; i++) {
    particle_rect.x = node->particles[i].pos.x - particle_rect.w/2; // x position of the top-left corner of the particle
    particle_rect.y = node->particles[i].pos.y - particle_rect.h/2; // y position of the top-left corner of the particle
    SDL_RenderFillRect(renderer, &particle_rect); // draw the particle
  } 
}

void render_tree(struct Node* node, SDL_Renderer* renderer) {

  // Render the current node as a square
  SDL_Rect rect;

  rect.w = node->dim;   // width of the square
  rect.h = node->dim;   // height of the square
  rect.x = node->pos.x-node->dim/2; // x position of the top-left corner of the square
  rect.y = node->pos.y-node->dim/2; // y position of the top-left corner of the square

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // set color of the square to white
  SDL_RenderDrawRect(renderer, &rect);                 // draw the square


  // Render the subnodes recursively
  for(int i = 0; i < node->no_subnodes; i++) {
    if(node->subnodes[i] != NULL) {
      render_tree(node->subnodes[i], renderer);
    }
  }
}
