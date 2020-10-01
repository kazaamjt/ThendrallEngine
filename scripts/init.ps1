param(
	# Install the dev requirements of the tools
	[switch]$InstallDevTools
)

$Return = Get-Location
Set-Location "$PSScriptRoot\.."

# Init submodules
git submodule init
git submodule update

# init tools
if (!(Test-Path .env)) {
	python.exe -m venv .env
}
.env\Scripts\python -m pip install pip --upgrade
.env\Scripts\pip.exe install -r .\tools\texture_generator\requirements.txt

if ($InstallDevTools) {
	.env\Scripts\pip.exe install -r .\tools\texture_generator\requirements.dev.txt
}

Set-Location $Return
