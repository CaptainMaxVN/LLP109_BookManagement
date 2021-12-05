                                                                                                        //Name:
                                                                                                        //Student Number:

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SEPARATOR "\n----------------------------------------------------\n"
#define DEFAULT_BOOK_STORAGE_CAPACITY 1000

//Struct for Book
//it contains 4 members: idNo, title, author and year.
//idNo must be unique, and shall be validated when user insert new book.
typedef struct
{
    char idNo[20];
    char title[100];
    char author[100];
    int year;
} Book;

int bookStorageCapacity = DEFAULT_BOOK_STORAGE_CAPACITY;
Book *books;       //A global pointer variable pointing to book storage.
int bookCount = 0; //A global integer variable to count the number of inserted books.

//This section for declaring function prototypes.
void displayMainScreen();
void displayBookInsertionScreen();
void displayListOfBooksScreen();
void displayBookDeletionScreen();
void displayBookSearchScreen();
void displayAdjustBookStorageCapacityScreen();
char displayOptionSelection(char *options[], int size);
void printBookDetail(Book book);
void inputBookIdAndValidate(Book *book);
void inputBookYearAndValidate(Book *book);
int searchBookByIdNo();
int inputNumberAsStringAndConvert();

int main()
{
    //init book storage array
    books = (Book *)malloc(bookStorageCapacity * sizeof(Book));

    //In startup, the application will show Main screen
    displayMainScreen();

    //free allocated memory of book storage array
    free(books);
    return 0;
}

//This function for generating and operating Main screen
void displayMainScreen()
{
    printf(SEPARATOR);
    printf("=== Book Management System ===\n");
    if (bookCount == 0)
    {
        printf("There is no book added yet. Please insert a book first!\n");
    }

    //These are options supported in Main screen.
    char *options[6] = {
        "1 - List all of books in the system",
        "2 - Insert new book",
        "3 - Delete book",
        "4 - Search book",
        "5 - Adjust book storage capacity",
        "6 - Exit application"};

    char optionCode = displayOptionSelection(options, 6);
    //This section for screen navigation
    //Option 1 selected -> display List of Books screen
    if (optionCode == options[0][0])
    {
        displayListOfBooksScreen();
    }
    //Option 2 selected -> display Insert Book screen
    else if (optionCode == options[1][0])
    {
        displayBookInsertionScreen();
    }
    //Option 3 selected -> display Delete Book screen
    else if (optionCode == options[2][0])
    {
        displayBookDeletionScreen();
    }
    //Option 4 selected -> display Search Book screen
    else if (optionCode == options[3][0])
    {
        displayBookSearchScreen();
    }
    //Option 5 selected -> display Adjust book storage capacity screen
    else if (optionCode == options[4][0])
    {
        displayAdjustBookStorageCapacityScreen();
    }

    //If user select 5, function will reach to the end and finish, no need to handle by code.
    //Other invalid option codes were handled in the method 'displayOptionSelection' above already.
}

//This function for generating and operating List of Books screen
void displayListOfBooksScreen()
{
    printf(SEPARATOR);
    printf("=== List of Books in System ===\n\n");

    //In case of no book added, prompt message to add book first.
    if (bookCount == 0)
    {
        printf("There is no book added yet. Please insert a book first!\n");
    }
    else
    {
        //Make a loop to traverse throught books array
        //in order to print individual book detail
        for (int i = 0; i < bookCount; i++)
        {
            printBookDetail(books[i]);
            printf(SEPARATOR);
        }
    }

    //These are options supported in List of Books screen.
    char *options[4] = {
        "1 - Search book",
        "2 - Insert new book",
        "3 - Delete book",
        "4 - Back to main menu"};

    char optionCode = displayOptionSelection(options, 4);

    //This section for screen navigation
    //Option 1 selected -> display Search Book screen
    if (optionCode == options[0][0])
    {
        displayBookSearchScreen();
    }
    //Option 2 selected -> display Insert Book screen
    else if (optionCode == options[1][0])
    {
        displayBookInsertionScreen();
    }
    //Option 3 selected -> display Delete Book screen
    else if (optionCode == options[2][0])
    {
        displayBookDeletionScreen();
    }
    //Option 4 selected -> display Main screen
    else if (optionCode == options[3][0])
    {
        displayMainScreen();
    }
}

