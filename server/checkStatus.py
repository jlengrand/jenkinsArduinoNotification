#!/usr/bin/python

import serial
import sys
import time
from jenkinsapi import jenkins
from jenkinsapi import build

port = "/dev/ttyACM0"
baudrate = 9600
#url = 'http://localhost:8080'
url = 'http://192.168.1.20:8080'
project = 'test_1'

FAIL = "f"
BUILD = "b"
SUCCESS = "s"
frequency = 2

lastState = ''
j = jenkins.Jenkins(url)

if len(sys.argv) == 3:
        output = serial.Serial(sys.argv[1], sys.argv[2])
else:
        print "# please specify a port and a number"
        print "# using hard coded defaults " + port + " " + str(baudrate)
        output = serial.Serial(port, baudrate)

# the arduino need some time to warm up
time.sleep(4)

def check():
        try:
                job = j.get_job(project)

                print job
                # builds which are queued or running are not listed in the jenkins
                # dictionary, so at this time the job.__build__ related calls fails by
                # reference error
                #
                # so i take the lastBuild array an create an own Build instance

                current = job._data['lastBuild']
                currentBuild = build.Build(current['url'], current['number'], job)

                if currentBuild.is_running():
                        light(BUILD)
                        return

                if currentBuild.is_good():
                        light(SUCCESS)
                        return

                light(FAIL)
        except:
                print "Error"
                print sys.exc_info()[1]
                light(FAIL)

def light(state):
        global lastState

        if state != lastState:
                print lastState, state
                output.write(state)
                lastState = state

while True:
        check()
        time.sleep(frequency)
