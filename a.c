#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>
#include <stdbool.h>

// DATA STRUCTURES NEEDED FOR BANKERS ALGO
// *** All data structures currently hard-coded size to match input file for testing ***

int *available;  // represents the number of available resources of each type
int *max;        // m x n matrix representing max number of instances of each resource that a process can request
int *allocation; // m x n matrix representing the num of resources of each type currently allocated to each process
int *need;       // m x n matrix representing the remaining resource needs of each process. Need[i][j] = max[i][j] - allocation[i][j]

int n_rows = -1;
int n_col = -1;

int readFileCustomers(char *fileName);
void *readFileSequences(char *fileName);
int safety();
int sum_arr(int arr[], int n);
void get_n_col(char *filename);

typedef struct thread //represents a single thread, you can add more members if required
{
    char tid[4]; //id of the thread as read from file
    unsigned int startTime;
    int state;
    pthread_t handle;
    int retVal;
} Thread;

int main(int argc, char *argv[]) // modify to take commandline arguments
{
    if (argc < 3)
    {
        printf("missing command line arguments.... exiting");
        return -1;
    }

    int TotalCustomers = readFileCustomers("sample4_in.txt");

    n_rows = TotalCustomers; // number of rows = amount of customers
    get_n_col("sample4_in.txt");

    // *****intialize data structures *****
    available = (int *)malloc(n_col * sizeof(int));
    for (int i = 0; i < n_col; i++)
    {
        //printf("argv == %d\n", atoi(argv[i + 1]));
        available[i] = atoi(argv[i + 1]);
    }

    safety();

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

    char *token;
    while (!feof(in))
    {
        char line[100];
        if (fgets(line, 100, in) != NULL)
        {
            printf("%s", line);
            token = strtok(line, ",");
            while (token != NULL)
            {
                token = strtok(NULL, ",");
            }
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

    // for (int i = 0; i < (sizeof(finish) / sizeof(finish[0])); i++)
    // {
    //     int need_n = (int)(sizeof(need[i]) / sizeof(need[i][0]));
    //     int available_n = (int)(sizeof(available) / sizeof(available[0]));

    //     printf("test >>> need_n = %d :: available_n = %d", need_n, available_n);

    //     int need_sum = sum_arr(*need[i], need_n);
    //     int available_sum = sum_arr(*available, available_n);
    //     if (finish[i] == false && need_sum <= available_sum)
    //     {
    //     }
    // }
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

void get_n_col(char *filename)
{
    FILE *in = fopen("sample4_in.txt", "r");

    if (!in)
    {
        printf(
            "Error in opening input file...exiting with error code -1\n");
        exit(-1);
    }

    char *token;
    if (!feof(in))
    {
        char line[100];
        if (fgets(line, 100, in) != NULL)
        {
            token = strtok(line, ",");
            n_col = 0;
            while (token != NULL)
            {
                n_col += 1;
                token = strtok(NULL, ",");
            }
        }
    }
    fclose(in);
    //printf("%d COLUMNS\n", n_col);
}

//***************************************************************
// **TESTING FUNCTIONS**
