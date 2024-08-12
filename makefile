all:
	cd rimpexp
	nmake -f rimpexp32.mak
	cd ..
	nmake -f refs32.mak
	cd ../filters
	nmake -f filters32.mak
	cd ../languages
	nmake -f languages32.mak
	