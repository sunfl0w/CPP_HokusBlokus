# Version 1.2.0

import sys
import argparse
import subprocess
import shutil
import os
import glob
import time

import xml.etree.ElementTree as ET


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

    args = argumentParser.parse_args()

    typeOfBuild = "debug"
    if(args.buildType == "release"):
        typeOfBuild = "release"

    threads = 1
    if(args.threads is not None and int(args.threads) >= 1):
        threads = args.threads

    # Read project description
    projectDescription = readProjectDescriptionFile("projectDescription.xml")

    # Generating include list and source list files
    if not os.path.exists("cmakeListings"):
        os.mkdir("cmakeListings")

    print("Generating include lists")
    includeSearch = listFilesOfTypeInDirectories(projectDescription[0], (".h", ".hpp"))
    print("Saving include lists")
    saveStringsInFile(includeSearch[0], "cmakeListings/includeFilesAbs.cmake")
    saveStringsInFile(includeSearch[1], "cmakeListings/includeFilesRel.cmake")
    saveStringsInFile(includeSearch[2], "cmakeListings/includeDirsAbs.cmake")
    saveStringsInFile(includeSearch[3], "cmakeListings/includeDirsRel.cmake")

    print("Generating source lists")
    sourceSearch = listFilesOfTypeInDirectories(projectDescription[1], (".c", ".cpp"))
    print("Saving source lists")
    saveStringsInFile(sourceSearch[0], "cmakeListings/sourceFilesAbs.cmake")
    saveStringsInFile(sourceSearch[1], "cmakeListings/sourceFilesRel.cmake")
    saveStringsInFile(sourceSearch[2], "cmakeListings/sourceDirsAbs.cmake")
    saveStringsInFile(sourceSearch[3], "cmakeListings/sourceDirsRel.cmake")

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
    filePathsAbs = []
    filePathsRel = []
    populatedDirectoryPathsAbs = []
    populatedDirectoryPathsRel = []

    for directoryPath in directoryPathsToSearch:
        directoryPath = os.path.join(os.getcwd(), directoryPath)
        if directoryPath:
            for dirpath, dirs, files in os.walk(directoryPath):
                relativeDirectoryPath = os.path.relpath(dirpath, os.getcwd())
                if relativeDirectoryPath not in populatedDirectoryPathsAbs:
                    populatedDirectoryPathsAbs.append(os.path.abspath(relativeDirectoryPath))
                    populatedDirectoryPathsRel.append(relativeDirectoryPath)
                for filename in files:
                    filePath = os.path.relpath(os.path.join(dirpath, filename), os.getcwd())
                    if isFileOfType(filename, fileExtensions) and filePath not in filePathsAbs:
                        filePathsAbs.append(os.path.abspath(filePath))
                    if isFileOfType(filename, fileExtensions) and filePath not in filePathsRel:
                        filePathsRel.append(filePath)

    return (filePathsAbs, filePathsRel, populatedDirectoryPathsAbs, populatedDirectoryPathsRel)


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


if __name__ == "__main__":
    main()