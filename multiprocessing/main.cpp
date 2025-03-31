#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

// number for all people in the fill
const int nmbr_of_ppl = 501;

void calculateBMI(int start, int end, string* gender, int* height, int* weight, double* BMI)
{
    for (int i = start; i < end; i++)
    {
        // to make it in meters
        float height_meters = height[i] / 100.0;
        // this to calculate the bmi for each one
        BMI[i] = weight[i] / (height_meters * height_meters);
        cout << "The BMI for index " << i << " is: " << BMI[i] << endl;
    }
}

int main()
{
    string gender[nmbr_of_ppl];
    int height[nmbr_of_ppl];
    int weight[nmbr_of_ppl];
    int numofPeople = 0;

    struct timeval start_read, end_read; // to measure time for reading from file
    struct timeval start_avg, end_avg;   // to measure time for calculating average BMI

    ifstream file("bmi.csv");
    if (!file.is_open())
    {
        cout << "Sorry, but there is a problem with opening the file" << endl;
        exit(0);
    }

    gettimeofday(&start_read, NULL); // Start measuring reading time

    string line;
    while (getline(file, line))
    {
        stringstream reader(line);
        getline(reader, gender[numofPeople], ',');
        reader >> height[numofPeople];
        reader.ignore(1, ',');
        reader >> weight[numofPeople];
        numofPeople++;
    }
    file.close();

    gettimeofday(&end_read, NULL); // End measuring reading time

    // to inseart the data of the fill in the gender, height, and weight arrays
    if (numofPeople > 0)
    {
        for (int i = 1; i < numofPeople; ++i)
        {
            gender[i - 1] = gender[i];
            height[i - 1] = height[i];
            weight[i - 1] = weight[i];
        }
        numofPeople--;
    }

    // this to print the arrays
    for (int i = 0; i < numofPeople; ++i)
    {
        cout << "Gender: " << gender[i] << ", Height: " << height[i] << ", Weight: " << weight[i] << endl;
    }

    struct timeval start_bmi, end_bmi; // this to measure time
    gettimeofday(&start_bmi, NULL); // to measure the start time of the BMI calculation.

    double BMI[nmbr_of_ppl];

    int numProcesses = 4; // Number of child processes
    int dataPerProcess = numofPeople / numProcesses; // Number of data that each child will handle
    int remainingData = numofPeople % numProcesses; // calculate data points that are not distributed among processes

    pid_t childPid; // to get the ID for children
    int status;

    for (int i = 0; i < numProcesses; i++)
    {
        int start = i * dataPerProcess;
        int end = (i == numProcesses - 1) ? start + dataPerProcess + remainingData : start + dataPerProcess;

        childPid = fork();

        if (childPid == 0) // Child process
        {
            calculateBMI(start, end, gender, height, weight, BMI);
            exit(0);
        }
        else if (childPid < 0) // Fork failed
        {
            cout << "Fork failed." << endl;
            exit(1);
        }
    }

    // wait for all child processes to finish
    while ((childPid = wait(&status)) > 0)
    {
        // Do nothing
    }

    double summation = 0.0;
    // loop to sum all the results of BMI
    for (int u = 0; u < numofPeople; u++)
    {
        summation += BMI[u];
    }
    // calculate the average for all BMI
    double finalavg = summation / numofPeople;
    cout << "The Average BMI is: " << finalavg << endl;
    // this part to calculate the time ( start with process one and end when the code reaches the last process )
    gettimeofday(&end_bmi, NULL); // End measuring BMI calculation time

    // Calculate the time taken for reading from the file
    long long read_time = (end_read.tv_sec - start_read.tv_sec) * 1000000LL + (end_read.tv_usec - start_read.tv_usec);
    cout << "Reading time: " << read_time << " microseconds" << endl;

    // Calculate the time taken for calculating the average BMI
    long long bmi_time = (end_bmi.tv_sec - start_bmi.tv_sec) * 1000000LL + (end_bmi.tv_usec - start_bmi.tv_usec);
    cout << "BMI calculation time: " << bmi_time << " microseconds" << endl;

    return 0;
}
