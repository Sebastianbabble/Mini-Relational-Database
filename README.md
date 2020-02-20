![](Desktop/READMEimg/make.png)
# Relational Database
This project implements a mini relational database. The data inside is stored using a b-tree data structure. You can access the database through fundamental sql commands. You can make tables and select tables. You can select using conditional statements as well as select everything via *.
***
## SQL queries 
1. make - makes table 
2. insert - inserts fields into specific table 
3. select - select everything from a table or specific fields using conditionals
***
## **Query examples**
1. make table employee fields last, first, dep, salary, year
2. insert into employee values Blow, Joe, CS, 100000, 2018
3. insert into employee values Yang, Bo, CS, 160000, 2013
4. select * from employee
5. select * from student where lname = Jackson
6. select * from employee where salary <= 23500
7. select * from student where major = "CS" and age < 25
8. select * from student where fname = Flo or lname = Jackson
9. select * from emplyee where last = "Van Gogh" or last = Jackson and salary >= 165000
10. select * from employee where dep = CS or year > 2014 and year < 2018 or salary >= 265000
***
<img width="1105" alt="make" src="https://user-images.githubusercontent.com/26701495/74970504-50fa3080-53d3-11ea-8a73-f45f56935340.png">

## **Implementation** 

 This database holds its data in tables which are binary files stored on disk. This allows the data to be stored and loaded when opening and closing sessions. To parse through the queires I use a parser class that uses a tokenizer to retrieve all valid tokens and stores them in a vector. This vector is then run through a statemachine in which I check each state of the query and if its a valid query then proceed to retrieving data.
 
 ## Run
   This program can be runned through the terminal using cmake. Clone the repisitory to a distinct directory and once in the directory you can type ./RDB to run the program. To exit out of the program type control-c. 
 
 ## Future improvements
    1. The ability to delete and merge tables
    2. An exit command instead of control-c
    3. Some sort of GUI
 
