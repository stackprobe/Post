template <class Element_t>
class autoList
{
private:
	int Count;
	int ListSize;
	Element_t *List;

public:
	autoList()
	{
		this->Count = 0;
		this->ListSize = 0;
		this->List = (Element_t *)memAlloc(0);
	}
	autoList(int buffer_size)
	{
		errorCase(buffer_size < 0 || INT_MAX / sizeof(Element_t) < buffer_size);

		this->Count = 0;
		this->ListSize = buffer_size;
		this->List = (Element_t *)memAlloc(buffer_size * sizeof(Element_t));
	}
	autoList(const autoList &source)
	{
		error();
	}
	~autoList()
	{
		memFree(this->List);
	}

	Element_t *UnbindBuffer()
	{
		Element_t *list_ret = this->List;

		this->Count = 0;
		this->ListSize = 0;
		this->List = (Element_t *)memAlloc(0);

		return list_ret;
	}

	void Clear()
	{
		this->Count = 0;
	}
	int GetCount()
	{
		return this->Count;
	}

	Element_t GetElement(int index)
	{
		errorCase(index < 0 || this->Count <= index);

		return this->List[index];
	}
	Element_t GetLastElement()
	{
		return this->GetElement(this->Count - 1);
	}
	Element_t *ElementAt(int index)
	{
		if(index == 0)
			return this->List;

		errorCase(index < 0 || this->Count <= index);

		return this->List + index;
	}

	void AddElement(Element_t element)
	{
		if(this->ListSize <= this->Count)
		{
			errorCase((INT_MAX / sizeof(Element_t)) / 2 < this->ListSize);

			if(this->ListSize < 16)
				this->ListSize += 2;
			else
				this->ListSize += this->ListSize / 2; // *= 1.5

			this->List = (Element_t *)memRealloc(this->List, this->ListSize * sizeof(Element_t));
		}
		this->List[this->Count] = element;
		this->Count++;
	}
	Element_t UnaddElement()
	{
		errorCase(this->Count < 1);

		this->Count--;
		return this->List[this->Count];
	}

	void AddElements(Element_t *list, int count)
	{
		if(this->Count + count <= this->ListSize) // fast mode
		{
			memcpy(this->List + this->Count, list, count * sizeof(Element_t));
			this->Count += count;
			return;
		}
		for(int index = 0; index < count; index++)
		{
			this->AddElement(list[index]);
		}
	}
};
