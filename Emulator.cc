#include <iostream>
#include <chrono>
#include <SDL.h>

#define SUCCESS 0;
#define FAILURE 0;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef float f32;
typedef double f64;

struct Emulator
{
private:
    void Chip8()
    {

    }

    void clear()
    {
        SDL_RenderClear(renderer);
    }

    void render()
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }

    void update()
    {
        clear();
        render();

        SDL_RenderPresent(renderer);
        SDL_UpdateWindowSurface(window);
    }

public:
    SDL_Window* window;
    SDL_Renderer* renderer;


    u32 init(const char title[], u32 w, u32 h, u32 flags)
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            std::cout << "SDL initialization failed: " << SDL_GetError() << std::endl;
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialization", SDL_GetError(), NULL);
            return FAILURE;
        }
        else
        {
            std::cout << "SDL initialization success!" << std::endl;
        }

        window = SDL_CreateWindow((char*)title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);

        if (window == nullptr)
        {
            std::cerr << "SDL window creation failed: " << SDL_GetError() << std::endl;
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Window", SDL_GetError(), NULL);
            return FAILURE;
        }
        else
        {
            printf("SDL window: \x1B[32m%s\033[0m creation success!\n", title);
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (renderer == nullptr)
        {
            std::cerr << "SDL renderer creation failed: " << SDL_GetError() << std::endl;
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Renderer", SDL_GetError(), NULL);
            return FAILURE;
        }
        else
        {
            std::cout << "SDL renderer creation success!" << std::endl;
        }

        bool run = true;
        SDL_Event evt;

        while (run)
        {
            while (SDL_PollEvent(&evt) != 0)
            {
                switch (evt.type)
                {
                case SDL_QUIT:
                    run = false;
                    break;
                }
            }

            update();
        }

        SDL_DestroyWindow(window);
        SDL_Quit();

        return SUCCESS;
    }
};