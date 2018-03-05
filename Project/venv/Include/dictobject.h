<<<<<<< Updated upstream
#ifndef Py_DICTOBJECT_H
#define Py_DICTOBJECT_H
#ifdef __cplusplus
extern "C" {
#endif


/* Dictionary object type -- mapping from hashable object to object */

/* The distribution includes a separate file, Objects/dictnotes.txt,
   describing explorations into dictionary design and optimization.
   It covers typical dictionary use patterns, the parameters for
   tuning dictionaries, and several ideas for possible optimizations.
*/

#ifndef Py_LIMITED_API

typedef struct _dictkeysobject PyDictKeysObject;

/* The ma_values pointer is NULL for a combined table
 * or points to an array of PyObject* for a split table
 */
typedef struct {
    PyObject_HEAD

    /* Number of items in the dictionary */
    Py_ssize_t ma_used;

    /* Dictionary version: globally unique, value change each time
       the dictionary is modified */
    uint64_t ma_version_tag;

    PyDictKeysObject *ma_keys;

    /* If ma_values is NULL, the table is "combined": keys and values
       are stored in ma_keys.

       If ma_values is not NULL, the table is splitted:
       keys are stored in ma_keys and values are stored in ma_values */
    PyObject **ma_values;
} PyDictObject;

typedef struct {
    PyObject_HEAD
    PyDictObject *dv_dict;
} _PyDictViewObject;

#endif /* Py_LIMITED_API */

PyAPI_DATA(PyTypeObject) PyDict_Type;
PyAPI_DATA(PyTypeObject) PyDictIterKey_Type;
PyAPI_DATA(PyTypeObject) PyDictIterValue_Type;
PyAPI_DATA(PyTypeObject) PyDictIterItem_Type;
PyAPI_DATA(PyTypeObject) PyDictKeys_Type;
PyAPI_DATA(PyTypeObject) PyDictItems_Type;
PyAPI_DATA(PyTypeObject) PyDictValues_Type;

#define PyDict_Check(op) \
                 PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_DICT_SUBCLASS)
#define PyDict_CheckExact(op) (Py_TYPE(op) == &PyDict_Type)
#define PyDictKeys_Check(op) PyObject_TypeCheck(op, &PyDictKeys_Type)
#define PyDictItems_Check(op) PyObject_TypeCheck(op, &PyDictItems_Type)
#define PyDictValues_Check(op) PyObject_TypeCheck(op, &PyDictValues_Type)
/* This excludes Values, since they are not sets. */
# define PyDictViewSet_Check(op) \
    (PyDictKeys_Check(op) || PyDictItems_Check(op))


PyAPI_FUNC(PyObject *) PyDict_New(void);
PyAPI_FUNC(PyObject *) PyDict_GetItem(PyObject *mp, PyObject *key);
#ifndef Py_LIMITED_API
PyAPI_FUNC(PyObject *) _PyDict_GetItem_KnownHash(PyObject *mp, PyObject *key,
                                       Py_hash_t hash);
#endif
PyAPI_FUNC(PyObject *) PyDict_GetItemWithError(PyObject *mp, PyObject *key);
#ifndef Py_LIMITED_API
PyAPI_FUNC(PyObject *) _PyDict_GetItemIdWithError(PyObject *dp,
                                                  struct _Py_Identifier *key);
PyAPI_FUNC(PyObject *) PyDict_SetDefault(
    PyObject *mp, PyObject *key, PyObject *defaultobj);
#endif
PyAPI_FUNC(int) PyDict_SetItem(PyObject *mp, PyObject *key, PyObject *item);
#ifndef Py_LIMITED_API
PyAPI_FUNC(int) _PyDict_SetItem_KnownHash(PyObject *mp, PyObject *key,
                                          PyObject *item, Py_hash_t hash);
#endif
PyAPI_FUNC(int) PyDict_DelItem(PyObject *mp, PyObject *key);
#ifndef Py_LIMITED_API
PyAPI_FUNC(int) _PyDict_DelItem_KnownHash(PyObject *mp, PyObject *key,
                                          Py_hash_t hash);
PyAPI_FUNC(int) _PyDict_DelItemIf(PyObject *mp, PyObject *key,
                                  int (*predicate)(PyObject *value));
#endif
PyAPI_FUNC(void) PyDict_Clear(PyObject *mp);
PyAPI_FUNC(int) PyDict_Next(
    PyObject *mp, Py_ssize_t *pos, PyObject **key, PyObject **value);
