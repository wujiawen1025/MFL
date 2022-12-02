@echo off

if exist C:\Keil_v5\ARM\ARMCC\bin\fromelf.exe (
if exist .\..\..\AppProject\Project_Keil\Obj_UseBoot\AppUseBoot.axf (C:\Keil_v5\ARM\ARMCC\bin\fromelf.exe ".\..\..\AppProject\Project_Keil\Obj_UseBoot\AppUseBoot.axf" --bin --output ".\..\AppUpdateFile.bin")

 )


