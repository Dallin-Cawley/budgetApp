a.out: budget.o recipe.o ingredient.o insertionSort.o stringManip.o category.o
	g++ *.o -g

budget.o: *.cpp *.h
	g++ -c budget.cpp -g

category.o: category.h category.cpp
	g++ -c category.cpp -g

ingredient.o: ingredient.h ingredient.cpp
	g++ -c ingredient.cpp -g

recipe.o: recipe.h recipe.cpp stringManip.cpp ingredient.h ingredient.cpp
	g++ -c recipe.cpp -g

insertionSort.o: ../sorts/InsertionSort/insertionSort.h ../sorts/InsertionSort/insertionSort.cpp
	g++ -c ../sorts/InsertionSort/insertionSort.cpp -g

stringManip.o: stringManip.h stringManip.cpp
	g++ -c stringManip.cpp -g

clean: 
	rm a.out *.o
