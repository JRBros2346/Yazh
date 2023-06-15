#!/usr/bin/env python3
import platform,os,sys
from pathlib import Path
os.chdir(Path(__file__).parent)
operatingSystem=platform.system()
#Build script for testbed

Path('../../bin').mkdir(parents=True, exist_ok=True)

#Get a list of all the .cpp files.
cppFilenames=' '.join([str(file) for file in Path().rglob(r'*.cpp')])

#print("Files:",cppFilenames)

assembly='testbed'
compilerFlags = { 'Windows': '-g -std=c++17',                            #-Wall -Werror
                  'Linux'  : '-g -fPIC -std=c++17' }[operatingSystem]    # -fms-extensions    # -Wall -Werror
includeFlags='-Isrc -I../engine/src/'
linkerFlags={
    'Windows': '-L../../bin/ -lengine',
    'Linux'  : "-L../../bin/ -lengine -lxcb -lX11 -lX11-xcb -lxkbcommon -Wl,-rpath,'$ORIGIN'" }[operatingSystem]
defines='-D_DEBUG -DYIMPORT'
outputFilename = { 'Windows': f'{assembly}.exe', 'Linux': f'{assembly}' }[operatingSystem]

print(f"Building {assembly}...")
ERRORLEVEL=os.system(f'g++ {cppFilenames} {compilerFlags} -o ../../bin/{outputFilename} {defines} {includeFlags} {linkerFlags}')
if ERRORLEVEL:
    sys.exit(ERRORLEVEL)
