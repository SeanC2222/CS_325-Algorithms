CS-325-Algorithms Project 2

SHORTCUT COMMAND: make example
Will make all 3 algorithms, and run them against planned outputs and create output files amountSlow.txt, amountGreedy.txt, and amountCDP.txt.

Longer Explanation:

This project contains 3 algorithms to solve the coin problem in 3 different ways using a brute force method, greedy method, and dynamic programming method.

Using the makefile and the basic "make" command three programs will be created. proj2 and proj2Slow and proj2CDP will be the resulting executable files. proj2 contains the greedy algorithms, proj2Slow contains the brute force algorithm using recursion, and projCDP contains the dynamic programming algorithm and associated data structure coinCount. Due to very long run times for the changeslow algorithm, it was placed in it's own file so that input files with smaller amounts can be run with the program. Depending on the number of coin values, the upper bound for the amount varies between 35 and 80 for the changeslow algorithm. To be safe, execute it with values of 35 or less.

As an example for running the first executable file, type:

proj2 CoinInput.txt

Where proj2 is the executable name and CoinInput.txt is the input file containing the arrays of coin values and the amounts. The input file is formatted in the following fashion:

[1, 5, 10, 15]
56

The output file containing the results of the number of each coin and the number of minimum coins required is provided in a text file with the same name as the input file, appended with the word "change". For the example using prog2 provided above, the output file name would be CoinInputchange.txt. Be careful with the amountCDPchange.txt file. There are a few 10,000 length coin arrays that will take up a lot of screen real estate in a basic text editor. The first few examples match amountGreedy.txt so comparisons on those will be easiest.
