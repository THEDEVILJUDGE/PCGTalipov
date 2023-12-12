import os
import timeit
import matplotlib.pyplot as plt

def plot_point(ax, x, y):
    ax.plot(x, y, 'ko')
    ax.plot(-x, y, 'ko')
    ax.plot(x, -y, 'ko')
    ax.plot(-x, -y, 'ko')

    ax.plot(y, x, 'ko')
    ax.plot(y, -x, 'ko')
    ax.plot(-y, x, 'ko')
    ax.plot(-y, -x, 'ko')

def draw_line(ax, x1, y1, x2, y2, algorithm_name):
    dx = x2 - x1
    dy = y2 - y1
    slope = abs(dy / dx)

    error = 0.0
    y = y1
    x = x1

    while x < x2:
        plot_point(ax, x, y)
        x = x + 1
        error = error + slope
        if error >= 0.5:
            y = y + 1
            error -= 1.0

    ax.set_title(algorithm_name)

def draw_circle(ax, r, algorithm_name):
    x = 0
    y = r
    d = 3 - 2 * r

    while y >= x:
        plot_point(ax, x, y)
        x = x + 1
        if d > 0:
            y = y - 1
            d = d + 4 * (x - y) + 10
        else:
            d = d + 4 * x + 6

    ax.set_title(algorithm_name)

def main():
    # Линия пошаговым алгоритмом
    f1, ax1 = plt.subplots(figsize=(8, 8))
    ax1.set_xlim([0, 50])
    ax1.set_ylim([0, 50])

    x1 = 1.0
    y1 = 1.0
    x2 = 20.0
    y2 = 40.0

    time_line_dda = timeit.timeit(lambda: draw_line(ax1, x1, y1, x2, y2, 'DDA Line'), number=1)

    # Линия алгоритмом ЦДА
    f2, ax2 = plt.subplots(figsize=(8, 8))
    ax2.set_xlim([0, 50])
    ax2.set_ylim([0, 50])

    x1 = 0.0
    y1 = 0.0
    x2 = 20.0
    y2 = 40.0

    time_line_dda = timeit.timeit(lambda: draw_line(ax2, x1, y1, x2, y2, 'Bresenham Line'), number=1)

    # Линия алгоритмом Брезенхема
    f3, ax3 = plt.subplots(figsize=(8, 8))
    ax3.set_xlim([0, 50])
    ax3.set_ylim([0, 50])

    x1 = 0.0
    y1 = 0.0
    x2 = 20.0
    y2 = 40.0

    time_line_bresenham = timeit.timeit(lambda: draw_line(ax3, x1, y1, x2, y2, 'Bresenham Line'), number=1)

    # Окружность алгоритмом Брезенхема
    f4, ax4 = plt.subplots(figsize=(8, 8))
    ax4.set_xlim([-50, 50])
    ax4.set_ylim([-50, 50])

    r = 20
    time_circle_bresenham = timeit.timeit(lambda: draw_circle(ax4, r, 'Bresenham Circle'), number=1)

    # Отображение графиков
    plt.show()

    print('Time spent (DDA Line): {:.6f} seconds'.format(time_line_dda))
    print('Time spent (Bresenham Line): {:.6f} seconds'.format(time_line_bresenham))
    print('Time spent (Bresenham Circle): {:.6f} seconds'.format(time_circle_bresenham))

if __name__ == "__main__":
    main()
    input("Press Enter to exit...")
