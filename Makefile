all:
	gcc broadcaster.c network.c -o broadcaster
	gcc listener.c network.c -o listener
	python test.py
