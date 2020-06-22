function Invoke-BatchFile ($file) {
	$cmd = "`"$file`" amd64 & set"
	cmd /c $cmd | Foreach-Object {
		$p, $v = $_.split('=')
		if($p -and $v){
			Set-Item -path env:$p -value $v
		}
	}
}
