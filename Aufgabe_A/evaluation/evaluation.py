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
                "filename":"../report/images/comp_upper_"
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
                    iterations: int,
                    series_par: pd.Series,
                    series_seq: pd.Series) -> None:
    mean_par = np.mean(series_par)
    mean_seq = np.mean(series_seq)
    print(mean_par, mean_seq)

    fig, ax = plt.subplots()
    plt.title(strings["title"]+f"{iterations} chars.", pad=20)
    plt.ylabel(strings["ylabel"])
    plt.xlabel(strings["xlabel"])
    plt.hlines(mean_par, series_par.index.values[0], series_par.index.values[-1], color=strings["color_par"], label="parallel mean")
    plt.hlines(mean_seq, series_seq.index.values[0], series_seq.index.values[-1], color=strings["color_seq"], label="parallel mean")
    plt.scatter(series_par.index.values, series_par.values, color=strings["color_par"], label="parallel", marker=strings["marker_par"])
    plt.scatter(series_seq.index.values, series_seq.values, color=strings["color_seq"], label="sequential", marker=strings["marker_seq"])
    plt.legend()
    plt.savefig(strings["filename"] + f"{iterations}.png", bbox_inches = "tight")
    #plt.show()
    plt.clf()
    plt.cla()
    plt.close()


def comparison_plots(df: pd.DataFrame, iterations: int):
    # count
    strings = get_strings("count")
    series_par = df["count_par"]
    series_seq = df["count_seq"]
    comparison_plot(strings, iterations, series_par, series_seq)

        # uppercase
    strings = get_strings("up")
    series_par = df["upper_par"]
    series_seq = df["upper_seq"]
    comparison_plot(strings, iterations, series_par, series_seq)

    # lower
    strings = get_strings("low")
    series_par = df["lower_par"]
    series_seq = df["lower_seq"]
    comparison_plot(strings, iterations, series_par, series_seq)


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



def main():
    df_10k = pd.read_csv("./data/string_times_10000.csv")
    df_100k = pd.read_csv("./data/string_times_100000.csv")
    df_1M = pd.read_csv("./data/string_times_1000000.csv")
    df_100M = pd.read_csv("./data/string_times_100000000.csv")

    if not os.path.isdir("../report/images"):
        os.mkdir("../report/images")

    complex_plots(df_10k, df_100k, df_1M, df_100M)

    comparison_plots(df_10k, 10000)
    comparison_plots(df_100k, 100000)
    comparison_plots(df_1M, 1000000)
    comparison_plots(df_100M, 100000000)



if __name__ == "__main__":
    main()
