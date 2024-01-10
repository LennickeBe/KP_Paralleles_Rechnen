#!/bin/python3
"""
Script to read the data for the string manipulation measurement
and plot the results.
"""
import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def get_strings(key: str) -> dict:
    """ Returns a dict for plot related strings.

    Args:
        key (str): which set of strings for the plots are desired

    Returns:
        (dict): dictionary with strings for plots (e.g. "title",...)
    """
    return {
            "count": {"title": f"Processing time to count chars in a string with ",
                "ylabel":"time in ns",
                "xlabel":"iterations",
                "color_par":"green",
                "marker_par":"^",
                "color_seq":"orange",
                "marker_seq":"s",
                "filename":"../report/images/comp_count_"
                },
            "up": {"title": f"Processing time to uppercase chars in a string with ",
                "ylabel":"time in ns",
                "xlabel":"iterations",
                "color_par":"green",
                "marker_par":"^",
                "color_seq":"orange",
                "marker_seq":"s",
                "filename":"../report/images/comp_upper_"
                },
            "low": {"title": f"Processing time to lowercase chars in a string with ",
                "ylabel":"time in ns",
                "xlabel":"iterations",
                "color_par":"green",
                "marker_par":"^",
                "color_seq":"orange",
                "marker_seq":"s",
                "filename":"../report/images/comp_lower_"
                },
            "complex_count": {"title": f"Mean processing time to count chars in strings of different length.",
                "ylabel":"time in ns",
                "xlabel":"string length",
                "color_par":"green",
                "marker_par":"^",
                "color_seq":"orange",
                "marker_seq":"s",
                "filename":"../report/images/complex_count.png"
                },
            "complex_up": {"title": f"Mean processing time to uppercase string with of different length.",
                "ylabel":"time in ns",
                "xlabel":"string length",
                "color_par":"green",
                "marker_par":"^",
                "color_seq":"orange",
                "marker_seq":"s",
                "filename":"../report/images/complex_upper.png"
                },
            "complex_low": {"title": f"Mean processing time to lowercase chars in a string with of different length.",
                "ylabel":"time in ns",
                "xlabel":"string length",
                "color_par":"green",
                "marker_par":"^",
                "color_seq":"orange",
                "marker_seq":"s",
                "filename":"../report/images/complex_lower.png"
                }
            }[key]


def comparison_plot(strings: dict,
                    str_length: int,
                    series_par: pd.Series,
                    series_seq: pd.Series) -> None:
    """ Creates a scatter plot with the given data and strings.

    The given strings dict is from the 'get_strings' function contains
    the information about the title (together with 'str_length',
    labels for the axes, etc.
    The 'series_par' and 'series_seq' are scatter-plotted.

    Args:
        strings (dict): dict with strings for the plot
        str_length (int): length of the string the data corresponds to
        series_par (pd.Series): Data for the parallel function
        series_seq (pd.Series): Data for the sequential function
    Returns:
    """
    mean_par = np.mean(series_par)
    std_par = np.std(series_par)
    mean_seq = np.mean(series_seq)
    std_seq = np.std(series_seq)

    fig, ax = plt.subplots()
    plt.title(strings["title"]+f"{str_length} chars.", pad=20)
    plt.ylabel(strings["ylabel"])
    plt.xlabel(strings["xlabel"])
    # means
    plt.hlines(mean_par, series_par.index.values[0], series_par.index.values[-1], color=strings["color_par"], label="parallel mean")
    plt.hlines(mean_seq, series_seq.index.values[0], series_seq.index.values[-1], color=strings["color_seq"], label="sequential mean")
    # standard deviation / error
    plt.hlines(mean_par+std_par, series_par.index.values[0], series_par.index.values[-1], color=strings["color_par"], alpha=0.6)
    plt.hlines(mean_seq+std_seq, series_seq.index.values[0], series_seq.index.values[-1], color=strings["color_seq"], alpha=0.6)
    plt.hlines(mean_par-std_par, series_par.index.values[0], series_par.index.values[-1], color=strings["color_par"], alpha=0.6)
    plt.hlines(mean_seq-std_seq, series_seq.index.values[0], series_seq.index.values[-1], color=strings["color_seq"], alpha=0.6)
    # box between

 

    # values
    plt.scatter(series_par.index.values, series_par.values, color=strings["color_par"], label="parallel", marker=strings["marker_par"])
    plt.scatter(series_seq.index.values, series_seq.values, color=strings["color_seq"], label="sequential", marker=strings["marker_seq"])
    plt.legend()
    plt.savefig(strings["filename"] + f"{str_length}.png", bbox_inches = "tight")
    #plt.show()
    plt.clf()
    plt.cla()
    plt.close()


