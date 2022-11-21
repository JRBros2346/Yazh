#!/usr/bin/env python3
import os,sys,pathlib
from pathlib import Path
os.chdir(Path(__file__).parent)
#Build Everything...

print("Building everything...")

ERRORLEVEL=os.system('python {}'.format(pathlib.Path('.','engine','build.py')))
if ERRORLEVEL:
    sys.exit(ERRORLEVEL)

ERRORLEVEL=os.system('python {}'.format(pathlib.Path('.','testbed','build.py')))
if ERRORLEVEL:
    sys.exit(ERRORLEVEL)

print("All assemblies built successfully.")
