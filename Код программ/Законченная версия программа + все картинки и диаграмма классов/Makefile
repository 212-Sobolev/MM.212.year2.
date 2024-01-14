all: prog

prog: main.o Hill.o my_ran.o Stoun.o Log.o Landscape.o boundary.o control.o Rover.o Point.o Rprocessor.o
	g++ main.o Hill.o my_ran.o Stoun.o Log.o Landscape.o boundary.o control.o Rover.o Point.o Rprocessor.o -o prog

main.o: main.cpp
	g++ -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wno-long-long -Wcast-align -Winline -pedantic -pedantic-errors  -Wmissing-declarations -Wuninitialized -fPIC -c main.cpp

Hill.o: Hill.cpp
	g++ -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wno-long-long -Wcast-align -Winline -pedantic -pedantic-errors  -Wmissing-declarations -Wuninitialized -fPIC -c Hill.cpp

my_ran.o: my_ran.cpp
	g++ -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wno-long-long -Wcast-align -Winline -pedantic -pedantic-errors  -Wmissing-declarations -Wuninitialized -fPIC -c my_ran.cpp

Stoun.o: Stoun.cpp
	g++ -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wno-long-long -Wcast-align -Winline -pedantic -pedantic-errors  -Wmissing-declarations -Wuninitialized -fPIC -c Stoun.cpp

Log.o: Log.cpp
	g++ -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wno-long-long -Wcast-align -Winline -pedantic -pedantic-errors  -Wmissing-declarations -Wuninitialized -fPIC -c Log.cpp

Landscape.o: Landscape.cpp
	g++ -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wno-long-long -Wcast-align -Winline -pedantic -pedantic-errors  -Wmissing-declarations -Wuninitialized -fPIC -c Landscape.cpp

boundary.o: boundary.cpp
	g++ -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wno-long-long -Wcast-align -Winline -pedantic -pedantic-errors  -Wmissing-declarations -Wuninitialized -fPIC -c boundary.cpp

control.o: control.cpp
	g++ -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wno-long-long -Wcast-align -Winline -pedantic -pedantic-errors  -Wmissing-declarations -Wuninitialized -fPIC -c control.cpp

Rover.o: Rover.cpp
	g++ -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wno-long-long -Wcast-align -Winline -pedantic -pedantic-errors  -Wmissing-declarations -Wuninitialized -fPIC -c Rover.cpp

Point.o: Point.cpp
	g++ -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wno-long-long -Wcast-align -Winline -pedantic -pedantic-errors  -Wmissing-declarations -Wuninitialized -fPIC -c Point.cpp

Rprocessor.o: Rprocessor.cpp
	g++ -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wno-long-long -Wcast-align -Winline -pedantic -pedantic-errors  -Wmissing-declarations -Wuninitialized -fPIC -c Rprocessor.cpp

clean:
	del *.o $(prog)
