S-325-Algorithms Project 1

This project contains 4 algorithms to solve the Maximum Sum Subarray (MSS)
problem in 4 different ways, each with a different asymptotic complexity.

The enumeration method involves iterating over every index pair (i,j),
and computing the sum of all the values between the two indices. This
is computationally intensive, and runs in O(n^3) time.

The second enumeration method (enumeration2) involves iterating over
each index pair, but instead of computing from i to j each iteration
it keeps a running sum as it iterates through the j indices. This is
still fairly intensive and runs in O(n^2) time.

The third method is a divide and conquer method that involves breaking
the data sets into 2 parts. The maximum sub array could then exist in
the lower half, upper half, or overlap the two halves. The halves are
then halved until we have n unit sized containers which are then 
themselves their own maximum subarray. These units are then combined
into a maximum sub array as the recursion unwinds. As a solution can
exist entirely in the "bottom" half, entirely in the "top" half, or 
overlap the halfway point, each of these areas are checked when
combining the sub solutions into a larger sub solution. The final
solution will be when the two halves are put back together. At this
point if its possible a maximum sub array can overlap the two halves
then a combined solution is found. If not, the solution exists entirely
in the bottom half, or entirely in the top half and the previous sub
solutions are checked against each other. Whichever is the maximum
is taken as the maximum sub array for the whole array.

The fourth method is a linear time MSS algorithm. This algorithm
iterates over each index keeping track of a low bound, highbound,
and current best sum. As a new index is considered, it is either a new
high bound for a current MSS, or it is not. If it is not, then when
a positive value index is found, a new subarray is considered. If/when
the new subarray has a total sum exceeding the saved sum the bounds
are saved, and the total sum is saved. 
