# Run todo.exe with the correct MSYS2 runtime DLLs on PATH.
# Usage: ./run.ps1 help | ./run.ps1 add "buy milk"

$env:PATH = "D:\Tools\msys2\ucrt64\bin;D:\Tools\msys2\usr\bin;$env:PATH"
& "$PSScriptRoot/build-gcc-debug/todo.exe" @args
