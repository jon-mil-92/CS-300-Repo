# CS-300-Repo

## ABC University Course Planner Retrospective

> *What was the problem you were solving in the projects for this course?*

ABC University wanted an efficient program to store, print, and search for specified data (courses) from a comma separated values file. ABCU wanted a program that would parse and check the csv file of courses for the correct format, store the courses from the csv file in a data structure that would be appropriate for the task, print all of the stored courses, and search for and print a specified course along with its prerequisites.

First, pseudocode was created for the functions that were needed to check the file format, load the courses, print all of the courses, and search for and print a specified course. Pseudocode for each function was created for each potential data structure to store the courses in (vector, hash table, or binary search tree). Then, a runtime and memory analysis was conducted for each function to determine the best data structure to store the courses in. Following the analysis, a data structure was chosen for the project. And lastly, the project was implemented using C++.

> *How did you approach the problem? Consider why data structures are important to understand.*

The problem that ABCU wanted solved was completed incrementally. Pseudocode was first created, then a worst-case runtime and memory analysis of the pseudocode was performed, then the project was implemented and tested. It was important to choose the correct data structure so that the program would run efficiently. Choosing the wrong data structure to store the courses in would have resulted in slower sorting/searching/print times and potentially large memory usage.
  
> *How did you overcome any roadblocks you encountered while going through the activities or project?*

I had encountered some roadblocks during the developement of the project. These were overcome by careful research, debugging, and testing.
  
> *How has your work on this project expanded your approach to designing software and developing programs?*

This project expanded my approach towards software developement in a positive way. It enabled me to think more carefully of the data structures that are chosen for a task in a program. I learned of the consequences of choosing sub-optimal data structures for tasks through the analysis of algorithms and data structures. During the planning and analysis phases of developement, I now consider the best possible data structures for the task.

> *How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?*

This project was great practice towards maintainable, readable, and adaptable code. The project consisted of the development and implementation of data structures such as a hash table and a binary search tree. It was also modular in a sense because a class was created for each data structure that was developed, and these data structure classes could be reused and adapted towards the data in other projects. The code for the project was created in a manner that applied industry standard best practices, which resulted in well-oranized, readable code.
