{ pkgs }: {
	deps = [
   pkgs.gti
		pkgs.clang
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}