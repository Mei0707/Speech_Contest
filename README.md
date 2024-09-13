# Speech Contest Management System
This repository contains a C++ program for managing a speech contest. The system allows you to conduct a speech contest with multiple rounds, track scores, save records, and display historical contest results.

## Features

* Start the Contest: Conduct the speech contest in multiple rounds with automatic speaker drawing and scoring.
* View Contest Records: Display historical contest results from saved records.
* Clear Records: Option to clear all saved contest records.
* Exit the System: Exit the application gracefully.

## File Descriptions

* `speechmanager.cpp:`
Contains the SpeechManager class that handles the core functionalities of the speech contest, including initializing speakers, conducting the contest, drawing results, and managing records.
* `contestmanagementsystem.cpp:`
The main file that creates an instance of the SpeechManager class and provides a user interface for interacting with the system.
## Compilation

To compile the program, use a C++ compiler such as g++. Ensure that both speechmanager.cpp and contestmanagementsystem.cpp are in the same directory. Use the following command to compile:
```
g++ -o contestmanagementsystem speechmanager.cpp contestmanagementsystem.cpp
```
## Usage
1. Run the compiled executable:
```
./contestmanagementsystem
```
2. Use the menu options to:
* Start the Contest: Choose option 1 to start a new speech contest.
* View Contest Records: Choose option 2 to display records of past contests.
* Clear Records: Choose option 3 to clear all existing contest records.
* Exit the System: Choose option 0 to exit the application.

## Data File

The program reads from and writes to a CSV file named `speech.csv` to save and load contest records. Ensure this file is in the same directory as the executable for proper functionality.

## Notes

Ensure that you have a C++ compiler installed on your system.
The system uses random numbers for generating scores, so results will vary with each run.
