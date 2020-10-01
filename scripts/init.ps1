$Return = Get-Location
Set-Location "$PSScriptRoot\.."

# Init submodules
git submodule init
git submodule update

# init tools
python.exe -m venv .\tools\texture_generator\.env
.\tools\texture_generator\.env\Scripts\python -m pip install pip --upgrade
.\tools\texture_generator\.env\Scripts\pip.exe install -r .\tools\texture_generator\requirements.txt

Set-Location $Return
