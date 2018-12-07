base64conv: main.cpp converter.cpp base64coder.cpp base64decoder.cpp
	g++ main.cpp converter.cpp base64coder.cpp base64decoder.cpp -o base64conv --std=c++14 -O3

.PHONY: clean

clean:
	rm -f base64conv
