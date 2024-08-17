#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <math.h>
#include "structs.h"
#include "renderer.h"
#include "auxfunc.h"

#define ACELLARATION_MOD 1


//void calc_pos(object *objects, int num_objects);
//float calc_v(object *objects, int num_objects);



int main(int argc, char *argv[]) {

  int n = 7, cutoff = 1;
  
  if(argc > 1)
    n = atoi(argv[1]);
  if(argc > 2)
    cutoff = atoi(argv[2]);
  
  struct Node *node = init_root(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH, n);
  //print_particles(node->particles);
  init_tree(node, 0, cutoff);

  //Print nodes to check if everything is right

  //print_particles(node->particles);
  //print_node(node);
  

  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  render_particle(node, renderer);
  render_tree(node, renderer);

  SDL_RenderPresent(renderer);

  SDL_Delay(6000);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  
  //free(particles);
  return 0; 
}



