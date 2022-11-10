#!/usr/bin/env python3
import os,sys,pathlib
os.chdir(pathlib.Path(__file__).parent)
#Build Everything...

print("Building everything...")

ERRORLEVEL=os.system('python {}'.format(pathlib.Path(r'.\engine\build.py')))
if ERRORLEVEL:
    sys.exit(ERRORLEVEL)

ERRORLEVEL=os.system('python {}'.format(pathlib.Path(r'.\testbed\build.py')))
if ERRORLEVEL:
    sys.exit(ERRORLEVEL)

print("All assemblies built successfully.")
