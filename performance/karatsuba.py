import matplotlib.pyplot as plt
import numpy as np

thresholds = list(range(4, 308, 4))
times = [
    74821,
    73798,
    72404,
    72773,
    74324,
    73656,
    72923,
    73198,
    76075,
    71464,
    71807,
    70907,
    70846,
    70843,
    70800,
    70598,
    70763,
    70928,
    70779,
    70676,
    70922,
    71052,
    70798,
    70830,
    70914,
    70748,
    70875,
    70806,
    70788,
    70840,
    70844,
    70696,
    70920,
    70731,
    70737,
    70791,
    71027,
    70990,
    70930,
    70881,
    70923,
    70987,
    70764,
    70855,
    70753,
    70922,
    71112,
    70942,
    70799,
    70744,
    70776,
    71043,
    70777,
    70899,
    70731,
    70976,
    70918,
    70855,
    70896,
    70826,
    70787,
    70940,
    70807,
    70731,
    70833,
    70824,
    70862,
    70940,
    71002,
    70758,
    70741,
    70836,
    70895,
    70763,
    70612,
    70801,
]

plt.figure(figsize=(12, 6))
plt.plot(thresholds, times, marker="o", linestyle="-", color="b", markersize=4)
plt.title("Karatsuba Algorithm Threshold Performance", fontsize=14)
plt.xlabel("Threshold Value", fontsize=12)
plt.ylabel("Execution Time (ms)", fontsize=12)
plt.grid(True, linestyle="--", alpha=0.7)

# Находим минимум
min_time = min(times)
min_index = times.index(min_time)
min_threshold = thresholds[min_index]

plt.scatter(
    min_threshold,
    min_time,
    color="red",
    s=100,
    label=f"Minimum: {min_time} ms at threshold {min_threshold}",
)

# Строим среднюю линию для точек после минимума
post_min_thresholds = thresholds[min_index:]
post_min_times = times[min_index:]

# Линейная регрессия для точек после минимума
coefficients = np.polyfit(post_min_thresholds, post_min_times, 1)
trend_line = np.poly1d(coefficients)
plt.plot(
    post_min_thresholds,
    trend_line(post_min_thresholds),
    color="green",
    linestyle="--",
    label=f"Trend after min: y={coefficients[0]:.2f}x+{coefficients[1]:.2f}",
)

plt.legend()

plt.text(
    min_threshold,
    min_time + 1000,
    f"Optimal threshold: {min_threshold}",
    horizontalalignment="center",
    fontsize=10,
    bbox=dict(facecolor="white", alpha=0.8),
)

plt.xticks(range(0, 309, 32))
plt.yticks(range(70000, 77000, 1000))

plt.tight_layout()
plt.savefig("karatsuba_thresholds_with_trend.png", dpi=300, bbox_inches="tight")
plt.show()
