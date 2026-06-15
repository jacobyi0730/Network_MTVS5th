from typing import Any
from pathlib import Path

from fastapi import FastAPI
from fastapi.responses import FileResponse
from pydantic import BaseModel


class EchoRequest(BaseModel):
    message: Any


app = FastAPI(title="Echo Server")
BASE_DIR = Path(__file__).resolve().parent


@app.get("/health")
async def health() -> dict[str, str]:
    return {"status": "ok"}


@app.get("/")
async def index() -> FileResponse:
    return FileResponse(BASE_DIR / "index.html")


@app.post("/echo")
async def echo(payload: EchoRequest) -> dict[str, Any]:
    return {"echo": payload.message}
