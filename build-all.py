#!/usr/bin/env python3
import os,sys,traceback
#Build Everything...

print("Building everything...")

try:
    os.chdir('engine')
    ERRORLEVEL=os.system('build.py')
    if ERRORLEVEL:
        sys.exit('Error:%s'%ERRORLEVEL)
    os.chdir('..')
except:
    sys.exit(traceback.format_exc())

try:
    os.chdir('testbed')
    ERRORLEVEL=os.system('build.py')
    if ERRORLEVEL:
        sys.exit('Error:%s'%ERRORLEVEL)
    os.chdir('..')
except:
    sys.exit(traceback.format_exc())

print("All assemblies built successfully.")
