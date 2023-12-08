#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
using namespace std;

SDL_Window* window = NULL;
SDL_Surface* wsurface = NULL;
SDL_Surface* images = NULL;

enum keypress{
     KEY_DEFAULT,
     KEY_UP,
     KEY_DOWN,
     KEY_LEFT,
     KEY_RIGHT,
     KEY_TOTAL,
};

SDL_Surface* keysurface[KEY_TOTAL];

bool init()
{
       bool initialized = true;
       SDL_Init( SDL_INIT_EVERYTHING );
       window=SDL_CreateWindow( "keypress" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 1000 ,  1000 , SDL_WINDOW_RESIZABLE);
       wsurface = SDL_GetWindowSurface( window );
       return initialized;     
}

SDL_Surface* loadsurface( string path ) // loads the image at given path and returns loaded surface 
{
         SDL_Surface* optimized = NULL;
         SDL_Surface* loaded= SDL_LoadBMP( path.c_str() );
         if( loaded == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}
        else
        {
            optimized = SDL_ConvertSurface( loaded , wsurface->format , 0 );
        }
         SDL_FreeSurface( loaded );
         return optimized;
}

bool loadmedia()
{
     bool mediaload=true;
     keysurface[KEY_DEFAULT]=loadsurface( "Assets/default.bmp");
     keysurface[KEY_UP]= loadsurface( "Assets/up.bmp" );
     keysurface[KEY_DOWN]=loadsurface( "Assets/down.bmp");
     keysurface[KEY_LEFT]=loadsurface( "Assets/left.bmp");
     keysurface[KEY_RIGHT]=loadsurface( "Assets/right.bmp");
     return mediaload;
}

void close()
{
        for( int i = 0; i < KEY_TOTAL; ++i )
	{
		SDL_FreeSurface( keysurface[ i ] );
		keysurface[ i ] = NULL;
	}      
        SDL_DestroyWindow(window);
        window=NULL;

}
int main( int argc , char* argv[] ){
        SDL_Rect stretchRect;
                stretchRect.x = 0;
                stretchRect.y = 0;
                stretchRect.w = 1000;
                stretchRect.h = 1000;
     
     bool quit = false;
     SDL_Event e ;

     if(init())cout<<"INITIALIZED"<<endl;
     if(loadmedia())cout<<"LOADED MEDIA"<<endl;

      images = keysurface[KEY_DEFAULT];
      
     while(!quit)
     {
        while(SDL_PollEvent( &e ) != 0)
        {
                if( e.type == SDL_QUIT ) quit=true ;
                else if( e.type == SDL_KEYDOWN )//this event happens when any key on keyboard is pressed
                  {
                     switch(e.key.keysym.sym)
                     {       
                           case SDLK_UP:
                           images = keysurface[KEY_UP];
                           break;
                           case SDLK_DOWN:
                           images = keysurface[KEY_DOWN];
                           break;
                           case SDLK_LEFT:
                           images = keysurface[KEY_LEFT];
                           break;
                           case SDLK_RIGHT:
                           images = keysurface[KEY_RIGHT];
                           break;

                           default:
                           images = keysurface[KEY_DEFAULT];
                           break;
                     }
                  }
       }

        SDL_BlitScaled( images , NULL , wsurface , &stretchRect );
        SDL_UpdateWindowSurface( window );     
     }
         
        close();

return 0;
}