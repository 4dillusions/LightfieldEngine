#pragma once

#include <vector>
#include "SMGameComponent.h"
#include "SMSmartPtr.h"

namespace SMEngine { namespace Core
{
	/*
	Rendereléshez pointeres lightweight lista, ami támogatja a menet közbeni törlést.

	Deklaráció:
	SMGameComponentList list; //size auto
	SMGameComponentList list2(100); //size 100

	Bejáró/törlõ:
	Bejáró, csak kereséshez beszúrásnál:
	for (list.First(); list.IsDone(); list.Next())
	    list.Current()...

    Bejáró 2. automatikus bejárás frissítéshez:
	Update(double deltaTime);
	*/
	class SMGameComponentList
	{
	private:
		std::vector<SMGameComponent *> data;
		typedef std::vector<SMGameComponent *>::iterator iterator;
		iterator gcIterator;

	public:
		SMGameComponentList();
		SMGameComponentList(int size);

		~SMGameComponentList();

		void First();
		bool IsDone();
		void Next();
		SMGameComponent *Current();

		void Add(SMGameComponent *item);
		void Remove(SMGameComponent *item); //Csak a renderelés után használható!
		void Update(double deltaTime); //Firssítés és IsAlive = false elemek törlése menet közben (nem determinisztikus.
		void WriteReport(); //riport készítése
		void RemoveAll(); //Csak a renderelés után használható!
	};
};};
