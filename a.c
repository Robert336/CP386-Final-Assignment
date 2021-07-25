#include "a.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>
#include <stdbool.h>

typedef struct thread //represents a single thread, you can add more members if required
{
    char tid[4]; //id of the thread as read from file
    unsigned int startTime;
    int state;
    pthread_t handle;
    int retVal;
} Thread;

int main() // modify to take commandline arguments
{

    // *****intialize data structures *****

    safety();

    int TotalCustomers = readFileCustomers("sample4_in.txt");
    printf("Number of Customers: %d\n", TotalCustomers);
    printf("Maximum resources from file:\n");
    void *CustomerSequences = readFileSequences("sample4_in.txt");

    // Finish bankersalgo
    // printf("Enter Command:");

    return 0;
}

/*
*Program should automatically read the text file and count the 'customers' (sequence of numbers)
*/
int readFileCustomers(char *fileName)
{
    FILE *in = fopen("sample4_in.txt", "r");

    if (!in)
    {
        printf(
            "Error in opening input file...exiting with error code -1\n");
        return -1;
    }
    int count = 0;
    struct stat st;
    fstat(fileno(in), &st);
    char *fileContent = (char *)malloc(((int)st.st_size + 1) * sizeof(char));
    fileContent[0] = '\0';

    while (!feof(in))
    {

        count += 1;
        char line[100];
        if (fgets(line, 100, in) != NULL)
        {
            strncat(fileContent, line, strlen(line));
        }
    }
    fclose(in);
    return count;
}

void *readFileSequences(char *fileName)
{
    FILE *in = fopen("sample4_in.txt", "r");

    if (!in)
    {
        printf(
            "Error in opening input file...exiting with error code -1\n");
        return NULL;
    }
    while (!feof(in))
    {
        char line[100];
        if (fgets(line, 100, in) != NULL)
        {
            printf("%s", line);
        }
    }
    printf("\n");
    fclose(in);
    return NULL;
}

// impliments requestResource(), releaseResource(), and saftey() functions
int bankersalgo() // REMEMBER TO DEFINE ABOVE
{
}

// function to request a resource
// Return: 0 = Sucess
// Return: -1 = Failed
int request_resource() // REMEMBER TO DEFINE ABOVE
{
}

// function to release a resource
// Return: 0 = Sucess
// Return: -1 = Failed
int release_resource() // REMEMBER TO DEFINE ABOVE
{
}

// Saftey algo mentioned in chapter 8
// Use: find whether or not a system is in a safe state.
int safety() // REMEMBER TO DEFINE ABOVE
{
    //int work[] = available;

    // **HARD CODEED**
    // initalize 0, ..., n-1 = false
    bool finish[] = {false,
                     false,
                     false,
                     false,
                     false};

    //printf("test sizeof finish = %d\n", (int)(sizeof(finish) / sizeof(finish[0])));
    //printf("test sizeof available = %d\n", (int)(sizeof(available) / sizeof(available[0])));

    for (int i = 0; i < (sizeof(finish) / sizeof(finish[0])); i++)
    {
        int need_n = (int)(sizeof(need[i]) / sizeof(need[i][0]));
        int available_n = (int)(sizeof(available) / sizeof(available[0]));

        printf("test >>> need_n = %d :: available_n = %d", need_n, available_n);

        int need_sum = sum_arr(*need[i], need_n);
        int available_sum = sum_arr(*available, available_n);
        if (finish[i] == false && need_sum <= available_sum)
        {
        }
    }
}

int sum_arr(int arr[], int n)
{
    if (n > 0)
    {
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += arr[i];
        }
        return sum;
    }
}

//***************************************************************
// **TESTING FUNCTIONS**
