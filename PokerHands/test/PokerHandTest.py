""" Runs test files for the PokerHands comparison tool

Runs all files in the Input folder using the specified path
and prints results to console for review.
"""
import os
import glob

# Relative path to executable from the folder contatining
# this test manager
EXECUTABLE_PATH = '../build/x64/PokerHands.exe'


def main():
    # Setup working directory
    start_path = os.getcwd()
    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    exe_path = os.path.join(os.getcwd(), EXECUTABLE_PATH)
    input_path = os.path.join(os.getcwd(), '../input/')
    files = os.listdir(input_path)
    # Iterate through Test files
    for file_name in files:
        test_string = exe_path + ' "' + \
            os.path.join(input_path, file_name) + '"'
        os.system(test_string)
        print('\n')

    # Return working dir to starting location
    os.chdir(start_path)


if __name__ == "__main__":
    main()
