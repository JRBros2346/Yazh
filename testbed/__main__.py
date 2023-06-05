#!/usr/bin/env python3
import platform,os,sys
from pathlib import Path
os.chdir(Path(__file__).parent)
operatingSystem=platform.system()

if operatingSystem=='Windows':
    #Build script for testbed

    #Get a list of all the .cpp files.
    cppFilenames=' '.join([str(file) for file in Path().rglob(r'*.cpp')])

    #print("Files:",cppFilenames)

    assembly='testbed'
    compilerFlags='-g -std=c++17'
    #-Wall -Werror
    includeFlags='-Isrc -I../engine/src/'
    linkerFlags='-L../bin/ -lengine'
    defines='-D_DEBUG -DYIMPORT'

    print(f"Building {assembly}...")
    ERRORLEVEL=os.system(f'g++ {cppFilenames} {compilerFlags} -o ../bin/{assembly}.exe {defines} {includeFlags} {linkerFlags}')
    if ERRORLEVEL:
        sys.exit(ERRORLEVEL)

elif operatingSystem=='Linux':
    # Build script for engine

    Path('../bin').mkdir(parents=True, exist_ok=True)

    # Get a list of all the .cpp files.
    cppFilenames=' '.join([str(file) for file in Path().rglob(r'*.cpp')])

    # print("Files:",cppFilenames)

    assembly="testbed"
    compilerFlags="-g -fPIC -std=c++17"
    # -fms-extensions
    # -Wall -Werror
    includeFlags="-Isrc -I../engine/src/"
    linkerFlags="-L../bin/ -lengine -Wl,-rpath,'$ORIGIN'"
    defines="-D_DEBUG -DYIMPORT"

    print(f"Building {assembly}...")
    print(f'g++ {cppFilenames} {compilerFlags} -o ../bin/{assembly} {defines} {includeFlags} {linkerFlags}')
    ERRORLEVEL=os.system(f'g++ {cppFilenames} {compilerFlags} -o ../bin/{assembly} {defines} {includeFlags} {linkerFlags}')
    if ERRORLEVEL:
        sys.exit(ERRORLEVEL)
