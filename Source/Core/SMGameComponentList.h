#pragma once

#include <vector>
#include "SMGameComponent.h"
#include "SMSmartPtr.h"

namespace SMEngine { namespace Core
{
	/*
	Renderel�shez pointeres lightweight lista, ami t�mogatja a menet k�zbeni t�rl�st.

	Deklar�ci�:
	SMGameComponentList list; //size auto
	SMGameComponentList list2(100); //size 100

	Bej�r�/t�rl�:
	Bej�r�, csak keres�shez besz�r�sn�l:
	for (list.First(); list.IsDone(); list.Next())
	    list.Current()...

    Bej�r� 2. automatikus bej�r�s friss�t�shez:
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
		void Remove(SMGameComponent *item); //Csak a renderel�s ut�n haszn�lhat�!
		void Update(double deltaTime); //Firss�t�s �s IsAlive = false elemek t�rl�se menet k�zben (nem determinisztikus.
		void WriteReport(); //riport k�sz�t�se
		void RemoveAll(); //Csak a renderel�s ut�n haszn�lhat�!
	};
};};
