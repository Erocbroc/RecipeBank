*** Instructions on how to use the Recipe Bank Application ***
**************************************************************

The Recipe Bank Application is intended to help users decide on what to eat by providing a 
list of possible foods to make. This should ideally eliminate the thinking stage of food decision 
and immediately move on to meal prep as the user may select one choice out of possibly many. The 
program's effectiveness depend on the number of options saved in the user's recipe database.

Home Screen:
    This is the window that appears when the application is booted. It contains the "Add Recipe" and 
    "Display Recipe" buttons which takes you to their respective screens. Upon selection of either option, the 
    Home Screen hides until the previously selected window is closed. The application is closed by clicking the 'X'
    button on this screen.

Add Recipe Screen:
    To add a new recipe, type in a valid name and press the "Enter" key to confirm. Valid names are words/sentences
    that consists of more than 1 letter and do not start with any punctuation. If a valid name is submitted, another
    window appears that displays the recipe name and a textbox to type the ingredients of that recipe. The recipe is
    saved when the green "Save" button is pressed. 

    Existing recipies may be edited in this screen by typing the name into the search bar.

Display Recipe Screen:
    Saved recipies appear on this screen. To view recipe details, make sure the "view Ingredients" radio button
    is selected, then click on a recipe name. A new window pops up with ingredient information relating to
    the recipe that was picked. To delete recipies, selected the "delete Recipe" radio button
    and click on a recipe name.

**************************************************************
Notes:
    - This program was designed with a primary focus on its functionality over appearance
    - The nana library treats the space character (' ') as a newline character ('\n'), so bugs occur when
        inputting recipies or ingredients with spaces in them. To account for that, spaces that occur in words
        are replaced with an underscore ('_') when the window calls for text from database.
    - The 'X' Button to close a window essentially functions as a "back" button. To close the program, you 
        need to press the 'X' button on the Home Screen
