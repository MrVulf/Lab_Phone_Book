Project configuration:
	1. create an empty project
	2. Make a change to the configuration:
		Project -> project properties: 
		a. Configuration properties -> Advanced -> use of MFC : use MFC in a shared DLL 
 		b. C/C++ -> code generation -> the run-time Library : multi-threaded debug DLL (/MDd) 
 		c. Linker -> System -> Subsystem : Windows (/SUBSYSTEM:WINDOWS) 

If you have problems during linking, you should play around with the points "a" & "b".