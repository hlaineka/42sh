#!/usr/bin/python

import subprocess
from subprocess import *
import os
import time
subprocess.call(['make', 're'])
command_shell42 = ['./42sh', 'test']
command_bash = ['bash']
if os.path.isfile("./testoutput.txt"):
    os.remove("./testoutput.txt")
output = open("./testoutput.txt", "a")
if os.path.isfile("./shelloutput.txt"):
    os.remove("./shelloutput.txt")
bashoutput = open("./shelloutput.txt", "a")
inputfile = open("./testinput.txt", "r")
shell42 = subprocess.Popen(command_shell42, stdin=subprocess.PIPE, stdout=output, stderr=output)
bash = subprocess.Popen(command_bash, stdin=subprocess.PIPE, stdout=bashoutput, stderr=bashoutput)
while True:
    input = inputfile.readline()
    if not input:
        break
    shell42.stdin.write(input.encode(encoding='ascii'))
    bash.stdin.write(input.encode(encoding='ascii'))
