#include "csapp.h"
int cache_cnt = 0;

unsigned hash(char *s);
struct nlist *find(char *s);
char *hashstrdup(char *s);  // strdup 라는 이름은 사용할 수 없음(string.h에 이미 정의됨)
struct nlist *insert(char *name, char *defn);


/* 해시테이블  https://stackoverflow.com/questions/21850356/error-conflicting-types-for-strdup */
struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};

#define HASHSIZE 1049000
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* find: look for s in hashtab */
struct nlist *find(char *s)
{
    printf("looking for %s\n", s);
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
        {
          printf("[find func]cache hit!!!!!");
          return np; /* found */
        }
    return NULL; /* not found */
}

/* insert: put (name, defn) in hashtab */
struct nlist *insert(char *name, char *defn)
{
    printf("inserting name=%s defn=%s\n", name, defn);
    struct nlist *np;
    unsigned hashval;
    if ((np = find(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = hashstrdup(name)) == NULL)
          return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
        cache_cnt++;
    } else /* already there */
        free((void *) np->defn); /*free previous defn */
    if ((np->defn = hashstrdup(defn)) == NULL)
       return NULL;
    return np;
}

char *hashstrdup(char *s) /* make a duplicate of s */
{
    char *p;
    p = (char *) malloc(strlen(s)+1); /* +1 for ’\0’ */
    if (p != NULL)
       strcpy(p, s);
    return p;
}