#ifndef ARRAY_H
#define ARRAY_H

// ������
template <class type> class Array
{
	// ����������
protected:
	type* _arrayData;                                                           // ��������� �� ������
	int  _arrayLength;                                                          // ���������� ��������

	// ������������ � ����������
public:
	Array();																	// ����������� �� ���������
	Array(const Array& aArray);													// ����������� �����������
	virtual ~Array();															 // ����������

	// ������ ������� ������
public:
	virtual int GetCount() const;                                               // ��������� ���������� ��������

	virtual bool Add();                                                         // ���������� ������ �������
	virtual bool Insert(int uObjectIndex);                                      // ������� ������ �������
	virtual bool Delete(int uObjectIndex);                                      // �������� ������ �������
	virtual void Clear();                                                       // �������

	// ���������
public:
	virtual Array <type>& operator =(const Array<type>& aArray);				// ������������� �������� ������������
	virtual type& operator [](int iPositionition);                                   // ������������� �������� ��������������

	// ������ ������
public:
	static bool Copy(Array<type>& aResultArray, const Array<type>& aArray);		// ����������� �������
};

//---------------------------------------------
// ������������ � ����������

// ����������� �� ���������
template <class type>
Array <type>::Array()
{
	_arrayData = 0; // ��������� �� ������
	_arrayLength = 0;    // ���������� ���������
}

// ����������� �����������
template <class type>
Array <type>::Array(const Array<type>& aArray)
{
	// ������������� ����������
	_arrayData = 0; // ��������� �� ������
	_arrayLength = 0;    // ���������� ���������

	// ����������� �������
	Array<type>::Copy(*this, aArray);
}

// ����������
template <class type>
Array <type>::~Array()
{
	Clear(); // �������
}

//---------------------------------------------
// ������ ������� ������

// ��������� ���������� ��������
template <class type>
int Array <type>::GetCount() const
{
	return _arrayLength;
}

// ���������� ������ �������
template <class type>
bool Array <type>::Add()
{
	// ��������� ������
	type* newData = new type[_arrayLength + 1]();
	if (newData == 0)
		return false;

	// ����������� ������ �� ������� �������
	if (_arrayData)
	{
		for (int i = 0; i<_arrayLength; ++i)
			newData[i] = _arrayData[i];
		delete[] _arrayData; // ������� ������ ��-��� ������� �������
	}

	_arrayData = newData; // ��������������� ���������
	++_arrayLength; // ��������� ����������

	// �������� ����������
	return true;
}


// ������� ������ �������
template <class type>
bool Array <type>::Insert(int uObjectIndex)
{
	// �������� �� ���������� � �����
	if (uObjectIndex >= _arrayLength)
		return Add(); // ���������� � �����

	// ��������� ������
	type* newData = new type[_arrayLength + 1]();
	if (newData == 0)
		return false;

	// ����������� ������ �� ������� �������
	if (_arrayData)
	{
		// ����������� ������, ������� ����������� �� ������� ������������ �������
		for (int i = 0; i<uObjectIndex; ++i)
			newData[i] = _arrayData[i];

		// ����������� ������, ������� ����������� ����� ������� ������������ �������
		int newLength = _arrayLength + 1;
		for (int i = uObjectIndex + 1; i<newLength; ++i)
			newData[i] = _arrayData[i - 1];

		delete[] _arrayData; // ������� ������ ��-��� ������� �������
		_arrayData = newData; // ��������������� ���������
		_arrayLength = newLength; // ��������� ����������
	}
	else
		return false;

	// �������� ����������
	return true;
}



// �������� ������ �������
template <class type>
bool Array <type>::Delete(int uObjectIndex)
{
	// �������� �� ������� ������
	if (uObjectIndex >= _arrayLength)
		return false;

	if (_arrayLength == 1)
	{
		Clear(); // �������� ����� �������
		return true;
	}

	// ��������� ������
	type* newData = new type[_arrayLength - 1]();
	if (newData == 0)
		return false;

	// ����������� ������ �� ������� �������
	if (_arrayData)
	{
		// ����������� ������, ������� ����������� �� ������� ������������ ��������
		for (int i = 0, j = 0; i<_arrayLength; ++i, ++j)
		{
			if (i == uObjectIndex) // ������� ���������� ��������
			{
				--j;
				continue;
			}
			newData[j] = _arrayData[i];
		}

		delete[] _arrayData; // ������� ������ ��-��� ������� �������
		_arrayData = newData; // ��������������� ���������
		--_arrayLength; // ��������� ����������
	}
	else
		return false;

	// �������� ����������
	return true;
}

// �������
template <class type>
void Array <type>::Clear()
{
	// ������� ���������� ������
	if (_arrayData)
		delete[] _arrayData;

	// ������� ����������
	_arrayData = 0; // ��������� �� ������
	_arrayLength = 0;    // ���������� ���������
}

//---------------------------------------------
// ���������

// ������������� �������� ������������
template <class type>
Array <type>& Array <type>::operator =(const Array<type>& aArray)
{
	// ����������� �������
	Array<type>::Copy(*this, aArray);

	// ������� ������
	return *this;
}

// ������������� �������� ��������������
template <class type>
type& Array <type>::operator [](int iPositionition)
{
	return _arrayData[iPositionition]; // ������� ����������� ��������
}

//---------------------------------------------
// ������ ������

// ����������� �������
template <class type>
bool Array <type>::Copy(Array<type>& aResultArray, const Array<type>& aArray)
{
	// ������������� �����
	if (&aResultArray == &aArray)
		return true;

	// ������� �������
	aResultArray.Clear();

	// �������� ���������� ��������� �������
	if (aArray._arrayLength == 0)
		return true;

	// ��������� ������
	aResultArray._arrayData = new type[aArray._arrayLength]();
	if (!aResultArray._arrayData)
		return false;

	// ����������� �������
	for (int i = 0; i<aArray._arrayLength; ++i)
		aResultArray._arrayData[i] = aArray._arrayData[i];

	// ����������� ����������
	aResultArray._arrayLength = aArray._arrayLength;

	// �������� ����������
	return true;
}

#endif // #ifndef ARRAY_H
