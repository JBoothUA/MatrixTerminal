!IFDEF _USE_AERO
RC_FLAGS=/D "_USE_AERO"
!ELSE
RC_FLAGS=
!ENDIF

build:
	@echo $(lang) $(configuration)
	@xcopy "..\console\resource.h" "$(lang)\" /F /Y
	@xcopy "..\console\res" "$(lang)\res\" /F /Y /E
	iconv -f UTF-8 -t UCS-2LE "$(lang)\console.rc" > "$(lang)\console.ucs2.rc"
	rc.exe /I"..\console" /I"../shared" /I"../wtl/wtl/include" $(RC_FLAGS) /D "_UNICODE" /D "UNICODE" /nologo /fo"..\obj\l10n\$(configuration)\console_$(lang).res" "$(lang)\console.ucs2.rc"
	link.exe /OUT:"..\bin\l10n\$(configuration)\console_$(lang).dll" /NOENTRY /DLL /SUBSYSTEM:WINDOWS /MACHINE:X86 /ERRORREPORT:PROMPT /NOLOGO "..\obj\l10n\$(configuration)\console_$(lang).res"

release:
	@for /D %d in (*) do @if exist %d\console.ini $(MAKE) build /C /F makefile /D lang=%d /D configuration="$(configuration)"

clean:
	@echo clean
