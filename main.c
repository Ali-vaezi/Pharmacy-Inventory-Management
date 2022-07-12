#include <stdio.h>
#include <string.h> // reshte --> EX: strcpy, strcmp
#include <stdlib.h> // system('cls') --> clear screen
#include <time.h> // delay
#include <stdbool.h> // boolean --> True False

struct drug {
    char name[30];
    char type[30];
    int code;
    char date[10];
    int price;
    char company[30];
    int number;
};

//-------------- functions --------------
void menu() {
    printf("=====================DrugStore Manager=====================\n");
    printf("-----------Menu-----------\n");
    printf("1_ ADD\n");
    printf("2_ REMOVE\n");
    printf("3_ SEARCH\n");
    printf("4_ PRINT ALL\n");
    printf("5_ EDIT\n");
    printf("6_ EXIT\n");
}

void delay(float seconds) {
    // Converting time into milli_seconds
    int milli_seconds = 1000 * seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

void printDrug(struct drug d) {
    printf("Name: %s\n", d.name);
    printf("Type: %s\n", d.type);
    printf("Code: %d\n", d.code);
    printf("Date: %s\n", d.date);
    printf("Price: %d\n", d.price);
    printf("Company: %s\n", d.company);
    printf("Number: %d\n", d.number);
}

//----------------end functions--------------------


int main() {
    FILE *file = fopen("save.dat", "rb");
    FILE *sizeFile = fopen("size.dat", "rb");
    int size;
    if (!sizeFile) {
        // "sizeFile doesn't exist"
        size = 0;
    } else fread(&size, sizeof(int), 1, sizeFile);

    struct drug drugs[100]; // maximum drugs is 100
    if (file != NULL) {
        fread(drugs, sizeof(struct drug), size, file);
    }
    fclose(file);
    fclose(sizeFile);

    char user[10];
    char pass[10];
    printf("Please enter the username: ");
    scanf("%s", &user);
    printf("\n");
    printf("Please enter the password: ");
    scanf("%s", &pass);
    if (strcmp(user, "admin") == 0 && strcmp(pass, "admin") == 0) {
        printf("Welcome\n");
        delay(1);
    } else {
        printf("Your username or password was wrong... please try later\n");
        delay(3);
        return 0;
    }

    char key = 'n';
    while (key == 'n') {
        menu(); // show menu
        int n;
        scanf("%d", &n);
        switch (n) {
            case 1: { // ADD
                system("cls");
                delay(1);
                struct drug d;
                printf("-----------Add-----------\n");
                if (size == 100) {
                    printf("The list is full !!!\n");
                    printf("Press Enter to continue!\n");
                    getchar();
                    getchar();
                    break;
                }
                printf("name: ");
                scanf("%s", &d.name);
                printf("type: ");
                scanf("%s", &d.type);
                printf("code: ");
                scanf("%d", &d.code);
                printf("date: ");
                scanf("%s", &d.date);
                printf("price: ");
                scanf("%d", &d.price);
                printf("company: ");
                scanf("%s", &d.company);
                printf("number: ");
                scanf("%d", &d.number);
                drugs[size] = d;
                size++;
                printf("Done!\n");
                printf("Press Enter to continue!\n");
                getchar();
                getchar();
                break;
            }
            case 2: { // Remove
                system("cls");
                delay(0.5);
                printf("-----------Remove-----------\n");

                if (size == 0) {
                    printf("There is nothing in list to remove !!!\n");
                    printf("Press Enter to continue!\n");
                    getchar();
                    getchar();
                    break;
                }

                printf("choose how to search:\n1_name\n2_code\n");
                bool find = false;
                int choice;
                scanf("%d", &choice);
                if (choice == 1) {
                    char name[30];
                    printf("name: ");
                    scanf("%s", &name);
                    for (int i = 0; i < size; ++i) {
                        if (strcmp(drugs[i].name, name) == 0) {
                            find = true;
                            size--;
                            for (int k = i; k < 99; ++k) {
                                drugs[k] = drugs[k + 1]; // shift all drugs to left so drug[i] will delete
                            }
                        }
                        printf("Removed!\n");
                        break; // it is for: for
                    }
                    if (!find) {
                        printf("there is no drug with name: %s\n", name);
                    }
                    // end of 1

                } else if (choice == 2) {
                    int code;
                    printf("code: ");
                    scanf("%d", &code);
                    for (int j = 0; j < size; ++j) {
                        if (code == drugs[j].code) {
                            find = true;
                            size--;
                            for (int k = j; k < 99; ++k) {
                                drugs[k] = drugs[k + 1]; // shift all drugs to left so drug[j] will delete
                            }
                            printf("Removed!\n");
                            break;
                        }
                    }
                    if (!find) {
                        printf("there is no drug with code: %d\n", code);
                    }
                    // end of 2

                } else { // if it wasn't 1 or 2
                    printf("Wrong answer...try again\n");
                }


                printf("Press Enter to continue!\n");
                getchar();
                getchar();
                break;
            }
            case 3: { // Search
                system("cls");
                delay(0.5);
                printf("-----------Search-----------\n");
                printf("choose how to search:\n1_name\n2_code\n");
                int choice;
                bool find = false;
                scanf("%d", &choice);

                if (choice == 1) {
                    char name[30];
                    printf("name: ");
                    scanf("%s", &name);
                    for (int i = 0; i < size; ++i) {
                        if (strcmp(drugs[i].name, name) == 0) {
                            printDrug(drugs[i]);
                            find = true;
                            break;
                        }
                    }
                    if (!find) {
                        printf("there is no drug with name: %s\n", name);
                    }
                } else if (choice == 2) {
                    int code;
                    printf("code: ");
                    scanf("%d", &code);
                    for (int i = 0; i < size; ++i) {
                        if (drugs[i].code == code) {
                            printDrug(drugs[i]);
                            find = true;
                            break;
                        }
                    }
                    if (!find) {
                        printf("there is no drug with code: %d\n", code);
                    }
                } else { // if it was not 1 or 2
                    printf("Wrong answer...try again\n");
                }
                printf("Press Enter to continue!\n");
                getchar();
                getchar();
                break;
            }
            case 4: { // print All
                system("cls");
                delay(0.5);

                if (size == 0) {
                    printf("The list is empty !!!\n");
                    printf("Press Enter to continue!\n");
                    getchar();
                    getchar();
                    break;
                }

                printf("-----------Print All-----------\n");
                struct drug temp;
                for (int i = 0; i < size; ++i) {
                    for (int j = i + 1; j < size; ++j) {
                        if (strcmp(drugs[i].name, drugs[j].name) > 0) {
                            // swap bubbles
                            temp = drugs[i];
                            drugs[i] = drugs[j];
                            drugs[j] = temp;
                        }
                    }
                }
                for (int i = 0; i < size; ++i) {
                    printDrug(drugs[i]);
                }
                printf("Press Enter to continue!\n");
                getchar();
                getchar();
                break;
            }
            case 5: { // Edit
                system("cls");
                delay(0.5);
                printf("-----------Edit-----------\n");
                printf("choose how to search for edit:\n1_name\n2_code\n");
                int choice;
                bool find = false;
                scanf("%d", &choice);


                if (choice == 1) { // name
                    char name[30];
                    printf("name: ");
                    scanf("%s", &name);
                    for (int i = 0; i < size; ++i) {
                        if (strcmp(drugs[i].name, name) == 0) {
                            find = true;
                            printf("choose what item to edit:\n1_code\n2_number\n3_name\n4_type\n5_date\n6_price");
                            scanf("%d", &choice);
                            if (choice == 1) {
                                printf("Enter the new code: ");
                                scanf("%d", &drugs[i].code);
                                printf("Edited!\n");
                                break;
                            } else if (choice == 2) {
                                printf("Enter the new number: ");
                                scanf("%d", &drugs[i].number);
                                printf("Edited!\n");
                                break;
                            } else if (choice == 3) {
                                printf("Enter the new name: ");
                                scanf("%s", &drugs[i].name);
                                printf("Edited!\n");
                                break;
                            } else if (choice == 4) {
                                printf("Enter the new type: ");
                                scanf("%s", &drugs[i].type);
                                printf("Edited!\n");
                                break;
                            } else if (choice == 5) {
                                printf("Enter the new date: ");
                                scanf("%s", &drugs[i].date);
                                printf("Edited!\n");
                                break;
                            } else if (choice == 6) {
                                printf("Enter the new price: ");
                                scanf("%d", &drugs[i].price);
                                printf("Edited!\n");
                                break;
                            } else { // it wan't 1-2-3-4-5-6
                                printf("Wrong answer...try again\n");
                            }
                            break;
                        }
                    }
                    if (!find) {
                        printf("there is no drug with name: %s\n", name);
                    }
                } else if (choice == 2) { // code
                    int code;
                    printf("code: ");
                    scanf("%d", &code);
                    for (int i = 0; i < size; ++i) {
                        if (drugs[i].code == code) {
                            find = true;
                            printf("choose what item to edit:\n1_code\n2_number\n");
                            scanf("%d", &choice);
                            if (choice == 1) {
                                int code;
                                printf("Enter the new code: ");
                                scanf("%d", &code);
                                drugs[i].code = code;
                                printf("Edited!\n");
                                break;
                            } else if (choice == 2) {
                                int number;
                                printf("Enter the new number: ");
                                scanf("%d", &number);
                                drugs[i].number = number;
                                printf("Edited!\n");
                                break;
                            } else if (choice == 3) {
                                printf("Enter the new name: ");
                                scanf("%s", &drugs[i].name);
                                printf("Edited!\n");
                                break;
                            } else if (choice == 4) {
                                printf("Enter the new type: ");
                                scanf("%s", &drugs[i].type);
                                printf("Edited!\n");
                                break;
                            } else if (choice == 5) {
                                printf("Enter the new date: ");
                                scanf("%s", &drugs[i].date);
                                printf("Edited!\n");
                                break;
                            } else if (choice == 6) {
                                printf("Enter the new price: ");
                                scanf("%d", &drugs[i].price);
                                printf("Edited!\n");
                                break;
                            } else { // 1-6
                                printf("Wrong answer...try again\n");
                            }
                            break;
                        }
                    }
                    if (!find) {
                        printf("there is no drug with code: %d\n", code);
                    }
                } else { // it was not 1 or 2
                    printf("Wrong answer...try again\n");
                }


                printf("Press Enter to continue!\n");
                getchar();
                getchar();
                break;
            }
            case 6: { //exit
                system("cls");
                file = fopen("save.dat", "wb");
                sizeFile = fopen("size.dat", "wb");
                fwrite(&size, sizeof(int), 1, sizeFile);
                fwrite(drugs, sizeof(struct drug), size, file); // save the whole array in file
                key = 'y'; // exit from while()
                break; // break of switch
            }
        }
    }
    fclose(sizeFile);
    fclose(file);
    return 0;
}
