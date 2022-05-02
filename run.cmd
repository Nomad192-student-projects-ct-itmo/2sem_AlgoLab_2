@echo off

goto start

:: old old version
:: ---------------------------------------------------------------------------------------
:: set "path_folder=%cd%"
:: cd..
:: call:set_name %cd%
:: echo %name%
:: cd %path_folder%

:: cmake --build . && (echo START & %name%)
:: echo.
:: echo return code: %errorlevel%
:: goto:eof

:: :set_name
:: set "name=%~nx1"
:: ---------------------------------------------------------------------------------------


:: old version
:: ---------------------------------------------------------------------------------------
:: For %%i in (*.exe) Do cmake --build . && (echo START & %%i) & goto:print_return_code 
:: :print_return_code
:: echo.
:: echo return code: %errorlevel%
:: ---------------------------------------------------------------------------------------


:: new version
:: ---------------------------------------------------------------------------------------


:start
:: current version
:: ---------------------------------------------------------------------------------------
cmake --build . && (echo START & %1)
echo.
if not exist "C:\Windows\nhcolor.exe" (
	IF %errorlevel% == 0 (
		echo return code: %errorlevel%
	) ELSE (
		echo crash with code: %errorlevel%
	)
) else (
	IF %errorlevel% == 0 (
		echo return code: %errorlevel% | nhcolor 0A
	) ELSE (
		echo crash with code: %errorlevel% | nhcolor 0C
	)
)
:: https://nhutils.ru/blog/nhcolor/
:: ---------------------------------------------------------------------------------------

:: simple version
:: ---------------------------------------------------------------------------------------
:: cmake --build . && (echo START & %1)
:: echo.
:: IF %errorlevel% == 0 (
:: echo return code: %errorlevel%
:: ) ELSE (
:: echo crash with code: %errorlevel%
::)
:: ---------------------------------------------------------------------------------------