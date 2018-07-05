#pragma once

namespace SMEngine { namespace Core
{
	/*
	2D-s tömb, ami a C-s tömb muveleteket is támogatja.
	Objektumokat kell benne tárolni, vagy SmartPtr-t.

	Deklaráció:
	SMArray2D<int> array(2, 3);

	Bejáró:
	for(int x = 0; x < array.LenghtX(); ++x)
        for(int y = 0; y < array.LenghtY(); ++y)
            array(x, y)...

    SmartPtr-el:
    SMArray2D<SMSmartPtr<Test> > array(2, 3);

    for(int x = 0; x < array.LenghtX(); ++x)
        for(int y = 0; y < array.LenghtY(); ++y)
            array(x, y) = SMSmartPtr<Test>(new Test(x + y));

    for(int x = 0; x < arrayTest.LenghtX(); ++x)
        for(int y = 0; y < arrayTest.LenghtY(); ++y)
            array(x, y)->...
	*/
	template <typename T> class SMArray2D
	{
	private:
		T **data;
		int sizeX, sizeY;

	public:
		SMArray2D(int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeY)
		{
			data = new T *[sizeX];

			for (int x = 0; x < sizeX; ++x)
				data[x] = new T[sizeY];
		}

		~SMArray2D()
		{
			for (int x = 0; x < sizeX; ++x)
				delete []data[x];

			delete []data;

			sizeX = sizeY = 0;
		}

		int LenghtX() const
		{
			return sizeX;
		}

		int LenghtY() const
		{
			return sizeY;
		}

		//int a = array(0, 0);
		T operator() (int indexX, int indexY) const
		{
			return data[indexX][indexY];
		}

		//array(0, 0) = 22;
		T &operator() (int indexX, int indexY)
		{
			return data[indexX][indexY];
		}

		void SetAll(T value)
		{
			for (int x = 0; x < sizeX; ++x)
				for (int y = 0; y < sizeY; ++y)
					data[x][y] = value;
		}

		//C-s tömb kinullázása: SMArray2D<int>::Zero(0, &array[0][0], 3, 2);
		static void SetAll(T value, T *array, int sizeX, int sizeY)
		{
			for (int i = 0; i < sizeX * sizeY; ++i)
				array[i] = value;
		}

		//Másolás ebbe a tömbbe másik SMArray-bol
		void Copy(const SMArray2D &array)
		{
			for (int x = 0; x < sizeX; ++x)
				for (int y = 0; y < sizeY; ++y)
					data[x][y] = array(x, y);
		}

		//Másolás C-s tömbbol egy másik C-s tömbbe: SMArray2D<int>::Zero(&array[0][0], &array2[0][0], 3, 2);
		static void Copy(T *source, T *target, int sizeX, int sizeY)
		{
			for (int i = 0; i < sizeX * sizeY; ++i)
				target[i] = source[i];
		}
	};
};};