#ifndef Py_LIMITED_API
PyDictKeysObject *_PyDict_NewKeysForClass(void);
PyAPI_FUNC(PyObject *) PyObject_GenericGetDict(PyObject *, void *);
PyAPI_FUNC(int) _PyDict_Next(
    PyObject *mp, Py_ssize_t *pos, PyObject **key, PyObject **value, Py_hash_t *hash);
PyObject *_PyDictView_New(PyObject *, PyTypeObject *);
#endif
PyAPI_FUNC(PyObject *) PyDict_Keys(PyObject *mp);
PyAPI_FUNC(PyObject *) PyDict_Values(PyObject *mp);
PyAPI_FUNC(PyObject *) PyDict_Items(PyObject *mp);
PyAPI_FUNC(Py_ssize_t) PyDict_Size(PyObject *mp);
PyAPI_FUNC(PyObject *) PyDict_Copy(PyObject *mp);
PyAPI_FUNC(int) PyDict_Contains(PyObject *mp, PyObject *key);
#ifndef Py_LIMITED_API
PyAPI_FUNC(int) _PyDict_Contains(PyObject *mp, PyObject *key, Py_hash_t hash);
PyAPI_FUNC(PyObject *) _PyDict_NewPresized(Py_ssize_t minused);
PyAPI_FUNC(void) _PyDict_MaybeUntrack(PyObject *mp);
PyAPI_FUNC(int) _PyDict_HasOnlyStringKeys(PyObject *mp);
Py_ssize_t _PyDict_KeysSize(PyDictKeysObject *keys);
Py_ssize_t _PyDict_SizeOf(PyDictObject *);
PyAPI_FUNC(PyObject *) _PyDict_Pop(PyObject *, PyObject *, PyObject *);
PyObject *_PyDict_Pop_KnownHash(PyObject *, PyObject *, Py_hash_t, PyObject *);
PyObject *_PyDict_FromKeys(PyObject *, PyObject *, PyObject *);
#define _PyDict_HasSplitTable(d) ((d)->ma_values != NULL)

PyAPI_FUNC(int) PyDict_ClearFreeList(void);
#endif

/* PyDict_Update(mp, other) is equivalent to PyDict_Merge(mp, other, 1). */
PyAPI_FUNC(int) PyDict_Update(PyObject *mp, PyObject *other);

/* PyDict_Merge updates/merges from a mapping object (an object that
   supports PyMapping_Keys() and PyObject_GetItem()).  If override is true,
   the last occurrence of a key wins, else the first.  The Python
   dict.update(other) is equivalent to PyDict_Merge(dict, other, 1).
*/
PyAPI_FUNC(int) PyDict_Merge(PyObject *mp,
                                   PyObject *other,
                                   int override);

#ifndef Py_LIMITED_API
/* Like PyDict_Merge, but override can be 0, 1 or 2.  If override is 0,
   the first occurrence of a key wins, if override is 1, the last occurrence
   of a key wins, if override is 2, a KeyError with conflicting key as
   argument is raised.
*/
PyAPI_FUNC(int) _PyDict_MergeEx(PyObject *mp, PyObject *other, int override);
PyAPI_FUNC(PyObject *) _PyDictView_Intersect(PyObject* self, PyObject *other);
#endif

/* PyDict_MergeFromSeq2 updates/merges from an iterable object producing
   iterable objects of length 2.  If override is true, the last occurrence
   of a key wins, else the first.  The Python dict constructor dict(seq2)
   is equivalent to dict={}; PyDict_MergeFromSeq(dict, seq2, 1).
*/
PyAPI_FUNC(int) PyDict_MergeFromSeq2(PyObject *d,
                                           PyObject *seq2,
                                           int override);

PyAPI_FUNC(PyObject *) PyDict_GetItemString(PyObject *dp, const char *key);
#ifndef Py_LIMITED_API
PyAPI_FUNC(PyObject *) _PyDict_GetItemId(PyObject *dp, struct _Py_Identifier *key);
#endif /* !Py_LIMITED_API */
PyAPI_FUNC(int) PyDict_SetItemString(PyObject *dp, const char *key, PyObject *item);
#ifndef Py_LIMITED_API
PyAPI_FUNC(int) _PyDict_SetItemId(PyObject *dp, struct _Py_Identifier *key, PyObject *item);
#endif /* !Py_LIMITED_API */
PyAPI_FUNC(int) PyDict_DelItemString(PyObject *dp, const char *key);

