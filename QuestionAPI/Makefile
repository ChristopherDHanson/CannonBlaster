CFLAGS =
TESTFILE = ./testFile.csv

libQuestionAPI.a: QuestionAPI.o
	ar rvs libQuestionAPI.a QuestionAPI.o

QuestionAPI.o: QuestionAPI.cpp QuestionAPI.h
	g++ -c QuestionAPI.cpp

QuestionTest: QuestionAPI.cpp QuestionAPI.h QuestionTest.cpp
	g++ $(CFLAGS) -o QuestionTest QuestionTest.cpp QuestionAPI.cpp

clean:
	rm -rf ./QuestionTest ./libQuestionAPI.a ./QuestionAPI.o

test:
	./QuestionTest $(TESTFILE)
