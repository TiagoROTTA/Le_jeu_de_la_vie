CXX = clang++
CXXFLAGS = -I/usr/include/SFML -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system -g -Wmost -Werror

SRCS = $(shell find . -type f -name '*.cpp')
HEADERS = $(shell find . -type f -name '*.h')

main: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o "$@"

main-debug: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -U_FORTIFY_SOURCE -O0 $(SRCS) -o "$@"

clean:
	rm -f main main-debug
