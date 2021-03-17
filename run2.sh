if make debug; then
	valgrind --leak-check=yes --track-origins=yes ./21sh
fi
