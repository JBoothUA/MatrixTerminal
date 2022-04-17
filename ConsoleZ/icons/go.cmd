@echo off

rem This script requires
rem - InkScape installed in C:\Program Files\Inkscape\inkscape.exe
rem - ImageMagick with legacy tools (convert.exe)

if not exist "%~dp0\out" mkdir "%~dp0\out"

for %%S in (16 20 24 32 40 48 64 80 128) do (
	if not exist "%~dp0\%%Sx%%S" mkdir "%~dp0\%%Sx%%S"
	for %%I in (%~dp0\*.svg) do (
		echo %%~nI : %%Sx%%S
		"C:\Program Files\Inkscape\inkscape.exe" "--file=%~dp0\%%~nxI" "--export-png=%~dp0\%%Sx%%S\%%~nI.png" --export-area-page --export-width=%%S --export-height=%%S
	)

	convert.exe -size %%Sx%%S xc:transparent "png32:%temp%\empty.png"
	convert.exe ^
		"%temp%\empty.png" ^
		"%~dp0\%%Sx%%S\14-PreviousFind.png" ^
		"%~dp0\%%Sx%%S\15-NextFind.png" ^
		"%~dp0\%%Sx%%S\18-ConsoleZSpecial.png" ^
		"%~dp0\%%Sx%%S\19-MatchWholeWordOnly.png" ^
		+append "%~dp0\out\search_%%S.png"
	convert.exe ^
		"%~dp0\%%Sx%%S\01-NewTab.png" ^
		"%~dp0\%%Sx%%S\02-PreviousTab.png" ^
		"%~dp0\%%Sx%%S\03-NextTab.png" ^
		"%~dp0\%%Sx%%S\04-RenameTab.png" ^
		"%~dp0\%%Sx%%S\05-Copy.png" ^
		"%~dp0\%%Sx%%S\06-Paste.png" ^
		"%~dp0\%%Sx%%S\07-InsertSnippet.png" ^
		"%~dp0\%%Sx%%S\08-AddHorizontalSplit.png" ^
		"%~dp0\%%Sx%%S\09-AddVerticalSplit.png" ^
		"%~dp0\%%Sx%%S\10-Fullscreen.png" ^
		"%~dp0\%%Sx%%S\12-About.png" ^
		"%~dp0\%%Sx%%S\13-Help.png" ^
		+append "%~dp0\out\toolbar_%%S.png"
	copy "%~dp0\%%Sx%%S\11-ReduceScreen.png" "%~dp0\out\fullscreen1_%%S.png" /y
	copy "%~dp0\%%Sx%%S\10-Fullscreen.png" "%~dp0\out\fullscreen2_%%S.png" /y
)
