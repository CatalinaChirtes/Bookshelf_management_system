#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Book
{
	char title[100];
	char author[100];
	int pages;
	char genre[100];
	float rating;
	char series[100];
	char language[100];
} books[1000];


struct Collection
{
	char title[100];
	char author[100];
	int pages;
	char genre[100];
	float rating;
	char series[100];
	char language[100];
} collection[1000];


int total_books = 0;
int total_collection = 0;
int rez[1000];
int fez[1000];
int ent[1000];
int borrow_book;

FILE * in_file;
FILE * out_file;

void console_menu()
{
    printf("Hello! This is a program where you can see all the available books in my library.\nIn order to borrow a book you can firstly check out all the available options and then decide which one you want.\nPlease select one of the following options: \n\n");
    printf("If you want to see every detail about every available book, press 1\n");
    printf("If you want to see all the available authors, press 2\n");
    printf("If you want to search for the books of an author, press 3\n");
    printf("If you want to see all the available book titles, press 4\n");
    printf("If you want to search for a book by its title, press 5\n");
    printf("If you want to see all the available genres, press 6\n");
    printf("If you want to search for the books in a genre, press 7\n");
    printf("If you want to see the available book series, press 8\n");
    printf("If you want to search for the books in a series, press 9\n");
    printf("If you want to see the books in order sorted by their rating on Goodreads, press 10\n");
    printf("If you want to see all the books in English, press 11\n");
    printf("If you want to see all the books in Romanian, press 12\n");
    printf("If you want to donate a book, press 13\n");
    printf("If you want to borrow a book, press 14\n");
    printf("If you want to return a book, press 15\n");
    printf("If you no longer wish to borrow a book, you can end this session by pressing 16\n");
}

void create_books()
{
    char b[1000];
    int c=-1;
    total_books = 0;
    rez[0] = 0;
    fez[0] = 0;
    in_file = fopen("books.txt", "r");
    out_file = fopen("books.txt", "a");
    while(fgets(b, 1000, (FILE *) in_file))
    {
        c=-1;
        total_books++;
        rez[++rez[0]]=total_books;
        fez[++fez[0]]=total_books;
        char *p = strtok(b, ";");
        while(p != NULL)
        {
            c++;
            if(c == 0)
                strcpy(books[total_books].title, p);
            if(c == 1)
                strcpy(books[total_books].author, p);
            if(c == 2)
                books[total_books].pages = atoi(p);
            if(c == 3)
                strcpy(books[total_books].genre, p);
            if(c == 4)
                books[total_books].rating = atof(p);
            if(c == 5)
                strcpy(books[total_books].series, p);
            if(c == 6)
                strcpy(books[total_books].language, p);
            p = strtok(NULL, ";");
        }
    }
}

void create_entire_collection()
{
    char b[1000];
    int c=-1;
    total_collection = 0;
    ent[0] = 0;
    in_file = fopen("entire_collection.txt", "r");
    out_file = fopen("entire_collection.txt", "a");
    while(fgets(b, 1000, (FILE *) in_file))
    {
        c=-1;
        total_collection++;
        ent[++ent[0]]=total_collection;
        char *p = strtok(b, ";");
        while(p != NULL)
        {
            c++;
            if(c == 0)
                strcpy(collection[total_collection].title, p);
            if(c == 1)
                strcpy(collection[total_collection].author, p);
            if(c == 2)
                collection[total_collection].pages = atoi(p);
            if(c == 3)
                strcpy(collection[total_collection].genre, p);
            if(c == 4)
                collection[total_collection].rating = atof(p);
            if(c == 5)
                strcpy(collection[total_collection].series, p);
            if(c == 6)
                strcpy(collection[total_collection].language, p);
            p = strtok(NULL, ";");
        }
    }
}

//1. If you want to see every detail about every available book --> good
void book_details(char * b)
{
    int i,p;
    for(i=1;i<=fez[0];i++)
    {
        //p = fez[i];
        p=i;
        printf("\n\nTitle: %s\n", books[p].title);
        printf("Author: %s\n", books[p].author);
        printf("Number of pages: %d\n", books[p].pages);
        printf("Genre: %s\n", books[p].genre);
        printf("The rating of Goodreads: %.2f\n", books[p].rating);
        printf("Part of the series: %s\n", books[p].series);
        printf("Language: %s\n", books[p].language);
        printf("\n-------------------------------------------------------------------");
    }
    printf("\n");
}

