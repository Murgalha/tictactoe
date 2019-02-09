all:
	@g++ -o tictactoe src/*.cpp -Iinclude -lsfml-graphics -lsfml-window -lsfml-system -O2
run:
	@./tictactoe
