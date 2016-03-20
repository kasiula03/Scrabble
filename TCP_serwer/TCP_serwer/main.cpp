#include <iostream>
#include "Serwer.h"
#include <thread>
using namespace std;

int main()
{

	Serwer serwer;
	
	
	thread watekAkceptacji(std::ref(serwer), "d");
	thread watekWysylania(std::ref(serwer), "Wysylanie");
	
	watekWysylania.join();	//Przylaczenie do glownego watku (czekanie na zakonczenie)
	
	//watekAkceptacji.join();
	//watekAkceptacji.join();
	//thread watekWysylania2(serwer, "d");
	//system("pause");
	return 0;
}