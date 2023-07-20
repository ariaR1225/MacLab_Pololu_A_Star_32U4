import machine
import time

file_name = "sensorReading.txt"

# Function to save data to a file
def save_data_to_file(file_name, data):
    try:
        # Open the file in write mode ("w")
        with open(file_name, "a") as file:
            # Write the data to the file
            file.write(data)
            print("Data saved successfully.")
    except Exception as e:
        print("Error saving data:", e)

# Call the function to save the data


# Configure the serial port
uart = machine.UART(2, 9600)  # UART port 2, baudrate 9600
ls = []
print("start")
State = True
while State:
    if uart.any():
        data1 = uart.read(1)  # Read one byte from the serial port
        #buf = data1.decode("utf-8")
        ls.append(ord(data1))
        if len(ls) >= 20:
            State = False
            for s in ls:
                saved = f"{s}\r\n"
                save_data_to_file(file_name, saved)
            print("ready to download sensorReading.txt")
    time.sleep(.1)
