@echo off
echo setup.bat
echo setting for local environment...
echo.
echo [SET USER HOOKS]
git config --local core.hooksPath src/src_user/Script/GitHooks
echo done.
echo.
echo The process has been completed.
echo Press any key to exit...
pause >nul
