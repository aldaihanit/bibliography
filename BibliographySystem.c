//
// Created by aldai on 05/07/2025.
//

#include "BibliographySystem.h"

#include <stdio.h>

void runSystem() {
showMenu();
}
 void showMenu() {
    int menu_choice;
    printf("Choose what would you like to do \n");
    printf("1- Search using author name \n");
    printf("2- Search using title \n");
    printf("3- Search by year \n");
    printf("4- Search using a range of year \n");
    printf("5- Display publication types and numbers \n");
    printf("6- arranged authors alphabetically \n");
    printf("7- Detect duplication  \n");
    printf("8- Generate UWE Harvard refernce  \n");
    printf("9- show missing info  \n");
    printf("10- Add new entry  \n");

    scanf("%d",&menu_choice);

    if (menu_choice == 1) {
    }
    else if (menu_choice == 2) {

    }
    else if (menu_choice == 3) {

    }
    else if (menu_choice == 4) {

    }
    else if (menu_choice == 5) {

    }
    else if (menu_choice == 6) {

    }
    else if (menu_choice == 7) {

    }
    else if (menu_choice == 8) {

    }
    else if (menu_choice == 9) {

    }
    else if (menu_choice == 10) {

    }
    else {
        printf("please enter a valid value\n");
    }


}

void search_authors(char *name) {

}

void search_titles(char *title) {

}
void search_year(int year) {

}

void search_range_year(int startY , int endY) {

}