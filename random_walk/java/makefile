JC = javac
JFLAGS = -g

#SOURCES = $(wildcard *.java)
SOURCES = Walker.java WalkerSelfAvoid.java WalkerTester.java
CLASSES = $(SOURCES:.java=.class)

all : $(CLASSES)

%.class : %.java
	$(JC) $(JFLAGS) $<

clean :
	rm $(CLASSES)
