#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>
#include <stdbool.h>
#include <ctype.h> //For run_cmd
// DATA STRUCTURES NEEDED FOR BANKERS ALGO
// *** All data structures currently hard-coded size to match input file for testing ***

int *available_ptr;  // represents the number of available resources of each type
int *max_ptr;        // m x n matrix representing max number of instances of each resource that a process can request
int *allocation_ptr; // m x n matrix representing the num of resources of each type currently allocated to each process
int *need_ptr;       // m x n matrix representing the remaining resource needs of each process. Need[i][j] = max[i][j] - allocation[i][j]

int n_rows = -1;
int n_col = -1;

int readFileCustomers(char *fileName);
void readFileSequences(char *fileName, int max[n_rows][n_col]);
bool safety(int *available, int *allocated, int *need);
int sum_arr(int arr[], int n);
void get_n_col(char *filename);
int bankersalgo();
void run_cmd();
int request_resource(int resource[]);
int release_resource(int resource[]);
void status(int *available, int *max, int *allocation, int *need);

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

    get_n_col("sample4_in.txt"); // find how many different resources the bank will have (number of columns in the matrix)

    /**
 * Error checking to ensure user gives the right amount of avaiable resources
 * Also checks if the given resource is a number or a letter
 * */
    if (argc < n_col + 1) // check if the user gave the right amount of arguments (n_col available resources)
    {
        printf("missing command line arguments.... exiting\n");
        return -1;
    }
    else if (argc > n_col + 1) //Error checking to ensure user only enters n_col arguments for current resources
    {
        printf("Too many command line arguments....exiting\n");
        return -1;
    }
    else
    { //Checks to ensure the given available resources is a number and not a letter

        for (int i = 1; i < argc; i++)
        {
            // printf("%d\n", isalpha(*argv[i]));
            if (isalpha(*argv[i]) != 0)
            {
                printf("Enter a number for available resources not a letter....exiting\n");
                return -1;
            }
        }
    }

    /**
     * Calculates the number of total customer sequences given with the sample 
     * txt file and displays it to the user
     */
    int TotalCustomers = readFileCustomers("sample4_in.txt");
    printf("Number of Customers: %d\n", TotalCustomers);
    printf("Currently Available resources: "); // Prints out the current list of available resources
    for (int i = 1; i < n_col; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("%s\n", argv[n_col]);

    n_rows = TotalCustomers; // number of rows = amount of customers

    // *****intialize AVAILABLE*****
    int *available = (int *)malloc(n_col * sizeof(int)); // takes arguments from the command line when the program is started
    for (int i = 0; i < n_col; i++)
    {
        //printf("argv == %d\n", atoi(argv[i + 1]));
        available[i] = atoi(argv[i + 1]); // populating the available array with the values passed thru the command line
    }

    // *****intialize ALLOCATION*****
    //int *allocation = (int *)malloc(n_col * n_rows * sizeof(int)); // initalize 2D array
    int allocation[n_rows][n_col];
    for (int i = 0; i < n_rows; i++)
    {
        for (int j = 0; j < n_col; j++)
        {
            allocation[i][j] = 0;
        }
    }

    // *****intialize MAX*****
    int max[n_rows][n_col];
    //int *max = (int *)malloc(n_col * n_rows * sizeof(int)); // initalize 2D array
    // MAX array is filled with the data from the textfile
    printf("Maximum resources from file:\n");
    readFileSequences("sample4_in.txt", max);

    // *****intialize NEED*****
    //int *need = (int *)malloc(n_col * n_rows * sizeof(int)); // initalize 2D array
    int need[n_rows][n_col];
    for (int i = 0; i < n_rows; i++)
    {
        for (int j = 0; j < n_col; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    available_ptr = &available[0];      // represents the number of available resources of each type
    max_ptr = &max[0][0];               // m x n matrix representing max number of instances of each resource that a process can request
    allocation_ptr = &allocation[0][0]; // m x n matrix representing the num of resources of each type currently allocated to each process
    need_ptr = &need[0][0];

    printf("\nTESTING >>>>\n");
    bool safe = safety(available, *allocation, *need);
    printf("\n<<<<<<<<<<<<<\n");

    // Finish bankersalgo

    // printf("Enter Command:");
    // //Ask user to enter a command followed by sequence
    // char command = scanf("%s", &command);
    // bankersalgo(command); //Takes and executes command
    run_cmd();
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

void readFileSequences(char *fileName, int max[n_rows][n_col])
{
    FILE *in = fopen("sample4_in.txt", "r");

    if (!in)
    {
        printf(
            "Error in opening input file...exiting with error code -1\n");
        exit(-1);
    }

    char *token;

    int i = 0;
    while (!feof(in))
    {
        char line[100];
        if (fgets(line, 100, in) != NULL)
        {
            printf("%s", line);
            token = strtok(line, ",");
            int j = 0;
            while (token != NULL)
            {
                //printf("\n");
                //printf(" %d ", atoi(token));
                max[i][j] = atoi(token);
                token = strtok(NULL, ",");
                j += 1;
            }
        }
        i += 1;
    }
    printf("\n");
    fclose(in);
}

// impliments requestResource(), releaseResource(), and saftey() functions
int bankersalgo() // REMEMBER TO DEFINE ABOVE
{
}

// function to request a resource
// Return: 0 = Sucess
// Return: -1 = Failed
int request_resource(int resource[]) // REMEMBER TO DEFINE ABOVE
{
    //Testing
    for (int i = 0; i < n_col + 1; i++)
    {
        printf("%d ", resource[i]);
        printf("\n");
    }
    return 0;
}

// function to release a resource
// Return: 0 = Sucess
// Return: -1 = Failed
int release_resource(int resource[]) // REMEMBER TO DEFINE ABOVE
{
    //Testing
    for (int i = 0; i < n_col + 1; i++)
    {
        printf("%d ", resource[i]);
        printf("\n");
    }

    return 0;
}

// Saftey algo mentioned in chapter 8
// Use: find whether or not a system is in a safe state.
// Return: true - system is in a safe state
//         false - system is not in a safe state
bool safety(int *available, int *allocated, int *need)
{
    int work[n_col];
    for (int i = 0; i < n_col; i++) // work = available
    {
        work[i] = *(available + i); // work[i] = available[i]
        printf("work[%d] = %d ", i, *(available + i));
    }
    printf("\n");

    // initalize finish - 0, ..., n-1 = false
    bool finish[n_rows];
    for (int i = 0; i < n_rows; i++)
    {
        finish[i] = false;
    }

    int safe_seq[n_rows];

    int ind = 0;
    while (ind < n_rows)
    {
        bool found = false;
        for (int i = 0; i < n_rows; i++)
        {
            if (finish[i] == false)
            {
                int j = 0;
                for (j = 0; j < n_col; j++)
                {
                    if (*((need + i * n_col) + j) > work[j]) // need[i][j] > allocated[i][j] (why do I need to do this, I hate C)
                    {
                        break;
                    }
                }
                if (j == n_rows)
                {
                    for (int y = 0; y < n_col; y++)
                    {
                        work[y] += *((allocated + i * n_col) + y);
                    }
                    finish[i] = true;

                    found = true;
                    safe_seq[ind++] = i;
                }
            }
        }
        if (found == false)
        {
            printf("System is not in safe state");
            return false;
        }
    }

    printf("The SAFE sequence is: ");
    for (int i = 0; i < n_rows - 1; i++)
    {
        printf(" P%d ->", safe_seq[i]);
    }
    printf(" P%dn\n", safe_seq[n_rows - 1]);

    return true;
}

void status(int *available, int *max, int *allocation, int *need)
{
    printf("Currently Available resources: ");
    for (int i = 0; i < n_col; i++)
    {
        printf("%d ", available[i]);
    }
    printf("\n");

    printf("Maximum Resources:\n");
    for (int i = 0; i < n_rows; i++)
    {
        for (int j = 0; j < n_col; j++)
        {
            printf("%d ", *((max + i * n_rows) + j));
        }
        printf("\n");
    }
    printf("Allocated Resources:\n");
    for (int i = 0; i < n_rows; i++)
    {
        for (int j = 0; j < n_col; j++)
        {
            printf("%d ", *((allocation + i * n_rows) + j));
        }
        printf("\n");
    }
    printf("Need Resources:\n");
    for (int i = 0; i < n_rows; i++)
    {
        for (int j = 0; j < n_col; j++)
        {
            printf("%d ", *((need + i * n_rows) + j));
        }
        printf("\n");
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

void run_cmd()
{
    char command[100]; //Change command name to something else that matches bc its cmd and sequence
    char cmd[2];
    bool ongoing = true;

    /**
 * The next ints are the values that come after the user enters the command
 * */

    while (ongoing)
    {
        printf("Enter Command: ");

        // %29s makes it so theres no buffer overload
        // scanf("%29s", command); //With this it becomes difficult to check what command

        fgets(command, 100, stdin);

        char *onlyCommand = strtok(command, " "); //removes all white spaces and retrieves only the command
        //printf("COMMAND >>> %s\n", onlyCommand);

        int args[n_col + 1];
        char *token;
        token = strtok(NULL, " ");
        int j = 0;
        while (token != NULL)
        {
            // printf("\n");
            // printf(" %d ", atoi(token));
            args[j] = atoi(token);
            // printf("%d ", args[j]);
            token = strtok(NULL, " ");
            j += 1;
        }

        // TESTING args[]
        // printf("\n");
        // for (int i = 0; i < n_col + 1; i++)
        // {
        //     printf("%d ", args[i]);
        // }

        // strcpy(line, ptr);

        /**
         * User can avoid trying to be case sensitve and type command however they want
         * */
        for (char *lowercase_cmd = command; *lowercase_cmd; lowercase_cmd++)
            *lowercase_cmd = tolower(*lowercase_cmd);

        /**
         * The scanf and if statements don't work properly need to fix
         * Find a way to split the string
         * */
        // char *k = &command[0];
        // printf("%s", k);
        /**
         * strcmp causes errors with not allowing a delemiter to work
         * */
        if (strstr(command, "rq") != NULL)
        {

            /**
             * Include content for if the user requests resources
             * */
            printf("work rq\n");

            request_resource(args);
        }
        else if (strstr(command, "rl") != NULL)
        {

            /**
             * Include content for if the user wants to release resources
             * */
            printf("work rl\n");
            release_resource(args);
        }
        else if (strstr(command, "status") != NULL)
        {

            //Execute the status command
            printf("status\n");
            status(available_ptr, max_ptr, allocation_ptr, need_ptr);
        }
        else if (strstr(command, "run") != NULL)
        {
            //execute the run command

            printf("run\n");
        }
        else if (strstr(command, "quit") != NULL)
        {

            printf("Exit\n");
            ongoing = false;
        }
        else
        {
            // if (k != "run" && k != "quit" && k != "status" && k != "rl" && k != "rq")
            printf("Invalid Command. Retry and type the following {RQ, RL, Run, Status}\n");
        }
    }
}

//***************************************************************
// **TESTING FUNCTIONS**
