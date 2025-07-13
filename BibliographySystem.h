//
// Created by aldai on 05/07/2025.
//

#ifndef BIBLIOGRAPHYSYSTEM_H
#define BIBLIOGRAPHYSYSTEM_H

#define type_size 50
#define title_size 200
#define name_size 200
#define maximumData 500
#define LINE_BUFFER 1024
typedef struct  {
    char type[type_size];
    char title[title_size];
    char author[name_size];
    int year;
    char booktitle[type_size];
    char page[title_size];
    char publisher[name_size];
    char volume[name_size];
    char url[name_size];
}BiblioData;

typedef  struct {
    char dataType[maximumData][type_size];
    int dataTypesCount[maximumData];
    int uniqueData;
}Types;

void runSystem();
void showMenu();
int read_bib_file(const char *filename, BiblioData entries[], int max_entries) ;
void search_authors(char *name);
void search_titles(char *title);
void search_year(int year);
void search_range_year(int startY , int endY);
void show_missing_info ();
void detect_duplication ();
void getEntriesTypesAndCount();
void insertNewEntry();
void updateFile(char *filename);
void printEntryData(int index);
void swapValues(int i , int j);
void arranged_authors_alphabetically();
void generate_UWE_Harvard_refernce();
#endif //BIBLIOGRAPHYSYSTEM_H
