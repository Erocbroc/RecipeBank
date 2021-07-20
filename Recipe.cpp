#include "Recipe.hpp"

/***********  RECIPE CLASS DEFINITIONS  ***********/

Recipe::Recipe(std::string n) {
		name = n;
}

const std::unordered_set<std::string>& Recipe::getAllIngr() {
	return ingredients;
}

void Recipe::clear() {
	ingredients.clear();
}

/* Sends Recipe data to a .txt file
	Returns FALSE if the file name is invalid. Does not save recipe info.
	Returns TRUE otherwise and saves recipe info.
*/
bool Recipe::save() {
	if (!validName(name))
		return false;

	//std::string filename = name;
	//converttotxt(filename);
	// *create folder if it doesn't exist
 	file.open((FOLDER + name), std::fstream::out | std::fstream::trunc);

	for (std::string ingr : ingredients) {
		file << ingr << '\n';
	}

	file.close();
	return true;
}

/* Fills Recipe data structure with information from specified file name
   Returns FALSE if the file name is invalid or file does not exist.
   Returns TRUE otherwise
*/
bool Recipe::load(const std::string& name) {
	if (!validName(name))
		return false;

	this->name = name;
	file.open((FOLDER + name), std::fstream::in);
	if (!file.is_open())
		return false;

	std::string ingr;
	while (!file.eof()) {
		file >> ingr;
		ingredients.insert(ingr);
	}

	file.close();
	return true;
}

void Recipe::addIngr(const std::string& ingr) { ingredients.insert(ingr); }
std::size_t Recipe::getNumIngr() { return ingredients.size(); }
std::string Recipe::getName() { if (name.empty()) return NONAME; else return name; }
//std::string getIngr(std::size_t slot);


/***********  RECIPE_BANK CLASS DEFINITIONS  ***********/

RecipeBank::RecipeBank() {
	std::experimental::filesystem::create_directory(FOLDER);
	//load();
}

std::set<std::string>& RecipeBank::getAllRecipies() {
	return recipies;
}

void RecipeBank::addRecipe(const std::string& name) {
	if (validName(name))
		recipies.insert(name);
}

void RecipeBank::removeRecipe(const std::string& name) {
	recipies.erase(name);
	std::experimental::filesystem::remove(FOLDER + name);
}

/* Checks if a recipe exists already.
   Returns true if the recipe is in database, false if not
*/
bool RecipeBank::exists(const std::string& name) {
	return (recipies.find(name) != recipies.end());
}

/* Sends data to the RECIPEBANK text file.

*/
bool RecipeBank::save() {
	bank.open(RECIPEBANK, std::fstream::out | std::fstream::trunc);
	if (!bank.is_open())
		return false;

	for (std::string recipe : recipies) {
		bank << recipe << '\n';
	}

	bank.close();
	return true;

}

/* Retrieve recipe names from the RECIPEBANK text file.
   Returns true if successful, false otherwise
*/
bool RecipeBank::load() {
	bank.open(RECIPEBANK, std::fstream::in);
	if (!bank.is_open())
		return false;

	if (bank.eof())
		return false;

	recipies.clear();
	std::string name;
	while (!bank.eof()) {
		bank >> name;
		recipies.insert(recipies.end(), name);
	}

	bank.close();
	return true;
}

std::size_t RecipeBank::numRecipies() {
	return recipies.size();
}


/***********  FREE FUNCTIONS  ***********/

bool validName(const std::string& name) {
	return ((name.size() > 1) && isalpha(name[0]));
}

void filterWord(std::string& word) {
	if (word.length() < 1)
		return;
	
	// eliminate unnecessary spaces
	std::size_t i;
	for (i = word.length() - 1; i != 0; i--) {
		if (word[i] != 32)
			break;
	}
	word = word.substr(0, i + 1);

	// replace functional spaces with underscores
	for (i = 0; i < word.length(); i++) {
		if (word[i] == ' ')
			word[i] = '_';
	}


}