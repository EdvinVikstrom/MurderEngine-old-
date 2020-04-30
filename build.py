from distutils.core import setup, Extension
from os import listdir
from os.path import isfile, isdir, join
import glob

SOURCES = []

def find_files(dir):
    files = glob.glob(dir)
    for file in files:
        print("file: " + file)
        if os.path.isdir(file):
            find_files(file + '/')
        if os.path.isfile(file):
            SOURCES.append(file)

find_files("/home/edvinskomputa/Dokument/OnePunchEngine/")
print(SOURCES)

#module = Extension('MurderEngine', sources = SOURCES)

#setup(name = 'packagewhat',
    #version = '1.0',
    #description = 'testar grejer',
    #ext_modules = [module])
