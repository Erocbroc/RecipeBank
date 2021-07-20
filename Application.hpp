
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <nana/gui.hpp>
#include <nana/gui/msgbox.hpp>
#include <nana/gui/screen.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/group.hpp>
#include "Recipe.hpp"

#define PROGNAME "Recipe Bank"
#define SEARCH_WIDTH 800
#define SEARCH_HEIGHT 530

namespace myfonts{
	nana::paint::font headerF();
	nana::paint::font defaultF();
	nana::paint::font smallF();

}

class RecipeDetails {
public:
	nana::form* screen = nullptr;
	RecipeDetails(nana::form*&, const std::string&, bool);
	~RecipeDetails();

	bool success();


private:
	nana::label title;
	nana::textbox ingr;
	nana::place layout;
	nana::button save;
	Recipe rec;

};

class RecipeList {
public:
	nana::form* screen = nullptr;
	RecipeList(nana::form*&, RecipeBank&);
	~RecipeList();

	
	


private:
	RecipeDetails* rec;
	nana::listbox list;
	nana::checkbox viewO;
	nana::checkbox delO;
	nana::place layout;
	nana::radio_group options;

	bool delState;

	void initializeEvents(nana::form*&, RecipeBank&);

	struct Confirmation {
		nana::form* screen = nullptr;
		Confirmation(nana::form*&, const std::string&);
		~Confirmation();

		bool show();

	private:
		nana::button yesB;
		nana::button noB;
		nana::label msg;
		nana::place layout;

	};

	Confirmation* confirm;



};

class SearchBar {
public:
	nana::form* screen;
	SearchBar(nana::form*&, const std::string& title, RecipeBank& list);
	~SearchBar();




private:
	nana::textbox input;
	nana::label prompt;
	nana::place layout;
	nana::msgbox nameInv;
	RecipeDetails* recScr;

	void initializeEvents(nana::form*&, RecipeBank&);


};

class Home {
public:
	
	Home();
	~Home();

	void run();

private:
	nana::form* screen = nullptr;
	SearchBar* addRecipe = nullptr;
	RecipeList* viewRecipe = nullptr;
	RecipeBank list;
	nana::button addR;
	nana::button viewR;
	nana::place layout;
	nana::msgbox err;
	bool focused;

	nana::rectangle appSize();
	void initializeEvents(SearchBar*& addScreen, RecipeList*& viewScreen);




};