//This function for generating and operating Insert Book screen
void displayBookInsertionScreen()
{
    printf(SEPARATOR);
    printf("=== Insert new book ===\n\n");

    //If the number of books reached to the maximum, prompt message to inform user.
    if (bookCount == bookStorageCapacity)
    {
        printf("Number of books reached to maximum: %d. Please adjust book storage capacity.\n", bookCount);
    }
    else
    {
        //This method for inputting and validating book's Identification number.
        inputBookIdAndValidate(&books[bookCount]);

        printf("Please input book's title: ");
        fgets(books[bookCount].title, 100, stdin);

        printf("Please input book's author: ");
        fgets(books[bookCount].author, 100, stdin);

        inputBookYearAndValidate(&books[bookCount]);

        //print book's detail after adding
        printf(SEPARATOR);
        printf("New book was addded successfully:\n");
        printBookDetail(books[bookCount]);

        bookCount++; //increase bookCount by 1 after each insertion
    }

    //These are options supported in Insert Book screen.
    char *options[4] = {
        "1 - Insert another book",
        "2 - Adjust book storage capacity",
        "3 - List all of books in the system",
        "4 - Back to main menu"};

    char optionCode = displayOptionSelection(options, 4);

    //This section for screen navigation
    //Option 1 selected -> display Insert Book screen
    if (optionCode == options[0][0])
    {
        displayBookInsertionScreen();
    }
    //Option 2 selected -> display Adjust book storage capacity screen
    else if (optionCode == options[1][0])
    {
        displayAdjustBookStorageCapacityScreen();
    }
    //Option 3 selected -> display List of Books screen
    else if (optionCode == options[2][0])
    {
        displayListOfBooksScreen();
    }
    //Option 4 selected -> display Main screen
    else if (optionCode == options[3][0])
    {
        displayMainScreen();
    }
}

//This function for generating and operating Delete Book screen
void displayBookDeletionScreen()
{
    printf(SEPARATOR);
    printf("=== Delete book ===\n\n");

    //If there is no book added yet, prompt message to user.
    if (bookCount == 0)
    {
        printf("There is no book to delete!\n");
    }
    else
    {
        int deletedBookIndex = searchBookByIdNo();
        //searchBookByIdNo function return -1 means no book found.
        if (deletedBookIndex == -1)
        {
            printf(SEPARATOR);
            printf("No book found!\n");
        }
        else
        {
            char idNo[20];
            strcpy(idNo, books[deletedBookIndex].idNo);

            //start deleting book
            for (int i = deletedBookIndex; i < bookCount; i++)
            {
                //shift all books on the right side from deletedBookIndex to left by 1
                books[i] = books[i + 1];
            }
            bookCount--; //decrease bookCount by 1 after deletion

            printf(SEPARATOR);
            printf("Book with Identification number: %s has been deleted successfully!\n", idNo);
        }
    }

    //These are options supported in Delete Book screen.
    char *options[4] = {
        "1 - Delete another book",
        "2 - Insert new book",
        "3 - List all of books in the system",
        "4 - Back to main menu"};

    char optionCode = displayOptionSelection(options, 4);

    //This section for screen navigation
    //Option 1 selected -> display Delete Book screen
    if (optionCode == options[0][0])
    {
        displayBookDeletionScreen();
    }
    //Option 2 selected -> display Insert Book screen
    else if (optionCode == options[1][0])
    {
        displayBookInsertionScreen();
    }
    //Option 3 selected -> display List of Books screen
    else if (optionCode == options[2][0])
    {
        displayListOfBooksScreen();
    }
    //Option 4 selected -> display Main screen
    else if (optionCode == options[3][0])
    {
        displayMainScreen();
    }
}

