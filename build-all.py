#!/usr/bin/env python3
import os,sys,traceback
#Build Everything...

print("Building everything...")

try:
    os.chdir('engine')
    ERRORLEVEL=os.system('python build.py')
    if ERRORLEVEL:
        sys.exit('engine Error(terminal):\033[91m"%s\033[0m'%ERRORLEVEL)
    os.chdir('..')
except:
    sys.exit("engine Error(python):\033[91m",traceback.format_exc(),"\033[0m",sep='\n')

try:
    os.chdir('testbed')
    ERRORLEVEL=os.system('python build.py')
    if ERRORLEVEL:
        sys.exit('testbed Error(terminal):\033[91m"%s\033[0m'%ERRORLEVEL)
    os.chdir('..')
except:
    sys.exit("testbed Error(python):\033[91m",traceback.format_exc(),"\033[0m",sep='\n')

print("All assemblies built successfully.")
