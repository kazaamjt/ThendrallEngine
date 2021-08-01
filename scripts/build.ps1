param(
	[parameter(mandatory=$false)]
	[string]$Name="main",
	[ValidateSet('msvc', 'clang')]
	[string]$Compiler='clang',

	[switch]$Clean=$false,
	# Regenerate all art assets
	[switch]$GenerateAssets=$false
)

$Return = Get-Location
Set-Location "$PSScriptRoot\.."

if ($Clean) {
	bazel clean
}

if ($GenerateAssets) {
	.env\Scripts\python.exe .\tools\texture_generator\main.py --in .\art --out .\data\textures
}

if ($Compiler -eq 'clang') {
	bazel build $Name --config=clang-cl --compiler=clang-cl --keep_going
} else {
	bazel build $Name --config=cl --keep_going
}

Set-Location $Return
