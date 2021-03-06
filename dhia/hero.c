#include "hero.h"
#include <math.h>
#include "defs.h"
#include "background.h"
void initialiser_hero(hero *h)
{
	h->position_hero.x=100;
	h->position_hero.y=NIVEAU_SOL;
	h->direction=0;

	h->sprite.image=IMG_Load("./img/hero/girl.png");
	h->sprite.frame.x=0;
	h->sprite.frame.y=0;
	h->sprite.frame.w=50;
	h->sprite.frame.h=69;
	h->sprite.curframe=0;
	h->sprite.maxframe=4;
}
SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y)
{
	SDL_Color color;
	Uint32 col=0;
	char* pPosition=(char* ) pSurface->pixels;
	pPosition+= (pSurface->pitch * y);
	pPosition+= (pSurface->format->BytesPerPixel *x);
	memcpy(&col ,pPosition ,pSurface->format->BytesPerPixel);
	SDL_GetRGB(col,pSurface->format, &color.r, &color.g, &color.b);
	return (color);
}
int CollisionParfaite(SDL_Surface* backgroundMask, SDL_Rect frame, SDL_Rect position)
{	
	SDL_Color couleur_obstacle={255,255,255};
	int i=0;
	int collision=0;
	SDL_Rect pos[8];

	pos[0].x=position.x;
	pos[0].y=position.y;
	pos[1].x=position.x+frame.w/2;
	pos[1].y=position.y;
	pos[2].x=position.x+frame.w;
	pos[2].y=position.y;

	pos[3].x=position.x;
	pos[3].y=position.y+frame.h/2;
	pos[4].x=position.x+frame.w;
	pos[4].y=position.y+frame.h/2;

	pos[5].x=position.x;
	pos[5].y=position.y+frame.h;
	pos[6].x=position.x+frame.w/2;
	pos[6].y=position.y+frame.h;
	pos[7].x=position.x+frame.w;
	pos[7].y=position.y+frame.h;

	while (i<8 && collision==0)
	{
		couleur_obstacle=GetPixel(backgroundMask,pos[i].x,pos[i].y);
		if (couleur_obstacle.r==0 && couleur_obstacle.g==0 && couleur_obstacle.b==0)
			collision=1;
		i++;
	}
	if (collision!=0)
	{
		if (i==0 || i==3 || i==5)
			collision=-1;
		else if (i==2 || i==4)
			collision=1;
		else if (i==1)
			collision=2;
		else
			collision=-2;
	}
	return collision;
}

void deplacer_hero(hero *h,SDL_Event event,SDL_Surface* backgroundMask)
{
	/*static int t=0;
	if (t==17)
		t=0;*/
	//to not execute jump for the first 2 frames
	switch(event.type)
	{
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
				case SDLK_RIGHT:
				if (CollisionParfaite(backgroundMask,h->sprite.frame,h->position_hero)!=-1)
				{
					h->position_hero.x+=4;
					h->direction=1;
				}
				break;
			case SDLK_LEFT:
				if (CollisionParfaite(backgroundMask,h->sprite.frame,h->position_hero)!=1)
				{
					h->position_hero.x-=4;
					h->direction=-1;
				}
				break;
			case SDLK_UP:
				if (CollisionParfaite(backgroundMask,h->sprite.frame,h->position_hero)!=2 /*&& t==16*/)
				{	
					//if (h->position_hero.y!=NIVEAU_SOL-60)
					//	h->position_hero.y-=1; //doit ne pas depasser
					//h->direction=2;
					h->direction=2;
				}
				
				//t++;
				break;
			case SDLK_DOWN:
				if (CollisionParfaite(backgroundMask,h->sprite.frame,h->position_hero)!=-2)
					h->position_hero.y+=5;
				break;
			case SDLK_d:
				h->direction=3;
				break;
			}
			break;
		case SDL_KEYUP:
			//h->direction=0;
			break;
	}
	//Added
	/*if (CollisionParfaite(backgroundMask,h->sprite.frame,h->position_hero)!=2 && h->direction==2)
	{	
		if (h->position_hero.y!=NIVEAU_SOL-60)
			h->position_hero.y-=1; //doit ne pas depasser
		//h->direction=2;
	}
	if (h->position_hero.y==NIVEAU_SOL-60)
		h->direction=0;*/
}
void afficher_hero(hero *h, SDL_Surface* screen)
{
	SDL_BlitSurface(h->sprite.image,&h->sprite.frame,screen,&h->position_hero);
}
void animer_hero(hero *h)
{
	static int tempsActuel=0;
	static int tempsPrecedent=0;

	if (h->direction==0)
	{
		h->sprite.frame.y=0;
		h->sprite.frame.h=69;
		h->sprite.maxframe=4;
		h->sprite.frame.w=50;
	}
	else if(h->direction==-1)
	{
		h->sprite.frame.y=140;
		h->sprite.frame.h=69;
		h->sprite.maxframe=4;
		h->sprite.frame.w=50;
	}
	else if(h->direction==2)
	{
		h->sprite.frame.y=400;
		h->sprite.frame.h=120;
		h->sprite.maxframe=7;
		h->sprite.frame.w=50;
	}
	else if(h->direction==3)
	{
		h->sprite.frame.y=280;
		h->sprite.frame.h=73;
		h->sprite.frame.w=49;
		h->sprite.maxframe=9;
	}
	tempsActuel=SDL_GetTicks();
	if (tempsActuel-tempsPrecedent >150)
	{
		h->sprite.curframe+=1;
		if (h->sprite.curframe > h->sprite.maxframe)
			h->sprite.curframe=0;
		h->sprite.frame.x=h->sprite.curframe*h->sprite.frame.w;
		tempsPrecedent=tempsActuel;
	}
}
void free_hero(hero *h)
{
	SDL_FreeSurface(h->sprite.image);
}