all:
	gcc broadcaster.c udp.c -o broadcaster
	gcc listener.c udp.c -o listener
	python test.py
