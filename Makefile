all:
	@g++ -o tictactoe src/*.cpp -Iinclude -lsfml-graphics -lsfml-window -lsfml-system -g
run:
	@./tictactoe
