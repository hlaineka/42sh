if make ; then
	valgrind --leak-check=yes --track-origins=yes ./42sh debug
fi