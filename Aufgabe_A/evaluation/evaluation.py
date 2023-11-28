#!/bin/python3
"""
Script to read the data for the string manipulation measurement
and plot the results.
"""

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def get_strings(key: str) -> dict:
    return {
            "count": {"title": f"Processing time to count chars in a string with ",
                "ylabel":"time in ns",
                "xlabel":"iterations",
                },
            "up": {"title": f"Processing time to uppercase chars in a string with ",
                "ylabel":"time in ns",
                "xlabel":"iterations",
                },
            "low": {"title": f"Processing time to lowercase chars in a string with ",
                "ylabel":"time in ns",
                "xlabel":"iterations",
                }
            }[key]


def comparison_plot(df: pd.DataFrame, iterations: int):
    # count
    strings = get_strings("count")
    series_par = df["count_par"]
    series_seq = df["count_seq"]
    mean_par = np.mean(series_par)
    mean_seq = np.mean(series_seq)
    print(mean_par, mean_seq)

    fig, ax = plt.subplots()
    plt.title(strings["title"]+f"{iterations} chars.")
    plt.ylabel(strings["ylabel"])
    plt.xlabel(strings["xlabel"])
    plt.hlines(mean_par, series_par.index.values[0], series_par.index.values[-1], color="blue", label="parallel mean")
    plt.hlines(mean_seq, series_seq.index.values[0], series_seq.index.values[-1], color="green", label="parallel mean")
    plt.scatter(series_par.index.values, series_par.values, color="blue", label="parallel")
    plt.scatter(series_seq.index.values, series_seq.values, color="green", label="sequential")
    plt.legend()
    plt.show()
    plt.clf()
    plt.cla()
    plt.close()

    # uppercase
    strings = get_strings("up")
    series_par = df["upper_par"]
    series_seq = df["upper_seq"]
    mean_par = np.mean(series_par)
    mean_seq = np.mean(series_seq)
    print(mean_par, mean_seq)

    fig, ax = plt.subplots()
    plt.title(strings["title"]+f"{iterations} chars.")
    plt.ylabel(strings["ylabel"])
    plt.xlabel(strings["xlabel"])
    plt.hlines(mean_par, series_par.index.values[0], series_par.index.values[-1], color="blue", label="parallel mean")
    plt.hlines(mean_seq, series_seq.index.values[0], series_seq.index.values[-1], color="green", label="parallel mean")
    plt.scatter(series_par.index.values, series_par.values, color="blue", label="parallel")
    plt.scatter(series_seq.index.values, series_seq.values, color="green", label="sequential")
    plt.legend()
    plt.show()
    plt.clf()
    plt.cla()
    plt.close()

    # lower
    strings = get_strings("low")
    series_par = df["lower_par"]
    series_seq = df["lower_seq"]
    mean_par = np.mean(series_par)
    mean_seq = np.mean(series_seq)
    print(mean_par, mean_seq)

    fig, ax = plt.subplots()
    plt.title(strings["title"]+f"{iterations} chars.")
    plt.ylabel(strings["ylabel"])
    plt.xlabel(strings["xlabel"])
    plt.hlines(mean_par, series_par.index.values[0], series_par.index.values[-1], color="blue", label="parallel mean")
    plt.hlines(mean_seq, series_seq.index.values[0], series_seq.index.values[-1], color="green", label="parallel mean")
    plt.scatter(series_par.index.values, series_par.values, color="blue", label="parallel")
    plt.scatter(series_seq.index.values, series_seq.values, color="green", label="sequential")
    plt.legend()
    plt.show()
    plt.clf()
    plt.cla()
    plt.close()



def main():
    df_10k = pd.read_csv("./data/string_times_10000.csv")
    df_100k = pd.read_csv("./data/string_times_100000.csv")
    df_1M = pd.read_csv("./data/string_times_1000000.csv")
    df_100M = pd.read_csv("./data/string_times_100000000.csv")

    comparison_plot(df_10k, 10000)
    comparison_plot(df_100k, 100000)
    comparison_plot(df_1M, 1000000)
    comparison_plot(df_100M, 100000000)



if __name__ == "__main__":
    main()
