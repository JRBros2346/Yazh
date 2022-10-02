#Build script for testbed
import os

#Get a list of all the .cpp files.
cfilenames=''
for (root,dirs,files) in os.walk(os.getcwd()):
    for file in files:
        if file.endswith('.cpp'):
            cfilename+=' '+root+file

#print("Files:",cfilenames)

assembly='testbed'

print("Building %s..."%assembly)
