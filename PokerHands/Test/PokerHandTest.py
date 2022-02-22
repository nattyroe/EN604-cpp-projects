import os
import glob

def main():
    # Setup working directory
    start_path = os.getcwd()
    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    exe_path = os.path.join(os.getcwd(), '../build/x64/PokerHands.exe')
    input_path = os.path.join(os.getcwd(), '../Input/')
    files = os.listdir(input_path)
    for file_name in files:
        test_string = exe_path + ' "' + os.path.join(input_path, file_name) + '"'
        os.system(test_string)
        print('\n')

    # Return working dir to starting location
    os.chdir(start_path)

if __name__ == "__main__":
    main()