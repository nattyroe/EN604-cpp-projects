""" Runs tests comparing the Python 'statistics' to C++ class

This will read lines from file 'tests.csv' stored in
the same folder as this file, and calculate the sample
mean and sample standard deviation using the
python 'statistics' module, and the TestStatistics C++
class stored in the ../ folder.
"""

import csv
import os
import statistics


def run_stats(values):
    """Calculate the mean and samle std dev for given values

    Args:
        values (list[int or float]): List of values to run stats on
    """
    try:
        # Attempt conversion to floats
        values = [float(v) for v in values]
        # Calculate statistics
        print('Mean:', statistics.mean(values))
        print('Std Deviation:', statistics.stdev(values))
    # Catch float conversion errors
    except ValueError as e:
        print(e)


def main():
    """Main function. Reads distributions from tests.csv
    and calculates stats in two different ways.
    """
    # Setup working directory
    start_path = os.getcwd()
    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    # Read 'tests.csv' in current folder
    with open(r'tests.csv') as file:
        csv_reader = csv.reader(file)
        for row in csv_reader:
            row = [value.strip() for value in row]
            if row:
                # Print distribution to console
                print('CSV Values:', row)

                # Run python stats and print results
                print('\nPython Results:')
                run_stats(row)

                # Run C++ stats and print results
                print('\nC++ Results:')
                test_string = '../StatisticTest ' + ' '.join(row)
                print(test_string)
                os.system(test_string)

                print('\n')

    # Return working dir to starting location
    os.chdir(start_path)


if __name__ == "__main__":
    main()
