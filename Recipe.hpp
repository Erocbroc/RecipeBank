#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <stdlib.h>
#include <string>
#include <unordered_set>
#include <set>
#include <fstream>
#include <experimental/filesystem>

#define FOLDER "Recipe/"
#define RECIPEBANK "Recipe/recipe_bank"
#define NONAME "-"

class Recipe {
public:
	Recipe(std::string n = NONAME);
	~Recipe() = default;


	const std::unordered_set<std::string>& getAllIngr();
	void clear();
	bool save();
	bool load(const std::string& name);
	void addIngr(const std::string& ingr);
	std::size_t getNumIngr();
	std::string getName();

private:
	std::unordered_set<std::string> ingredients;
	std::string name;
	std::fstream file;

};


class RecipeBank {
public:
	RecipeBank();
	~RecipeBank() = default;

	std::set<std::string>& getAllRecipies();
	void addRecipe(const std::string& name);
	void removeRecipe(const std::string& name);
	bool exists(const std::string& name);
	bool save();
	bool load();
	std::size_t numRecipies();



private:
	std::set<std::string> recipies;
	std::fstream bank;
};

bool validName(const std::string& name);
void filterWord(std::string& word);