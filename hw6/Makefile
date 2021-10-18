# Makefile for HW5, ecs36b, s2020
#

CC = g++ -std=c++14
CFLAGS = -g -I/usr/include/jsoncpp

# CFLAGS = -g -D_ECS35B_DEBUG_ -I/usr/include/jsoncpp
# CFLAGS = -g -Wall -Wstrict-prototypes
# CFLAGS = -O3

LDFLAGS = 	-ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -lcurl -ljsonrpccpp-client

CORE_INCS =	Core.h Person.h Post.h Comment.h Reaction.h	\
		Action.h Link.h Message.h JvTime.h Tag.h
CORE_OBJS =	Core.o Person.o Post.o Comment.o Reaction.o	\
	 	Action.o Link.o JvTime.o Tag.o

# rules.
all: 	 hw6server hw6search hw6update

#
#

hw6client.h:		ecs36b_hw6.json
	jsonrpcstub ecs36b_hw6.json --cpp-server=hw6Server --cpp-client=hw6Client

hw6server.h:		ecs36b_hw6.json
	jsonrpcstub ecs36b_hw6.json --cpp-server=hw6Server --cpp-client=hw6Client

#hw6client.o:		hw6client.h hw6client.cpp $(CORE_INCS)
#	$(CC) -c $(CFLAGS) hw6client.cpp

hw6server_redacted.o:		hw6server.h hw6server_redacted.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) hw6server_redacted.cpp

hw6server:		$(CORE_OBJS) hw6server_redacted.o JSON_Post_redacted.o
	$(CC) -o hw6server $(CORE_OBJS) hw6server_redacted.o JSON_Post_redacted.o $(LDFLAGS)

#hw6client:		$(CORE_OBJS) hw6client.o JSON_Post.o
#	$(CC) -o hw6client $(CORE_OBJS) hw6client.o JSON_Post.o $(LDFLAGS)

hw6search.o:	hw6client.h hw6search.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) hw6search.cpp

hw6update.o:	hw6client.h hw6update.cpp $(CORE_INCS)
	$(CC) -c hw6update.cpp

hw6search:		$(CORE_OBJS) hw6search.o JSON_Post_redacted.o
	$(CC) -o hw6search $(CORE_OBJS) hw6search.o JSON_Post_redacted.o $(LDFLAGS)

hw6update:		$(CORE_OBJS) hw6update.o JSON_Post_redacted.o
	$(CC) -o hw6update $(CORE_OBJS) hw6update.o JSON_Post_redacted.o $(LDFLAGS)

Core.o:			Core.cpp Core.h
	$(CC) -c $(CFLAGS) Core.cpp

Tag.o:			Tag.cpp Tag.h
	$(CC) -c $(CFLAGS) Tag.cpp

Person.o:		Person.cpp Person.h Core.h
	$(CC) -c $(CFLAGS) Person.cpp

Post.o:			Post.cpp Post.h
	$(CC) -c $(CFLAGS) Post.cpp

Comment.o:		Comment.cpp Comment.h
	$(CC) -c $(CFLAGS) Comment.cpp

Reaction.o:		Reaction.cpp Reaction.h
	$(CC) -c $(CFLAGS) Reaction.cpp

JvTime.o:		JvTime.cpp JvTime.h
	$(CC) -c $(CFLAGS) JvTime.cpp

Link.o:			Link.cpp Link.h
	$(CC) -c $(CFLAGS) Link.cpp

Action.o:		Action.cpp Action.h
	$(CC) -c $(CFLAGS) Action.cpp

JSON_Post_redacted.o:		JSON_Post_redacted.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) JSON_Post_redacted.cpp

#hw6test.o:		hw6test.cpp $(CORE_INCS)
#	$(CC) -c $(CFLAGS) hw6test.cpp

#hw6test:		$(CORE_OBJS) hw6test.o JSON_Post.o
#	$(CC) -o hw6test $(CORE_OBJS) hw6test.o JSON_Post.o $(LDFLAGS)

clean:
	rm -f *.o *~ core hw6test hw6server hw6client hw6server.h hw6client.h


