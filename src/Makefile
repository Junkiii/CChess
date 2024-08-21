files = main.o cchess.o board.o evaluation.o forsyth_edwards_notation.o minimax.o pieces.o utilities.o random_generator.o zobrist_hashing.o

chess_ai:$(files)
	gcc $(files) -o chess_ai

%.o:%.c
	gcc -c $<

clean:
	rm -f $(files) chess_ai