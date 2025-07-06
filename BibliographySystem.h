//
// Created by aldai on 05/07/2025.
//

#ifndef BIBLIOGRAPHYSYSTEM_H
#define BIBLIOGRAPHYSYSTEM_H

#define type_size 50
#define title_size 200
#define name_size 200

struct BiblioData {
    char type[type_size];
    char title[title_size];
    char author[name_size];
    int year;
};

void runSystem();
void showMenu();
void search_authors(char *name);
void search_titles(char *title);
void search_year(int year);
void search_range_year(int startY , int endY);

#endif //BIBLIOGRAPHYSYSTEM_H
