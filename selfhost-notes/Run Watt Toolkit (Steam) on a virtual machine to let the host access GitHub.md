# Run Watt Toolkit inside Virtual Machine for Host GitHub Access
> Personal hands‑on troubleshooting notes for learning purposes only.

I encountered unstable connectivity when accessing github.com.
I did not want to run Watt Toolkit directly on my host PC to avoid potential pollution of host network environment, so I tried deploying Watt Toolkit inside a VMware virtual machine and let host machine utilize the proxy service.

## Environment setup
I created a Windows 10 virtual machine on VMware:
- Storage: 60 GB maximum
- Memory: 3 GB
- CPU: 1 processor, 2 cores
- Removed sound‑card device to reduce resource overhead.

After the VM was ready, I installed Watt Toolkit and switched it to HTTP proxy mode.
I exported the security certificate and copied it to host Windows via VMware shared folder.

The service only bound to loopback address inside VM, so port forwarding configuration was required.
Inside VM PowerShell, I forwarded local port `127.0.0.1:7890` to `0.0.0.0:7890`.
From host PowerShell, I verified connectivity with telnet, and the proxy was reachable.

On host browser, I configured SwitchyOmega extension for proxy rule switching.
I performed cross‑validation: confirmed mobile network could not reach GitHub, then used host browser with this VM‑based proxy — the solution worked.

## Attempt to automate startup
To achieve automatic boot‑up workflow:
1. On host: created batch script to launch `.vmx` virtual machine file, registered in Windows Task Scheduler.
2. Inside VM: wrote PowerShell `.ps1` script for port forwarding, also added to VM Task Scheduler.
3. Took a VM snapshot for rollback in case of failure.

## Network malfunction & debugging
Shortly after automation was configured, serious network issues occurred:
Watt Toolkit acceleration stopped working, and the VM itself could not load web pages.
Investigation showed massive IP‑port spamming behavior inside virtual machine.
Disabling scheduled tasks and restarting system network services could not repair the damage.
The only recovery method was restoring from the previously saved snapshot.

After restoring snapshot and removing custom port‑forward rules, the same network anomaly still reproduced. It appeared the virtual machine runtime state got corrupted.
I was grateful for the snapshot backup and that I had not run Watt Toolkit on my physical host, as improper proxy configuration may break host network.

Temporary workaround: use batch script to automatically revert snapshot then start VM in headless mode.
```bat
%VMRUN% revertToSnapshot %VMX_PATH% %SNAP_NAME%
%VMRUN% start %VMX_PATH% nogui
```
Registered this batch file into Windows Task Scheduler. This workflow functioned in short‑term tests.
## Root cause & final fix (2026‑09‑07)
I discovered the root cause: the service listening address was set to `0.0.0.0`, which caused address binding conflicts.
Steps taken:
1. Re-configure Watt Toolkit service bind address to the virtual machine's LAN IP instead of 0.0.0.0 / localhost.
2. Abandon original port 7890, switch service to use port 7891.

After modification, proxy service operated normally.

Writer: Swuty3 Record Date: 2026-09-07

##Disclaimer
 
This document records my personal experimental process.
Improper proxy‑related configuration may cause network failure. Operate with caution.
For learning reference only.
