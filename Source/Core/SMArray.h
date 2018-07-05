#pragma once

namespace SMEngine { namespace Core
{
	/*
	1D-s t�mb, ami a C-s t�mb muveleteket is t�mogatja
	Objektumokat kell benne t�rolni, vagy SmartPtr-t

	Deklar�ci�:
	SMArray<int> array(10);

	Bej�r�:
	for (int i = 0; i < array.Lenght(); ++i)
		array[i]...

    SmartPtr-el:
    SMArray<SMSmartPtr<Test> > array(3);
    array[0] = SMSmartPtr<Test>(new Test(1));
    array[1] = SMSmartPtr<Test>(new Test(2));
    array[2] = SMSmartPtr<Test>(new Test(3));

    for (int i = 0; i < array.Lenght(); ++i)
		array[i]->...
	*/
	template <typename T> class SMArray
	{
	private:
		T *data;
		int size;

	public:
		SMArray(int size) : size(size)
		{
			data = new T[size];
		}

		~SMArray()
		{
		    delete []data;
		    size = 0;
		}

		int Lenght() const
		{
			return size;
		}

		//int a = array[0];
		T operator[] (int index) const
		{
			return data[index];
		}

		//array[0] = 22;
		T &operator[] (int index)
		{
			return data[index];
		}

		void SetAll(T value)
		{
			for (int i = 0; i < size; ++i)
				data[i] = value;
		}

		//C-s t�mb kinull�z�sa: SMArray2D<int>::Zero(0, &array[0], 3);
		static void SetAll(T value, T *array, int size)
		{
			for (int i = 0; i < size; ++i)
				array[i] = value;
		}

		//M�sol�s ebbe a t�mbbe m�sik SMArray-bol
		void Copy(const SMArray &array)
		{
			for (int i = 0; i < size; ++i)
				data[i] = array[i];
		}

		//M�sol�s C-s t�mbbol egy m�sik C-s t�mbbe
		static void Copy(T *source, T *target, int size)
		{
			for (int i = 0; i < size; ++i)
				target[i] = source[i];
		}
	};
};};
