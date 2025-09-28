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

3. Trapping Rain water problem
https://leetcode.com/problems/trapping-rain-water/description/

Idea is to start with two pointers left and right and also keep tracking max_left and max_right and then keep moving towards smaller one as we know the other one is bigger one. For ex. if left is the smaller one then check if this is the max height on left if yes then replace if no then calc sum by subtracting height[left] from max_left, keeping in might that right pointer currenlty is greater than max_left, so it is safe to compare it with max_left. Solution is on leetcode
