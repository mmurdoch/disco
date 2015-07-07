all:
	rm -rf build
	mkdir -p build/test

	gcc test/detest-test.c src/detest/detest.c -I src -o build/test/detest-test
	build/test/detest-test

	gcc test/time-test.c src/detest/detest.c src/disco/time.c -I src -o build/test/time-test
	build/test/time-test

	gcc test/broadcaster.c src/disco/udp.c src/disco/time.c src/disco/broadcast.c -I src -o build/test/broadcaster
	gcc test/listener.c src/disco/udp.c src/disco/time.c src/disco/broadcast.c -I src -o build/test/listener
	cp test/test.py build/test/test.py
	python build/test/test.py
