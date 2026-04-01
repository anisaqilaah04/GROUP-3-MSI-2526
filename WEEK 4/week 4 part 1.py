import serial
import time
from collections import deque
import numpy as np

SERIAL_PORT = 'COM11'
BAUD_RATE = 9600

history_x = deque(maxlen=40)
history_y = deque(maxlen=40)

def is_circular_motion(x_data, y_data):
    if len(x_data) < 10:
        return False
    #step 1: mean
    mean_x = np.mean(x_data)
    mean_y = np.mean(y_data)

    #step 2: variance
    var_x = np.var(x_data)
    var_y = np.var(y_data)
    if var_x < 0.5 or var_y < 0.5:
        return False

    #step 3 : Check Symmetry
    std_x = np.std(x_data)
    std_y = np.std(y_data)
    ratio =  std_x/std_y if std_y != 0 else 0
    if not (0.6 < ratio < 1.4):
        return False

    #step 4 and 5: check rotation
    cx = [x - mean_x for x in x_data]
    cy = [y - mean_y for y in y_data]

    cw_turns = 0
    ccw_turns = 0

    for i in range(len(cx) - 1):
        cross_product = (cx[i] * cy[i+1] - (cy[i] * cx[i+1]))

        if cross_product > 0:
            cw_turns += 1
        elif cross_product < 0:
            ccw_turns += 1

    total_turns = cw_turns + ccw_turns
    if total_turns == 0:
        return False

    max_consistency = max(cw_turns, ccw_turns) / total_turns

    return max_consistency > 0.70



def main():
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2) #wait for arduino to reset
    print("System ready. Move the MPU6050 in a circle to toggle the LED.. ")

    led_is_on = False

    try:
        while True:
            raw = ser.readline().decode(errors='ignore').strip()
            if raw:
                parts = raw.split(',')

                if len(parts) >= 3:
                    try:
                        ax = int(parts[0])
                        ay = int(parts[1])

                        history_x.append(ax)
                        history_y.append(ay)

                        if len(history_x) == 40:
                            if is_circular_motion(history_x, history_y):

                                led_is_on = not led_is_on

                                if led_is_on:
                                    print("Circle Detected! Toggling LED: ON")
                                    ser.write(b'O')
                                else:
                                    print("Circle Detected! Toggling LED: OFF")
                                    ser.write(b'F')

                                history_x.clear()
                                history_y.clear()

                    except ValueError:
                        pass

    except KeyboardInterrupt:
        print("\nProgram terminated by user")
    finally:
        ser.write(b'F')
        ser.close()
        print("Serial connection closed.")

if __name__ == "__main__":
    main()
