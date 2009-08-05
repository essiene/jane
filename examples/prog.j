fun summer(a, b) {
    print "inside summer" a + b;
    return a + b;
}

fun main() {
    # This is a single line comment
    a := 5; # declare a
    b := 6;
    c := 7;

    #
    # This is a multiline
    # Comment
    #
    # Uhh... actually its multiple
    # single line comments used
    # to simulate multiline comments :)

    print a;
    print b;
    print c;

    print "Sum of 6 and 7 = " summer(b, c);

    e := a + b - c;

    print e * 2 - 5;

    d := 10;

    print d % 9;

    print 2 ^ 5;

    while d > 0 && 1 <= 5 {
        d = d - 1;
        if d%2 == 0 || d%5 == 0 {
            print "even or multiple of 5:>" d;
        }
    }

    while d < 15 {
        d = d + 1;
        if d%10 == 5 {
            stop;
        } else {
            print d;
            next;
        }
    }

    return 0;
}


