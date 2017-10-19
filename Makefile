OUT = shell
CC = gcc
SRC = src
ODIR = obj
OBJS = $(patsubst %, $(ODIR)/%, list.o str_util.o shell.o main.o)

.PHONY: all
all: clean $(OUT)

.PHONY: clean
clean:
	rm -rf $(ODIR)

$(ODIR)/%.o : $(SRC)/%.c
	if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi
	$(CC) $(CFLAGS) -lreadline -c -o $@ $<

$(OUT): $(OBJS)
	$(CC) -Wall -lreadline -o $(ODIR)/$(OUT) $(OBJS)
