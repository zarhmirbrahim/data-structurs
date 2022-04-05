#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Element
{
	int donnee;
	struct Element *suivant;
} Element;

typedef struct List
{
	Element *debut;
	Element *fin;
	int taille;
} List;

//////////////////////////////////////////
void resetlist(List *l)
{
	l->debut = l->fin = NULL;
	l->taille = 0;
}

Element *newElement()
{
	Element *elm = (Element *)malloc(sizeof(Element));
	if (!elm)
	{
		printf("memoire echec");
		exit(1);
	}
	return elm;
}

//////////////////////////////////////////
void insertlistvide(List *l, int x)
{
	Element *elementadd = newElement();
	elementadd->donnee = x;
	elementadd->suivant = NULL;

	l->debut = l->fin = elementadd;
	l->taille++;
}
//////////////////////////////////////////
int lireN()
{
	int n;
	puts("enter your element");
	scanf("%d", &n);
	return n;
}
//////////////////////////////////////////

void printlist(List *l)
{
	Element *counter = l->debut;
	int i = 0;
	puts("-------------------------------------");
	while (counter != NULL)
	{
		printf("List[%d] = %d\n", i, counter->donnee);
		counter = counter->suivant;
		++i;
	}
	puts("-------------------------------------");
}
///////////////////////////////////////////
void insertlistdebut(List *l, int n)
{
	Element *elementadd = newElement();
	elementadd->donnee = n;
	elementadd->suivant = l->debut;
	l->debut = elementadd;
	l->taille++;
}

///////////////////////////////////////////
void insertlistfin(List *l, int n)
{
	Element *elementadd = newElement();
	elementadd->donnee = n;
	elementadd->suivant = NULL;

	l->fin->suivant = elementadd;
	l->fin = elementadd;
	l->taille++;
}

///////////////////////////////////////////
void insertlistafter(List *l, int n, int pos)
{
	Element *counter = l->debut;
	while (pos > 0 && counter != NULL)
	{
		counter = counter->suivant;
		--pos;
	}

	if (pos == 0)
	{
		if (counter != NULL)
		{
			Element *elementadd = newElement();
			elementadd->donnee = n;
			elementadd->suivant = counter->suivant;
			counter->suivant = elementadd;
			l->taille++;
		}
		else
			insertlistfin(l, n);
	}
}

//////////////////////////////////////////////
void deletebegin(List *l)
{
	Element *elementdelete = l->debut;
	if (l->debut == l->fin)
		l->debut = l->fin = NULL;
	else
		l->debut = elementdelete->suivant;

	l->taille--;
	free(elementdelete);
}

//////////////////////////////////////////////
void delete_after_n(List *l, int pos)
{

	{
		Element *counter = l->debut;
		while (pos-- > 0 && counter)
			counter = counter->suivant;

		if (counter)
		{
			Element *eldelete = counter->suivant;
			counter->suivant = eldelete->suivant;

			l->taille--;
			free(eldelete);
		}
	}
}

void delete_at_n(List *l, int n)
{
	delete_after_n(l, n - 1);
}

//////////////////////////////////////////////

void finderase(List *l, int x)
{
	Element *el = l->debut;
	Element *precedent = el;

	int i = 0;
	while (el)
	{
		if (el->donnee == x)
		{
			if (i == 0)
				deletebegin(l);
			else
				delete_at_n(l, i);

			break;
		}
		precedent = el;
		el = el->suivant;
		i++;
	}
}

///////////////////////////////////////////////////////////////////
int sort_list_fn(const void *a, const void *b)
{
	return *(int *)a > *(int *)b;
}

void trieer_liste(List *l)
{
	int *elements = (int *)malloc(l->taille * sizeof(int));

	int n = 0;
	Element *el = l->debut;

	while (el)
	{
		elements[n] = el->donnee;
		el = el->suivant;
		++n;
	}

	qsort(elements, l->taille, sizeof(int), sort_list_fn);

	el = l->debut;
	n = 0;
	while (el)
	{
		el->donnee = elements[n];
		el = el->suivant;
		++n;
	}

	free(elements);
}

///////////////////////////////////////////////////////////////////////
void insert_trieer(List* l, int x)
{
	Element* el = l->debut;
	while (el)
	{
		if (el->donnee >= x)
		{
			Element *newel = newElement();

			newel->donnee = x;
			newel->suivant = el->suivant;
			el->suivant = newel;

			l->taille++;
			return;
		}
		el = el->suivant;
	}

	insertlistfin(l, x);
}


///////////////////////////////////////////////////////////////
void delete_list(List* l)
{
    Element* el=l->debut;
    while(el)
    {
        Element* tmp=el;
        el=el->suivant;
        free(tmp);
    }
	resetlist(l);
}


int main()
{
	List l;
	resetlist(&l);

	insertlistvide(&l, lireN());
	insertlistdebut(&l, lireN());
	insertlistfin(&l, lireN());

	/*
	puts("Entrez position");
	int pos;
	scanf("%d", &pos);
	insertlistafter(&l, lireN(), pos);
	printlist(&l);
	deletebegin(&l);
	printlist(&l);

	printf("HiH\n");

	trieer_liste(&l);
	printlist(&l);

	finderase(&l, lireN());
	printlist(&l);
	*/
}
