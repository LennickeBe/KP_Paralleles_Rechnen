import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

thread_paths = ["1", "2", "4", "8", "16", "32"]
board_sizes = ["128", "512", "2048", "8192", "32768"]


def df_to_mean_std(data: dict):
    result = dict()
    for thread in thread_paths:
        result[thread] = dict()
        for size in board_sizes:
            result[thread][size] = (np.mean(data[thread][size]),
                np.std(data[thread][size]))
    return result


def main():
    data_path = "data"
    gcc_path = "gcc"
    icc_path = "icc"

    # gcc
    gcc_data = dict()
    for thread in thread_paths:
        thread_data = dict()
        for size in board_sizes:
            path = os.path.join(data_path,
                                gcc_path,
                                thread,
                                f"times{size}.csv")
            thread_data[size] = pd.read_csv(path)

        gcc_data[thread] = thread_data
    # icc
    icc_data = dict()
    for thread in thread_paths:
        thread_data = dict()
        for size in board_sizes:
            path = os.path.join(data_path,
                                icc_path,
                                thread,
                                f"times{size}.csv")
            thread_data[size] = pd.read_csv(path)

        icc_data[thread] = thread_data

    gcc_data = df_to_mean_std(gcc_data)
    for i in gcc_data.items():
        print(f"{i[0]}\n")
        for j in i[1].items():
            print(j[1].head(5))


if __name__=="__main__":
    main()
