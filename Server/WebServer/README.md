# FastAPI Echo Server

## Install

```powershell
uv venv .venv
uv pip install --python .venv\Scripts\python.exe -r requirements.txt
```

or

```powershell
.\install_requirements.bat
```

## Run

```powershell
uv run --with-requirements requirements.txt uvicorn main:app --host 0.0.0.0 --port 8000 --reload
```

or

```powershell
.\run_server.bat
```

브라우저에서 `http://127.0.0.1:8000/`로 접속하면 에코 테스트 페이지가 열립니다.

## Note

If `uv` is installed, you do not need `pip` on `PATH`.
`run_server.bat` runs the server directly through `uv`.

## Example

```powershell
Invoke-RestMethod `
  -Method Post `
  -Uri http://127.0.0.1:8000/echo `
  -ContentType "application/json" `
  -Body '{"message":"hello"}'
```
