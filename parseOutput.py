import csv
import sys
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter
import numpy as np

if 3 != len(sys.argv):
    print("Usage: python3 parseOutput.py [input file path] [output file path]")
else:
    fileOpen = 0
    fields = []

    wheel1Angles = []
    wheel1Timestamps = []

    wheel2Angles = []
    wheel2Timestamps = []

    wheel3Angles = []
    wheel3Timestamps = []

    wheel4Angles = []
    wheel4Timestamps = []
    with open(sys.argv[1]) as csvfile:
        fileOpen = 1
        csvreader = csv.reader(csvfile)
        fields = next(csvreader)
        for row in csvreader:
            wheelIndex = int(float(row[2]))
            if wheelIndex == 0:
                wheel1Angles.append(float(row[4]))
                wheel1Timestamps.append(float(row[0]))
            elif wheelIndex == 1:
                wheel2Angles.append(float(row[4]))
                wheel2Timestamps.append(float(row[0]))
            elif wheelIndex == 16:
                wheel3Angles.append(float(row[4]))
                wheel3Timestamps.append(float(row[0]))
            elif wheelIndex == 17:
                wheel4Angles.append(float(row[4]))
                wheel4Timestamps.append(float(row[0]))
    if 1 == fileOpen :
        fig,plots = plt.subplots(2,2)

        plots[0][0].plot(wheel1Timestamps, wheel1Angles)
        plots[0][0].set_title('Front Left Wheel Inner Angle')
        plots[0][0].set_xlabel('Time (s)')
        plots[0][0].set_ylabel('Angle (degrees)')

        plots[0][1].plot(wheel2Timestamps, wheel2Angles)
        plots[0][1].set_title('Front Right Wheel Inner Angle')
        plots[0][1].set_xlabel('Time (s)')
        plots[0][1].set_ylabel('Angle (degrees)')

        plots[1][0].plot(wheel3Timestamps, wheel3Angles)
        plots[1][0].set_title('Rear Left Wheel Inner Angle')
        plots[1][0].set_xlabel('Time (s)')
        plots[1][0].set_ylabel('Angle (degrees)')

        plots[1][1].plot(wheel4Timestamps, wheel4Angles)
        plots[1][1].set_title('Rear Right Wheel Inner Angle')
        plots[1][1].set_xlabel('Time (s)')
        plots[1][1].set_ylabel('Angle (degrees)')
        fig.tight_layout()
        fig.show()
        fig.savefig(sys.argv[2])
