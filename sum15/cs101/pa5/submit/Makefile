# 
# Name:			Cecilia Condes
# ID:			ccondes
# Class:		CMPS 101
# Date:			7.28.15
# Filename:		Makefile
# Description:	Makefile for pa4
#

FLAGS   = -std=c99 -Wall
EXEBIN  = FindComponents
SUPPORT = List Graph
CLIENTS = GraphTest 
SOURCES = $(patsubst %, %.c, $(SUPPORT) $(EXEBIN))
OBJECTS = $(patsubst %, %.o, $(SUPPORT) $(EXEBIN))
HEADERS = $(patsubst %, %.h, $(SUPPORT))

TESTFILES = in out

CLASS = cmps101-pt.u15
ASSIGNMENT = pa5
SUBMITFILES = $(SOURCES) $(HEADERS) $(patsubst %, %.c, $(CLIENTS)) Makefile README



all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES) $(HEADERS)
	gcc -c -g $(FLAGS) $(SOURCES)

clean:
	rm -f $(EXEBIN) $(OBJECTS)

test: 
	./$(EXEBIN) $(TESTFILES)

check:
	valgrind --leak-check=full ./$(EXEBIN) 

submit: $(SUBMITFILES)
	submit $(CLASS) $(ASSIGNMENT) $(SUBMITFILES)

