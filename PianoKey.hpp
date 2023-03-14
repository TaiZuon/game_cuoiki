#include <SDL.h>
#include "LTexture.hpp"

LTexture PianoKeyTexture;

class PianoKey
{
    public:
        //thong so cua phim 
        const int HEIGHT = 20;    
        //van toc
        const int PKEY_VEL_MAX = 100;

        //buoc nhay
        const int PKEY_POS_JUMP = HEIGHT;

        //ham khoi tao
        PianoKey();

        //ham kiem soat bam keyboard
        void handleEvent( SDL_Event& e );

        //ham chuyen dong cua phim - chay xuong
        void move();

        //hien thi phim
        void render( SDL_Renderer* gRenderer );
        
        //load anh phim 
        bool loadMedia ( SDL_Renderer* gRenderer, std::string path );

    private:
        //vi tri phim 
        int PosX, PosY;

        //van toc phim
        int Vel;
};

PianoKey::PianoKey()
{
    PosX = 0;
    PosY = 0;

    Vel = 0;
}

void PianoKey::handleEvent( SDL_Event& e )
{
    if( e.type == SDL_KEYDOWN && e.key.repeat ==0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_1: 
                Vel == PKEY_VEL_MAX;
                PosY += PKEY_POS_JUMP;
                break; 
            
        }
    }
}

void PianoKey::move()
{
    PosY += Vel;
}

void PianoKey::render( SDL_Renderer* gRenderer )
{
    PianoKeyTexture.render( gRenderer, PosX, PosY );
}

bool PianoKey::loadMedia( SDL_Renderer* gRenderer, std::string path)
{
    bool success;
    if( !PianoKeyTexture.loadFromFile( gRenderer, path ) )
    {
        success = false;
    }

    return success;
}