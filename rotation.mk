# to run this file:
# $ make -f clock.mk
# $ make -f clock.mk clean

FLAGS = -c -std=c++11

rotation-app : base.o reference_frame.o rotation.o
	g++ base.o reference_frame.o rotation.o -o rotation-app -lsfml-graphics -lsfml-window -lsfml-system

base.o : base.cpp
	g++ ${FLAGS} base.cpp

reference_frame.o : reference_frame.cpp
	g++ ${FLAGS} reference_frame.cpp

#vector_class.o : vector_class.cpp
#	g++ ${FLAGS} vector_class.cpp

rotation.o : rotation.cpp
	g++ ${FLAGS} rotation.cpp

clean :
	rm -f *~ rotation.o vector_class.o reference_frame.o base.o