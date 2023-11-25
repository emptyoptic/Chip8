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
    struct Chip8_data
    {
    public:
        const static u16 fontset_size = 80;
        const static u16 max_file_size = 3584;
        const static u16 num_keys = 16;
        const static u16 num_registers = 16;
        const static u16 screen_width = 64;
        const static u16 screen_height = 32;
        const static u16 sprite_width =8;
        const static u16 stack_size = 16;
        const static u16 system_memory = 4096;
        const static u16 F = 15;

        u8 memory[system_memory];

        
        u8 V[num_registers];

       
        unsigned short I;

        
        unsigned short pctr;

        
        unsigned char display[screen_width][screen_height];

        
        unsigned char delay_timer;
        unsigned char sound_timer;

        
        unsigned short stack[stack_size];
        unsigned short sptr;

        
        unsigned char key;

        const unsigned char fontset[fontset_size] = {
            0xF0, 0x90, 0x90, 0x90, 0xF0,		// 0
            0x20, 0x60, 0x20, 0x20, 0x70,		// 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0,		// 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0,		// 3
            0x90, 0x90, 0xF0, 0x10, 0x10,		// 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0,		// 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0,		// 6
            0xF0, 0x10, 0x20, 0x40, 0x40,		// 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0,		// 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0,		// 9
            0xF0, 0x90, 0xF0, 0x90, 0x90,		// A
            0xE0, 0x90, 0xE0, 0x90, 0xE0,		// B
            0xF0, 0x80, 0x80, 0x80, 0xF0,		// C
            0xE0, 0x90, 0x90, 0x90, 0xE0,		// D
            0xF0, 0x80, 0xF0, 0x80, 0xF0,		// E
            0xF0, 0x80, 0xF0, 0x80, 0x80		// F
        };

    };

    void Chip8()
    {
        Chip8_data data = Chip8_data();
        data.pctr = 0x200;
        data.I = 0;
        data.sptr = 0;

        memset(data.memory, 0, data.system_memory);
        memset(data.stack, 0, data.stack_size);
        memset(data.display, 0, data.screen_width * data.screen_height);
        memset(data.V, 0, data.num_registers);

        int i;
        for (i = 0; i < data.fontset_size; i++)
        {
            data.memory[i] = data.fontset[i];
        }

        data.delay_timer = 0;
        data.sound_timer = 0;

        data.key = 0;

        std::string file_name;
        char c;
        int loop = 1;

        printf("Please select a game from the list (enter a number).\n1.TETRIS\n2.PONG\n3.EXIT\n");
        scanf("%c", &c);

        while (loop)
        {
            switch (c)
            {
            case '1':
                file_name = "TETRIS.bin";
                loop = 0;
                break;
            case '2':
                file_name = "PONG.bin";
                loop = 0;
                break;
            case '3':
                printf("Exiting emulator...\n");
                exit(0);
            default:
                break;
            }
        }

        /*
        
        11-25-2023: I have got to learn C++ more in-depth, I don't really understand what I am doing so I will 
                    try continuing or just developing other things until I understand this.

                    If you read this, thank you for reading :)
                    Will be continued...
        */
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