#include "engine/menu/main.hpp"
#include "engine/screen.hpp"
#include <iostream>
using namespace std;
using namespace Engine;

void handle(Screen *screen, bool can_display) {
  if (can_display)
    return;

  delete screen;
  cout << "Error while opening screen" << endl;
  exit(1);
}

int main() {
  Screen *screen = new Screen();
  handle(screen, screen->open());

  Menu::Main *main_menu = new Menu::Main(screen->get_container());
  screen->set_content(main_menu);

  int key;
  while ((key = getch()) != 'q') {
    switch (key) {
    case KEY_RESIZE:
      handle(screen, screen->reposition());
      break;
    };
    screen->send_event(Drawable::Event::redraw);
  }

  delete screen;
  return 0;
}
