#!/usr/bin/python

import serial
import sys
import time
from jenkinsapi import jenkins
from jenkinsapi import build

port = "/dev/ttyACM0"
baudrate = 9600
url = 'http://127.0.0.1:8090'
#url = 'http://192.168.7.64:8080'


FAIL = "f"
BUILD = "b"
SUCCESS = "s"
frequency = 2

project_1 = "test_1"
project_2 = "test_2"

# each project has an identifier, to be sent using the serial link as well
id_1 = "1"
id_2 = "2"

lastState_1= ''
lastState_2= ''

j = jenkins.Jenkins(url)

if len(sys.argv) == 3:
        output = serial.Serial(sys.argv[1], sys.argv[2])
else:
        print "# please specify a port and a number"
        print "# using hard coded defaults " + port + " " + str(baudrate)
        output = serial.Serial(port, baudrate)

# the arduino need some time to warm up
time.sleep(4)

def checkAll():
        check(project_1, id_1)
	check(project_2, id_2)

def check(project, id):
        try:
                job = j.get_job(project)

                # builds which are queued or running are not listed in the jenkins
                # dictionary, so at this time the job.__build__ related calls fails by
                # reference error
                #
                # so i take the lastBuild array an create an own Build instance

                current = job._data['lastBuild']
                currentBuild = build.Build(current['url'], current['number'], job)

                if currentBuild.is_running():
                        light(BUILD, id)
                elif currentBuild.is_good():
                        light(SUCCESS, id)
                else:
                        light(FAIL, id)
        except:
                print "Server Side Error"
                print sys.exc_info()[1]
                #light(FAIL)
                #TODO: Another led later for server side errors

def light(state, id):
	global lastState_1
	global lastState_2

	if id == "1":
		lastState = lastState_1
	else:
		lastState = lastState_2

        msg = id
        if state != lastState:
                msg += state
		print msg
                output.write(msg)

		if id == "1":
			lastState_1 = state
		else:
			lastState_2 = state

	#print msg, lastState_1, lastState_2

while True:
        checkAll()
        time.sleep(frequency)
