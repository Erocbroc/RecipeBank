#include "Application.hpp"

RecipeList::RecipeList(nana::form*& p, RecipeBank& l) {
    delState = false;

    // Create screen and bind widgets
    screen = new nana::form(*p, { SEARCH_WIDTH, SEARCH_HEIGHT });
    (*screen).caption(PROGNAME);

    list.create(*screen);
    viewO.create(*screen);
    delO.create(*screen);
    layout.bind(*screen);


    // Set fonts
    viewO.typeface(myfonts::defaultF());
    viewO.caption("View Ingredients");
    viewO.radio(true);
    viewO.fgcolor(nana::colors::midnight_blue);

    delO.typeface(myfonts::defaultF());
    delO.caption("Delete Recipe");
    delO.radio(true);
    delO.fgcolor(nana::colors::indian_red);

    list.typeface(myfonts::defaultF());
    options.add(delO);
    options.add(viewO);
    viewO.check(true);

    // Arrange widgets
    layout.div("vert<weight=5%><<><view margin=10 weight=40%><><del margin=10 weight=40%> weight=10%><list weight=85% margin=10>");
    layout["view"] << viewO;
    layout["del"] << delO;
    layout["list"] << list;
    layout.collocate();

    list.clear_headers();
    list.append_header("Recipies:", list.size().width - 10);
    list.column_resizable(false);

    for (std::string recipe : l.getAllRecipies()) {
        filterWord(recipe);
        list.at(0).append(recipe);
    }

    initializeEvents(p, l);

}

RecipeList::~RecipeList() {
    delete screen;
}

void RecipeList::initializeEvents(nana::form*& p, RecipeBank& l) {

    // Events
    options.on_clicked([&]() {
        delState = delO.checked();
        });

    list.events().mouse_up([&] {
        // Gets the name of a selected Recipe. 
        if (list.selected().data() != nullptr) {
            std::string word = list.at(*list.selected().data()).text(0);

            if (delState) { // if delete radio button is checked
                // Delete recipe from file and list if confirmed
                confirm = new Confirmation(screen, word);
                if (confirm->show()) {
                    list.erase(list.selected());
                    l.removeRecipe(word);
                    l.save();
                }
                delete confirm;
            }

            else {
                // Opens a window containing recipe info
                rec = new RecipeDetails(this->screen, word, false);
                rec->screen->show();
                rec->screen->modality();
                delete rec;

            }
        }
        });

    this->screen->events().destroy([&]() {
        p->show();
        });
}

RecipeList::Confirmation::Confirmation(nana::form*& p, const std::string& d) {
    screen = new nana::form(*p, { 300, 200 });
    (*screen).caption("Delete Recipe");
    yesB.create(*screen);
    noB.create(*screen);
    msg.create(*screen);
    layout.bind(*screen);

    yesB.typeface(myfonts::smallF());
    noB.typeface(myfonts::smallF());
    yesB.caption("Yes");
    noB.caption("No");
    msg.typeface(myfonts::defaultF());
    msg.caption("Are you sure you want to delete " + d + "?");

    layout.div("vert<cap margin=10><<y margin=10><n margin=10> weight=30%>");
    layout["cap"] << msg;
    layout["y"] << yesB;
    layout["n"] << noB;
    layout.collocate();

}

RecipeList::Confirmation::~Confirmation() {
    delete screen;
}

bool RecipeList::Confirmation::show(){
        bool checked = false;
        screen->show();
        yesB.events().click([&]() {
            screen->close();
            checked = true;
            });

        noB.events().click([&]() {
            screen->close();
            });

        screen->modality();
        return checked;
    }
