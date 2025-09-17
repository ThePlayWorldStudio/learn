javac -cp "usr/share/java/testng.jar"  src/*.java -d bin/
jar cvfm prog.jar manifest.mf -C bin .
