fun main() 
{
    current := 100;
    sum := 0;

    while current > 0  {

        sum = sum + current;
        current = current - 1;

    }

    print "The sum of the first 100 numbers is = " sum;

    return 0;
}
