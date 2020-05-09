![Build status](https://github.com/radu-v/umbrella-mod/workflows/master/badge.svg)

# Custom kernel for Nokia 8 (NB1)

[Umbrella kernel](https://github.com/resident-nokia/umbrella) with some patches and additions.

- KCal support
- HW button backlight as notification LEDs

# For building under WSL on Windows 10
1. enable case sensitivity for repo directory
    in Powershell:
    ```shell
    cd repo_directory
    powershell -c "(Get-ChildItem -Recurse -Directory).FullName | ForEach-Object {fsutil.exe file setCaseSensitiveInfo $_ enable}"
    ```
2. in a wsl linux distro, eg. Ubuntu, enable case sensitivity per directory for automount
    /etc/wsl.conf:
    ```ini
    [automount]
    enabled = true
    root = /mnt/
    options = "metadata,umask=22,fmask=11,case=dir"
    mountFsTab = false
    ```
3. terminate the linux distro, eg. `wsl --terminate Ubuntu`
4. proceed building kernel as on linux
