
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/time.h>
/// Student's Name : Mariam Turk
/// Student's ID : 1211115
/// Section : 1
/// Instructor's Name : Abel Salam Sayyad
using namespace std;

const int nmbr_of_ppl = 501;

int main()
{
    string gender[nmbr_of_ppl]; // the array of gender is created just in case it needed later
    //--->>> These two main arrays will be used for the claculations and all data will be sorted in them
    int height[nmbr_of_ppl];
    int weight[nmbr_of_ppl];
    int numofPeople = 0; // this will be used as pointer
    // open the file, and make sure that it exists so we can read the data
    ifstream file("tst.csv");
    if (!file.is_open())
    {
        cout << "sorry but there is a problem with opening the file" << endl;
        exit(0);
    }
    string line; // this will be used as pointers on the lines while reading from a file
    while (getline(file, line))
    {
        stringstream reader (line); // here the whole line will be stored
        // -->> now i need to seperate the gender, wieght and hieght using the comma technique
        getline(reader, gender[numofPeople], ',');
        reader >> height[numofPeople];
        reader.ignore(1, ',');
        reader >> weight[numofPeople];
        numofPeople++;
    }
    file.close();
    // the first row of the arrays will be some random chars, to fix this i just remives the first index
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
    // Now I need to start with the BMI calculations and here we need to measure the time for this operation
    struct timeval start_bmi, end_bmi;
    gettimeofday(&start_bmi, NULL); // ti begin from here
    double BMI[nmbr_of_ppl];
    for (int k = 0; k < numofPeople; k++)
    {
        // first to get the BMI, the hieght supposed to be in meters so i converted it into meters
        float height_meters = (height[k]) / 100.0;
        BMI[k] = (weight[k]) / (height_meters * height_meters); // this is the equation for getting the correct BMI
        cout << "The BMI for index " << k << " is: " << BMI[k] << endl;
    }
    //---> I need now to get the BMI avg for the new array
    double summation = 0.0;
    for (int u=0; u<nmbr_of_ppl; u++)
    {
        summation = summation + BMI[u];
    }
    double finalavg = summation / (nmbr_of_ppl-1);
    cout << "The Average BMI is : " << finalavg << endl;
    gettimeofday(&end_bmi, NULL);
    long long bmi_time = (end_bmi.tv_sec - start_bmi.tv_sec) * 1000000LL +
                         (end_bmi.tv_usec - start_bmi.tv_usec);
    cout << "BMI calculation time: " << bmi_time << " microseconds" << endl;

    return 0;
}
