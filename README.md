# Custom kernel for Nokia 8 (NB1)

[Umbrella kernel](https://github.com/resident-nokia/umbrella) with some patches and additions.

- KCal support
- HW button backlight as notification LEDs (not working in Android 11 ROMs)
- Energy Aware Scheduling
- schedutil, blu_schedutil and pwrutilx CPU governors
- lzo-rle support for zram

# For building with Treble support provided by [T-Virus](https://github.com/resident-nokia/t-virus)
- use branch `treble`

# For building under WSL on Windows 10
1. WSL 2 strongly recommended
1. if pulling the repo on some NTFS drive instead of using WSL home dir:
    - enable case sensitivity for repo directory
        in Powershell:
        ```shell
        cd repo_directory
        powershell -c "(Get-ChildItem -Recurse -Directory).FullName | ForEach-Object {fsutil.exe file setCaseSensitiveInfo $_ enable}"
        ```
    - in a wsl linux distro, eg. Ubuntu, enable case sensitivity per directory for automount
        /etc/wsl.conf:
        ```ini
        [automount]
        enabled = true
        root = /mnt/
        options = "metadata,umask=22,fmask=11,case=dir"
        mountFsTab = false
        ```
    - terminate the linux distro, eg. `wsl --terminate Ubuntu`
    - proceed building kernel as on linux
