BONUS SIBLING - README

EXPLANATION ARE VERY SIMILAR TO BASIC SPA README.TXT

Building Autotester is exactly the same as the Basic SPA version,
The only difference is this version is able to handle Sibling Queries.






CS3202 Sem1-2014, Team members details can be found in contact.txt.

Team 05:
- A0099214B	Adinda Ayu Savitri	
- A0098139R	Hisyam Nursaid Indrakesuma
- A0103494J	Lacie Fan Yuxin	
- A0101286N	Ipsita Mohapatra	
- A0080415N	Steven Kester Yuwono	
- A0099768Y	Yohanes Lim	

Code05 Folder contains our Visual Studio solution (source files).
Tests05 Folder contains our test files (only for sibling)


--------------- SOURCE ------------------

The source files are located inside each module's folder.

For example the source files for DesignExtractor will be in "..\Team05\Code05\DesignExtractor\"
together with the solution files (.vcxproj) for each of the module.

-----------------------------------------



---------------- AUTOTESTER --------------------

Open "Static-Code-Analyzer.sln" in Visual C++ Express 2010 (this is the version we use)
Set the build box on top to be in "Release" mode, not "Debug".

We have set the dependencies such that building AutoTester directly is possible.
However if it somehow unable to build,
Please build in the following order:
- PKB
- CodeParser
- DesignExtractor
- QueryProcessor
- AutoTester

After building the AutoTester, please navigate to the Release folder. The AutoTester.exe will be inside.
i.e. "..\Team05\Bonus\Code05\Release\AutoTester.exe"
and find AutoTester.exe in the directory

Please move the AutoTester.exe to the desired directory with the source file and test cases.
Then launch command prompt in the directory and run AutoTester as defined in the AutoTester guide.
i.e. AutoTester.exe source1.txt query1.txt result1.xml

------------------------------------------------



----------------- SYSTEM TESTING ---------------------

To execute full system testing, please follow the steps to build Autotester above.
After Autotester is built and AutoTester.exe is created,

Please copy AutoTester.exe and paste it in the "Tests05" folder
i.e. "..\Team05\Bonus\Tests05\"

Once Autotester.exe is copied/pasted in the respective directory,
The System testing can simply be done by running/double-clicking "auto.bat"
It is a batch file to run all the test cases with the correct sources and query files in that particular directory.

The result of the testing will be produced in the same directory with standardized naming convention:
The .xml files will have "Result" prefix.
The stdout (cout) fill have "Stdout" prefix.

---------------------------------------------------------