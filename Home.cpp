#include "Application.hpp"

#define FILEDNE "No recipies exist yet"

namespace myfonts {
    nana::paint::font headerF() {
        return { "", 30., nana::detail::font_style { 500, false, false, false } };
    }

    nana::paint::font defaultF() {
        return { "", 16., nana::detail::font_style { 300, false, false, false } };
    }

    nana::paint::font smallF() {
        return { "", 10., nana::detail::font_style {200, false, false, false} };
    }
};

Home::Home() {
    screen = new nana::form(appSize());
    (*screen).caption(PROGNAME);
    layout.bind(*screen);

    addR.create(*screen);
    addR.caption("Add Recipe");
    addR.typeface(myfonts::headerF());
    addR.bgcolor(nana::colors::lawn_green);

    viewR.create(*screen);
    viewR.caption("Display Recipies");
    viewR.typeface(myfonts::headerF());
    viewR.bgcolor(nana::colors::yellow);
    focused = false;

    layout.div("vert<><add weight=40% margin=15><view weight=40% margin=15><>");
    layout["add"] << addR;
    layout["view"] << viewR;
    layout.collocate();

    err = nana::msgbox(*screen, "ERROR");
    err << FILEDNE;
}

Home::~Home() {
    delete screen;
}

void Home::run() {
    using namespace nana;

    initializeEvents(addRecipe, viewRecipe);
    screen->show();
    exec();
}

nana::rectangle Home::appSize() {
    nana::screen monitor;
    nana::size mainScreen = monitor.primary_monitor_size(); // <- height + width
    return nana::API::make_center(mainScreen.width / 3, mainScreen.height / 2);
}

void Home::initializeEvents(SearchBar*& addScreen, RecipeList*& viewScreen) {

    // Event to handle Home Screen Functions
    screen->events().focus([&]() {
        this->focused = !(this->focused);
        if (this->focused) {

            this->addR.events().click([&]() {

                // switch to Recipe Search Bar
                addScreen = new SearchBar(screen, "Recipe", list);

                // Transition windows
                screen->hide();
                addScreen->screen->show();
                addScreen->screen->wait_for_this();
                delete addScreen;
                });

            this->viewR.events().click([&]() {

                // switch to Recipe List if Recipe_Bank file exists
                if (list.load() && !(list.numRecipies() == 1 && list.exists(""))) {
                    viewScreen = new RecipeList(screen, list);
                    screen->hide();
                    viewScreen->screen->show();
                    viewScreen->screen->wait_for_this();
                    delete viewScreen;
                }

                // else, output an error window 
                else {
                    err();
                }

                });
        }
        });
}