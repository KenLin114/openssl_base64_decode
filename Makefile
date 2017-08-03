FILENAME=base64_chunk_decode
all:
	gcc $(FILENAME).c -g -o $(FILENAME) -lcrypto
	valgrind --leak-check=full --show-leak-kinds=all ./$(FILENAME)

clean:
	rm $(FILENAME) tmpFile