#ifndef Py_LIMITED_API
PyAPI_FUNC(int) _PyDict_DelItemId(PyObject *mp, struct _Py_Identifier *key);
PyAPI_FUNC(void) _PyDict_DebugMallocStats(FILE *out);

int _PyObjectDict_SetItem(PyTypeObject *tp, PyObject **dictptr, PyObject *name, PyObject *value);
PyObject *_PyDict_LoadGlobal(PyDictObject *, PyDictObject *, PyObject *);
#endif

#ifdef __cplusplus
}
#endif
#endif /* !Py_DICTOBJECT_H */
|||||||
=======
#ifndef Py_DICTOBJECT_H
#define Py_DICTOBJECT_H
#ifdef __cplusplus
extern "C" {
#endif


/* Dictionary object type -- mapping from hashable object to object */

/* The distribution includes a separate file, Objects/dictnotes.txt,
   describing explorations into dictionary design and optimization.
   It covers typical dictionary use patterns, the parameters for
   tuning dictionaries, and several ideas for possible optimizations.
*/

/*
There are three kinds of slots in the table:

1. Unused.  me_key == me_value == NULL
   Does not hold an active (key, value) pair now and never did.  Unused can
   transition to Active upon key insertion.  This is the only case in which
   me_key is NULL, and is each slot's initial state.

2. Active.  me_key != NULL and me_key != dummy and me_value != NULL
   Holds an active (key, value) pair.  Active can transition to Dummy upon
   key deletion.  This is the only case in which me_value != NULL.

3. Dummy.  me_key == dummy and me_value == NULL
   Previously held an active (key, value) pair, but that was deleted and an
   active pair has not yet overwritten the slot.  Dummy can transition to
   Active upon key insertion.  Dummy slots cannot be made Unused again
   (cannot have me_key set to NULL), else the probe sequence in case of
   collision would have no way to know they were once active.

Note: .popitem() abuses the me_hash field of an Unused or Dummy slot to
hold a search finger.  The me_hash field of Unused or Dummy slots has no
meaning otherwise.
*/

/* PyDict_MINSIZE is the minimum size of a dictionary.  This many slots are
 * allocated directly in the dict object (in the ma_smalltable member).
 * It must be a power of 2, and at least 4.  8 allows dicts with no more
 * than 5 active entries to live in ma_smalltable (and so avoid an
 * additional malloc); instrumentation suggested this suffices for the
 * majority of dicts (consisting mostly of usually-small instance dicts and
 * usually-small dicts created to pass keyword arguments).
 */
#define PyDict_MINSIZE 8

typedef struct {
    /* Cached hash code of me_key.  Note that hash codes are C longs.
     * We have to use Py_ssize_t instead because dict_popitem() abuses
     * me_hash to hold a search finger.
     */
    Py_ssize_t me_hash;
    PyObject *me_key;
    PyObject *me_value;
} PyDictEntry;

/*
To ensure the lookup algorithm terminates, there must be at least one Unused
slot (NULL key) in the table.
The value ma_fill is the number of non-NULL keys (sum of Active and Dummy);
ma_used is the number of non-NULL, non-dummy keys (== the number of non-NULL
values == the number of Active items).
To avoid slowing down lookups on a near-full table, we resize the table when
it's two-thirds full.
*/
typedef struct _dictobject PyDictObject;
struct _dictobject {
    PyObject_HEAD
    Py_ssize_t ma_fill;  /* # Active + # Dummy */
    Py_ssize_t ma_used;  /* # Active */

    /* The table contains ma_mask + 1 slots, and that's a power of 2.
     * We store the mask instead of the size because the mask is more
     * frequently needed.
     */
    Py_ssize_t ma_mask;

    /* ma_table points to ma_smalltable for small tables, else to
     * additional malloc'ed memory.  ma_table is never NULL!  This rule
     * saves repeated runtime null-tests in the workhorse getitem and
     * setitem calls.
     */
    PyDictEntry *ma_table;
    PyDictEntry *(*ma_lookup)(PyDictObject *mp, PyObject *key, long hash);
    PyDictEntry ma_smalltable[PyDict_MINSIZE];
};

PyAPI_DATA(PyTypeObject) PyDict_Type;
PyAPI_DATA(PyTypeObject) PyDictIterKey_Type;
PyAPI_DATA(PyTypeObject) PyDictIterValue_Type;
PyAPI_DATA(PyTypeObject) PyDictIterItem_Type;
PyAPI_DATA(PyTypeObject) PyDictKeys_Type;
PyAPI_DATA(PyTypeObject) PyDictItems_Type;
PyAPI_DATA(PyTypeObject) PyDictValues_Type;

#define PyDict_Check(op) \
                 PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_DICT_SUBCLASS)
