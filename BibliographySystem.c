//
// Created by aldai on 05/07/2025.
//

#include "BibliographySystem.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 BiblioData entries [maximumData];
Types types;
int entries_number = 0;

void trim(char *str, const char *chars_to_trim) {
    if (!str) return;

    int i = 0;
    int j = strlen(str) - 1;

    while (i <= j && strchr(chars_to_trim, str[i])) {
        i++;
    }

    while (j >= i && strchr(chars_to_trim, str[j])) {
        j--;
    }

    int k;
    for (k = 0; k <= j - i; k++) {
        str[k] = str[i + k];
    }
    str[k] = '\0';
}

void extract_value(const char *line, char *value_out, size_t max_len) {
    const char *start = strchr(line, '=');
    if (start == NULL) {
        value_out[0] = '\0';
        return;
    }
    start++;

    strncpy(value_out, start, max_len - 1);
    value_out[max_len - 1] = '\0';

    trim(value_out, " \t\n\r,{}");
}

void check_count_types(char *type) {
    int type_found=0;

    for (int i=0; i<types.uniqueData; i++) {
        if (strcmp(type, types.dataType[i]) == 0) {
            types.dataTypesCount[i]++;
            type_found=1;
            break;
        }
    }
    if (type_found == 0) {
        strcpy(types.dataType[types.uniqueData], type);
        types.dataTypesCount[types.uniqueData]=1;
        types.uniqueData++;
    }
}
int read_bib_file(const char *filename, BiblioData entries[], int max_entries) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        printf("Please make sure your BibTeX data is in a file named '%s' in the same directory.\n", filename);
        return -1;
    }

    int entry_count = 0;
    char line[LINE_BUFFER];
    int in_entry = 0;
    BiblioData current_entry;

    current_entry.type[0] = '\0';
    current_entry.title[0] = '\0';
    current_entry.author[0] = '\0';
    current_entry.year = -1;

    while (fgets(line, sizeof(line), file) != NULL && entry_count < max_entries) {

        char *p = line;
        while (isspace((unsigned char)*p)) p++;

        if (*p == '@') {
            if (in_entry && strlen(current_entry.type) > 0) {
                entries[entry_count++] = current_entry;
            }

            current_entry.type[0] = '\0';
            current_entry.title[0] = '\0';
            current_entry.author[0] = '\0';
            current_entry.year = -1;
            in_entry = 1;

            char *type_start = p + 1;
            char *type_end = strchr(type_start, '{');
            if (type_end) {
                size_t len = type_end - type_start;
                if (len < type_size) {
                    strncpy(current_entry.type, type_start, len);
                    current_entry.type[len] = '\0';
                }
                check_count_types(current_entry.type);
            }
            continue;
        }

        if (in_entry && strchr(line, '}') != NULL) {
            p = line;
            while(isspace((unsigned char)*p)) p++;
            if (*p == '}') {
                if (strlen(current_entry.type) > 0) {
                    entries[entry_count++] = current_entry;
                }

                in_entry = 0;
                continue;
            }
        }

        if (in_entry) {
            if (strstr(line, "author")) {
                extract_value(line, current_entry.author, name_size);
            } else if (strstr(line, "title")) {
                extract_value(line, current_entry.title, title_size);
            } else if (strstr(line, "year")) {
                char year_str[10];
                extract_value(line, year_str, 10);
                current_entry.year = atoi(year_str);
            }
        }
    }

    fclose(file);
    return entry_count;
}


void runSystem() {
   entries_number= read_bib_file("bi.txt",entries,maximumData);
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
        //call search by author name
        char name_str[50];
        printf("Please enter the name of the author");
        scanf("%s",name_str);
        search_authors(name_str);
    }
    else if (menu_choice == 2){
        char title_str[200];
        printf("Please enter the name of the title");
        scanf("%s",title_str);
        search_titles(title_str);
    }
    else if (menu_choice == 3) {
        int year;
        printf("Please enter the year");
        scanf("%d",&year);
        search_year(year);
    }
    else if (menu_choice == 4) {
        int startY ;
        int endY ;
        printf("Please enter the StartY");
        scanf("%d",&startY);
        printf("Please enter the endY");
        scanf("%d",&endY);
        search_range_year( startY ,  endY);
    }
    else if (menu_choice == 5) {
        getEntriesTypesAndCount();
    }
    else if (menu_choice == 6) {

    }
    else if (menu_choice == 7) {
        detect_duplication();
    }
    else if (menu_choice == 8) {

    }
    else if (menu_choice == 9) {
       show_missing_info() ;
    }
    else if (menu_choice == 10) {
     insertNewEntry();
    }
    else {
        printf("please enter a valid value\n");
    }


}

void search_authors(char *name) {
    for ( int i = 0 ; i < entries_number ; i++ ) {
        if ( strstr(entries[i].author, name) ) {
           printEntryData(i);
        }
    }
}

void search_titles(char *title) {
    for ( int i = 0 ; i < entries_number ; i++ ) {
        if ( strstr(entries[i].title, title) ) {
            printEntryData(i);
        }
    }
}
void search_year(int year) {
    for ( int i = 0 ; i < entries_number ; i++ ) {
        if ((entries[i].year == year) ) {
            printEntryData(i);
        }
    }
}

void search_range_year(int startY , int endY) {
    for ( int i = 0 ; i < entries_number ; i++ ) {
        if ((entries[i].year >= startY && entries[i].year <= endY  ) ) {
            printEntryData(i);
        }
    }
}


void show_missing_info () {
    for ( int i = 0 ; i < entries_number ; i++ ) {
        if (strlen (entries[i].title) == 0 ) {
            printf("Title is missing entry number %d \n" , i+1);
        }
         if (strlen (entries[i].author) == 0) {
            printf("Author is missing entry number %d\n" , i+1);
        }
         if ( strlen(entries[i].type ) ==0 ) {
                printf("Type is missing entry number %d \n" , i+1);
        }
         if (entries[i].year == -1 ) {
            printf("Year is missing entry number %d\n" , i+1);
        }
    }
}

void detect_duplication () {
    for (int i = 0 ; i < entries_number ; i++ ) {
        for (int j = 0 ; j < entries_number ; j++ ) {
            if (entries[i].type == entries[j].type) {
                if (entries[i].title == entries[j].title) {
                    printf("duplicate detected for entry number %d , i");
                }
            }
        }
    }
}

void getEntriesTypesAndCount() {
    for ( int i = 0 ; i < types.uniqueData ; i++ ) {
        printf("Type : %s : %d \n",types.dataType[i],types.dataTypesCount[i]);
    }
}

void insertNewEntry() {
    printf("Enter type");
    scanf("%s",entries[entries_number].type);

    printf("Enter title");
    scanf("%s",entries[entries_number].title);

    printf("Enter author");
    scanf("%s",entries[entries_number].author);

    printf("Enter year");
    scanf("%d",&entries[entries_number].year);

    updateFile("bi.txt");

}
void updateFile(char *filename) {
    FILE *file = fopen(filename, "a");
    fprintf(file , "@%s{,\n" , entries[entries_number].type );
    fprintf(file , "author = { %s},\n" , entries[entries_number].author  );
    fprintf(file , "title  = { %s},\n" , entries[entries_number].title  );
    fprintf(file , "year   = { %d},\n }" , entries[entries_number].year  );
    fclose(file);
    printf("File updated\n");
    entries_number++;



}
void printEntryData (int index) {
    printf("Title is : %s \n Author is : %s \n Type is : %s \n Year is : %d \n\n ",
        entries[index].title, entries[index].author, entries[index].type, entries[index].year);
}


