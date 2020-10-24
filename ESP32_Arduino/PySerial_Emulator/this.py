# The code for changing pages was derived from: http://stackoverflow.com/questions/7546050/switch-between-two-frames-in-tkinter
# License: http://creativecommons.org/licenses/by-sa/3.0/   

import matplotlib
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk
from matplotlib.figure import Figure
import matplotlib.animation as animation
from matplotlib import style
from scipy.signal import medfilt
from scipy.signal import find_peaks

import sys

import tkinter as tk
from tkinter import ttk
from numpy import trapz


LARGE_FONT= ("Verdana", 12)
style.use("ggplot")
current = 0 
average_power = 0 
times = 0.0002
total_energy = 0.0002
base_line = 0 
net_energy = 0 
max_power =0
def onclick(event):
    global current
    if(current==0):
        T.delete("1.0", "end")
        T.insert(tk.END,str(int(event.xdata)))
        current=1;
    else:
        T1.delete("1.0", "end")
        T1.insert(tk.END,str(int(event.xdata)))
        current=0;
def res():
    global current
    current = 0
    T.delete("1.0", "end")
    T.insert(tk.END,"0")
    T1.delete("1.0", "end")
    T1.insert(tk.END,"0")
def time_bound():
    global current
    current=0
    try:
        time_wind= float(ex_time_wind.get("1.0",tk.END))
        start_time = int(T.get("1.0",tk.END))
        T1.delete("1.0", "end")
        T1.insert(tk.END,int(time_wind*(1/0.2))+start_time-1)
    except:
        pass

f = Figure(figsize=(12,4), dpi=100)
a = f.add_subplot(111)

app = tk.Tk()
app.geometry("1000x1000")
log_title = tk.Text(app, height=0, width=30)
def logger():
    log_file= open("log.csv","a")
    global max_power,average_power, total_energy, base_line, net_energy, log_title
    str_val  = str(log_title.get("1.0",tk.END))
    log_file.write(str_val[:-1]+", "+str(max_power)+ ", "+ str(average_power)+ ", "+str(total_energy)+", "+str(base_line)+", "+str(net_energy)+", "+str(times*1000)+"\n")
    log_file.close()
T = tk.Text(app, height=0, width=30)
T1 = tk.Text(app, height=0, width=30)
T2 = tk.Text(app, height=0, width=30)
T3 = tk.Text(app, height=0, width=30)
T4 = tk.Text(app, height=0, width=30)
ex_time_wind = tk.Text(app, height=0, width=30)
t1 = tk.StringVar()
t2 = tk.StringVar()
t3 = tk.StringVar()
t4 = tk.StringVar()
t5 = tk.StringVar()
t6 = tk.StringVar()
l1=tk.Label(app, textvariable=t1, font=LARGE_FONT)
l2=tk.Label(app, textvariable=t2, font=LARGE_FONT)
l3=tk.Label(app, textvariable=t3, font=LARGE_FONT)
l4=tk.Label(app, textvariable=t4, font=LARGE_FONT)
l5=tk.Label(app, textvariable=t5, font=LARGE_FONT)
l6=tk.Label(app, textvariable=t6, font=LARGE_FONT)
switch_variable = tk.StringVar(value="off")
xList = []
yList = []
pullData = open(str(sys.argv[1]),"r").read()
dataList = pullData.split('\n')
dataList.pop(0)
for eachLine in dataList:
    if len(eachLine) > 1:
        x, y = eachLine.split(',')
        xList.append(float(x))
        yList.append(float(y)*1)
