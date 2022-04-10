import os
import sys
import random
import pandas as pd


def main():
    """Main Loop
    """
    start_path = os.getcwd()
    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    random.seed(7)
    num_passengers = 10
    if len(sys.argv) > 1:
        num_passengers = int(sys.argv[1])
    max_start_time = 200
    if len(sys.argv) > 2:
        max_start_time = int(sys.argv[2])
    num_floors = 100
    if len(sys.argv) > 3:
        num_floors = int(sys.argv[3])

    index = pd.Series(data=[p for p in range(0, num_passengers)], name="Passenger")
    df = pd.DataFrame(index=index)

    for passenger in range(0, num_passengers):
        start_floor = random.randint(0, num_floors)
        end_floor = 0
        while True:
            end_floor = random.randint(0, num_floors)
            if not start_floor == end_floor:
                break
        start_time = random.randint(0, max_start_time)
        df.loc[passenger, 'Start Time'] = start_time
        df.loc[passenger, 'Start Floor'] = start_floor
        df.loc[passenger, 'End Floor'] = end_floor

    df.to_csv("Elevator.csv")
    print(df)

    # Return working dir to starting location
    os.chdir(start_path)

if __name__ == '__main__':
    main()