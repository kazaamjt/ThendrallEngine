$Return = Get-Location
Set-Location "$PSScriptRoot\.."

# init tools
if (!(Test-Path .env)) {
	Write-Output "Creating python venv"
	python.exe -m venv .env
}
.env\Scripts\python -m pip install pip --upgrade

mkdir tools/texture_generator -Force
Invoke-WebRequest https://raw.githubusercontent.com/kazaamjt/Texture-Generator/master/src/main.py -UseBasicParsing -OutFile tools/texture_generator/main.py
Invoke-WebRequest https://raw.githubusercontent.com/kazaamjt/Texture-Generator/master/requirements.txt -UseBasicParsing -OutFile tools/texture_generator/requirements.txt
.env\Scripts\pip.exe install -r .\tools\texture_generator\requirements.txt

Set-Location $Return
