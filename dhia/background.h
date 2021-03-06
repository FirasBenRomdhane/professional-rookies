#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"

typedef struct Background
{
	SDL_Surface *image;
	SDL_Surface *background_mask;
	SDL_Rect position_background;
	SDL_Rect position_background_mask;
}background;

void initialiser_background(background *b);
void afficher_background(background *b,SDL_Surface *screen);
void free_background(background *b);