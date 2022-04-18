# Hacking Console with PowerShell + Git
## Customizable Command-Line Console for Hackers

# Installation
1. Install Chocolatey: https://chocolatey.org/install
2. From a Command Line run "Choco Install ConsoleZ"
<ol>
  <li>Pull down the config files from this repo and move to -> C:\Users\{user}\AppData\Roaming\Console</li>
  <li>Open the settings and snippets xml files and make adjustments based on your folder structure, etc</li>
</ol>
You also will need a Git PowerShell (Posh-Git).<br />
<ol>
  <li>Install GitHub Desktop</li>
  <li>
    If GitHub Desktop did not set it up, you can install it to your shell
    <ol>
      <li>Choco Install poshgit</li>
      <li>Set-ExecutionPolicy RemoteSigned</li>
      <li>Install-Module Posh-Git -Scope AllUsers</li>
      <li>Add-PoshGitToProfile -AllHosts -Force</li>
    </ol>
  </li>
</ol>

## Troubleshooting
### Git in PowerShell Troubleshooting:
https://git-scm.com/book/en/v2/Appendix-A%3A-Git-in-Other-Environments-Git-in-PowerShell

### Initial ConsoleZ Credit:
https://haacked.com/archive/2015/10/29/git-shell

### Initial Setup Credit:
https://haacked.com/archive/2015/10/29/git-shell

## TODO
### Calculate Points / High Scores!
<div>
  Every Snippet would use curl to call an API.
  This API could take the Command and somehow the user, and save the timestamp.
  It could then calculate scores per day.
  Example, every time you run Explore you get 100 points.
  Have a cool UI (maybe even video game) to track High Scores per day.
</div>

