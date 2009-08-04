max := 0;
count := 0;
sum := 0;
avg := 0;

read "Enter the total number of entries we'll process: > " max;

i := 0;

while count < max {
    read ":>" i;
    sum = sum + i;
    count = count + 1;
}

avg = sum/max;

print "max = " max;
print "count = " count;
print "sum = " sum;
print "avg = " avg;

