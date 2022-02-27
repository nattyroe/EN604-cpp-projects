import os
import glob
import subprocess

import libconf


# Relative path to executable from the folder contatining
# this test manager
EXECUTABLE_PATH = '../build/x64/PokerHands.exe'

""" Runs Unit Test for PokerHands c++ executable

Compares output to Expected result stored in input files. The
expected results are based on c++ output formatting, and are
verified to be the correct hand ranking; tests should be used
to verify that code updates do not result in errors in ranking.
"""
def main():
    # Setup working directory
    start_path = os.getcwd()
    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    exe_path = os.path.join(os.getcwd(), EXECUTABLE_PATH)
    input_path = os.path.join(os.getcwd(), '../Input/')
    files = os.listdir(input_path)
    for file_name in files:
        test_path = os.path.join(input_path, file_name)
        try:
            # Run Executable and Print Results
            output_bits = subprocess.check_output([exe_path, test_path])
            output_strings = [line.rstrip() for line in output_bits.decode('UTF-8').split('\n') if line]
            print('Output:')
            for line in output_strings:
                print('    ', line)

            # Compare Executable Output with expected results
            with open(test_path) as f:
                config = libconf.load(f)
                try:
                    expected_output = config['expectedResult']
                    if expected_output == output_strings[-1]:
                        print('Test Result: PASS\n')
                    else:
                        print('Test Result: FAIL\n')
                except KeyError:
                    print('No Expected Result Found.\n')
                    continue
        except subprocess.CalledProcessError:
            print(f'Could not run file {test_path}\n')

    # Return working dir to starting location
    os.chdir(start_path)

if __name__ == "__main__":
    main()
