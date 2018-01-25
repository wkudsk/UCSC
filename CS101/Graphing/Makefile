#Makefile copied from Lab1
graph.jar: graph.class LoadGraph.class InputLib.class IntList.java Organizer.java
	echo Main-class: graph > Manifest
	jar cvfm graph.jar Manifest graph.class LoadGraph.class InputLib.class IntList.java Organizer.class
	rm Manifest

graph.class LoadGraph.class InputLib.class IntList.class Organizer.class: graph.java LoadGraph.java InputLib.java IntList.java Organizer.java
	javac -Xlint *.java

clean:
	rm *.class
	rm *.jar
