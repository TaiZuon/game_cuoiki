#include <SDL.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include "PianoKey.hpp"
#include "LTimer.hpp"
#include <conio.h>

using namespace std;

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 700;

SDL_Renderer* gRenderer = NULL;

bool init( SDL_Window* window )
{
	bool success = true;
	window = NULL;
	
	SDL_Surface* screenSurface = NULL;

if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "Gemu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
		}
		else
		{

			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );

			//Fill the surface white
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
			
			//Update the surface
			SDL_UpdateWindowSurface( window );
            
            //Hack to get window to stay up
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
		}
	}
    if (success) return true;
    else return false;
}

void close( SDL_Window* window )
{
	SDL_DestroyWindow( window );
	SDL_Quit();
}

int main( int argc, char* argv[] )
{

	SDL_Window* myWindow = NULL;
	
	SDL_Surface* screenSurface = NULL;

    PianoKey pianokey;

	if ( !init( myWindow ) or !pianokey.loadMedia( gRenderer, "PianoKey.bmp" ) ) 
    {
        printf("Failed!");
        return 0;
    } 
    else
    { 
            bool quit = false;

            SDL_Event e;

            while ( !quit )
            {
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_QUIT )
					{
						quit = true;
					}
                    pianokey.handleEvent( e );    
                }

                pianokey.move();

                //Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

                pianokey.render( gRenderer );

                SDL_RenderPresent( gRenderer );
            }
    }

    close( myWindow );

    char c;
    c = getch();

	return 0;

}