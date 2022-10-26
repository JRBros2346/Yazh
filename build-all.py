#!/usr/bin/env python3
import os,sys,traceback
#Build Everything...

print("Building everything...")

try:
    os.chdir('engine')
    ERRORLEVEL=os.system('python build.py')
    if ERRORLEVEL:
        sys.exit('engine Error(terminal): \033[91m%s \033[0m'%ERRORLEVEL)
    os.chdir('..')
except:
    exc=sys.exc_info()
    sys.exit("engine Error(python): \033[91m \ntype: %s \nvalue: %s \ntraceback: %s \033[0m"%(str(exc[0]),str(exc[1]),str(exc[2])))

try:
    os.chdir('testbed')
    ERRORLEVEL=os.system('python build.py')
    if ERRORLEVEL:
        sys.exit('testbed Error(terminal): \033[91m%s \033[0m'%ERRORLEVEL)
    os.chdir('..')
except:
    exc=sys.exc_info()
    sys.exit("testbed Error(python): \033[91m \ntype: %s \nvalue: %s \ntraceback: %s\033[0m"%(str(exc[0]),str(exc[1]),str(exc[2])))

print("All assemblies built successfully.")
