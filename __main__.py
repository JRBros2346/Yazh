#!/usr/bin/env python3
import os,sys
from pathlib import Path
os.chdir(Path(__file__).parent)
#Build Everything...

print("Building everything...")

ERRORLEVEL=os.system('python engine')
if ERRORLEVEL:
    sys.exit(ERRORLEVEL)

ERRORLEVEL=os.system('python testbed')
if ERRORLEVEL:
    sys.exit(ERRORLEVEL)

print("All assemblies built successfully.")