//This function for generating and operating Search Book screen
void displayBookSearchScreen()
{
    printf(SEPARATOR);
    printf("=== Search book ===\n\n");

    //In case of no book added yet, prompt message to user.
    if (bookCount == 0)
    {
        printf("There is no book to search!\n");
    }
    else
    {
        int searchedBookIndex = searchBookByIdNo();
        //searchBookByIdNo method return -1 means no book found.
        if (searchedBookIndex == -1)
        {
            printf(SEPARATOR);
            printf("No book found!\n");
        }
        else
        {
            //If there is book found with inputted ID number
            //then print inform user and print book's details
            printf(SEPARATOR);
            printf("Book found!\n");
            printBookDetail(books[searchedBookIndex]);
        }
    }

    //These are options supported in Search Book screen.
    char *options[5] = {
        "1 - Search another book",
        "2 - Delete book",
        "3 - Insert new book",
        "4 - List all of books in the system",
        "5 - Back to main menu"};

    char optionCode = displayOptionSelection(options, 5);

    //This section for screen navigation
    //Option 1 selected -> display Search Book screen
    if (optionCode == options[0][0])
    {
        displayBookSearchScreen();
    }
    //Option 2 selected -> display Delete Book screen
    else if (optionCode == options[1][0])
    {
        displayBookDeletionScreen();
    }
    //Option 3 selected -> display Insert Book screen
    else if (optionCode == options[2][0])
    {
        displayBookInsertionScreen();
    }
    //Option 4 selected -> display List of Books screen
    else if (optionCode == options[3][0])
    {
        displayListOfBooksScreen();
    }
    //Option 5 selected -> display Main screen
    else if (optionCode == options[4][0])
    {
        displayMainScreen();
    }
}

//This function for generating and operating Adjust book storage capacity screen
void displayAdjustBookStorageCapacityScreen()
{
    printf(SEPARATOR);
    printf("=== Adjust book storage capacity ===\n\n");

    printf("Current book storage capacity: %d\n", bookStorageCapacity);

    int newCapacity;
    //Use an infinity loop in case of new book storage capacity invalid
    while (1)
    {
        // printf("Please input new book storage capacity: ");
        newCapacity = inputNumberAsStringAndConvert("Please input new book storage capacity: ", 10); //newCapacity supposed has 10 digits or less.
        //In case of inputted value less than number of books stored, require user to input again.
        if (newCapacity < bookCount)
        {
            printf("Value cannot be less than actual number of books stored: %d. Please try again!\n", bookCount);
            continue;
        }
        //Value is valid, update new capacity and break the infinity loop.
        else
        {
            bookStorageCapacity = newCapacity;
            books = (Book *)realloc(books, bookStorageCapacity);

            printf(SEPARATOR);
            printf("Book storage capacity has been updated successfully to %d!\n", bookStorageCapacity);
            break;
        }
    }

    //These are options supported in Adjust book storage capacity screen.
    char *options[6] = {
        "1 - List all of books in the system",
        "2 - Insert new book",
        "3 - Delete book",
        "4 - Search book",
        "5 - Update book storage capacity",
        "6 - Back to main screen"};

    char optionCode = displayOptionSelection(options, 6);
    //This section for screen navigation
    //Option 1 selected -> display List of Books screen
    if (optionCode == options[0][0])
    {
        displayListOfBooksScreen();
    }
    //Option 2 selected -> display Insert Book screen
    else if (optionCode == options[1][0])
    {
        displayBookInsertionScreen();
    }
    //Option 3 selected -> display Delete Book screen
    else if (optionCode == options[2][0])
    {
        displayBookDeletionScreen();
    }
    //Option 4 selected -> display Search Book screen
    else if (optionCode == options[3][0])
    {
        displayBookSearchScreen();
    }
    //Option 5 selected -> display Adjust book storage capacity screen
    else if (optionCode == options[4][0])
    {
        displayAdjustBookStorageCapacityScreen();
    }
    //Option 6 selected -> display Main screen
    else if (optionCode == options[5][0])
    {
        displayMainScreen();
    }
}

