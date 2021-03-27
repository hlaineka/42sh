if make ; then
	valgrind --leak-check=yes --track-origins=yes ./21sh debug
fi
