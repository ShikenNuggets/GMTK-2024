xcopy /s "GadgetEngine\GadgetEngine\Graphics\OpenGL\Shaders" "Resources\Shaders\OpenGL\" /Y
xcopy /s "GadgetEngine\GadgetEngine\Graphics\DX12\Shaders" "Resources\Shaders\DX12\" /Y

START /WAIT /B %~dp0\GadgetEngine\Build\DataBuilder\Release\DataBuilder.exe -f

@echo off
if %errorlevel%==-1 ( echo Data Build was not successful && PAUSE && EXIT /B 2)
@echo on

xcopy /s "GadgetEngine\Resources\" "Build\Game\Debug\Resources" /Y /d
xcopy /s "GadgetEngine\Resources\" "Build\Game\Develop\Resources" /Y /d
xcopy /s "GadgetEngine\Resources\" "Build\Game\Release\Resources" /Y /d

xcopy /s "Resources\" "Build\Game\Debug\Resources" /Y /d
xcopy /s "Resources\" "Build\Game\Develop\Resources" /Y /d
xcopy /s "Resources\" "Build\Game\Release\Resources" /Y /d

PAUSE