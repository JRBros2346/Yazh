#!/usr/bin/env python3
import os,sys,traceback
#Build Everything...

print("Building everything...")

try:
    os.chdir('engine')
    ERRORLEVEL=os.system('python build.py')
    if ERRORLEVEL:
        sys.exit(f'engine Error(terminal): \33[91m{ERRORLEVEL} \33[0m')
    os.chdir('..')
except:
    etype,evalue,etb=sys.exc_info()
    sys.exit(f"""engine Error(python):
\33[92m{'''
'''.join(traceback.format_tb(etb))}

\33[93m{str(etype)[7:-1]}: \33[91m{evalue}
\33[0m""")

try:
    os.chdir('testbed')
    ERRORLEVEL=os.system('python build.py')
    if ERRORLEVEL:
        sys.exit(f'testbed Error(terminal): \033[91m{ERRORLEVEL} \033[0m')
    os.chdir('..')
except:
    etype,evalue,etb=sys.exc_info()
    sys.exit(f"""testbed Error(python):
\33[92m{'''
'''.join(traceback.format_tb(etb))}

\33[93m{str(etype)[7:-1]}: \33[91m{evalue}
\33[0m""")

print("All assemblies built successfully.")
