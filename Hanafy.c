#include <stdio.h>
#include <stdlib.h>

typedef struct movie
{
    char name[50];
    char genre[50];
    char leading_actor[50];
    int release_date;
    int rating;
}movie;

void read_movies(movie arr[])
{
    static int index=0;
    char choice;
    printf("Enter name: ");
    fgets(arr[index].name, sizeof(arr[index].name), stdin);
    printf("Enter genre: ");
    fgets(arr[index].genre, sizeof(arr[index].genre), stdin);
    printf("Enter leading actor: ");
    fgets(arr[index].leading_actor, sizeof(arr[index].leading_actor), stdin);
    printf("Enter release date: ");
    scanf("%p", arr[index].release_date);
    printf("Enter rating: ");
    scanf("%p", arr[index].rating);
    index++;
    printf("Enter another Movie? [y/n]: ");
    scanf("%c", choice);
    while(choice=="y")
    {
        printf("Enter name: ");
        fgets(arr[index].name, sizeof(arr[index].name), stdin);
        printf("Enter genre: ");
        fgets(arr[index].genre, sizeof(arr[index].genre), stdin);
        printf("Enter leading actor: ");
        fgets(arr[index].leading_actor, sizeof(arr[index].leading_actor), stdin);
        printf("Enter release date: ");
        scanf("%p", arr[index].release_date);
        printf("Enter rating: ");
        scanf("%p", arr[index].rating);
        index++;
        printf("Enter another Movie? [y/n]: ");
        scanf("%c", choice);
    }
}

void search_movies(movie arr[], char name[])
{
    for(int i=0;i<50;i++)
    {
        if(name==arr[i].name)
        {
            puts(arr[i].name);
        }
    }
}

void avg_rating(movie arr[], char genre[])
{
    int sum=0;
    int number=0;
    for(int i=0;i<50;i++)
    {
        if(genre==arr[i].genre)
        {
            number++;
            sum+=arr[i].rating;
        }
        printf("The average rating: ");
        printf(sum/number);
    }
}

int main()
{
    movie arr[50];
    read_movies(&arr);
    char movie_name[50];
    printf("Enter movie name: ");
    fgets(movie_name, sizeof(movie_name), stdin);
    search_movies(arr, movie_name);
    char movie_genre[50];
    printf("Enter genre name: ");
    fgets(movie_genre, sizeof(movie_genre),stdin);
    avg_rating(arr, movie_genre);
    return 0;
}
