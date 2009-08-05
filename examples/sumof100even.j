# A jane program to calculate
# the sum of the first 100
# even numbers
#
#

#if b is even add it to
# a, else just return a
fun sum_if_even(a, b)
{
    if b % 2 != 0 {
        return a;
    }

    return a + b;
}

fun main()
{

    print "This program prints the sum";
    print " of the first 100 even numbers";

    max := 100;
    sum := 0;
    current := 0;

    while current <= max {
        current = current + 1;
        
        sum = sum_if_even(sum, current);
    }

    print "The sum of the first 100 even numbers is = " sum;

    return 0;
}
