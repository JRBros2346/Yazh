#!/usr/bin/env python3
import platform,os
operatingSystem=platform.system()

if operatingSystem=='Windows':
    #Build script for testbed

    #Get a list of all the .cpp files.
    cppFilenames=''
    for (root,dirs,files) in os.walk(os.getcwd()):
        for file in files:
            if file.endswith('.cpp'):
                cppFilenames+=' '+os.path.join(root,file)

    #print("Files:",cppFilenames)

    assembly='testbed'
    compilerFlags='-g'
    #-Wall -Werror
    includeFlags='-Isrc -I../engine/src/'
    linkerFlags='-L../bin/ -lengine'
    defines='-D_DEBUG -DYIMPORT'

    print(f"Building {assembly}...")
    os.system(f'g++ {cppFilenames} {compilerFlags} -o ../bin/{assembly}.exe {defines} {includeFlags} {linkerFlags}')
elif operatingSystem=='Linux':
    # Build script for engine

    os.makedirs('../bin',exist_ok=True)

    # Get a list of all the .cpp files.
    cppFilenames=''
    for (root,dirs,files) in os.walk(os.getcwd()):
        for file in files:
            if file.endswith('.cpp'):
                cppFilenames+=' '+os.path.join(root,file)

    # print("Files:",cppFilenames)

    assembly="testbed"
    compilerFlags="-g -fPIC"
    # -fms-extensions
    # -Wall -Werror
    includeFlags="-Isrc -I../engine/src/"
    linkerFlags="-L../bin/ -lengine -Wl,-rpath,'$ORIGIN'"
    defines="-D_DEBUG -DYIMPORT"

    print(f"Building {assembly}...")
    print(f'g++ {cppFilenames} {compilerFlags} -o ../bin/{assembly} {defines} {includeFlags} {linkerFlags}')
    os.system(f'g++ {cppFilenames} {compilerFlags} -o ../bin/{assembly} {defines} {includeFlags} {linkerFlags}')

