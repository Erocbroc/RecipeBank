#include "Application.hpp"

#define SUCCESS "Recipe has been successfully added."

RecipeDetails::RecipeDetails(nana::form*& p, const std::string& d, bool editable) {

    // Create screens and bind widgets
    screen = new nana::form(*p, { 3 * SEARCH_WIDTH / 5, SEARCH_HEIGHT });
    (*screen).caption(PROGNAME);

    title.create(*screen);
    ingr.create(*screen);
    layout.bind(*screen);

    // Set font
    title.typeface(myfonts::headerF());
    title.caption(d);
    ingr.typeface(myfonts::defaultF());
    ingr.multi_lines(true);
    ingr.editable(editable);
    ingr.fgcolor(nana::colors::black);

    layout.div("vert<<t margin=10>><details margin=10 weight=70%><<><s margin=10><>>");
    layout["t"] << title;
    layout["details"] << ingr;
    layout.collocate();

    if (!editable && !rec.load(d)) {
        ingr.fgcolor(nana::colors::red);
        ingr.append("Could not find ingredients for selected Recipe.", false);
    }

    if (rec.load(d)) {

        for (std::string i : rec.getAllIngr()) {
            filterWord(i);
            ingr.append(i + "\n", false);
        }
    }

    if (editable) {
        save.create(*screen);
        save.caption("Save");
        save.typeface(myfonts::defaultF());
        save.bgcolor(nana::colors::lawn_green);

        layout["s"] << save;
        layout.collocate();
    }

}

RecipeDetails::~RecipeDetails() {
    delete screen;
}

bool RecipeDetails::success() {
    bool checker = false;
    save.events().click([&]() {
        rec.clear();
        std::string s;
        for (std::size_t i = 0; i < ingr.text_line_count(); i++) {
            ingr.getline(i, s);
            filterWord(s);
            rec.addIngr(s);
        }
        rec.save();

        nana::msgbox confirm(*screen, "Confirmed");
        confirm << SUCCESS;
        confirm();
        checker = true;
        screen->close();


        });


    screen->show();
    screen->modality();
    return checker;
}