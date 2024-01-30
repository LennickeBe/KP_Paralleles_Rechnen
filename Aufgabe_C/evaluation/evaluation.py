import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

thread_paths = [1, 2, 4, 8, 16, 32]
board_sizes = [128, 512, 2048, 8192, 32768]
image_path = "../report/slow_images"
res_path = "../report/slow_results.txt"
res_file = open(res_path, 'w')

def fix_size_plot(size: int, gcc_data: dict, icc_data: dict):
    fig = plt.subplots()
    plt.title("Durchschnittliche Laufzeit von update_board() mit "
            + str(size) + "x" + str(size) + " Boardgröße.")
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
    #plt.show()
    plt.savefig(os.path.join(image_path,
        f"fix_size_{size:05}.png"), bbox_inches="tight")
    plt.clf()
    plt.cla()
    plt.close()


def fix_threads_plot(threads: int, gcc_data: dict, icc_data: dict):
    fig,ax = plt.subplots()
    if threads==1:
        plt.title("Durchschnittliche Laufzeit von update_board() mit 1 Thread.")
    else:
        plt.title("Durchschnittliche Laufzeit von update_board() mit "
            + str(threads) + " Threads.")
    plt.ylabel("Laufzeit [s]")
    plt.xlabel("Boardsize")
    ax.set_xscale("log")
    ax.set_yscale("log")
    plt.errorbar(board_sizes,
            [ gcc_data[size][0] for size in board_sizes],
            yerr=[ gcc_data[size][1] for size in board_sizes],
            color="green", fmt="^", label="gcc", capsize=4)
    plt.errorbar(board_sizes,
            [ icc_data[size][0] for size in board_sizes],
            yerr=[ icc_data[size][1] for size in board_sizes],
            color="orange", fmt="s", label="icc", capsize=4)
    plt.legend()
    #plt.show()
    plt.savefig(os.path.join(image_path,
        f"fix_threads_{threads:02}.png"), bbox_inches="tight")
    plt.clf()
    plt.cla()
    plt.close()

def compiler_compare_plots(gcc_data: dict, icc_data: dict):
    # fixed size multiple threads
    for size in board_sizes:
        fix_size_plot(size, gcc_data, icc_data)
    # fixed threads mulitple sized
    for threads in thread_paths:
        fix_threads_plot(threads, gcc_data[threads], icc_data[threads])


def omp_sched_compare(omp_data: dict):
    fig, ax = plt.subplots()
    plt.title("Durchschnittliche Laufzeit für 128x128 Board mit 32 Threads für verschiedene OMP_SCHEDULEs. (icc compiled)")
    plt.xlabel("OMP_SCHEDULE Typ")
    plt.ylabel("Laufzeit [s]")
    for key, value in omp_data.items():
        # use value.values for std otherwise a series is returned for some reason
        plt.errorbar([key], [np.mean(value)], yerr=np.std(value.values), color="green", fmt="s")
        #res_file.write(f"omp_schedule: {key} mean: {np.mean(value):.6f} std: {np.std(value.values):.6f}\n")
        res_file.write(f"{key} & {np.mean(value):.6f} & {np.std(value.values):.6f} \\\\\n")

    #plt.show()
    plt.savefig(os.path.join(image_path,
        f"omp_sched_compare.png"), bbox_inches="tight")
    plt.clf()
    plt.cla()
    plt.close()


def df_to_mean_std(data: dict):
    result = dict()

    for thread in thread_paths:
        result[thread] = dict()
        for size in board_sizes:
            result[thread][size] = (np.mean(data[thread][size]),
                np.std(data[thread][size].values))
            #res_file.write(f"thread: {thread} boardsize: {size} mean: {result[thread][size][0]:.6f} std: {result[thread][size][1]:.6f}\n")  
            res_file.write(f"{thread} & {size} & {result[thread][size][0]:.6f} & {result[thread][size][1]:.6f} \\\\\n")  
    return result


def main():
    data_path = "slow_data"
    gcc_path = "gcc"
    icc_path = "icc"

    # make sure path for the images is there
    if not os.path.isdir(image_path):
        os.makedirs(image_path)

    # gcc
    gcc_data = dict()
    for thread in thread_paths:
        thread_data = dict()
        for size in board_sizes:
            path = os.path.join(data_path,
                                gcc_path,
                                str(thread),
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
                                str(thread),
                                f"times{size}.csv")
            thread_data[size] = pd.read_csv(path)
        icc_data[thread] = thread_data

    res_file.write("gcc:\n")
    gcc_data = df_to_mean_std(gcc_data)
    res_file.write("icc:\n")
    icc_data = df_to_mean_std(icc_data)

    compiler_compare_plots(gcc_data, icc_data)

    # OMP_SCHEDULE plots
    omp_schedule = ["auto", "guided", "static", "dynamic"]
    omp_data = dict()
    res_file.write("omp_sched:\n")
    path = os.path.join(data_path, icc_path, "32")
    for sched_type in omp_schedule:
        omp_data[sched_type] = pd.read_csv(os.path.join(path, f"{sched_type}.csv"))

    omp_sched_compare(omp_data)

    return

if __name__=="__main__":
    main()
    res_file.close()
