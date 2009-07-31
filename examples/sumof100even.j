# A jane program to calculate
# the sum of the first 100
# even numbers
#

max := 100;
sum := 0;
current := 0;

while current <= 100 {

    if current % 2 != 0 {
        print "Skipping the odd number: " current;
        next;
    }

    sum = sum + current;
    current = current + 1;
}

print "The sum of the first 100 even numbers is = " sum;
