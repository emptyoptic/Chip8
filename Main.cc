#include "Emulator.cc"

int main(int argc, char* argv[])
{
	Emulator emu = Emulator();
	emu.init("lol", 1200, 700, SDL_WINDOW_SHOWN);

	return SUCCESS;
}