import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

thread_paths = ["1", "2", "4", "8", "16", "32"]
board_sizes = ["128", "512", "2048", "8192", "32768"]

def fix_size_plot(size: int, gcc_data: dict, icc_data):
    fig = plt.subplots()
    plt.title("Durchschnittliche Laufzeit von update_board() mit "
            + size + "x" + size + " Boardgröße.")
    plt.ylabel("Laufzeit [s]")
    plt.xlabel("Threadanzahl")
    plt.errorbar(thread_paths,
            [ y[size][0] for x,y in gcc_data.items()],
            yerr=[ y[size][1] for x,y in gcc_data.items()],
            color="green", fmt="^", label="gcc", capsize=4)
    plt.errorbar(thread_paths,
            [ y[size][0] for x,y in icc_data.items()],
            yerr=[ y[size][1] for x,y in icc_data.items()],
            color="orange", fmt="s", label="icc", capsize=4)
    plt.legend()
    plt.show()


def compiler_compare_plots(gcc_data: dict, icc_data: dict):
    # fixed size multiple threads
    for size in board_sizes:
        fix_size_plot(size, gcc_data, icc_data)
    # fixed threads mulitple sized


def df_to_mean_std(data: dict):
    result = dict()
    for thread in thread_paths:
        result[thread] = dict()
        for size in board_sizes:
            result[thread][size] = (np.mean(data[thread][size]),
                np.std(data[thread][size].values))
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
    icc_data = df_to_mean_std(icc_data)
    
    compiler_compare_plots(gcc_data, icc_data)
    return
    for i in gcc_data.items():
        print(f"\n{i[0]}:")
        for j in i[1].items():
            print(j)


if __name__=="__main__":
    main()
