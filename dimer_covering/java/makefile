JC = javac
JFLAGS = -g

SOURCES = $(wildcard *.java)
CLASSES = $(SOURCES:.java=.class)
PACKAGES = dimers

all : $(CLASSES)

%.class : %.java
	$(JC) $(JFLAGS) $<

clean :
	rm $(CLASSES) $(PACKAGES)/*.class
