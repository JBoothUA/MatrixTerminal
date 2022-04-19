# Hacking Console
## Customizable PowerShell for Hackers

### Prerequisites

1. Install Chocolatey: https://chocolatey.org/install

2. Install Git for PowerShell
       a. From a Command Line run:

       choco install poshgit
       Set-ExecutionPolicy RemoteSigned
       Install-Module Posh-Git -Scope AllUsers
       Add-PoshGitToProfile -AllHosts -Force
      
3. Install ConsoleZ
       a. From a Command Line run:

       choco install consolez
       
4. Now you are ready to use this repository and customize your new Console

### Customization

1. Locate the files within the /Config directory of this repo and copy them to -> C:\Users\{user}\AppData\Roaming\Console

2. Open the settings and snippets xml files and make adjustments based on your folder structure, etc

### Advanced Customization

If you have knowledge of C++ code you can make further customizations.
The code C++ code is located within the /ConsoleZ directory.

### Troubleshooting
#### Git in PowerShell Troubleshooting:
https://git-scm.com/book/en/v2/Appendix-A%3A-Git-in-Other-Environments-Git-in-PowerShell

### Troubleshooting C++
If you see any errors related to Boost:
1. 

If you see any errors related to ahref:
1. 

More information here:
https://github.com/cbucher/console/wiki/How-to-compile

### Credit
#### Initial Console Credit:
https://github.com/cbucher/console

#### Initial Setup Credit:
https://haacked.com/archive/2015/10/29/git-shell

### TODO
#### Calculate Points / High Scores!

Every Snippet would use curl to call an API.
This API could take the Command and somehow the user, and save the timestamp.
It could then calculate scores per day.
Example, every time you run Explore you get 100 points.
Have a cool UI (maybe even video game) to track High Scores per day.
