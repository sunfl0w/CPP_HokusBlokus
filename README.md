### Readme of CPP_HokusBlokus

#### Licenses
Information about the used license my be found in the LICENSE file.

#### Acknowledgements and license notices of third party software
Acknowledgements and license notices may be found in the Acknowledgements.md.

#### Short description of CPP_HokusBlokus
CPP_HokusBlokus is a implementation of the game Blokus for the Software-Challange Germany 2020/2021. The software will make extensive use of bitsets and bit operators.

#### Setup
Before using this implementation the script '''PieceSetGenerator.py''' must be run. This will create several binary images in a generatedResources directory for later use. The software will need these files later for initialization so they should be always shipped alongside client. The client can easily be compiled with the help of CPPBuildAid.py with these commands: '''python CPPBuildAid.py -b release''' or '''python CPPBuildAid.py -b debug'''. Compile options can be changed in the CMakeLists.txt.

#### Suggestions and cooperation
I will gladly take any bugreports or feedback on the software. If you want to help improve the code, then feel free to do so.