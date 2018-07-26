#ifndef _SEQLIST_H
#define _SEQLIST_H

const int defaultSize=10;
template <typename T> class seqList
{
public:
	seqList(int size=defaultSize)
	{
		if (size > 0)
		{
			maxSize = size;
			element = new T[maxSize];
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
	T* element;
	int maxSize;
	int length;
};

template <typename T> bool seqList<T>::insertElement(T newElement)
{
	if (length >= maxSize) return false;
	else
	{
		element[length] = newElement;
		length++;
		return true;
	}
}
template <typename T> bool seqList<T>::deleteElement(int loc)
{	
	if(loc < 0 || loc >= length) return false;
	else
	{
		for (int i = loc; i < length; ++i)
		{
			element[i] = element[i+1];

		}
		length--;
		return true;
	}
}
template <typename T> T seqList<T>::getElement(int loc)
{
	if(loc < 0 || loc >= length) return false;
	else return element[loc];
}
template <typename T> bool seqList<T>::changeElement(int loc , T newElement)
{
	if (loc < 0 || loc >= length) return false;
	else
	{
		element[loc] = newElement;
		return true;
	}
}

#endif