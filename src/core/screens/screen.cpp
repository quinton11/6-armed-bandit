#include "screen.hpp"

Screen::~Screen() {}
Screen::Screen() {}
Screen::Screen(int w, int h) : width(w), height(h) {}

void Screen::render(SDL_Renderer *r) {}
void Screen::eventChecker() {}
