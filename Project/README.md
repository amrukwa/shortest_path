# Shortest path Search
[![CodeFactor](https://www.codefactor.io/repository/github/amrukwa/shortest_path/badge)](https://www.codefactor.io/repository/github/amrukwa/shortest_path) [![BCH compliance](https://bettercodehub.com/edge/badge/amrukwa/shortest_path?branch=main)](https://bettercodehub.com/) ![build and test](https://github.com/amrukwa/shortest_path/workflows/build%20and%20test/badge.svg) ![automatic releases](https://github.com/amrukwa/shortest_path/workflows/automatic%20releases/badge.svg)  
## Implementation of Dijikstra's algorithm
![image](https://user-images.githubusercontent.com/57860857/98136848-a757c280-1ec1-11eb-978c-b271e5fdada2.png)  
This is a program that looks for the shortest path between two points. All the single connections should be given in the file specified by the user. If the path does not exist, the user is informed. If it does exist, the file with the shortest path and consecutive connections is created.
## The commands
The program is designed to be run from the command line. The controls are defined as follows:
* dijikstra.exe - by default, program runs without the commands. In this configuration, it will look for the file "data.txt" in the same directory. If it cannot be found, you will be informed of this.
* dijikstra.exe --help - run this command to get basic information about the commands and further guidance through the messages.
* dijikstra.exe --input=location\data.txt - if you want to find the shortest path for the points defined in the file somewhere outside the current directory, specify its location and the programm will use it.
## The input file format
The file should consists of the lines of the following structure: start_point end_point distance between them. Always end the line with the enter. Do not use commas. If you want to specify the points between which you want to find the shortest path, write them in the following format: start_point end_point. End the line with enter as well. The nonpositive distance, lack of the distance in any other line, etc. will be expected to be corrected by the user through the command line during the execution process. Remember to write down the cities/point names consisting of more than one word with _ between them. Otherwise, you will be asked to specify the line once again.
## The outcome
![image](https://user-images.githubusercontent.com/57860857/98137541-63b18880-1ec2-11eb-9cf1-236e98497a55.png)  
The shortest path between the two specified points will be automatically saved into the file "path.txt" in the directory of the program. The path will be written down connection by connection. You will also see the names of the two points in the console, as well as the overall distance between them. If there is no connection, you will be informed about it. 
## The program
You can download the program [here](https://github.com/amrukwa/shortest_path/releases).  
The actual version of the program is marked as _Latest release_. To download the code, click `Source code (zip)` or `Source code (tar.gz)` and save it on your computer. To download the executable file, click `dijikstra.exe` and save it on your computer. The output file storing the path will be created in the same folder as saved `.exe` file. Remember to prepare the datafile as marked in **The data file**.