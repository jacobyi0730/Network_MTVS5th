@echo off
setlocal

cd /d "%~dp0"
set "UV_CACHE_DIR=%~dp0.uv-cache"
set "VENV_PYTHON=%~dp0.venv\Scripts\python.exe"

if not exist "%VENV_PYTHON%" (
    echo Virtual environment not found: "%VENV_PYTHON%"
    echo Run install_requirements.bat first.
    exit /b 1
)

"%VENV_PYTHON%" -m uvicorn main:app --host 0.0.0.0 --port 8000 --reload

endlocal
