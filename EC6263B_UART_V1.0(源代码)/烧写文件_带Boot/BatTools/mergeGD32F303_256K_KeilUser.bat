@echo off

if exist .\Obj_GD32F303_256K\Boot_GD32F303_256K.hex (
if exist .\..\..\AppProject\Project_Keil\Obj_UseBoot\AppUseBoot.hex (
.\..\..\��д�ļ�_��Boot\BatTools\mergehex.exe --merge .\Obj_GD32F303_256K\Boot_GD32F303_256K.hex    .\..\..\AppProject\Project_Keil\Obj_UseBoot\AppUseBoot.hex        --output .\..\..\��д�ļ�_��Boot\GD32F303_256K_BootMergeApp.hex)
)