//2. If you want to see all the available authors --> good
void authors(char * b)
{
    int i,j,k,p,c=0;
    char v[1000][1000];
    for(i=1;i<=fez[0];i++)
    {
        p = fez[i];
        strcpy(v[i], books[p].author);
        c++;
    }
    for(i=0;i<=c;i++)
    {
        for(j=i+1;j<=c;j++)
        {
            if(strcmp(v[i],v[j]) == 0)
            {
                for(k=j;k<c;k++)
                    strcpy(v[k],v[k+1]);
                c--;
                j--;
            }
        }
    }
    for(i=0;i<=c;i++)
        printf("%s\n", v[i]);
    printf("\n");
}

//3. If you want to search for the books of an author --> good
void searchauthor(char * b)
{
    int i,p,ok=0;
    char temp;
    char *fname = malloc(100*sizeof(char));
    printf("Enter the name of the author you are looking for: ");
    scanf("%c",&temp);
    scanf("%[^\n]",fname);
    printf("\n");
    for(i=1;i<=fez[0];i++)
    {
        p = fez[i];
        if(strcmp(books[p].author, fname) == 0)
        {
            printf("%s\n", books[p].title);
            ok++;
        }
    }
    if(ok == 0)
        printf("We don't have any books by this author.\n");
    printf("\n");
}

//4. If you want to see all the available book titles --> good
void titles(char * b)
{
    int i,p;
    for(i=1;i<=fez[0];i++)
    {
        p = fez[i];
        printf("%s\n", books[p].title);
    }
    printf("\n");
}

//5. If you want to search for a book by its title --> good
void searchtitle(char * b)
{
    int i,p,ok=0;
    char temp;
    char *fname = malloc(100*sizeof(char));
    printf("Enter the title of the book you are looking for: ");
    scanf("%c",&temp);
    scanf("%[^\n]",fname);
    printf("\n");
    for(i=1;i<=fez[0];i++)
    {
        p = fez[i];
        if(strcmp(books[p].title, fname) == 0)
        {
            printf("YAY! We found the title you were looking for:\n\nTitle: %s\nAuthor: %s\nNumber of pages: %d\nGenre: %s\nRating on Goodreads: %.2f\nSeries: %s\nLanguage: %s\n", books[p].title,books[p].author,books[p].pages,books[p].genre,books[p].rating,books[p].series,books[p].language);
            ok++;
        }
    }
    if(ok == 0)
        printf("We don't have this title.\n");
    printf("\n");
}

//6. If you want to see all the available genres --> good
void genres(char * b)
{
    int i,j,k,p,c=0;
    char v[1000][1000];
    for(i=1;i<=fez[0];i++)
    {
        p = fez[i];
        strcpy(v[i], books[p].genre);
        c++;
    }
    for(i=0;i<=c;i++)
    {
        for(j=i+1;j<=c;j++)
        {
            if(strcmp(v[i],v[j]) == 0)
            {
                for(k=j;k<c;k++)
                    strcpy(v[k],v[k+1]);
                c--;
                j--;
            }
        }
    }
    for(i=0;i<=c;i++)
        printf("%s\n", v[i]);
    printf("\n");
}

//7. If you want to search for the books in a genre --> good
void searchgenre(char * b)
{
    int i,p,ok=0;
    char temp;
    char *fname = malloc(100*sizeof(char));
    printf("Enter the genre you are looking for: ");
    scanf("%c",&temp);
    scanf("%[^\n]",fname);
    printf("\n");
    for(i=1;i<=fez[0];i++)
    {
        p = fez[i];
        if(strcmp(books[p].genre, fname) == 0)
        {
            printf("%s by %s\n",books[p].title,books[p].author);
            ok++;
        }
    }
    if(ok == 0)
        printf("We don't have any books in this genre.\n");
    printf("\n");
}

//8. If you want to see the available book series --> good
void series(char * b)
{
    int i,j,k,p,c=0;
    char v[1000][1000], ser[]="none";
    for(i=1;i<=fez[0];i++)
    {
        p = fez[i];
        strcpy(v[i], books[p].series);
        c++;
    }
    for(i=0;i<=c;i++)
    {
        for(j=i+1;j<=c;j++)
        {
            if(strcmp(v[i],v[j]) == 0)
            {
                for(k=j;k<c;k++)
                    strcpy(v[k],v[k+1]);
                c--;
                j--;
            }
        }
    }
    for(i=0;i<=c;i++)
        if(strcmp(v[i],ser) != 0)
            printf("%s\n", v[i]);
    printf("\n");
}

