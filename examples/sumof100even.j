# A jane program to calculate
# the sum of the first 100
# even numbers
#

print "This program prints the sum";
print " of the first 100 even numbers";

max := 100;
sum := 0;
current := 0;

while current <= max {
    current = current + 1;

    if current % 2 != 0 {
        print "Skipping the odd number: " current;
        next;
    }

    sum = sum + current;
}

print "The sum of the first 100 even numbers is = " sum;
