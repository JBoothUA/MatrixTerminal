!INCLUDE ../shared/version.h

release:
	@echo "copy help file"
	@xcopy "$(MAKEDIR)\..\help\console.chm" "$(MAKEDIR)\..\bin\Win32\Release\*" /F /Y
	@xcopy "$(MAKEDIR)\..\help\console.chm" "$(MAKEDIR)\..\bin\Win32\Release Legacy\*" /F /Y
	@xcopy "$(MAKEDIR)\..\help\console.chm" "$(MAKEDIR)\..\bin\x64\Release\*" /F /Y
	@xcopy "$(MAKEDIR)\..\help\console.chm" "$(MAKEDIR)\..\bin\x64\Release Legacy\*" /F /Y
	@echo "$(MAKEDIR)\..\bin\ConsoleZ.$(VERSION).7z"
	"C:\Program Files\7-Zip\7z.exe" a -t7z -m9=lzma2 -mx -mmt2 "$(MAKEDIR)\..\bin\ConsoleZ.$(VERSION).7z" -xr!*.xml "$(MAKEDIR)\..\bin\Win32" "$(MAKEDIR)\..\bin\x64" "$(MAKEDIR)\..\bin\l10n"
	@echo "$(MAKEDIR)\..\bin\ConsoleZ.x86.$(VERSION).zip"
	"C:\Program Files\7-Zip\7z.exe" a -tzip -mx9 -mmt2 "$(MAKEDIR)\..\bin\ConsoleZ.x86.$(VERSION).zip" -xr!*.pdb -xr!*.xml "$(MAKEDIR)\..\bin\Win32\Release\*" "$(MAKEDIR)\..\bin\l10n\Release\*"
	@echo "$(MAKEDIR)\..\bin\ConsoleZ.x64.$(VERSION).zip"
	"C:\Program Files\7-Zip\7z.exe" a -tzip -mx9 -mmt2 "$(MAKEDIR)\..\bin\ConsoleZ.x64.$(VERSION).zip" -xr!*.pdb -xr!*.xml "$(MAKEDIR)\..\bin\x64\Release\*" "$(MAKEDIR)\..\bin\l10n\Release\*"


clean:
	@echo clean