def comparison_plots(df: pd.DataFrame, str_length: int) -> None:
    """ Creates comparison plots for the string manipulation functions.

    In the dataframe are column pairs (parallel, sequential) for
    the countChar, toUppercase, toLowercase.
    This functions calls 'comparion_plot' for each pair with the
    matching plot-strings-dict.

    Args:
        df (pd.DataFrame): time measurement data
        str_length (int): length of the string the measurment used

    Returns:
    """
    # count
    strings = get_strings("count")
    series_par = df["count_par"]
    series_seq = df["count_seq"]
    comparison_plot(strings, str_length, series_par, series_seq)

        # uppercase
    strings = get_strings("up")
    series_par = df["upper_par"]
    series_seq = df["upper_seq"]
    comparison_plot(strings, str_length, series_par, series_seq)

    # lower
    strings = get_strings("low")
    series_par = df["lower_par"]
    series_seq = df["lower_seq"]
    comparison_plot(strings, str_length, series_par, series_seq)


def complex_plot(strings: dict,
                 means_par: list,
                 means_seq: list,
                 iter_list: list) -> None:
    fig, ax = plt.subplots()
    plt.title(strings["title"], pad=20)
    plt.xlabel(strings["xlabel"])
    plt.ylabel(strings["ylabel"])
    ax.set_xscale("log")
    ax.set_yscale("log")
    plt.scatter(iter_list, means_par, color=strings["color_par"], marker=strings["marker_par"], label="mean parallel")
    plt.scatter(iter_list, means_seq, color=strings["color_par"], marker=strings["marker_seq"], label="mean sequential")
    plt.legend()
    plt.savefig(strings["filename"], bbox_inches = "tight")
    #plt.show()
    plt.clf()
    plt.cla()
    plt.close()


def complex_plots(df_10k: pd.DataFrame,
                 df_100k: pd.DataFrame,
                 df_1M: pd.DataFrame,
                 df_100M: pd.DataFrame) -> None:
    iter_list = [10000, 100000, 1000000, 100000000]
    df_list = [df_10k, df_100k, df_1M, df_100M]

    # count
    means_par = []
    means_seq = []
    for df in df_list:
        means_par.append(np.mean(df["count_par"]))
        means_seq.append(np.mean(df["count_seq"]))
    strings = get_strings("complex_count")
    complex_plot(strings, means_par, means_seq, iter_list)
    
    # upper
    means_par = []
    means_seq = []
    for df in df_list:
        means_par.append(np.mean(df["upper_par"]))
        means_seq.append(np.mean(df["upper_seq"]))
    strings = get_strings("complex_up")
    complex_plot(strings, means_par, means_seq, iter_list)

    # lower
    means_par = []
    means_seq = []
    for df in df_list:
        means_par.append(np.mean(df["lower_par"]))
        means_seq.append(np.mean(df["lower_seq"]))
    strings = get_strings("complex_low")
    complex_plot(strings, means_par, means_seq, iter_list)

def write_tab_line(f,
                   iterations :int,
                   data_par: pd.Series,
                   data_seq: pd.Series) -> None:
        mean_par = np.mean(data_par)
        mean_seq = np.mean(data_seq)
        std_par = np.std(data_par)
        std_seq = np.std(data_seq)
        f.write(f"{iterations} & {mean_par:.2f} & {std_par:.2f} & {mean_seq:.2f} & {std_seq:.2f} \\\\\n")


def write_tab_lines(f,
                    df_10k, df_100k, df_1M, df_100M,
                    string_par: str, string_seq: str) -> None:
    write_tab_line(f, 10000, df_10k[string_par], df_10k[string_seq])
    write_tab_line(f, 100000, df_100k[string_par], df_100k[string_seq])
    write_tab_line(f, 1000000, df_1M[string_par], df_1M[string_seq])
    write_tab_line(f, 100000000, df_100M[string_par], df_100M[string_seq])


def create_tabulars(df_10k, df_100k, df_1M, df_100M):
    if not os.path.isdir("../report/tabulars"):
        os.mkdir("../report/tabulars")

    # count
    with open("../report/tabulars/count_tab.txt","w") as f:
        write_tab_lines(f, df_10k, df_100k, df_1M, df_100M, "count_par", "count_seq")

    # upper
    with open("../report/tabulars/upper_tab.txt","w") as f:
        write_tab_lines(f, df_10k, df_100k, df_1M, df_100M, "upper_par", "upper_seq")

    # count
    with open("../report/tabulars/lower_tab.txt","w") as f:
        write_tab_lines(f, df_10k, df_100k, df_1M, df_100M, "lower_par", "lower_seq")


def main():
    df_10k = pd.read_csv("./data/string_times_10000.csv")
    df_100k = pd.read_csv("./data/string_times_100000.csv")
    df_1M = pd.read_csv("./data/string_times_1000000.csv")
    df_100M = pd.read_csv("./data/string_times_100000000.csv")
    
    create_tabulars(df_10k, df_100k, df_1M, df_100M)

    if not os.path.isdir("../report/images"):
        os.mkdir("../report/images")

    complex_plots(df_10k, df_100k, df_1M, df_100M)

    comparison_plots(df_10k, 10000)
    comparison_plots(df_100k, 100000)
    comparison_plots(df_1M, 1000000)
    comparison_plots(df_100M, 100000000)

   

if __name__ == "__main__":
    main()
