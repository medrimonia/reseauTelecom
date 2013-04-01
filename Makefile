%-min-covering:
	echo $@ | sed  s/-min-covering// | xargs src/minCoveringTree >$@