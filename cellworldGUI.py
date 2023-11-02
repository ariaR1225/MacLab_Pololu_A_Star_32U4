import tkinter as tk
from tkinter import ttk

root = tk.Tk()
root.title("Cell World GUI")
# root.geometry("1000x200")

# Initial Val

def door_update():
    pass

def save_calibration():
    pass

def door_test():
    test_door = test_door_combobox.get()
    dt_time = int(dt_time_entry.get())
    dt_rep = int(dt_rep_entry.get())
    print(f"test door: {test_door}, time: {dt_time}, rep: {dt_rep}")

def feeder_test():
    test_feeder = test_feeder_combobox.get()
    ft_time = int(ft_time_entry.get())
    ft_rep = int(ft_rep_entry.get())
    ft_wait = int(ft_wait_entry.get())
    print(f"test door: {test_feeder}, time: {ft_time}, rep: {ft_rep}, wait: {ft_wait}")

def start_exp():
    pass


# Creating Tkinter BooleanVar variables
door0status = tk.BooleanVar()
door1status = tk.BooleanVar()
door2status = tk.BooleanVar()
door3status = tk.BooleanVar()


# Open and close door
door0check = ttk.Checkbutton(root, text="door 0", variable=door0status, onvalue=True, offvalue=False)
door0check.grid(row=0, column=1, padx=10, pady=5)
door1check = ttk.Checkbutton(root, text="door 1", variable=door1status, onvalue=True, offvalue=False)
door1check.grid(row=0, column=2, padx=10, pady=5)
door2check = ttk.Checkbutton(root, text="door 2", variable=door2status, onvalue=True, offvalue=False)
door2check.grid(row=0, column=3, padx=10, pady=5)
door3check = ttk.Checkbutton(root, text="door 3", variable=door3status, onvalue=True, offvalue=False)
door3check.grid(row=0, column=4, padx=10, pady=5)
door_update_button = ttk.Button(root,text="Open Door",command=door_update)
door_update_button.grid(row=0,column=0,padx=10,pady=10)


# Door test
door_test_button = ttk.Button(root,text="Test Door",command=door_test)
door_test_button.grid(row=1,column=0,padx=10,pady=10)
test_door_combobox = ttk.Combobox(root,width=8,values=["door 0","door 1","door 2","door 3"])
test_door_combobox.grid(row=1,column=1,padx=10,pady=5)
test_door_combobox.current(0)

dt_time_label = ttk.Label(root,text="Time")
dt_time_label.grid(row=1,column=2,padx=10,pady=5)
dt_time_entry = ttk.Entry(root,textvariable=tk.IntVar,width=5)
dt_time_entry.grid(row=1,column=3,padx=10,pady=5)

dt_rep_label = ttk.Label(root,text="Rep")
dt_rep_label.grid(row=1,column=4,padx=10,pady=5)
dt_rep_entry = ttk.Entry(root,textvariable=tk.IntVar,width=5)
dt_rep_entry.grid(row=1,column=5,padx=10,pady=5)


# Feeder test
feeder_test_button = ttk.Button(root,text="Test Feeder",command=feeder_test)
feeder_test_button.grid(row=4,column=0,padx=10,pady=10)
test_feeder_combobox = ttk.Combobox(root,width=8,values=["feeder 1","feeder 2"])
test_feeder_combobox.grid(row=4,column=1,padx=10,pady=5)
test_feeder_combobox.current(0)

ft_time_label = ttk.Label(root,text="Time")
ft_time_label.grid(row=4,column=2,padx=10,pady=5)
ft_time_entry = ttk.Entry(root,textvariable=tk.IntVar,width=5)
ft_time_entry.grid(row=4,column=3,padx=10,pady=5)

ft_rep_label = ttk.Label(root,text="Rep")
ft_rep_label.grid(row=4,column=4,padx=10,pady=5)
ft_rep_entry = ttk.Entry(root,textvariable=tk.IntVar,width=5)
ft_rep_entry.grid(row=4,column=5,padx=10,pady=5)

ft_wait_label = ttk.Label(root,text="Wait")
ft_wait_label.grid(row=4,column=6,padx=10,pady=5)
ft_wait_entry = ttk.Entry(root,textvariable=tk.IntVar,width=5)
ft_wait_entry.grid(row=4,column=7,padx=10,pady=5)


# Start Experiment
exp_start_button = ttk.Button(root,text="Start Experiment",command=start_exp)
exp_start_button.grid(row=8,column=2,padx=10,pady=10)
prefix_label = ttk.Label(root,text="Prefix")
prefix_label.grid(row=7,column=0,padx=10,pady=5)
prefix_entry = ttk.Entry(root,textvariable=tk.StringVar,width=10)
prefix_entry.grid(row=7,column=1,padx=10,pady=5)
suffix_label = ttk.Label(root,text="Suffix")
suffix_label.grid(row=7,column=2,padx=10,pady=5)
suffix_combobox = ttk.Combobox(root,width=3,values=["RT"])
suffix_combobox.grid(row=7,column=3,padx=10,pady=5)
suffix_combobox.current(0)

# Save calibration
# save_button = ttk.Button(root,text="Save Calibration",command=save_calibration)
# save_button.grid(row=8,column=2,padx=10,pady=10)

# Help

# Reconnect


# Upload experiment

# Status

# Give reward

# Enable feeder

# feeder reached

root.mainloop()

