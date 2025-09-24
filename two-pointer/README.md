#Two Pointer problems

Idea is to take to pointers, one from left and one from right, and then move in each others direction to find the best two points in an array which gives the best solution

For ex.

1. Container with most water
https://leetcode.com/problems/container-with-most-water/description/

Solution: here we will take two pointers, left and right where left will be 0 and right will be n -1 initially and these two will be keep moving towards each other until they will overlap and at each iteration will be keeping the best(height as well as area).

2. 3Sum
https://leetcode.com/problems/3sum/submissions/1781580672/

Solution: here we will iterate the array from start to end
i 0 ... n
we will take two pointers left and right
for each iteration
    left = i + 1 and right will be the end of array n-1

and also we will be keep skipping the duplicates while moving to next element


