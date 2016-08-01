# 
# Name:			Cecilia Condes
# ID:			ccondes
# Class:		12M
# Date:			5.22.15
# Filename:		Makefile
# Description:	Makefile for lab7
#

JAVAC      = javac 
MAINCLASS  = DictionaryClient
JAVASRC    = $(wildcard *.java)
SOURCES    = $(JAVASRC) Makefile README
CLASSES    = $(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES = $(patsubst %.class, %*.class, $(CLASSES))
JARFILE    = $(MAINCLASS) 
ASSIGNMENT	= lab7
SUBMIT		= submit cmps012b-pt.s15 $(ASSIGNMENT)


all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(JARCLASSES)
	chmod +x $(JARFILE)
	rm Manifest

%.class: %.java
	$(JAVAC) $<

test: $(JARFILE)
	./$(JARFILE)

clean:
	rm -f *.class $(JARFILE)

submit: 
	$(SUBMIT) $(SOURCES)



