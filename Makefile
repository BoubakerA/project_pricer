all:
	g++ -std=c++17 -Iinclude \
	    main.cpp \
	    src/black_and_scholes_pricer.cpp \
	    src/monte_carlo_pricer.cpp \
	    -o option_pricer

clean:
	rm -f option_pricer
