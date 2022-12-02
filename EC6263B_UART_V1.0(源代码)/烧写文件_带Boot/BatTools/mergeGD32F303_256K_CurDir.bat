@echo off

if exist .\..\..\BootProject\Project_Keil\Obj_GD32F303_256K\Boot_GD32F303_256K.hex (
if exist .\..\..\AppProject\Project_Keil\Obj_UseBoot\AppUseBoot.hex (
.\mergehex.exe --merge .\..\..\BootProject\Project_Keil\Obj_GD32F303_256K\Boot_GD32F303_256K.hex    .\..\..\AppProject\Project_Keil\Obj_UseBoot\AppUseBoot.hex        --output .\..\GD32F303_256K_BootMergeApp.hex)
)

#pause
