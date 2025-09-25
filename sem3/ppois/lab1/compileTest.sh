javac -cp "src/libs/junit4.jar"  src/*.java -d bin/
jar cvfm prog.jar manifest.mf -C bin .