//This function is for generating Option menu,
//receive user's choice, validate and return selection option code.
char displayOptionSelection(char *options[], int size)
{
    printf("\n-- OPTION MENU --\n");
    for (int i = 0; i < size; i++)
    {
        printf("%s\n", options[i]);
    }

    int inputtedOptionNumber;
    char selectedOptionCode;

    //It's just a flag to check if any option match to input value
    int validOptionCode = 0; 
    char optionCode;
    while (1)
    {
        inputtedOptionNumber = inputNumberAsStringAndConvert("Please select one option: ", 1);
        //since number options may be less than 10, so we can convert int to char by adding value by '0'.
        selectedOptionCode = inputtedOptionNumber + '0';
        for (int i = 0; i < size; i++)
        {
            //If it matches to an existing option, toggle value of the flag 'validOptionCode' and exit loop.
            optionCode = options[i][0];
            if (selectedOptionCode == optionCode)
            {
                validOptionCode = 1;
                break;
            }
        }

        //If inputted option doesn’t match to any available option code, then prompt message and let user try again.
        if (!validOptionCode) 
        {
            printf("You just entered invalid option code, please try again\n");
        }
        else
        {
            //exit infintity loop and return selected option code
            return selectedOptionCode;
        }
    }
}


//This function is for printing a single book's detail
void printBookDetail(Book book)
{
    printf("Identification Number: %s\n", book.idNo);
    printf("Title: %s\n", book.title);
    printf("Author: %s\n", book.author);
    printf("Year: %d\n", book.year);
}

//This function is for inputting book's Identification number
//and validate with existing IDs after
void inputBookIdAndValidate(Book *book)
{
    char idNo[20];
    //infinity loop for user to re-input book's ID number in case of inputted ID number existed.
    while (1)
    {
        printf("Please input book's Identification number: ");
        char selectedIdNo[20];
        fgets(selectedIdNo, 20, stdin);
        int idExisted = 0; //This's a flag to check whether inputted ID is existed in the system or not.
        for (int i = 0; i < bookCount; i++)
        {
            if (strcmp(selectedIdNo, books[i].idNo) == 0) //if inputted ID equals to an existing ID in the system, then update flag 'idExisted' and exit loop.
            {
                idExisted = 1;
                break;
            }
        }

        if (idExisted) //if flag 'idExisted' = 1 means it's existed already, prompt message to user and let they input again.
        {
            printf("The Identification number: %s has been existed, please select another one!\n", selectedIdNo);
        }
        else
        {
            strcpy(book->idNo, selectedIdNo); //if inputted ID is not existed in the system, copy value to selected book and exit loop.
            break;
        }
    }
}

//This function is for searching Book by Identification number from user input
//and return index of book in books array (return -1 if no book found)
int searchBookByIdNo()
{
    printf("Please input book's Identification number: ");
    char selectedIdNo[20];
    fgets(selectedIdNo, 20, stdin);
    for (int i = 0; i < bookCount; i++)
    {
        if (strcmp(selectedIdNo, books[i].idNo) == 0)
        {
            return i;
        }
    }

    return -1; //No book found
}

//This function is for user to input number value as string, 
//then validate, return an corresponding integer value.
int inputNumberAsStringAndConvert(char *inputLabel, int numberOfDigits)
{
    //inputted number value is supposed to have 20 digits or less.
    char inputValue[20];
    char shortenedValue[numberOfDigits];
    //Use infinity loop in case of invalid number string inputted.
    while (1)
    {
        printf("%s", inputLabel);
        fgets(inputValue, 20, stdin);
        strncpy(shortenedValue, inputValue, numberOfDigits);
        int numberValue = atoi(shortenedValue);
        //the inputted value is invalid and cannot convert to an integer
        if (numberValue == 0)
        {
            printf("Inputted value is invalid. Please try again!\n");
        }
        else
        {
            //return the converted number
            return numberValue;
        }
    }
}

void inputBookYearAndValidate(Book *book)
{
    //Use infinity loop in case of book's year invalid.
    while (1)
    {
        int inputtedYear = inputNumberAsStringAndConvert("Please input book's year: ", 4);

        //In case of invalid number inputted.
        if (inputtedYear <= 0)
        {
            printf("Invalid number inputted. Please try again!\n");
            continue;
        }
        //Otherwise, update book's year value and exit the loop.
        else
        {
            book->year = inputtedYear;
            break;
        }
    }
}