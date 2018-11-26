OBJS = test.c 
LIB = pidManager.c
LINK = pidManager.o
PACKAGE = lib.a			
INPUT_FILE = test.c
OUTPUT_FILE = test

built: $(OBJS)
	clear
	gcc -c $(LIB)									# 建立連接檔
	ar rcs $(PACKAGE) $(LINK)						# 若有多個連結檔，可以打包在一起
	gcc $(INPUT_FILE) $(PACKAGE) -o $(OUTPUT_FILE)
	rm $(PACKAGE) $(LINK)
	./$(OUTPUT_FILE)

clean:
	rm $(OUTPUT_FILE)