//9. If you want to search for the books in a series --> good
void searchseries(char * b)
{
    int i,p,ok=0;
    char temp;
    char *fname = malloc(100*sizeof(char));
    printf("Enter the name of the series you are looking for: ");
    scanf("%c",&temp);
    scanf("%[^\n]",fname);
    printf("\n");
    for(i=1;i<=fez[0];i++)
    {
        p = fez[i];
        if(strcmp(books[p].series, fname) == 0)
        {
            printf("%s by %s\n",books[p].title,books[p].author);
            ok++;
        }
    }
    if(ok == 0)
        printf("We don't have any books in this series.\n");
    printf("\n");
}

//10. If you want to see the books in order sorted by their rating on Goodreads --> good
void rating(char * b)
{
    int i,j,p,q;
    for(i=1;i<=rez[0];i++)
    {
        for(j=i+1;j<=rez[0];j++)
        {
            p = rez[i];
            q = rez[j];
            if(books[p].rating < books[q].rating)
            {
                int aux = rez[i];
                rez[i] = rez[j];
                rez[j] = aux;
            }
        }
    }
    for(i=1;i<=rez[0];i++)
    {
        p = rez[i];
        printf("%s --> ", books[p].title);
        printf("%.2f\n", books[p].rating);
    }
    printf("\n");
}

//11. If you want to see all the books in English --> good
void english(char * b)
{
    char lang[] = "English";
    int i,j=0,p;
    for(i=1;i<=fez[0];i++)
    {
        p = fez[i];
        if(strcmp(books[p].language, lang) == 0)
            printf("%s by %s\n", books[p].title, books[p].author);
    }
    printf("\n");
}

//12. If you want to see all the books in Romanian --> good
void romanian(char * b)
{
    char lang[] = "Romanian";
    int i,j=0,p;
    for(i=1;i<=fez[0];i++)
    {
        p = fez[i];
        if(strcmp(books[p].language, lang) == 0)
            printf("%s by %s\n", books[p].title, books[p].author);
    }
    printf("\n");
}

//13. If you want to donate a book --> good
void donate()
{
    total_books++;
    total_collection++;
    printf("Adding a new book to the library\n\n");

    char temp;
    char * title = malloc(sizeof(char) * 100);
    printf("Title: ");
    scanf("%c",&temp);
    scanf("%[^\n]", title);

    char * author = malloc(sizeof(char) * 100);
    printf("Author: ");
    scanf("%c",&temp);
    scanf("%[^\n]", author);

    int pages;
    printf("Number of pages: ");
    scanf("%d", &pages);

    char * genre = malloc(sizeof(char) * 100);
    printf("Genre: ");
    scanf("%c",&temp);
    scanf("%[^\n]", genre);

    float rating;
    printf("Rating on Goodreads: ");
    scanf("%f", &rating);

    char * series = malloc(sizeof(char) * 100);
    printf("Series: ");
    scanf("%c",&temp);
    scanf("%[^\n]", series);

    char * language = malloc(sizeof(char) * 100);
    printf("Language: ");
    scanf("%c",&temp);
    scanf("%[^\n]", language);

    strcpy(books[total_books].title, title);
    strcpy(books[total_books].author, author);
    books[total_books].pages = pages;
    strcpy(books[total_books].genre, genre);
    books[total_books].rating = rating;
    strcpy(books[total_books].series, series);
    strcpy(books[total_books].language, language);

    strcpy(collection[total_collection].title, title);
    strcpy(collection[total_collection].author, author);
    collection[total_collection].pages = pages;
    strcpy(collection[total_collection].genre, genre);
    collection[total_collection].rating = rating;
    strcpy(collection[total_collection].series, series);
    strcpy(collection[total_collection].language, language);

    reset_fez();
    reset_rez();
    update_books_file();
    reset_ent();
    update_entire_collection_file();
    scanf("%c",&temp);
}

void update_books_file()
{
    out_file = fopen("books.txt", "w");
    int j;
    char pg[100],ra[100],c[100];
    for(j=1;j<=total_books;j++)
    {
        if(borrow_book == j)
        {
            continue;
        }
        char p[100] = {0};
        strcat(p, books[j].title);
        strcat(p, ";");
        strcat(p, books[j].author);
        strcat(p, ";");
        itoa(books[j].pages, pg, 10);
        strcat(p, pg);
        strcat(p, ";");
        strcat(p, books[j].genre);
        strcat(p, ";");
        strcpy(c, gcvt(books[j].rating,3,ra));
        strcat(p, c);
        strcat(p, ";");
        strcat(p, books[j].series);
        strcat(p, ";");
        strcat(p, books[j].language);
        strcat(p, ";\n");
        fprintf(out_file, p);
    }
    fclose(out_file);
}

