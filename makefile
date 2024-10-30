processor : SPU.o SPU_function.o stack_function.o
	g++ SPU.o SPU_function.o stack_function.o -o result_processor

assembler : assembler.o
	g++ assembler.o -o result_assembler

assembler.o : assembler.cpp
	g++ -c assembler.cpp

SPU.o : SPU.cpp
	g++ -c SPU.cpp

SPU_function.o : SPU_function.cpp SPU_function.h
	g++ -c SPU_function.cpp

stack_function.o : stack_function.cpp stack_function.h
	g++ -c stack_function.cpp

clean_processor:
	del SPU.o SPU_function.o stack_function.o result_processor.exe

clean_assembler:
	del assembler.o  result_assembler.exe assembler.exe