@echo off
setlocal

cd /d "%~dp0"
set "UV_CACHE_DIR=%~dp0.uv-cache"

where uv >nul 2>nul
if errorlevel 1 (
    echo uv is not installed or not available on PATH.
    exit /b 1
)

uv venv .venv --allow-existing
if errorlevel 1 exit /b 1

uv pip install --python .venv\Scripts\python.exe -r requirements.txt

endlocal
