import sys
import argparse
import subprocess
import shutil
import os
import glob
import time

import xml.etree.ElementTree as ET

# Version 2.0.0
# Published under MIT license. Copyright (c) 2020 sunfl0w


def main():
    build(sys.argv)


def build(argv):
    print("Starting CPPBuildAid")
    startTime = time.time_ns()

    # Parsing command line arguments
    argumentParser = argparse.ArgumentParser()
    argumentParser.add_argument("-b", "--buildType")
    argumentParser.add_argument("-t", "--threads")
    argumentParser.add_argument("-i", "--installLocal", action='store_true')
    argumentParser.add_argument("-s", "--useSwig", action='store_true')
    argumentParser.add_argument("-l", "--swigLanguage")

    args = argumentParser.parse_args()

    typeOfBuild = "debug"
    if(args.buildType == "release"):
        typeOfBuild = "release"

    threads = 1
    if(args.threads is not None and int(args.threads) >= 1):
        threads = args.threads

    useSwig = args.useSwig
    swigLanguage = args.swigLanguage

    if(useSwig):
        generateSwigInterface(swigLanguage);

    # Read project description
    projectDescription = readProjectDescriptionFile("projectDescription.xml")

    # Generating include list and source list files
    print("Generating include list")
    includeSearch = listFilesOfTypeInDirectories(projectDescription[0], (".h", ".hpp"))
    print("Saving include list")
    saveStringsInFile(includeSearch[1], "includelist.cmake")

    print("Generating source list")
    sourceSearch = listFilesOfTypeInDirectories(projectDescription[1], (".c", ".cpp"))
    print("Saving source list")
    saveStringsInFile(sourceSearch[0], "sourcelist.cmake")

    # Count lines of code
    headerCodeLines = countLinesOfCode(includeSearch[0], projectDescription[2])
    sourceCodeLines = countLinesOfCode(sourceSearch[0], projectDescription[2])

    print("Headers: Total lines of code: " + str(headerCodeLines))
    print("Sources: Total lines of code: " + str(sourceCodeLines))
    print("Project: Total lines of code: " + str(headerCodeLines + sourceCodeLines))

    # Running cmake with specified arguments
    print("Running cmake")
    print("Using {} threads to build in {}-mode".format(threads, typeOfBuild))

    resultSetDirs = subprocess.call(["cmake", "-S", ".", "-B", "build"])
    if resultSetDirs:
        print("Setting cmake directories failed with errors")
        exit(1)

    resultBuildType = subprocess.call(["cmake", "-DCMAKE_BUILD_TYPE={}".format(typeOfBuild.capitalize()), "."], cwd="build")
    if resultBuildType:
        print("Build type setting failed with errors")
        exit(1)

    resultBuild = subprocess.call(["cmake", "--build", ".", "-j", str(threads)], cwd="build")
    if resultBuild:
        print("Build failed with errors")
        exit(1)

    if args.installLocal:
        resultInstall = subprocess.call(["cmake", "--install", "."], cwd="build")
        if resultInstall:
            print("Installing build software failed with errors")
            exit(1)

    buildTime = round((time.time_ns() - startTime) / pow(10, 9), 2)
    print("Build completed successfully in {}s".format(buildTime))


def readProjectDescriptionFile(path):
    with open(path, "r") as xmlFile:
        templateDoc = ET.parse(xmlFile)
        root = templateDoc.getroot()

        includeDirs = []
        includeDirsNode = root.find("IncludeDirs")
        if includeDirsNode:
            includeDirs = readDirectoryPathsFromNode(includeDirsNode)

        sourceDirs = []
        sourceDirsNode = root.find("SourceDirs")
        if sourceDirsNode:
            sourceDirs = readDirectoryPathsFromNode(sourceDirsNode)

        notCountedDirs = []
        notCountedDirsNode = root.find("NotCountedDirs")
        if notCountedDirsNode:
            notCountedDirs = readDirectoryPathsFromNode(notCountedDirsNode)

        return (includeDirs, sourceDirs, notCountedDirs)


def readDirectoryPathsFromNode(node):
    directories = []
    for directoryNode in node.iter("Dir"):
        directories.append(directoryNode.attrib.get("path"))
    return directories


def listFilesOfTypeInDirectories(directoryPathsToSearch, fileExtensions):
    filePaths = []
    populatedDirectoryPaths = []

    for directoryPath in directoryPathsToSearch:
        directoryPath = os.path.join(os.getcwd(), directoryPath)
        if directoryPath:
            for dirpath, dirs, files in os.walk(directoryPath):
                relativeDirectoryPath = os.path.relpath(dirpath, os.getcwd())
                if relativeDirectoryPath not in populatedDirectoryPaths:
                    populatedDirectoryPaths.append(relativeDirectoryPath)
                for filename in files:
                    filePath = os.path.relpath(os.path.join(dirpath, filename), os.getcwd())
                    if isFileOfType(filename, fileExtensions) and filePath not in filePaths:
                        filePaths.append(filePath)

    return (filePaths, populatedDirectoryPaths)


def isFileOfType(filename, fileExtensions):
    for fileExtension in fileExtensions:
        if(str(filename).endswith(fileExtension)):
            return True
    return False


def saveStringsInFile(strings, filename):
    file = open(filename, "w")
    for entry in strings:
        file.write(entry + "\n")
    file.close()


def countLinesOfCode(filePaths, ignoredDirectories):
    linesOfCode = 0
    for filePath in filePaths:
        if not isFileChildOfDirectories(filePath, ignoredDirectories):
            with open(filePath, "r") as file:
                linesOfCode += len(file.readlines())
    return linesOfCode


def isFileChildOfDirectories(filePath, directories):
    absFilePath = os.path.abspath(filePath)
    for directory in directories:
        absDirectoryPath = os.path.abspath(directory)
        commonPath = os.path.commonpath([absDirectoryPath, absFilePath])
        if absDirectoryPath == commonPath:
            return True
    return False


def generateSwigInterface(swigLanguage):
    if(swigLanguage == "python"):
        subprocess.call(["swig", "-c++", "-wall", "-doxygen", "-python", "-py3", "-o", "swigInterface.cpp", "-oh", "swigInterface.hpp", "-outdir", "swigOut", "swig.i"])
    else:
        print("Swig language not supportet")
        exit(1)
    
    os.replace("swigInterface.hpp", "include/swig/swigInterface.hpp")
    os.replace("swigInterface.cpp", "src/swig/swigInterface.cpp")


if __name__ == "__main__":
    main()