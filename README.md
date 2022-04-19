# Hacking Console

## Customizable PowerShell for Hackers

![image](https://user-images.githubusercontent.com/6255224/163909334-c0772e71-aa74-4c23-9296-fce15ab76bc1.png)<br />
(shown above: Final Fantasy Menu Mode / Darksaber Cursor Mode)

## Prerequisites

1. Install Chocolatey: https://chocolatey.org/install

2. Install Git for PowerShell<br />
  a. From the Command Line run:

       choco install poshgit
       Set-ExecutionPolicy RemoteSigned
       Install-Module Posh-Git -Scope AllUsers
       Add-PoshGitToProfile -AllHosts -Force
      
3. Install ConsoleZ<br />
  a. From the Command Line run:

       choco install consolez
       
4. You should now be able to run ConsoleZ, you are now ready to use this repository and customize your new Console.

## Customization

1. Locate the files within the /Config directory of this repo and copy them to -> C:\Users\{user}\AppData\Roaming\Console

2. Open the settings and snippets xml files and make adjustments based on your folder structure, etc.

## Advanced Customization

If you have knowledge of C++ code you can make further customizations.
The code C++ code is located within the /ConsoleZ directory.

## Troubleshooting Issues

### Git for PowerShell
https://git-scm.com/book/en/v2/Appendix-A%3A-Git-in-Other-Environments-Git-in-PowerShell

### Troubleshooting C++ Build

#### If you see any errors related to "boost":
1. You must install Boost, there is an installer in the /ConsoleZ directory.
2. Remember which directory that you install Boost into.
3. In Visual Studio, go to a Project's Properties -> C/C++ -> General.
4. Add your Boost directory to the "Additional Include Directories".
![image](https://user-images.githubusercontent.com/6255224/164079326-fec9f1d6-19f6-4ec5-908e-aea622ec0ff4.png)


#### If you see any errors related to "afxres":
1. Add/Remove Programs on your Windows computer.
2. Modify your Visual Studio installation.
3. Add all C++ tools, you must also go into the "Installation details" panel and include the extra MFC library.
4. "Visual C++ MFC for x86 and x64"

#### If you see any errors related to "32":
1. Ensure that your Solution Platform in Visual Studio is set to Win32 instead of x64.

#### More information on build here:
https://github.com/cbucher/console/wiki/How-to-compile

## Credit

### Initial Console Credit:
https://github.com/cbucher/console

### Initial Customization Credit:
https://haacked.com/archive/2015/10/29/git-shell

## TODO

### Gamification: Calculate Points / High Scores!

Every Snippet would use curl to call an API.
This API could take the Command and somehow the user, and save the timestamp.
It could then calculate scores per day.
Example, every time you run Explore you get 100 points.
Have a cool UI (maybe even video game) to track High Scores per day.
