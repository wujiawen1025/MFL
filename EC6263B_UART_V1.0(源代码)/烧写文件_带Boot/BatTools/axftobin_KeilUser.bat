@echo off

if exist C:\Keil_v5\ARM\ARMCC\bin\fromelf.exe (
if exist .\Obj_UseBoot\AppUseBoot.axf (C:\Keil_v5\ARM\ARMCC\bin\fromelf.exe ".\Obj_UseBoot\AppUseBoot.axf" --bin --output ".\..\..\ÉÕÐ´ÎÄ¼þ_´øBoot\AppUpdateFile.bin")
)


