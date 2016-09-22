# GPA-Calculator
I wrote this for fun when the official GPA calculator from UCLA went down.

# Compilation
1. Download the source code and unzip it.

2. In command line, type:

        make

# Usage
## Run without argument
In this way, simply run

        ./gpacalc 

Then the program will prompt:
Please type in the options:
[1] Input course info;
[2] Read a file;
[Other] Exit the Program.

### Input all course information manually
Type 1 and enter, then follow the instruction the program provides to enter all course information

### Manually enter the path of the file that contains all information
Type 2 and enter, then enter the full path of the destination file. For example:

      $ ./gpacalc 
      Please type in the options:
      [1] Input course info;
      [2] Read a file;
      [Other] Exit the program.
      2
      Please input file name: (default grade.txt)
      File needs to be in format "Name,Units,Grade,IsUpperDiv".
      ~/Documents/GPA/grade.txt 

## Run with argument
### --help argument
When we run the program with --help argument, the program will print help information to users.

      $ ./gpacalc --help

### the path of the file containing courses / grades information
The program will load information from the destination file. For eample:

      $ ./gpacalc grade.txt

The program will load information from grade.txt and print out information based on quarter. 
The program will also give a summary of GPA.

# Grade File format
The file should be a plaintext file with the following format
Comments start with the character \#. For example

      # This is a comment

Quarters information:

      QUARTER,YEAR

Note there is no white space around the comma. For example:

      FALL,2015
      WINTER,2016

Course information:

      COURSE NAME,UNITS,GRADE,IS IT UPPER DIV?
      
For "IS IT UPPER DIV?", it has to be 'y' or 'n', case insensitive. 
Note there is no white space around the comma. For example:

      CS 111,5,A+,y

