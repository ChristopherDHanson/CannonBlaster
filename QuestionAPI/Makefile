CFLAGS =
TESTFILE = ./testFile.csv

QuestionTest: QuestionAPI.cpp QuestionAPI.h QuestionTest.cpp
	g++ $(CFLAGS) -o QuestionTest QuestionTest.cpp QuestionAPI.cpp

clean:
	rm -rf ./QuestionTest

test:
	./QuestionTest $(TESTFILE)
