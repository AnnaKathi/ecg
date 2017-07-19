@echo off

set zipdir=Y:\Daten\source
set file=horus.ecgrestart.jul2017.zip

echo upload to DropBox Cryptomator Container
echo ----------------------------------------------------------------------
echo zip source to Cryptomator Container (%zipdir%)
echo filename %file%
echo ----------------------------------------------------------------------
cd
pause
7z a -r -tzip -x@exclude.txt %zipdir%\%file%
dir %zipdir%\%file%
echo -----------------------------------------------------------------------
pause



