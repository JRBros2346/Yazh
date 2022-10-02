#Build script for engine
import os

#Get a list of all the .cpp files.
cFilenames=''
for (root,dirs,files) in os.walk(os.getcwd()):
    for file in files:
        if file.endswith('.cpp'):
            cFilenames+=' '+root+file

#print("Files:",cfilenames)

assembly='engine'
compilerFlags='-g -shared -Wvarargs -Wall -Werror'
#'-Wall -Werror'
includeFlags='-Isrc -I%s/Include'%os.environ.get('VULKAN_SDK')
linkerFlags='-luser32 -lvulkan-1 -L%s/Lib'%os.environ.get('VULKAN_SDK')
defines=''

print("Building %s..."%assembly)
os.system('g++ %s %s -o ../bin/%s.dll %s %s %s'%(cFilenames,compilerFlags,assembly,defines,includeFlags,linkerFlags))
