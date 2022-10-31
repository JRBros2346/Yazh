#!/usr/bin/env python3
import os,sys,traceback
os.chdir(os.path.split(os.path.abspath(__file__))[0])
#Build Everything...

print("Building everything...")

try:
    os.chdir('engine')
    ERRORLEVEL=os.system('python build.py')
    if ERRORLEVEL:
        sys.exit(f'\33[91mengine Error(terminal):\33[31m {ERRORLEVEL} \33[m')
    os.chdir('..')
except:
    err_type,err_value,err_tb=sys.exc_info()
    sys.exit(f"""\33[91mengine Error(python):
\33[32m{'''
'''.join(traceback.format_tb(err_tb))}

\33[31m{err_type.__name__}: \33[36m{err_value}
\33[m""")

try:
    os.chdir('testbed')
    ERRORLEVEL=os.system('python build.py')
    if ERRORLEVEL:
        sys.exit(f'\33[91mtestbed Error(terminal):\033[31m {ERRORLEVEL} \033[m')
    os.chdir('..')
except:
    err_type,err_value,err_tb=sys.exc_info()
    sys.exit(f"""\33[91mtestbed Error(python):
\33[32m{'''
'''.join(traceback.format_tb(err_tb))}

\33[31m{err_type.__name__}: \33[36m{err_value}
\33[m""")

print("All assemblies built successfully.")
