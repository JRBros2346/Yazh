#!/usr/bin/env python3
import platform,os,sys
from pathlib import Path
os.chdir(Path(__file__).parent)
operatingSystem=platform.system()
#Build script for engine

Path('../../bin').mkdir(parents=True, exist_ok=True)

#Get a list of all the .cpp files.
cppFilenames=' '.join([str(file) for file in Path().rglob(r'*.cpp')])

#print("Files:",cppFilenames)

assembly='engine'
compilerFlags={
    'Windows':    "-g -shared -Wvarargs -Wall -Werror -std=c++20",    #-Wall -Werror
    'Linux'  :    "-g -shared -fPIC -std=c++20" }[operatingSystem]    # -fms-extensions    # -Wall -Werror
includeFlags={
    'Windows':    f"-Isrc -I{os.getenv('VULKAN_SDK')}/Include",
    'Linux'  :    f"-Isrc -I{os.getenv('VULKAN_SDK')}/include" }[operatingSystem]
linkerFlags={
    'Windows':    f"-luser32 -lvulkan-1 -L{os.getenv('VULKAN_SDK')}/Lib",
    'Linux'  :    f"-lvulkan -lxcb -lX11 -lX11-xcb -lxkbcommon -L{os.getenv('VULKAN_SDK')}/lib -L/usr/X11R6/lib" }[operatingSystem]
defines={
    'Windows':    "-D_DEBUG -DYEXPORT -D_CRT_SECURE_NO_WARNINGS",
    'Linux'  :    "-D_DEBUG -DYEXPORT" }[operatingSystem]
outputFilename = { 'Windows': f'{assembly}.dll', 'Linux': f'lib{assembly}.so' }[operatingSystem]

print(f"Building {assembly}...")
ERRORLEVEL=os.system(f'g++ {cppFilenames} {compilerFlags} -o ../../bin/{outputFilename} {defines} {includeFlags} {linkerFlags}')
if ERRORLEVEL:
    sys.exit(ERRORLEVEL)
