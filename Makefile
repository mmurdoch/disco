all:
	rm -rf build
	mkdir -p build/test
	gcc test/broadcaster.c src/disco/udp.c -I src -o build/test/broadcaster
	gcc test/listener.c src/disco/udp.c -I src -o build/test/listener
	python test/test.py
