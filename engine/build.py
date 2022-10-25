#!/usr/bin/env python3
import platform,os
OS=platform.system()

if OS=='Windows':
    #Build script for engine

    #Get a list of all the .cpp files.
    cppFilenames=''
    for (root,dirs,files) in os.walk(os.getcwd()):
        for file in files:
            if file.endswith('.cpp'):
                cppFilenames+=' '+root+'/'+file

    #print("Files:",cppFilenames)

    assembly='engine'
    compilerFlags='-g -shared -Wvarargs -Wall -Werror'
    #-Wall -Werror
    includeFlags='-Isrc -I%s/Include'%os.environ.get('VULKAN_SDK')
    linkerFlags='-luser32 -lvulkan-1 -L%s/Lib'%os.environ.get('VULKAN_SDK')
    defines='-D_DEBUG -DYEXPORT -D_CRT_SECURE_NO_WARNINGS'

    print("Building %s..."%assembly)
    os.system('g++ %s %s -o ../bin/%s.dll %s %s %s'%(cppFilenames,compilerFlags,assembly,defines,includeFlags,linkerFlags))
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
    
    assembly="engine"
    compilerFlags="-g -shared -fPIC"
    # -fms-extensions
    # -Wall -Werror
    includeFlags="-Isrc -I%s/include"%os.environ.get("VULKAN_SDK")
    linkerFlags="-lvulkan -lxcb -lX11 -lX11-xcb -lxkbcommon -L%s/lib -L/usr/X11R6/lib"%os.environ.get("VULKAN_SDK")
    defines="-D_DEBUG -DYEXPORT"

    print("Building %s..."%assembly)
    os.system('g++ %s %s -o ../bin/lib%s.so %s %s %s'%(cppFilenames,compilerFlags,assembly,defines,includeFlags,linkerFlags))
