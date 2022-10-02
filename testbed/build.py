#Build script for testbed
import os

#Get a list of all the .cpp files.
cppFilenames=''
for (root,dirs,files) in os.walk(os.getcwd()):
    for file in files:
        if file.endswith('.cpp'):
            cppFilenames+=' '+root+file

#print("Files:",cppFilenames)

assembly='testbed'
compilerFlags='-g'
#'-Wall -Werror'
includeFlags='-Isrc -I../engine/src/'
linkerFlags='-L../bin/ -lengine.lib'
defines='-D_DEBUG -DKIMPORT'

print("Building %s..."%assembly)
os.system('g++ %s %s -o ../bin/%s.exe %s %s %s'%(cppFilenames,compilerFlags,assembly,defines,includeFlags,linkerFlags))
