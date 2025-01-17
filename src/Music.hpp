#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
using namespace std;

class Music{
   
    public:

    Mix_Music* music = NULL;
    int volume;

    Music(){
         volume = 0;
    }

    Music( string path , int vol){ // vol ranges from 0 to 128
             
            if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1)
            {
                        cout << "Error loading audio"<<endl;
            }
             
            music = Mix_LoadMUS( path.c_str() );
            volume = vol; 
            Mix_VolumeMusic(volume);      

    }   

    void Load_Music( string path , int vol ){
     
         if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1)
            {
                        cout << "Error loading audio"<<endl;
            }
             
            music = Mix_LoadMUS( path.c_str() );
            volume = vol; 
            Mix_VolumeMusic(volume);  
        
    }
 
    ~Music(){
   //     Mix_FreeMusic( music );
    }   
    
    bool isplaying(){
           if( Mix_PlayingMusic())return true;
           else return false;
    }

    void playmusic( int loopcount ){  //set loopcount to -1 to play music forever
  
            Mix_PlayMusic( music , loopcount );

    }

    void fadein_music ( int loopcount , int miliseconds ){
         
      Mix_FadeInMusic( music , loopcount , 2000);


    }

    void stopmusic(){
        Mix_HaltMusic();
    }

    void pausemusic(){

        Mix_PauseMusic();

    }
    void resumemusic(){
 
        Mix_ResumeMusic();

    }
    
    void fadeout_music(){

            while(!Mix_FadeOutMusic(2000) && Mix_PlayingMusic()) {
             // wait for any fades to complete
            SDL_Delay(100);
            }

    }

};

class Sound{

    public:

    Mix_Chunk* sound = NULL;
    int volume;

    Sound(){
        volume = 0;
    }

    ~Sound(){
        Mix_FreeChunk( sound );
    }
    
    void Load_Sound( string path , int vol ){

         if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1)
            {
                        cout << "Error loading audio"<<endl;
            }

       sound = Mix_LoadWAV( path.c_str() );
       volume = vol;  
          
    }

    void set_sound_volume( int vol){
         volume = vol;
         Mix_VolumeChunk( sound , volume );
    }

    void Play_sound( int loopcount ){
   
           Mix_PlayChannel(-1 , sound , loopcount );

    }
    
};

#endif