void update_entire_collection_file()
{
    out_file = fopen("entire_collection.txt", "w");
    int j;
    char pg[100],ra[100],c[100];
    for(j=1;j<=total_collection;j++)
    {
        char p[100] = {0};
        strcat(p, collection[j].title);
        strcat(p, ";");
        strcat(p, collection[j].author);
        strcat(p, ";");
        itoa(collection[j].pages, pg, 10);
        strcat(p, pg);
        strcat(p, ";");
        strcat(p, collection[j].genre);
        strcat(p, ";");
        strcpy(c, gcvt(collection[j].rating,3,ra));
        strcat(p, c);
        strcat(p, ";");
        strcat(p, collection[j].series);
        strcat(p, ";");
        strcat(p, collection[j].language);
        strcat(p, ";\n");
        fprintf(out_file, p);
    }
    fclose(out_file);
}

void reset_fez()
{
    fez[0] = total_books;
    int i;
    for(i=1; i<=total_books; i++)
    {
        fez[i] = i;
    }
}

void reset_rez()
{
    rez[0] = total_books;
    int i;
    for(i=1; i<=total_books; i++)
    {
        rez[i] = i;
    }
}

void reset_ent()
{
    ent[0] = total_collection;
    int i;
    for(i=1; i<=total_collection; i++)
    {
        ent[i] = i;
    }
}

//14. If you want to borrow a book (basically a delete) --> good
void borrow()
{
    int i,p,ok=0;
    char temp;
    char *fname = malloc(100*sizeof(char));
    printf("Enter the title of the book you want to borrow: ");
    scanf("%c",&temp);
    scanf("%[^\n]",fname);
    for(i=1;i<=fez[0];i++)
    {
        p = fez[i];
        if(strcmp(books[p].title, fname) == 0)
        {
            printf("\nWe found the title you were looking for in our library: \n\nTitle: %s\nAuthor: %s\nNumber of pages: %d\nGenre: %s\nRating on Goodreads: %.2f\nSeries: %s\nLanguage: %s\n", books[p].title,books[p].author,books[p].pages,books[p].genre,books[p].rating,books[p].series,books[p].language);
            ok=1;
            break;
        }
    }
    if(ok==1)
    {
        borrow_book = p;
        update_books_after_borrow();
        reset_rez();
        reset_fez();
        update_books_file();
        printf("\nYou successfully borrowed the book.\n");
    }

    if(ok == 0)
        printf("We don't have this book.\n");
    printf("\n");
}

void update_books_after_borrow()
{
    int i,aux=0;
    for(i=1;i<total_books;i++)
    {
        if(borrow_book == i)
        {
            borrow_book = 0;
            aux = 1;
        }
        strcpy(books[i].title, books[i+aux].title);
        strcpy(books[i].author, books[i+aux].author);
        books[i].pages = books[i+aux].pages;
        strcpy(books[i].genre, books[i+aux].genre);
        books[i].rating = books[i+aux].rating;
        strcpy(books[i].series, books[i+aux].series);
        strcpy(books[i].language, books[i+aux].language);
    }
    total_books--;
}

//15. If you want to return a book --> good
void returnbook()
{
    int i,j,p,q,ok=0;
    char temp;
    char *fname = malloc(100*sizeof(char));
    printf("Enter the title of the book you want to return: ");
    scanf("%c",&temp);
    scanf("%[^\n]",fname);


    for(i=1;i<=ent[0];i++)
    {
        p = ent[i];
        if(strcmp(collection[p].title, fname) == 0)
        {
            printf("\nWe found the title you were looking for in our library: \n\nTitle: %s\nAuthor: %s\nNumber of pages: %d\nGenre: %s\nRating on Goodreads: %.2f\nSeries: %s\nLanguage: %s\n", collection[p].title,collection[p].author,collection[p].pages,collection[p].genre,collection[p].rating,collection[p].series,collection[p].language);
            ok=1;
            break;
        }
    }
    for(j=1;j<=fez[0];j++)
    {
        q = fez[j];
        if(strcmp(books[q].title, fname) == 0)
        {
             printf("The book is already in the library.");
             ok=2;
             break;
        }
    }
    if(ok==1)
    {
        total_books++;
        strcpy(books[total_books].title, collection[p].title);
        strcpy(books[total_books].author, collection[p].author);
        books[total_books].pages = collection[p].pages;
        strcpy(books[total_books].genre, collection[p].genre);
        books[total_books].rating = collection[p].rating;
        strcpy(books[total_books].series, collection[p].series);
        strcpy(books[total_books].language, collection[p].language);

        printf("\nYou successfully returned the book.\n");

        reset_fez();
        reset_rez();
        update_books_file();
        scanf("%c",&temp);
    }
    if(ok == 0)
        printf("\nWe don't have this book.\n");
    printf("\n");
}

