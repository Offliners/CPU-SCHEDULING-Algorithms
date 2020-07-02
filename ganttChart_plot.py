import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np
import os

SCHD_TYPES = ['FCFS', 'RR', 'SJF', 'PSJF'] 
TOTAL_COUNT = 5
W_FACTOR = 10
H_FACTOR = 10
H_OFFSET = 10
H_DIST = 20
GREENS = cm.get_cmap('Greens', 8)
REDS = cm.get_cmap('Blues', 8)

def createFile(path):
    if not os.path.isdir(path):
        os.makedirs(path)

def processSort(record):
    record.sort(key=lambda x: x[0])
    return record

for schd in SCHD_TYPES:
    for n in range(1, TOTAL_COUNT+1):

        fig, ax = plt.subplots()

        data_file = 'data/' + schd + '_' + str(n) + '.txt'
        calc_file = 'result/calc_' + schd + '_' + str(n) + '.txt'
        schd_file = 'result/schd_' + schd + '_' + str(n) + '.txt'

        y_ticklabels = []
        name_dict, indx_dict = dict(), dict()
        data_lines = open(data_file, 'r').read().splitlines()

        for i in range(2, len(data_lines)):
            name = data_lines[i].split()[0]
            y_ticklabels.append(name)
            name_dict[name] = i-2
            indx_dict[i-2] = name

        schd_times = []
        for i in range(2, len(data_lines)):
            data = data_lines[i].split()
            schd_times.append([data[0], float(data[2])/1000])

        num = len(y_ticklabels)

        calc_times = []
        calc_lines = open(calc_file, 'r').read().splitlines()

        for i in range(len(calc_lines)):
            data = calc_lines[i].split()
            if data:
                calc_times.append([int(data[1][1]), float(data[2]), float(data[3])])

        schd_times = []
        schd_lines = open(schd_file, 'r').read().splitlines()

        for i in range(len(schd_lines)):
            data = schd_lines[i].split()
            if data:
                schd_times.append([int(data[0][1]), float(data[1])/1000, float(data[2])/1000])
        
        for i in range(len(schd_times)):
            if calc_times[i][0] == 1:    
                bias = calc_times[i][1]
                
        calc_times_lines = []
        schd_times_lines = []

        bias = calc_times[0][1]

        for i in range(len(schd_times)):
            calc_times_lines.append([calc_times[i][0], calc_times[i][1] - bias, calc_times[i][2] - bias]) 
            schd_times_lines.append([schd_times[i][0], schd_times[i][1], schd_times[i][2]])

        calc_times_lines = processSort(calc_times_lines)
        schd_times_lines = processSort(schd_times_lines)

        x_ticks, y_ticks = [], []
        for i in range(num):
            ax.broken_barh([(schd_times_lines[i][1], schd_times_lines[i][2] - schd_times_lines[i][1])],
                           (H_OFFSET + 2*i*H_FACTOR, H_FACTOR), facecolors=GREENS((i+1)/num))
            y_ticks.append(H_OFFSET + 2*i*H_FACTOR + H_FACTOR / 2)
            ax.broken_barh([(calc_times_lines[i][1], calc_times_lines[i][2] - calc_times_lines[i][1])],
                           ((2*num-1+2*i) * H_FACTOR + H_OFFSET + H_DIST, H_FACTOR),
                           facecolors=REDS((i+1)/num))
            x_ticks.append(calc_times_lines[i][1])
            x_ticks.append(calc_times_lines[i][2])
            x_ticks.append(schd_times_lines[i][1])
            x_ticks.append(schd_times_lines[i][2])
            y_ticks.append((2*num-1+2*i) * H_FACTOR + H_OFFSET + H_DIST + H_FACTOR/ 2)

        x_ticks = np.unique(sorted(x_ticks))
        y_ticks = sorted(y_ticks)
        x_ticklabels = ['{:.1f}'.format(x_tick) for x_tick in x_ticks]

        ax.set_title(schd + '_' + str(n))
        ax.set_xlabel('secs since start')
        ax.xaxis.set_label_coords(0.5, -0.12)
        ax.set_ylabel('process names (Ideal Case v.s. Real Case)')

        ax.set_xticks(x_ticks)
        x_labels = ax.set_xticklabels(x_ticklabels, rotation=0)
        for i, x_label in enumerate(x_labels):
            x_label.set_y(x_label.get_position()[1] - (i % 3) * 0.032)
        ax.set_yticks(y_ticks)
        ax.set_yticklabels(y_ticklabels * 2)
        ax.grid(True)

        plt.tight_layout()
        createFile('images/' + schd + '/')
        plt.savefig('images/' + schd+ '/' + schd + '_' + str(n) + '.png')