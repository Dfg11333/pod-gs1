CFLAGS=-std=c99 -g -O0

OBJS=gs1.o gs1_data.o gs1_news.o gs1_message.o gs1_servers.o

all: gs1

gs1: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o gs1

clean:
	rm -f $(OBJS) gs1
