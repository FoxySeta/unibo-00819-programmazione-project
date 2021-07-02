#include "engine/menu/main.hpp"
#include "data/database.hpp"
#include "engine/colorable.hpp"
#include "engine/menu/select.hpp"
#include "engine/menu/settings.hpp"
#include "engine/screen.hpp"
#include <fstream>
#include <iostream>
#include <unistd.h>
using namespace std;
using namespace Engine;

void handle(bool can_display) {
  if (can_display)
    return;

  cout << "Error while opening screen" << endl;
  exit(1);
}

int main() {
  Data::Database d("tests/alma.conf.csv", "tests/assets/",
                   "tests/scoreboard.csv");

  Screen screen;
  handle(screen.open());
  screen.set_content<Menu::Main>();

  int key;
  bool running = true;
  while (running) {
    // quit if usleep is blocked by an interrupt and the key is an ERR
    if (usleep(1000000 / 25) == EINTR) // 25fps
      running = false;

    if (screen.get_content()->is_over()) {
      if (screen.is_content<Menu::Main>()) {
        // do something when the main menu is exited
        auto res = screen.get_content<Menu::Main>()->get_result();
        switch (res) {
        case Menu::Main::Result::quit:
          running = false;
          break;
        case Menu::Main::Result::settings:
          screen.set_content<Menu::Settings,
                             const Nostd::Vector<Data::Setting> &>(
              d.settings());
          break;
        case Menu::Main::Result::play:
          // TODO: change me
          /*screen.set_content<Menu::Results,
                             const Nostd::List<Data::Pawns::Result>
             &>(d.results());
                             */
          {
            Nostd::Vector<Data::Pawns::Hero> heroes(d.heroes().size());
            for (size_t i{0}; i < d.heroes().size(); ++i)
              heroes.at(i) = d.heroes().as_vector().at(i)->second;
            screen.set_content<Menu::Select,
                               const Nostd::Vector<Data::Pawns::Hero> &>(
                heroes);
          }
          break;
        default:
          break;
        }
      } else {
        if (screen.is_content<Menu::Settings>())
          d.settings() = screen.get_content<Menu::Settings>()->get_result();

        // always go back to the main menu after some menus close
        screen.set_content<Menu::Main>();
      }
    }

    // keyboard handling
    key = getch();
    switch (key) {
    case KEY_RESIZE:
      handle(screen.reposition());
      break;

    case '\n':
    case KEY_ENTER: // enter key for the numpad
      screen.send_event(Drawable::Event::interact);
      break;

    case 'k':
    case KEY_UP:
      screen.send_event(Drawable::Event::move_up);
      break;

    case 'j':
    case KEY_DOWN:
      screen.send_event(Drawable::Event::move_down);
      break;

    case 'h':
    case KEY_LEFT:
      screen.send_event(Drawable::Event::move_left);
      break;

    case 'l':
    case KEY_RIGHT:
      screen.send_event(Drawable::Event::move_right);
      break;
    case ERR:
      // ignore ncurses's getch errors
      break;
    };
  }
  return 0;
}
