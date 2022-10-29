#!/usr/bin/env python3
import platform,os
operatingSystem=platform.system()

if operatingSystem=='Windows':
    #Build script for engine

    #Get a list of all the .cpp files.
    cppFilenames=''
    for (root,dirs,files) in os.walk(os.getcwd()):
        for file in files:
            if file.endswith('.cpp'):
                cppFilenames+=' '+os.path.join(root,file)

    #print("Files:",cppFilenames)

    assembly='engine'
    compilerFlags='-g -shared -Wvarargs -Wall -Werror'
    #-Wall -Werror
    includeFlags=f"-Isrc -I{os.getenv('VULKAN_SDK')}/Include"
    linkerFlags=f"-luser32 -lvulkan-1 -L{os.getenv('VULKAN_SDK')}/Lib"
    defines='-D_DEBUG -DYEXPORT -D_CRT_SECURE_NO_WARNINGS'

    print(f"Building {assembly}...")
    os.system(f'g++ {cppFilenames} {compilerFlags} -o ../bin/{assembly}.dll {defines} {includeFlags} {linkerFlags}')
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

    assembly="engine"
    compilerFlags="-g -shared -fPIC"
    # -fms-extensions
    # -Wall -Werror
    includeFlags=f"-Isrc -I{os.getenv('VULKAN_SDK')}/include"
    linkerFlags=f"-lvulkan -lxcb -lX11 -lX11-xcb -lxkbcommon -L{os.getenv('VULKAN_SDK')}/lib -L/usr/X11R6/lib"
    defines="-D_DEBUG -DYEXPORT"

    print(f"Building {assembly}...")
    os.system(f'g++ {cppFilenames} {compilerFlags} -o ../bin/lib{assembly}.so {defines} {includeFlags} {linkerFlags}')
