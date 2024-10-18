import os

pid = os.getpid()
ppid = os.getppid()

print(f"PID: {pid}")
print(f"PPID: {ppid}")