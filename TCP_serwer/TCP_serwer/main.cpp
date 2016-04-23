#include <iostream>
#include "Serwer.h"
#include <thread>
using namespace std;

int main()
{

	Serwer serwer;
	
	//thread watekOdbierania1(std::ref(serwer), "Odbieranie",0);
	//thread watekOdbierania2(std::ref(serwer), "Odbieranie", 1);
	//thread watekOdbierania3(std::ref(serwer), "Odbieranie", 2);
	//thread watekOdbierania4(std::ref(serwer), "Odbieranie", 3);
	thread watekAkceptacji(&Serwer::AcceptClient, &serwer);
	thread watekWysylania(&Serwer::Send,&serwer);
	watekAkceptacji.join();
	
	
	//watekWysylania.join();	//Przylaczenie do glownego watku (czekanie na zakonczenie)
	
	return 0;
}