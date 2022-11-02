#!/usr/bin/env python3
import os,sys
os.chdir(os.path.split(os.path.abspath(__file__))[0])
#Build Everything...

print("Building everything...")

ERRORLEVEL=os.system('python ./engine/build.py')
if ERRORLEVEL:
    sys.exit(ERRORLEVEL)

ERRORLEVEL=os.system('python ./testbed/build.py')
if ERRORLEVEL:
    sys.exit(ERRORLEVEL)

print("All assemblies built successfully.")
