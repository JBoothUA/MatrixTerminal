# mario-shell
Super Mario Git PowerShell with all the coolest configurations.

<ol>
  <li>Install Chocolatey</li>
  <li>Choco Install ConsoleZ</li>
  <li>Install GitHub Desktop</li>
  <li>
    You need a Git PowerShell (Posh-Git).<br />
    C:\Users\{user}\AppData\Local\GitHub\GitHub.appref-ms --open-shell<br />
    If GitHub Desktop did not set it up, you can install it to your shell.
    <ol>
      <li>Choco Install Posh-Git</li>
      <li>Set-ExecutionPolicy RemoteSigned</li>
      <li>Import-Module posh-git</li>
      <li>Add-PoshGitToProfile -AllHosts -Force</li>
    </ol>
  </li>
  <li>Pull down the config files from this repo and move to -> C:\Users\{user}\AppData\Roaming\Console</li>
  <li>Replace the given file paths with your repo paths in the settings and snippets xml files</li>
</ol>

Initial Setup Credit:
<a target="_blank" href="https://haacked.com/archive/2015/10/29/git-shell/">Git Shell</a>

