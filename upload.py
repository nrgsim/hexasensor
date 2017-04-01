#!/usr/bin/env python
'''
upload.py

author: Ethan Lew
3/31/17

Executes a build sequence and uploads to arduino

./upload.py (optional)[BUILD|RESET|UPLOAD|CLEAN] (optional)-p NAME (optional) -v

TODO: Forward Errors, Add options

If no arguments, executes all

remove_build:   rm -rf build
build:          ./configure
reset_arduino:  setDTR
upload:         reset_arduino
                cd build
                make
                make upload
'''

import shutil
import subprocess
import os
import serial
import sys
import time

VERBOSE = False
OUT = open(os.devnull, 'w')
PORT = 'ttyACM0'

def reset_arduino(port = 'ttyACM0'):
    print(bcolors.OKGREEN + "Serial Resetting Arduino..."
      + bcolors.ENDC)
    arduino = serial.Serial('/dev/'+port,
                         baudrate=9600,
                         bytesize=serial.EIGHTBITS,
                         parity=serial.PARITY_NONE,
                         stopbits=serial.STOPBITS_ONE,
                         timeout=1,
                         xonxoff=0,
                         rtscts=0
                         )

    arduino.setDTR(False)
    time.sleep(1)
    arduino.flushInput()
    arduino.setDTR(True)

def remove_build():
    print(bcolors.WARNING + "Removing Previous Build..."
      + bcolors.ENDC)
    if(os.path.isdir("build")):
        shutil.rmtree("build")

def upload():
    print(bcolors.OKGREEN + "Starting Upload Sequence..."
      + bcolors.ENDC)
    if(not (os.path.isdir("build"))):
        build()

    reset_arduino(PORT);

    cwd = os.getcwd()

    make_process = subprocess.Popen(["make"], stdout=OUT, cwd=cwd+"/build")
    output, error = make_process.communicate()

    upload_process = subprocess.Popen(["make", "upload"], stdout=OUT, cwd=cwd+"/build")
    output, error = upload_process.communicate()

def build():
    print(bcolors.OKGREEN + "Starting Build..."
      + bcolors.ENDC)
    if(VERBOSE):
        FNULL = subprocess.PIPE
    else:
        FNULL = open(os.devnull, 'w')
    configure_process = subprocess.Popen(["./configure"], stdout=OUT, stderr=OUT)
    output, error = configure_process.communicate()

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

if __name__ == "__main__":
    if(VERBOSE):
        OUT = subprocess.PIPE
    else:
        OUT = open(os.devnull, 'w')

    if('-p' in sys.argv):
        idx = sys.argv.index('-p')
        if(len(sys.argv) == idx):
            print(bcolors.FAIL + "Could not find device name!"
              + bcolors.ENDC)
        else:
            PORT = sys.argv[idx+1]

    if('-v' in sys.argv):
        VERBOSE = True
    if('CLEAN' in sys.argv):
        remove_build()
    elif ('BUILD' in sys.argv):
        build()
    elif ('RESET' in sys.argv):
        reset_arduino(PORT)
    elif('UPLOAD' in sys.argv):
        upload()
    else:
        remove_build()
        build()
        upload()
