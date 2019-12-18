import csv
import matplotlib.pyplot as plt
import numpy as np

with open('data/12:41:09.CSV', 'rb') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    reader = list(reader)
    header = reader[0]
    reader.pop(0) 

    reader = [list(x) for x in zip(*reader)]

#    print len(reader[2])
    
    TimeStamp = [float(i) for i in reader[1]]
    Latitude = [float(i) for i in reader[2]]
    Longitude = [float(i) for i in reader[3]]
#    WindDirection = [float(i) for i in reader[4]]
#    WindSpeed = [float(i) for i in reader[5]]
    RudderAngle = [float(i) for i in reader[6]]
    SailAngle = [float(i) for i in reader[7]]
    GPSCourse = [float(i) for i in reader[8]]
    GPSSpeed = [float(i) for i in reader[9]]
    Yaw = [float(i) for i in reader[10]]
    Pitch = [float(i) for i in reader[11]]
    Roll = [float(i) for i in reader[12]]
    Magnetometer = [float(i) for i in reader[13]]

    for i in range(len(Latitude)):
        plt.plot(Latitude[i], Longitude[i])
#    plt.plot(Latitude,Longitude)
#    plt.plot(TimeStamp, RudderAngle)
#    plt.plot(TimeStamp, SailAngle)
#    plt.plot(TimeStamp, GPSCourse)
#    plt.plot(TimeStamp, GPSSpeed)
#    plt.plot(TimeStamp, Yaw, TimeStamp, Roll, TimeStamp, Pitch)
    plt.show()
