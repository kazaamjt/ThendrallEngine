param(
	[parameter(mandatory=$false)]
	[string]$Name,
	[ValidateSet('msvc', 'gcc', 'clang')]
	[string]$Compiler='clang',

	[switch]$Clean=$false,
	# Regenerate all art assets
	[switch]$GenerateAssets=$false
)

if ($Clean) {
	bazel clean
}

if ($GenerateAssets) {
	python .\scripts\texture_generator\main.py --in .\art --out .\data\textures
}

if ($Compiler -eq 'clang') {
	bazel build $Name --config=clang-cl --compiler=clang-cl --keep_going
}

else {
	bazel build $Name --config=cl --keep_going
}
Copy-Item lib/GL/win32/glew32.dll bazel-bin/glew32.dll
Copy-Item lib/SDL2/win32/SDL2.dll bazel-bin/SDL2.dll
