#include "Application.hpp"

#define INVALIDNAME "Invalid Name"
#define NAMEINSTR L"Please input a valid name. Names must be longer than one letter and may not start with punctuations."

SearchBar::SearchBar(nana::form*& p, const std::string& title, RecipeBank& list) {

    // Create screen and bind dependent widgets
    screen = new nana::form(*p, { SEARCH_WIDTH, SEARCH_HEIGHT });
    (*screen).caption(PROGNAME);
    input.create((*screen));
    prompt.create((*screen));
    layout.bind(*screen);
    input.multi_lines(false);
    //focused = false;

    // Set fonts
    input.typeface(myfonts::defaultF());
    prompt.typeface(myfonts::headerF());
    prompt.caption("Enter " + title + " name");

    // Arrange widgets
    layout.div("vert<weight=25%><text weight=20% margin=10><<box margin=20>><><weight=25%>");
    layout["box"] << input;
    layout["text"] << prompt;
    layout.collocate();

    nameInv = nana::msgbox(*screen, INVALIDNAME);
    nameInv << NAMEINSTR;

    initializeEvents(p, list);

}

SearchBar::~SearchBar() {
    delete screen;
}

void SearchBar::initializeEvents(nana::form*& p, RecipeBank& list) {

    this->input.events().key_press([&](const nana::arg_keyboard& arg) {
        if (arg.key == nana::keyboard::enter) {
            std::string text;
            input.getline(0, text);
            if (validName(text)) {
                filterWord(text);
                recScr = new RecipeDetails(screen, text, true);

                if (recScr->success()) {
                    list.addRecipe(text);
                    list.save();
                    screen->close();
                    input.reset();
                }
                delete recScr;

            }

            else {
                nameInv();
            }
        }

        });

    this->screen->events().destroy([&]() {
        p->show();
        });
}