@echo off
setlocal

cd /d "%~dp0"

where uv >nul 2>nul
if errorlevel 1 (
    echo uv is not installed or not available on PATH.
    exit /b 1
)

uv run --with-requirements requirements.txt uvicorn main:app --host 0.0.0.0 --port 8000 --reload

endlocal
