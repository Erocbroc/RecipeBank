#include "catch.hpp"
#include "Recipe.hpp"

TEST_CASE("Test Recipe Class", "[Recipe]") {
	Recipe test;

	REQUIRE(test.getName() == NONAME);

	Recipe realR("Cookies");
	realR.addIngr("flour");
	realR.addIngr("eggs");
	realR.addIngr("eggs");
	REQUIRE(realR.getName() == "Cookies");
	REQUIRE(realR.getNumIngr() == 2);

	/*
	std::string* ingr = nullptr;
	realR.getAllIngr();
	REQUIRE(ingr[0] == "flour");
	REQUIRE(ingr[1] == "eggs");
	delete[] ingr;
	*/

	REQUIRE_FALSE(test.save());
	REQUIRE(realR.save());

}

TEST_CASE("Test RecipeBank Class", "[RecipeBank]") {
	RecipeBank RecipeNames;

	RecipeNames.addRecipe("Cookies");
	RecipeNames.addRecipe("Cake");
	RecipeNames.addRecipe("Cookies");
	REQUIRE(RecipeNames.numRecipies() == 2);

	RecipeNames.removeRecipe("Cake");
	RecipeNames.removeRecipe("Cookee");
	REQUIRE(RecipeNames.numRecipies() == 1);

	RecipeNames.addRecipe("Cake");
	RecipeNames.addRecipe("Brownies");
	RecipeNames.save();

	RecipeNames.removeRecipe("Cake");
	RecipeNames.removeRecipe("Brownies");
	REQUIRE(RecipeNames.numRecipies() == 1);

	//REQUIRE(RecipeNames.load());
	CHECK(RecipeNames.numRecipies() == 1);
	RecipeNames.save();

	RecipeNames.removeRecipe("Cookies");
	RecipeNames.save();
	CHECK(RecipeNames.numRecipies() == 0);
	REQUIRE_FALSE(RecipeNames.load());

}