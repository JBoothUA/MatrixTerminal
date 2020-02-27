# Super Mario Git PowerShell
# Turns the Command Line into a Video Game

<ol>
  <li>
    Download from: https://github.com/cbucher/console/wiki/Downloads
    <ul>
      <li>OR</li>
      <li>Install Chocolatey: https://chocolatey.org/install</li>
      <li>Choco Install ConsoleZ</li>
    </ul>
  </li>
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

Additional Troubleshooting:
<a target="_blank" href="https://git-scm.com/book/en/v2/Appendix-A%3A-Git-in-Other-Environments-Git-in-Powershell">Git Shell</a>
<br />
Inital Setup Credit:
<a target="_blank" href="https://haacked.com/archive/2015/10/29/git-shell/">Git ConsoleZ</a>
