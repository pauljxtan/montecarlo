JC = javac
JFLAGS = -g

SOURCES = $(wildcard *.java) $(wildcard dimers/*.java)
CLASSES = $(SOURCES:.java=.class)

all : $(CLASSES)

%.class : %.java
	$(JC) $(JFLAGS) $<

clean :
	rm $(CLASSES)
