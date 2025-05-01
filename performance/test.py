import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
from scipy.stats import linregress


def analyze_results():
    df = pd.read_csv("performance_results.csv")

    fib_df = df[df["operation"] == "fibonacci"]
    fact_df = df[df["operation"] == "factorial"]

    sns.set_theme(style="whitegrid")

    plt.figure(figsize=(14, 10))

    plt.subplot(2, 2, 1)
    plt.plot(fib_df["n"], fib_df["time"], "b-o")
    plt.title("Fibonacci Computation Time (Linear)")
    plt.xlabel("n")
    plt.ylabel("Time (seconds)")
    plt.grid(True)

    plt.subplot(2, 2, 2)
    plt.plot(fact_df["n"], fact_df["time"], "r-o")
    plt.title("Factorial Computation Time (Linear)")
    plt.xlabel("n")
    plt.ylabel("Time (seconds)")
    plt.grid(True)

    plt.subplot(2, 2, 3)
    plt.plot(fib_df["n"], fib_df["time"], "b-o")
    plt.xscale("log")
    plt.yscale("log")
    plt.title("Fibonacci Computation Time (Log-Log)")
    plt.xlabel("n (log scale)")
    plt.ylabel("Time (seconds, log scale)")
    plt.grid(True, which="both")

    plt.subplot(2, 2, 4)
    plt.plot(fact_df["n"], fact_df["time"], "r-o")
    plt.xscale("log")
    plt.yscale("log")
    plt.title("Factorial Computation Time (Log-Log)")
    plt.xlabel("n (log scale)")
    plt.ylabel("Time (seconds, log scale)")
    plt.grid(True, which="both")

    plt.tight_layout()
    plt.savefig("performance_plots.png")
    plt.show()

    print("\nFibonacci Performance Stats:")
    print(fib_df.describe())

    print("\nFactorial Performance Stats:")
    print(fact_df.describe())

    # ⬇️ Наклон log-log графиков
    fib_log_n = np.log(fib_df["n"])
    fib_log_t = np.log(fib_df["time"])
    fib_slope, _, _, _, _ = linregress(fib_log_n, fib_log_t)

    fact_log_n = np.log(fact_df["n"])
    fact_log_t = np.log(fact_df["time"])
    fact_slope, _, _, _, _ = linregress(fact_log_n, fact_log_t)

    print(f"\nEstimated Fibonacci Time Complexity: O(n^{fib_slope:.2f})")
    print(f"Estimated Factorial Time Complexity: O(n^{fact_slope:.2f})")


if __name__ == "__main__":
    analyze_results()
