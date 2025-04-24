import serial
import time
from pynput import keyboard

PORT = "COM4" 

def open_serial():
    try:
        return serial.Serial(port=PORT, baudrate=9600, timeout=1)
    except serial.SerialException as e:
        print(f"Error opening serial: {e}")
        return None

bluetooth = open_serial()
if bluetooth is None:
    exit()

pressed_keys = set()

def on_press(key):
    try:
        if key.char.lower() in ('w', 'a', 's', 'd'):
            pressed_keys.add(key.char.lower())
        elif key.char.lower() == 'q':
            print("Exiting...")
            bluetooth.close()
            return False
    except AttributeError:
        pass

def on_release(key):
    try:
        pressed_keys.discard(key.char.lower())
    except AttributeError:
        pass

print("Hold W, A, S, or D to send. Press 'Q' to quit.")

listener = keyboard.Listener(on_press=on_press, on_release=on_release)
listener.start()

try:
    while True:
        for key in pressed_keys:
            bluetooth.write(key.encode())
            print(f"Sent: {key}")
        time.sleep(0.1)
except KeyboardInterrupt:
    bluetooth.close()
