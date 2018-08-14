#ifndef _SEQLIST_H
#define _SEQLIST_H


template <typename T, int defaultSize=10> class seqList
{
public:
	explicit seqList(int size = 10)
	{
		if (size > 0)
		{
			maxSize = size;
			element = new T[maxSize];
			length = 0;
		}
	}
	~seqList()
	{
		delete[] element;
	}

	bool insertElement(T newData);
	bool deleteElement(int loc);
	T getElement(int loc);
	bool changeElement(int loc , T newData);

private:
	seqList<T,defaultSize>(const seqList<T,defaultSize>&);
	seqList<T,defaultSize>& operator=(const seqList<T,defaultSize>&);
	T* element;
	int maxSize;
	int length;
};

template <typename T, int defaultSize> bool seqList<T,defaultSize>::insertElement(T newElement)
{
	if (length >= maxSize) return false;
	else
	{
		element[length] = newElement;
		length++;
		return true;
	}
}

template <typename T, int defaultSize> bool seqList<T,defaultSize>::deleteElement(int loc)
{
	if (loc < 0 || loc >= length) return false;
	else
	{
		for (int i = loc; i < length; ++i)
		{
			element[i] = element[i + 1];

		}
		length--;
		return true;
	}
}

template <typename T, int defaultSize> T seqList<T,defaultSize>::getElement(int loc)
{
	if (loc < 0 || loc >= length) return false;
	else return element[loc];
}

template <typename T, int defaultSize> bool seqList<T,defaultSize>::changeElement(int loc , T newElement)
{
	if (loc < 0 || loc >= length) return false;
	else
	{
		element[loc] = newElement;
		return true;
	}
}

#endif // end of _SEQLIST_H