int main()
{
    int nr;
    char auth[100];
    create_books();
    create_entire_collection();
    console_menu();

    printf("Please type the number of your choice: ");
    scanf("%d", &nr);
    while(nr != 16)
    {
        //1. If you want to see every detail about every available book
        if(nr == 1)
        {
            printf("\n");
            book_details(out_file);
            printf("\n");
            console_menu();
            printf("\n\nIf you want to continue, please type the number of  your choice: ");
            scanf("%d", &nr);
        }
        //2. If you want to see all the available authors
        else if(nr == 2)
        {
            printf("\n");
            authors(out_file);
            printf("\n");
            console_menu();
            printf("\n\nIf you want to continue, please type the number of  your choice: ");
            scanf("%d", &nr);
        }
        //3. If you want to search for the books of an author
        else if(nr == 3)
        {
            //char name[100];
            //printf("Enter the name of the author you are looking for: ");
            //scanf("%[^\n]",&name);
            printf("\n");
            searchauthor(out_file);
            printf("\n");
            console_menu();
            printf("\n\nIf you want to continue, please type the number of  your choice: ");
            scanf("%d", &nr);
        }
        //4. If you want to see all the available book titles
        else if(nr == 4)
        {
            printf("\n");
            titles(out_file);
            printf("\n");
            console_menu();
            printf("\n\nIf you want to continue, please type the number of  your choice: ");
            scanf("%d", &nr);
        }
        //5. If you want to search for a book by its title
        else if(nr == 5)
        {
            printf("\n");
            searchtitle(out_file);
            printf("\n");
            console_menu();
            printf("\n\nIf you want to continue, please type the number of  your choice: ");
            scanf("%d", &nr);
        }
        //6. If you want to see all the available genres
        else if(nr == 6)
        {
            printf("\n");
            genres(out_file);
            printf("\n");
            console_menu();
            printf("\n\nIf you want to continue, please type the number of  your choice: ");
            scanf("%d", &nr);
        }
        //7. If you want to search for the books in a genre
        else if(nr == 7)
        {
            printf("\n");
            searchgenre(out_file);
            printf("\n");
            console_menu();
            printf("\n\nIf you want to continue, please type the number of  your choice: ");
            scanf("%d", &nr);
        }
        //8. If you want to see the available book series
        else if(nr == 8)
        {
            printf("\n");
            series(out_file);
            printf("\n");
            console_menu();
            printf("\n\nIf you want to continue, please type the number of  your choice: ");
            scanf("%d", &nr);

        }
        //9. If you want to search for the books in a series
        else if(nr == 9)
        {
            printf("\n");
            searchseries(out_file);
            printf("\n");
            console_menu();
            printf("\n\nIf you want to continue, please type the number of  your choice: ");
            scanf("%d", &nr);
        }
        //10. If you want to see the books in order sorted by their rating on Goodreads
        else if(nr == 10)
        {
            printf("\n");
            rating(out_file);
            printf("\n");
            console_menu();
            printf("\n\nIf you want to continue, please type the number of  your choice: ");
            scanf("%d", &nr);
        }
        //11. If you want to see all the books in English
        else if(nr == 11)
        {
            printf("\n");
            english(out_file);
            printf("\n");
            console_menu();
            printf("\n\nIf you want to continue, please type the number of  your choice: ");
            scanf("%d", &nr);
        }
        //12. If you want to see all the books in Romanian
        else if(nr == 12)
        {
            printf("\n");
            romanian(out_file);
            printf("\n");
            console_menu();
            printf("\n\nIf you want to continue, please type the number of  your choice: ");
            scanf("%d", &nr);
        }
        //13. If you want to donate a book
        else if(nr == 13)
        {
            printf("\n");
            donate();
            printf("\n");
            console_menu();
            printf("\n\nIf you want to continue, please type the number of  your choice: ");
            scanf("%d", &nr);
        }
        //14. If you want to borrow a book
        else if(nr == 14)
        {
            printf("\n");
            borrow();
            printf("\n");
            console_menu();
            printf("\n\nIf you want to continue, please type the number of  your choice: ");
            scanf("%d", &nr);
        }
        //15. If you want to return a book
        else if(nr == 15)
        {
            printf("\n");
            returnbook();
            printf("\n");
            console_menu();
            printf("\n\nIf you want to continue, please type the number of  your choice: ");
            scanf("%d", &nr);
        }
        else
        {
            printf("Invalid choice! Please select one of the available choices: ");
            scanf("%d", &nr);
        }
    }
    return 0;
}
