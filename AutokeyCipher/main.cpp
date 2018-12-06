#include<iostream>
#include<string>
using namespace std;

#define A 65
#define TABLE_WIDTH 26

int initTable(char table[TABLE_WIDTH][TABLE_WIDTH]);
void copy(char *dest, char *src, int len);


int encrypt(char* key, char* src, char* dest)
{
	char table[TABLE_WIDTH][TABLE_WIDTH];
	char *pSrc = src;
	char *pKey = key;
	char *pDest = dest;

	initTable(table);

	do {
		if (!isalpha(*pSrc))
		{
			continue;
		}
		*pDest++ = table[toupper(*pKey) - A][toupper(*pSrc) - A];

		if (!(*(++pKey)))
			pKey = key;
	} while (*pSrc++);

	dest[strlen(src)] = 0;
	return 1;
}


int decrypt(char* key, char* src, char* dest)
{
	char *pSrc = src;
	char *pKey = key;
	char *pDest = dest;
	char offset;

	do {
		offset = (*pSrc) - toupper(*pKey);
		offset = offset >= 0 ? offset : offset + TABLE_WIDTH;
		*pDest++ = A + offset;

		if (!(*(++pKey)))
			pKey = key;
	} while (*pSrc++);

	dest[strlen(src)] = 0;
	return 1;
}

void getKey(char *key, char *text, char *keyword)
{
	int total = strlen(text);
	int len = strlen(keyword);

	if (len)
	{
		copy(key, keyword, len);
	}

	copy(key + len, text, total - len);
}

void copy(char *dest, char *src, int len)
{
	while (len-- > 0)
	{
		if (isalpha(*src))
		{
			*dest++ = toupper(*src);
		}

		src++;
	}
}

int main()
{
	
	char text[256] = "THIS IS A SECRET TEXT";
	char key[256] = "";
	char keyword[256] = "KEY";

	char ciphertext[256];
	char output[256];

	
	getKey(key, text, keyword);
	cout << "Key\n" << key;

	
	encrypt(key, text, ciphertext);
	cout << "Ciphertext\n" << ciphertext;

	
	decrypt(key, ciphertext, output);
	cout << "Decrypt\n" << output;
	system("PAUSE");
	return 0;
}


int initTable(char table[TABLE_WIDTH][TABLE_WIDTH])
{
	int i, j;
	for (i = 0; i < TABLE_WIDTH; i++) {
		for (j = 0; j < TABLE_WIDTH; j++) {
			table[i][j] = A + (i + j) % TABLE_WIDTH;
		}
	}
	return 1;
}