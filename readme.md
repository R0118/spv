## Zadanie - szablon sparse_vector
Do zaimplementowania jest szablon tablicy rzadkiej, tzn. takiej, w której zdecydowana większość elementów ma wartości inne niż wartość domyślna. Żeby efektywnie wykorzystać pamięć w wektorze elements przechowujemy pary (indeks, wartość spod indeksu).\
Interfejs szablonu jest zdefiniowany w pliku sp_vector.h.\
Wyjątek stanowi klasa const_iterator, której minimalny interfejs należy zdefiniować i zaimplementować. Jako podpowiedź została podana implementacja operatora << dla sp_vector (w tej chwili w komentarzu). Poprawna kompilacja i wykonanie tego operatora oznaczają spore szanse na to, że implementacja klasy iteratora jest właściwa.\
Proszę dodać testy const_iterator i operatora <<. Mogą to być testy korzystające z biblioteki gtest (wtedy umieszczacie je w spv_test.cpp) lub wykonane "ręcznie" (umieszczacie je wtedy w spv_demo.cpp).\
Proszę zwrócić uwagę, że iterator przechodzi przez wszystkie elementy wektora rzadkiego. Zatem spodziewamy się, że następujący kod:\
sparse_vector<int> sp;\
std::cout << sp << '\n';\
wyświetli na konsoli:\
[0 0 0 0 0 0 0 0 0 0 ]