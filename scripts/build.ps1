param(
	[parameter(mandatory=$false)]
	[ValidateSet('msvc', 'gcc', 'clang')]
	[string]$Compiler='clang',

	[switch]$Clean=$false
)

# TODO: implement linux

if ($Clean) {
	bazel clean
}

if ($Compiler -eq 'clang') {
	bazel build main --config=clang-cl --compiler=clang-cl --keep_going
}

else {
	bazel build main --config=cl --keep_going
}
Copy-Item lib/win32/GL/glew32.dll bazel-bin/glew32.dll
Copy-Item lib/win32/SDL2/SDL2.dll bazel-bin/SDL2.dll
