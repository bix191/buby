
CXXFLAGS=-g

OBJS=main.o tokenreader.o  token.o syntaxparser.o

buby: ${OBJS}
	${CXX} -o $@ ${OBJS}

clean:
	rm -f ${OBJS}


