# BMI Calculator in C++

This project implements and compares three versions of a **Body Mass Index (BMI)** calculator in C++. The goal is to evaluate the **performance difference** between:

1. ✅ Sequential Execution  
2. 🧵 Multithreaded Execution (using `std::thread`)  
3. 👨‍👩‍👧 Multiprocessing Execution (using `fork()` system calls)

Each version reads height and weight data from a CSV file, calculates the BMI for each person, and computes the average BMI. Execution time for file reading, BMI calculation, and average computation is measured and printed.

---

## 👩‍💻 Author
- **Name**: Mariam Turk  
- **ID**: 1211115  
- **Section**: 1  
- **Instructor**: Dr. Abdel Salam Sayyad

---

## 📁 File Descriptions

| File | Description |
|------|-------------|
| `bmi_sequential.cpp` | Sequential version: reads CSV, calculates BMI, and computes average |
| `bmi_multiprocessing.cpp` | Uses `fork()` to split workload among child processes |
| `bmi_multithreaded.cpp` | Uses C++ threads to parallelize BMI calculation |
| `bmi.csv` | Input file with rows formatted as: `Gender,Height(cm),Weight(kg)` |

---

## 📊 Output Example

Gender: Male, Height: 175, Weight: 70
The BMI for index 0 is: 22.86
...
The Average BMI is: 24.14
BMI calculation time: 1532 microseconds
Each version prints:

All loaded data

Individual BMI values

Average BMI

Timing measurements for:

File reading

BMI computation

Average calculation

## ⚙️ Performance Metrics
Each version measures and prints:

📂 File Read Time

🧠 BMI Calculation Time

📉 Average Calculation Time

Use these to compare the speedup gained from parallel execution.

## 📈 Example Data Format (bmi.csv)

Gender,Height,Weight
Male,180,75
Female,165,60
...
🚀 Key Concepts
BMI Calculation:

𝐵𝑀𝐼 = Weight (kg) / (Height (m)) ^2

System Calls Used:

fork() and wait() for multiprocessing

std::thread and join() for multithreading

gettimeofday() for microsecond timing

## 🔬 Learning Objectives
Understand how CPU parallelism affects performance

Implement and compare process-based vs thread-based parallel programming

Apply file I/O and time measurement in C++











