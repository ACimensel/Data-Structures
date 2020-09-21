#!/usr/bin/env python
import subprocess
import tempfile

passed = 0

n_tests = 6;

# Run a for loop of tests.
for i in range(1,n_tests+1):
    print "Running test " + str(i) + "... "
    
    # Create a temporary file to contain output
    tmpfile = tempfile.NamedTemporaryFile();

    # Run case i, put output into tmpfile
    cmdstr = "./hashtable_test " + str(i) + " " + tmpfile.name;
    subprocess.call(cmdstr,shell=True)
    
    # Compare output to the ground truth.
    cmdstr = "diff -b " + tmpfile.name + " " + str(i) + ".gt > /dev/null"
    rt = subprocess.call(cmdstr,shell=True);

    # Check if the test was passed.
    if rt == 0:
        passed += 1
        print "passed"
    else:
        print "failed"

    # Delete temporary file
    tmpfile.close();
    



print "Passed " + str(passed) + " of " + str(n_tests) + " tests"
