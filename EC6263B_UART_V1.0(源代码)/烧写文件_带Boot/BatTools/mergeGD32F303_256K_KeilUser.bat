@echo off

if exist .\Obj_GD32F303_256K\Boot_GD32F303_256K.hex (
if exist .\..\..\AppProject\Project_Keil\Obj_UseBoot\AppUseBoot.hex (
.\..\..\烧写文件_带Boot\BatTools\mergehex.exe --merge .\Obj_GD32F303_256K\Boot_GD32F303_256K.hex    .\..\..\AppProject\Project_Keil\Obj_UseBoot\AppUseBoot.hex        --output .\..\..\烧写文件_带Boot\GD32F303_256K_BootMergeApp.hex)
)