def animate(i):
    global current,average_power,times,total_energy,base_line,net_energy,max_power
    a.clear()
    try:
        x_low=int(T.get("1.0",tk.END))
        x_high=int(T1.get("1.0",tk.END))
        baseline_pow= float(T2.get("1.0",tk.END))
        med_filt=int(T3.get("1.0",tk.END))
        a.axvline(x=x_low,color="red")
        if(x_high ==0):
            lis = yList
            lis2 = [k+1 for k in range(len(lis))]
        else:
            lis = yList[x_low:x_high+1]
            lis2 = [k+1 for k in range(x_low,x_high+1)]
        if(med_filt !=0):
            lis= medfilt(lis, med_filt)
        # peaks = []
        # begin =0
        # arr= []
        # for ind in range(len(lis)):
    
        #     if (lis[ind]>862):
        #         if(begin ==0):
        #             arr.append(ind-3)
        #             begin = 1
        #     else:
        #         if(begin == 1):
        #             arr.append(ind)
        #             if(arr[1]-arr[0])> 100:
        #                 peaks.append(arr)
        #             begin = 0
        #             arr = []
        # peak_vals=[]
        # peak_x = []
        # for ele in peaks:
        #     for x in range(ele[0],ele[1]+1):
        #         peak_vals.append(lis[x])
        #         peak_x.append(lis2[x])
        #print peaks
        a.plot(lis2,lis,color="blue")
        # a.plot(peak_x,peak_vals,"x",color="green")
        average_power = sum(lis)/len(lis) 
        times = len(lis)*0.0002
        total_energy = trapz(lis,dx=0.0002)
        base_line = baseline_pow*times
        net_energy = total_energy- base_line
        max_power = max(lis)
        t1.set("average power :"+str(average_power)+" mW")
        t2.set("max power :"+str(max(lis))+" mW")
        t3.set("total energy :"+str(total_energy)+" mJ")
        t4.set("baseline energy :"+str(base_line)+" mJ")
        t5.set("net energy :"+str(net_energy)+ " mJ")
        t6.set("time :"+str(times*1000)+" ms")
    # try:
    #     pass
    except:
        print ("Error")
xval =0
yval = 0
xstep =180
ystep = 30
tk.Label(app, text="X lower", font=LARGE_FONT).place(x = xval, y=yval, anchor = tk.NW)
#grid(row = xval , column = yval)
xval+=xstep
T.place(x = xval, y=yval, anchor = tk.NW)
T.insert(tk.END,"0")
yval+=ystep
xval= 0
tk.Label(app, text="X Upper", font=LARGE_FONT).place(x = xval, y=yval, anchor = tk.NW)
xval+=xstep
T1.insert(tk.END,"0")
T1.place(x=xval,y=yval, anchor = tk.NW)
xval=0;
yval+=ystep
tk.Label(app, text="baseline power", font=LARGE_FONT).place(x=xval,y=yval, anchor = tk.NW)
xval+=xstep
T2.insert(tk.END,"0")
T2.place(x=xval,y=yval, anchor = tk.NW)
xval=0;
yval+=ystep;
tk.Label(app, text="median filter window", font=LARGE_FONT).place(x=xval,y=yval, anchor = tk.NW)
T3.insert(tk.END,"0")
xval+=xstep
T3.place(x=xval,y=yval, anchor = tk.NW)
xval=0
yval+=ystep;
tk.Label(app, text="Time window(ms)", font=LARGE_FONT).place(x=xval,y=yval, anchor = tk.NW)
ex_time_wind.insert(tk.END,"0")
xval+=xstep
ex_time_wind.place(x=xval,y=yval, anchor = tk.NW)
xval=0
yval+=ystep;
tk.Label(app, text="Log Title:", font=LARGE_FONT).place(x=xval,y=yval, anchor = tk.NW)
log_title.insert(tk.END,"0")
xval+=xstep
log_title.place(x=xval,y=yval, anchor = tk.NW)
yval+=ystep;
xval = 0;
tk.Button(text ="reset", command = res).place(x=xval,y=yval, anchor = tk.NW)
xval+=xstep
tk.Button(text ="Apply window", command = time_bound).place(x=xval,y=yval, anchor = tk.NW)
xval+=xstep
tk.Button(text ="log_data", command = logger).place(x=xval,y=yval, anchor = tk.NW)
yval =0;
xval=4*xstep;
l1.place(x=xval,y=yval, anchor = tk.NW)
xval=4*xstep;
yval+=ystep;
l2.place(x=xval,y=yval, anchor = tk.NW)
xval=4*xstep;
yval+=ystep;
l3.place(x=xval,y=yval, anchor = tk.NW)
xval=4*xstep;
yval+=ystep;
l4.place(x=xval,y=yval, anchor = tk.NW)
xval=4*xstep;
yval+=ystep;
l5.place(x=xval,y=yval, anchor = tk.NW)
xval=4*xstep;
yval+=ystep;
l6.place(x=xval,y=yval, anchor = tk.NW)
xval=0;
yval+=ystep;
yval+=ystep;
canvas = FigureCanvasTkAgg(f, app)
canvas.mpl_connect('button_press_event', onclick)
canvas.draw()
canvas.get_tk_widget().pack()
toolbar = NavigationToolbar2Tk(canvas,app )
toolbar.update()
canvas._tkcanvas.place(x=xval,y=yval,relx = -0.1, anchor = tk.NW)
ani = animation.FuncAnimation(f, animate, interval=1000)
app.mainloop();
