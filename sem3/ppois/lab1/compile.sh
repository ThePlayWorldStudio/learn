javac src/*.java -d bin/
jar cvfm prog.jar manifest.mf -C bin .
