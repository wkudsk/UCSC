#Makefile copied from Lab1
graph.jar: graph.class LoadGraph.class InputLib.class
	echo Main-class: graph > Manifest
	jar cvfm graph.jar Manifest graph.class LoadGraph.class InputLib.class
	rm Manifest

graph.class LoadGraph.class InputLib.class: graph.java LoadGraph.java InputLib.java
	javac -Xlint *.java

clean:
	rm *.class
	rm *.jar
