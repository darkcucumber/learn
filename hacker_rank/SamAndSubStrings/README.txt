https://www.hackerrank.com/challenges/sam-and-substrings


Apparently we have to calculate the number of substrings first, then proceed with a procedure that calculates and sums the substrings at each 'level'.

For example for 123, there are three levels:
3 1-char substrings
2 2-char substrings
1 3-char substrings

Thus if we calculate the number of substrings and proceed along the texts accordingly, we should be able to compute and sum up the substrings. 

Beware that we should also store the sum in a rather large integer data type, as the sum will obviously grow large (modulo cut at 10E9 + 7).