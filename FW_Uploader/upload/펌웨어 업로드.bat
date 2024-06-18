::@echo off
@echo off

: jprog upload routine
echo **** %hex_file% Firmware upload will start. ****

: stlink upload routine
ST-LINK_CLI.exe -c SWD -ME -p WIGY.hex -V "after_programming" -Rst -Run

TIMEOUT /t 30

echo **** Firmware upload was successful. ****
: pause
EXIT/B