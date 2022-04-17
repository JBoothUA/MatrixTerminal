doc: html\changelog.html
	-hhc console.hhp

html\changelog.html: ..\README.md
	@echo ^<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"^> >$@
	@echo ^<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en"^> >>$@
	@echo ^<head^> >>$@
	@echo ^<title^>Changelog^</title^> >>$@
	@echo ^<meta http-equiv="content-type" content='text/html; charset=utf-8' /^> >>$@
	@echo ^<link rel="stylesheet" type="text/css" href="../styles/help.css" /^> >>$@
	@echo ^</head^> >>$@
	@echo ^<body^> >>$@
	csplit --quiet ..\README.md /^Changelog$$/
	pandoc --from=markdown --to=html xx01 >>$@
	@echo ^</body^> >>$@
	@echo ^</html^> >>$@

clean:
	@if exist console.chm @del /f console.chm
	@if exist html\changelog.html @del /f html\changelog.html
	@del /f xx*