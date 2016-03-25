#include <iostream>
#include "Serwer.h"
#include <thread>
using namespace std;

int main()
{

	Serwer serwer;
	
	thread watekAkceptacji(std::ref(serwer), "Akceptacja");
	thread watekWysylania(std::ref(serwer), "Wysylanie");
	
	watekWysylania.join();	//Przylaczenie do glownego watku (czekanie na zakonczenie)
	
	return 0;
}