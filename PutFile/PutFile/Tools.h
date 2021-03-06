__int64 s2i64(char *line);
__int64 s2i64_x(char *line);
int s2i(char *line);
int s2i_x(char *line);

char *incrementColumnDigits(char *column, char *digits);
char *incrementPathDigits(char *path, char *digits);
char *incrementPath(char *path);
char *toCreatablePath(char *path, int faultCountMax = 1000);

char *getDateTimeStamp(time_t t);
char *thousandComma(char *line);
char *makeJStamp(char *eStamp);
char *makeJStamp_x(char *eStamp);

template <class Element_t>
int getIndex(autoList<Element_t> *list, Element_t e, int (*compFunc)(Element_t, Element_t))
{
	for(int index = 0; index < list->GetCount(); index++)
		if(!compFunc(e, list->GetElement(index)))
			return index;

	return -1; // not found
}

template <class Element_t>
void Shuffle(autoList<Element_t> *list)
{
	for(int index = list->GetCount() - 1; 1 <= index; index--)
		list->Swap(index, getCrypto32() % (index + 1));
}
