#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <thread>
#include <vector>

using namespace std;

const int nmbr_of_ppl = 501;

/// Student's Name : Mariam Turk
/// Student's ID : 1211115
/// Section : 1
/// Instructor's Name : Abel Salam Sayyad

// function ti calculate bmi for each person
void calculateBMI(int start, int end, string* gender, int* height, int* weight, double* BMI)
{
    for (int i = start; i < end; i++)
    {
        float height_meters = height[i] / 100.0;
        // equation for bmi
        BMI[i] = weight[i] / (height_meters * height_meters);
        cout << "The BMI for index " << i << " is: " << BMI[i] << endl;
    }
}

int main()
{
    string gender[nmbr_of_ppl]; //  to save male or female in array
    int height[nmbr_of_ppl]; //  to save the hight for each person
    int weight[nmbr_of_ppl]; // to save the wight for each person
    int numofPeople = 0;

    // this to calculate the time excution or the time of read from file or the time of calculate the avg of bmi
    struct timeval start_read, end_read;
    gettimeofday(&start_read, NULL);

    // this part to read the data from the file
    ifstream file("bmi.csv");
    if (!file.is_open())
    {
        cout << "Sorry, but there is a problem with opening the file" << endl;
        exit(0);
    }

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

     //  this to calculate the time for read from file
    gettimeofday(&end_read, NULL);
    long long read_time = (end_read.tv_sec - start_read.tv_sec) * 1000000LL + (end_read.tv_usec - start_read.tv_usec);
    cout << "File read time: " << read_time << " microseconds" << endl;

    // to save the data in the arrays
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

    for (int i = 0; i < numofPeople; ++i)
    {
        cout << "Gender: " << gender[i] << ", Height: " << height[i] << ", Weight: " << weight[i] << endl;
    }

    struct timeval start_bmi, end_bmi;
    gettimeofday(&start_bmi, NULL);

    double BMI[nmbr_of_ppl];

    // from here i beginig using threads
    int numThreads = 4; // Number of threads
    int dataPerThread = numofPeople / numThreads; // Number of data points each thread will handle
    int remainingData = numofPeople % numThreads; // Remaining data points

    // vector of type thread to save multiple thread in it
    vector<thread> threads;

    // this for loop to creating and starting multiple threads for parallel execution
    for (int i = 0; i < numThreads; i++)
    {
        int start = i * dataPerThread;
        int end = (i == numThreads - 1) ? start + dataPerThread + remainingData : start + dataPerThread;

        threads.push_back(thread(calculateBMI, start, end, gender, height, weight, BMI));
    }

    // this for loop to wait for each thread in the threads vector to finish executing before proceeding with the rest of the code
    for (auto& t : threads)
    {
        t.join();
    }

     // this part to calculate time of calculate the sum of bmi
    gettimeofday(&end_bmi, NULL);
    long long bmi_time = (end_bmi.tv_sec - start_bmi.tv_sec) * 1000000LL + (end_bmi.tv_usec - start_bmi.tv_usec);
    cout << "BMI calculation time: " << bmi_time << " microseconds" << endl;


    // this part to calculate time of calculate the avg of bmi
    double summation = 0.0;
    struct timeval start_avg, end_avg;
    gettimeofday(&start_avg, NULL);
    for (int u = 0; u < numofPeople; u++)
    {
        summation += BMI[u];
    }
    double finalavg = summation / numofPeople;
    gettimeofday(&end_avg, NULL);
    long long avg_time = (end_avg.tv_sec - start_avg.tv_sec) * 1000000LL + (end_avg.tv_usec - start_avg.tv_usec);
    cout << "Average BMI calculation time: " << avg_time << " microseconds" << endl;

    cout << "The Average BMI is: " << finalavg << endl;

    return 0;
}
