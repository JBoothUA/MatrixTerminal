# Super Mario Git PowerShell
# Turns Angular-CLI into a Video Game

<ol>
  <li>Install Chocolatey: https://chocolatey.org/install</li>
  <li>Choco Install ConsoleZ</li>
  <li>Install GitHub Desktop</li>
  <li>
    You need a Git PowerShell (Posh-Git).<br />
    It should be located here:<br />
    C:\Users\{user}\AppData\Local\GitHub\GitHub.appref-ms --open-shell<br />
    If GitHub Desktop did not set it up, you can install it to your shell
    <ol>
      <li>Choco Install Posh-Git</li>
      <li>Set-ExecutionPolicy RemoteSigned</li>
      <li>Import-Module poshgit</li>
      <li>Add-PoshGitToProfile -AllHosts -Force</li>
    </ol>
  </li>
  <li>Pull down the config files from this repo and move to -> C:\Users\{user}\AppData\Roaming\Console</li>
  <li>Open the settings and snippets xml files and make adjustments based on your folder structure, etc</li>
</ol>

Initial Setup Credit:
<a target="_blank" href="https://haacked.com/archive/2015/10/29/git-shell/">Git Shell</a>

