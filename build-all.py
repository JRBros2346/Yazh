#!/usr/bin/env python3
import os,sys,traceback
os.chdir(os.path.split(os.path.abspath(__file__))[0])
#Build Everything...

print("Building everything...")

try:
    os.chdir('engine')
    ERRORLEVEL=os.system('python build.py')
    if ERRORLEVEL:
        sys.exit(f'engine Error(terminal): \33[91m{ERRORLEVEL} \33[0m')
    os.chdir('..')
except:
    err_type,err_value,err_tb=sys.exc_info()
    sys.exit(f"""engine Error(python):
\33[92m{'''
'''.join(traceback.format_tb(err_tb))}

\33[93m{str(err_type)[7:-1]}: \33[91m{err_value}
\33[0m""")

try:
    os.chdir('testbed')
    ERRORLEVEL=os.system('python build.py')
    if ERRORLEVEL:
        sys.exit(f'testbed Error(terminal): \033[91m{ERRORLEVEL} \033[0m')
    os.chdir('..')
except:
    err_type,err_value,err_tb=sys.exc_info()
    sys.exit(f"""testbed Error(python):
\33[92m{'''
'''.join(traceback.format_tb(err_tb))}

\33[93m{str(err_type)[7:-1]}: \33[91m{err_value}
\33[0m""")

print("All assemblies built successfully.")
