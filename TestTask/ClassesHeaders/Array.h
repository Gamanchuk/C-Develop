#ifndef ARRAY_H
#define ARRAY_H

// массив
template <class type> class Array
{
	// переменные
protected:
	type* _arrayData;                                                           // указатель на массив
	int  _arrayLength;                                                          // количество объектов

	// конструкторы и деструктор
public:
	Array();																	// конструктор по умолчанию
	Array(const Array& aArray);													// конструктор копирования
	virtual ~Array();															 // деструктор

	// методы объекта класса
public:
	virtual int GetCount() const;                                               // получение количества объектов

	virtual bool Add();                                                         // добавление одного объекта
	virtual bool Insert(int uObjectIndex);                                      // вставка одного объекта
	virtual bool Delete(int uObjectIndex);                                      // удаление одного объекта
	virtual void Clear();                                                       // очистка

	// операторы
public:
	virtual Array <type>& operator =(const Array<type>& aArray);				// перегруженный оператор присваивания
	virtual type& operator [](int iPositionition);                                   // перегруженный оператор индексирования

	// методы класса
public:
	static bool Copy(Array<type>& aResultArray, const Array<type>& aArray);		// копирование массива
};

//---------------------------------------------
// конструкторы и деструктор

// конструктор по умолчанию
template <class type>
Array <type>::Array()
{
	_arrayData = 0; // указатель на массив
	_arrayLength = 0;    // количество элементов
}

// конструктор копирования
template <class type>
Array <type>::Array(const Array<type>& aArray)
{
	// инициализация переменных
	_arrayData = 0; // указатель на массив
	_arrayLength = 0;    // количество элементов

	// копирование массива
	Array<type>::Copy(*this, aArray);
}

// деструктор
template <class type>
Array <type>::~Array()
{
	Clear(); // очистка
}

//---------------------------------------------
// методы объекта класса

// получение количества объектов
template <class type>
int Array <type>::GetCount() const
{
	return _arrayLength;
}

// добавление одного объекта
template <class type>
bool Array <type>::Add()
{
	// выделение памяти
	type* newData = new type[_arrayLength + 1]();
	if (newData == 0)
		return false;

	// копирование данных из старого массива
	if (_arrayData)
	{
		for (int i = 0; i<_arrayLength; ++i)
			newData[i] = _arrayData[i];
		delete[] _arrayData; // очистка памяти из-под старого массива
	}

	_arrayData = newData; // перенаправление указателя
	++_arrayLength; // инкремент количества

	// успешное выполнение
	return true;
}


// вставка одного объекта
template <class type>
bool Array <type>::Insert(int uObjectIndex)
{
	// проверка на добавление в конец
	if (uObjectIndex >= _arrayLength)
		return Add(); // добавление в конец

	// выделение памяти
	type* newData = new type[_arrayLength + 1]();
	if (newData == 0)
		return false;

	// копирование данных из старого массива
	if (_arrayData)
	{
		// копирование данных, которые расположены до индекса вставляемого объекта
		for (int i = 0; i<uObjectIndex; ++i)
			newData[i] = _arrayData[i];

		// копирование данных, которые расположены после индекса вставляемого объекта
		int newLength = _arrayLength + 1;
		for (int i = uObjectIndex + 1; i<newLength; ++i)
			newData[i] = _arrayData[i - 1];

		delete[] _arrayData; // очистка памяти из-под старого массива
		_arrayData = newData; // перенаправление указателя
		_arrayLength = newLength; // инкремент количества
	}
	else
		return false;

	// успешное выполнение
	return true;
}



// удаление одного объекта
template <class type>
bool Array <type>::Delete(int uObjectIndex)
{
	// проверка на наличие ошибок
	if (uObjectIndex >= _arrayLength)
		return false;

	if (_arrayLength == 1)
	{
		Clear(); // удаление всего массива
		return true;
	}

	// выделение памяти
	type* newData = new type[_arrayLength - 1]();
	if (newData == 0)
		return false;

	// копирование данных из старого массива
	if (_arrayData)
	{
		// копирование данных, которые расположены до индекса вставляемого элемента
		for (int i = 0, j = 0; i<_arrayLength; ++i, ++j)
		{
			if (i == uObjectIndex) // пропуск удаляемого элемента
			{
				--j;
				continue;
			}
			newData[j] = _arrayData[i];
		}

		delete[] _arrayData; // очистка памяти из-под старого массива
		_arrayData = newData; // перенаправление указателя
		--_arrayLength; // декремент количества
	}
	else
		return false;

	// успешное выполнение
	return true;
}

// очистка
template <class type>
void Array <type>::Clear()
{
	// очистка выделенной памяти
	if (_arrayData)
		delete[] _arrayData;

	// очистка переменных
	_arrayData = 0; // указатель на массив
	_arrayLength = 0;    // количество элементов
}

//---------------------------------------------
// операторы

// перегруженный оператор присваивания
template <class type>
Array <type>& Array <type>::operator =(const Array<type>& aArray)
{
	// копирование массива
	Array<type>::Copy(*this, aArray);

	// возврат списка
	return *this;
}

// перегруженный оператор индексирования
template <class type>
type& Array <type>::operator [](int iPositionition)
{
	return _arrayData[iPositionition]; // возврат конкретного элемента
}

//---------------------------------------------
// методы класса

// копирование массива
template <class type>
bool Array <type>::Copy(Array<type>& aResultArray, const Array<type>& aArray)
{
	// корректировка ввода
	if (&aResultArray == &aArray)
		return true;

	// очистка массива
	aResultArray.Clear();

	// проверка количества элементов массива
	if (aArray._arrayLength == 0)
		return true;

	// выделение памяти
	aResultArray._arrayData = new type[aArray._arrayLength]();
	if (!aResultArray._arrayData)
		return false;

	// копирование массива
	for (int i = 0; i<aArray._arrayLength; ++i)
		aResultArray._arrayData[i] = aArray._arrayData[i];

	// копирование количества
	aResultArray._arrayLength = aArray._arrayLength;

	// успешное выполнение
	return true;
}

#endif // #ifndef ARRAY_H