#define PyDict_CheckExact(op) (Py_TYPE(op) == &PyDict_Type)
#define PyDictKeys_Check(op) (Py_TYPE(op) == &PyDictKeys_Type)
#define PyDictItems_Check(op) (Py_TYPE(op) == &PyDictItems_Type)
#define PyDictValues_Check(op) (Py_TYPE(op) == &PyDictValues_Type)
/* This excludes Values, since they are not sets. */
# define PyDictViewSet_Check(op) \
    (PyDictKeys_Check(op) || PyDictItems_Check(op))

PyAPI_FUNC(PyObject *) PyDict_New(void);
PyAPI_FUNC(PyObject *) PyDict_GetItem(PyObject *mp, PyObject *key);
PyAPI_FUNC(PyObject *) _PyDict_GetItemWithError(PyObject *mp, PyObject *key);
PyAPI_FUNC(int) PyDict_SetItem(PyObject *mp, PyObject *key, PyObject *item);
PyAPI_FUNC(int) PyDict_DelItem(PyObject *mp, PyObject *key);
PyAPI_FUNC(int) _PyDict_DelItemIf(PyObject *mp, PyObject *key,
                                  int (*predicate)(PyObject *value));

PyAPI_FUNC(void) PyDict_Clear(PyObject *mp);
PyAPI_FUNC(int) PyDict_Next(
    PyObject *mp, Py_ssize_t *pos, PyObject **key, PyObject **value);
PyAPI_FUNC(int) _PyDict_Next(
    PyObject *mp, Py_ssize_t *pos, PyObject **key, PyObject **value, long *hash);
PyAPI_FUNC(PyObject *) PyDict_Keys(PyObject *mp);
PyAPI_FUNC(PyObject *) PyDict_Values(PyObject *mp);
PyAPI_FUNC(PyObject *) PyDict_Items(PyObject *mp);
PyAPI_FUNC(Py_ssize_t) PyDict_Size(PyObject *mp);
PyAPI_FUNC(PyObject *) PyDict_Copy(PyObject *mp);
PyAPI_FUNC(int) PyDict_Contains(PyObject *mp, PyObject *key);
PyAPI_FUNC(int) _PyDict_Contains(PyObject *mp, PyObject *key, long hash);
PyAPI_FUNC(PyObject *) _PyDict_NewPresized(Py_ssize_t minused);
PyAPI_FUNC(void) _PyDict_MaybeUntrack(PyObject *mp);

/* PyDict_Update(mp, other) is equivalent to PyDict_Merge(mp, other, 1). */
PyAPI_FUNC(int) PyDict_Update(PyObject *mp, PyObject *other);

/* PyDict_Merge updates/merges from a mapping object (an object that
   supports PyMapping_Keys() and PyObject_GetItem()).  If override is true,
   the last occurrence of a key wins, else the first.  The Python
   dict.update(other) is equivalent to PyDict_Merge(dict, other, 1).
*/
PyAPI_FUNC(int) PyDict_Merge(PyObject *mp,
                                   PyObject *other,
                                   int override);

/* PyDict_MergeFromSeq2 updates/merges from an iterable object producing
   iterable objects of length 2.  If override is true, the last occurrence
   of a key wins, else the first.  The Python dict constructor dict(seq2)
   is equivalent to dict={}; PyDict_MergeFromSeq(dict, seq2, 1).
*/
PyAPI_FUNC(int) PyDict_MergeFromSeq2(PyObject *d,
                                           PyObject *seq2,
                                           int override);

PyAPI_FUNC(PyObject *) PyDict_GetItemString(PyObject *dp, const char *key);
PyAPI_FUNC(int) PyDict_SetItemString(PyObject *dp, const char *key, PyObject *item);
PyAPI_FUNC(int) PyDict_DelItemString(PyObject *dp, const char *key);

#ifdef __cplusplus
}
#endif
#endif /* !Py_DICTOBJECT_H */
>>>>>>> Stashed changes
