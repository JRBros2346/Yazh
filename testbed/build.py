#!/usr/bin/env python3
import platform,os
OS=platform.system()

if OS=='Windows':
    #Build script for testbed

    #Get a list of all the .cpp files.
    cppFilenames=''
    for (root,dirs,files) in os.walk(os.getcwd()):
        for file in files:
            if file.endswith('.cpp'):
                cppFilenames+=' '+root+'/'+file

    #print("Files:",cppFilenames)

    assembly='testbed'
    compilerFlags='-g'
    #-Wall -Werror
    includeFlags='-Isrc -I../engine/src/'
    linkerFlags='-L../bin/ -lengine'
    defines='-D_DEBUG -DYIMPORT'

    print("Building %s..."%assembly)
    os.system('g++ %s %s -o ../bin/%s.exe %s %s %s'%(cppFilenames,compilerFlags,assembly,defines,includeFlags,linkerFlags))
elif OS=='Linux':
    # Build script for engine

    os.makedirs('../bin',exist_ok=True)

    # Get a list of all the .cpp files.
    cppFilenames=''
    for (root,dirs,files) in os.walk(os.getcwd()):
        for file in files:
            if file.endswith('.cpp'):
                cppFilenames+=' '+root+'/'+file

    # print("Files:",cppFilenames)
    
    assembly="testbed"
    compilerFlags="-g -fPIC"
    # -fms-extensions
    # -Wall -Werror
    includeFlags="-Isrc -I../engine/src/"
    linkerFlags="-L../bin/ -lengine -Wl,-rpath=,%s/../bin"%os.environ.get('ORIGIN')
    defines="-D_DEBUG -DYIMPORT"

    print("Building %s..."%assembly)
    print('g++ %s %s -o ../bin/%s %s %s %s'%(cppFilenames,compilerFlags,assembly,defines,includeFlags,linkerFlags))
    os.system('g++ %s %s -o ../bin/%s %s %s %s'%(cppFilenames,compilerFlags,assembly,defines,includeFlags,linkerFlags))

