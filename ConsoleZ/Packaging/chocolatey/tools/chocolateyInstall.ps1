$packageName    = 'ConsoleZ'
$toolsDir       = "$(Split-Path -parent $MyInvocation.MyCommand.Definition)"
$url            = 'https://github.com/cbucher/console/releases/download/1.19.0/ConsoleZ.x86.1.19.0.19104.zip'
$url64          = 'https://github.com/cbucher/console/releases/download/1.19.0/ConsoleZ.x64.1.19.0.19104.zip'
$checksum       = 'BAF0D01A6FC2EBA66FE959740045CD268FCDE772B1F3B9F59C4CB1D4D54F252E'
$checksumType   = 'sha256'
$checksum64     = '671566592F1E8B0B71A5E8A5BCE3A5437A2F65C1E251715B0155774EC1BE669F'
$checksumType64 = 'sha256'


Install-ChocolateyZipPackage $packageName $url $toolsDir $url64 -checksum $checksum -checksumType $checksumType -checksum64 $checksum64 -checksumType64 $checksumType64