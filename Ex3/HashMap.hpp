#ifndef CPPEX3_HASHMAP_HPP
#define CPPEX3_HASHMAP_HPP

#include <iostream>
#include <vector>
#include <algorithm>



using std::vector;
using std::cout;
using std::endl;

static const char* BUCKER_IS_EMPTY = "Bucket Is Empty";  /**  message */
static const char* BAD_INPUT_IN = "Invalid input";  /**  message */
static const int TABLE_SIZE_DEFAULT = 16; /** the defaule size of the table*/
static const int NO_ELEMENTS = 0; /** if there is no elements in the map*/
static const float DEFAULT_LOWER_FACTOR = 0.25; /** default lower factor */
static const float DEFAULT_UPPER_FACTOR = 0.75; /** default upper factor*/
static const bool MAKE_IT_LARGE = true;
static const bool MAKE_IT_SMALLER = false;


/**
 * this class is a Bad input Excepetion class.
 */
class BadInputException : public std::exception
{
private:
    const char* err;
public:


    explicit BadInputException(const char* errorMessage) : err(errorMessage) {}

    /**
     * return "invali input" message to user
     * @return
     */
    const char* what() const noexcept override
    {
        return err;
    }
};

/**
 * Hashmap class is unsorted map implemeted by
 * @tparam KEY
 * @tparam VALUE
 */
template <class KEY, class VALUE>
class HashMap
{
private:

    using bucket = vector<std::pair<KEY, VALUE>>; /** represnt the bueckets */
    int _capacity; /** store the capacity of table */
    int _numberOfElements /**  counts the number of elements */;
    double _lFactor; /**  lower factor */
    double _UFactor; /**  lower upper */
    bucket* _table; /** represent the table of open has table */

    /**
     * private function which checks whether table increase is needed
     * @return
     */
    bool _needResizeUp();

    /**
     * private function which checks whether table decrease is needed
     * @return
     */
    bool _needResizeDown();

    /**
     * function make resize up or down as needed
     * @param flag - if true, resize up, else resize down
     */
    void _resize(bool flag);

    /**
     * this private function is the hash function which gets key and returns index of bucket
     * @param key
     * @return
     */
    int _getIndex(const KEY& key) const;

public:

    /**
     * constructor which get two doubles. the higher value will be the upper load factor
     * and ther smaller will be lower load factor
     * @param x
     * @param y
     */
    HashMap(double lower, double upper);

    /**
     * default constructor
     */
    HashMap();

    /**
     * constructor which get two vectors, a is keys and b is values and pair them up
     * @param a
     * @param b
     */
    HashMap(vector<KEY> a, vector<VALUE> b);

    /**
     * default copy constructor. because i used vectors no need to deal with memory
     * @param x
     */
    HashMap(const HashMap& other);

    /**
     * move constructor
     * @param other
     */
    HashMap(HashMap && other) noexcept;

    /**
     * default destructor
     */
    ~HashMap();
    /**
     * function creats a pair of key,value and insert to table to right bucket
     * @param key
     * @param val
     * @return
     */
    bool insert(const KEY& key, VALUE val);

    /**
     * function check whether a key is already inside table
     * @param key
     * @return
     */
    bool containsKey(const KEY& key) const;

    /**
     * private helper function for printing the map
     */
//    void printHash();

    /**
     * function gets key and delete it from table
     * @param key
     * @return
     */
    bool erase(const KEY& key);

    /**
     * function checks if key exists, if not throw exception, else return reference to VALUE
     * @param key
     * @return
     */
    VALUE& at(const KEY& key);


    /**
     * function checks if key exists, if not throw exception, else return reference to VALUE
     * @param key
     * @return
     */
    const VALUE& at(const KEY& key) const;

    /**
     * function delete all the elements;
     */
    void clear();

    /**
     * oprtatr [] behave exatcly like std::map operator
     * @param key
     * @return
     */
    VALUE& operator[](const KEY& key);

    /**
     * oprtatr [] behave exatcly like std::map operator
     * @param key
     * @return
     */
    const VALUE& operator[](const KEY& key) const;

    /**
     * default operator. because i used vectors no need to deal with memory
     * @param x
     * @return
     */
    HashMap& operator= (const HashMap& other);

    /**
     * move operator. because i used vectors no need to deal with memory
     * @param x
     * @return
     */
    HashMap& operator= (HashMap && other) noexcept;

    /**
     * checks whether two object have the same elements in the same bucket
     * @param other
     * @return
     */
    bool operator==(const HashMap& other) const;

    /**
     * checks whether two objects dont not have the same elements in the same bucket
     * @param other
     * @return
     */
    bool operator!=(const HashMap& other) const;

    /**
     * function return the number of elements in the array
     * @return
     */
    int size() const;

    bool checkIfPairInBucket(const KEY& key, const VALUE& value, int index) const;

    /**
     * function return the number of cells in the table
     * @return
     */
    int capacity() const;

    /**
     * load factor getter
     * @return
     */
    double getLoadFactor() const;

    /**
     * checks whther object has no elements
     * @return
     */
    bool empty() const;

    /**
     * checks bucket size
     * @param key
     * @return
     */
    int bucketSize(const KEY& key) const;

    /**
     * because iterator constructor are private
     */
    friend class iterator;

    /**
     * like swap function
     * @param first
     * @param second
     */
    void change(HashMap<KEY, VALUE> &first, HashMap<KEY, VALUE> &second);

    /**
     * iterator class inner class of Hashmap
     */
    class iterator
    {
        typedef typename vector<std::pair<KEY, VALUE>>::iterator vectorArray;

    private:
        const bucket* table; /** makes iterator inner class of hashmap */
        int counter; /** count the current buckets where the iterator is*/
        int size; /** the cuurent iterator position */

        /**
         * private consturctor as requested. gets an vector iterator
         * @param map
         * @param i
         */
        iterator(const bucket* table, int counter, int size) : table(table), counter(counter) , size(size) {}


    public:

        /**
         * operator ->. return pair of key and value
         * @return
         */
        const std::pair<KEY, VALUE>* operator->() const;

        /**
         * move iterator by one
         * @return
         */
        const iterator& operator++();

        /**
         * move iterator by one
         * @return
         */
        const iterator operator++(int);

        /**
         * dereference operator.
         * @return
         */
        const std::pair<KEY, VALUE>& operator*() const;

        /**
         * operator checks if two iterators are equals.
         * @param other
         * @return
         */
        bool operator==(const iterator& other) const;

        /**
         * operator checks if two iterators are not equals.
         * @param other
         * @return
         */
        bool operator!=(const iterator& other) const;

        friend HashMap<KEY, VALUE>;
    };

    /**
     * return iterator to the first key
     * @return
     */
    const iterator begin() const;

    /**
     * return iterator to the first key
     * @return
     */
    const iterator cbegin() const;

    /**
     * return iterator to last key(not a valid key)
     * @return
     */
    const iterator end() const;

    /**
     * return iterator to last key(not a valid key)
     * @return
     */
    const iterator cend() const;
};


/**
 * operator ->. return pair of key and value
 * @return
 */
template<class KEY , class VALUE>
const std::pair<KEY, VALUE>* HashMap<KEY , VALUE>::iterator::operator->() const
{
    const std::pair<KEY , VALUE>* dammy = &table[0][0];
    int innerCounter = 0;
    for (int bucket = 0; bucket < size; bucket++)
    {
        for (auto pairIterator = table[bucket].begin(); pairIterator!= table[bucket].end() ; pairIterator++)
        {
            if (counter == innerCounter)
            {
                return &(*pairIterator);
            }
            innerCounter++;
        }
    }
    return dammy;
}

/**
 * move iterator by one
 * @return
 */
template<class KEY , class VALUE>
const typename HashMap<KEY , VALUE>::iterator& HashMap<KEY , VALUE>::iterator::operator++()
{
    if (counter < size)
    {
        counter++;
    }
    return *this;

}

template<class KEY , class VALUE>
const typename HashMap<KEY , VALUE>::iterator HashMap<KEY , VALUE>::iterator::operator++(int)
{
    typename HashMap<KEY , VALUE>::iterator temp = *this;
    ++(*this);
    return temp;
}

/**
 * dereference operator.
 * @return
 */
template<class KEY , class VALUE>
const std::pair<KEY , VALUE> &HashMap<KEY , VALUE>::iterator::operator*() const
{
    const std::pair<KEY , VALUE>* dammy = &table[0][0];
    int innerCounter = 0;
    for (int bucket = 0; bucket < size; bucket++)
    {
        for (auto pairIterator = table[bucket].begin(); pairIterator!= table[bucket].end() ; pairIterator++)
        {
            if (counter == innerCounter)
            {
                return *pairIterator;
            }
            innerCounter++;
        }
    }
    return *dammy;
}

/**
  * operator checks if two iterators are equals.
  * @param other
  * @return
  */
template<class KEY , class VALUE>
bool HashMap<KEY , VALUE>::iterator::operator==(const HashMap<KEY , VALUE>::iterator& other) const
{
    return (counter == other.counter) && (*table == *other.table) && (size == other.size);
}

/**
 * operator checks if two iterators are not equals.
 * @param other
 * @return
 */
template<class KEY , class VALUE>
bool HashMap<KEY , VALUE>::iterator::operator!=(const HashMap<KEY , VALUE>::iterator& other) const
{
    return !(other == *this);
}


/**
 * constructor which get two doubles. the higher value will be the upper load factor
 * and ther smaller will be lower load factor
 * @param x
 * @param y
 */
template<class KEY, class VALUE>
HashMap<KEY, VALUE>::HashMap(double lower, double upper) : _capacity(TABLE_SIZE_DEFAULT), _numberOfElements(NO_ELEMENTS)
{
    if ( (lower <= 0) || (lower >= upper) || (upper >= 1))
    {
        throw BadInputException(BAD_INPUT_IN);
    }
    else
    {
        _UFactor = upper;
        _lFactor = lower;
    }
    _table = new bucket[TABLE_SIZE_DEFAULT];
}

/**
 * default constructor
 * @tparam KEY
 * @tparam VALUE
 */
template <class KEY, class VALUE>
HashMap<KEY, VALUE>::HashMap() : HashMap<KEY, VALUE>::HashMap(DEFAULT_LOWER_FACTOR,
                                                              DEFAULT_UPPER_FACTOR) {}
/**
 * constructor which get two vectors, a is keys and b is values and pair them up
 * @param a
 * @param b
 */
template <class KEY, class VALUE>
HashMap<KEY, VALUE>::HashMap(vector<KEY> a, vector<VALUE> b) : HashMap()
{
    if (a.size() != b.size())
    {
        throw BadInputException(BAD_INPUT_IN);
    }
    for (int i = 0; i < a.size(); ++i)
    {
        (*this)[a[i]] = b[i];
    }
}

/**
 * this private function is the hash function which gets key and returns index of bucket
 * @param key
 * @return
 */
template<class KEY, class VALUE>
int HashMap<KEY, VALUE>::_getIndex(const KEY& key) const
{
    std::hash<KEY> hasher;
    int hash = hasher(key);
    int index = hash & (HashMap<KEY, VALUE>::_capacity - 1);
    return index;
}

/**
 * function creats a pair of key,value and insert to table to right bucket
 * @param key
 * @param val
 * @return
 */
template<class KEY, class VALUE>
bool HashMap<KEY, VALUE>::insert(const KEY& key, VALUE val)
{
    int index = HashMap<KEY , VALUE>::_getIndex(key);
    std::pair<KEY, VALUE> pair(key, val);
    if (!HashMap<KEY, VALUE>::containsKey(key))
    {
        _table[index].push_back(pair);
        _numberOfElements++;
        if (HashMap<KEY , VALUE>::_needResizeUp())
        {
            HashMap<KEY , VALUE>::_resize(MAKE_IT_LARGE);
        }
        return true;
    }
    return false;
}

/**
 * function check whether a key is already inside table
 * @param key
 * @return
 */
template<class KEY, class VALUE>
bool HashMap<KEY, VALUE>::containsKey(const KEY& key) const
{
    bool flag = false;
    int index = HashMap<KEY , VALUE>::_getIndex(key);
    for (std::pair<KEY, VALUE> pair : _table[index])
    {
        if (pair.first == key)
        {
            flag = true;
            break;
        }
    }
    return flag;
}

/**
 * private function which checks whether table increase is needed
 * @return
 */
template<class KEY, class VALUE>
bool HashMap<KEY, VALUE>::_needResizeUp()
{
    return (((double)HashMap<KEY, VALUE>::_numberOfElements) / ((double)HashMap<KEY, VALUE>::_capacity) > _UFactor);
}

/**
 * private function which checks whether table decrease is needed
 * @return
 */
template<class KEY, class VALUE>
bool HashMap<KEY, VALUE>::_needResizeDown()
{
    return (((double)HashMap<KEY, VALUE>::_numberOfElements) / ((double)HashMap<KEY, VALUE>::_capacity) < _lFactor);
}

/**
 * function make resize up or down as needed
 * @param flag - if true, resize up, else resize down
 */
template<class KEY, class VALUE>
void HashMap<KEY, VALUE>::_resize(bool flag)
{
    int tempCapacity = _capacity;
    if (_capacity == 1)
    {
        return;
    }
    if (flag )
    {
        _capacity *= 2;
    }
    else if (_capacity != 1)
    {
        _capacity /= 2;
    }
    bucket* temp = new bucket[_capacity];
    for (int i = 0; i < tempCapacity ; ++i)
    {
        for (auto pair: _table[i])
        {
            int index = HashMap<KEY , VALUE>::_getIndex(pair.first);
            temp[index].push_back(std::pair<KEY, VALUE>(pair.first, pair.second));
        }
    }
    delete[] _table;
    _table = temp;
}

/**
 * function gets key and delete it from table
 * @param key
 * @return
 */
template<class KEY, class VALUE>
bool HashMap<KEY, VALUE>::erase(const KEY& key)
{
    int index = HashMap<KEY , VALUE>::_getIndex(key);
    if (HashMap<KEY, VALUE>::containsKey(key))
    {
        auto i = _table[index].begin();
        for (auto it = _table[index].begin(); it != _table[index].end(); ++it)
        {
            if (it->first == key)
            {
                i = it;
            }
        }
        _table[index].erase(i);
        _numberOfElements--;
        if (HashMap<KEY , VALUE>::_needResizeDown())
        {
            HashMap<KEY , VALUE>::_resize(MAKE_IT_SMALLER);
        }
        return true;
    }
    return false;
}

/**
 * oprtatr [] behave exatcly like std::map operator
 * @param key
 * @return
 */
template<class KEY, class VALUE>
VALUE& HashMap<KEY , VALUE>::operator[](const KEY& key)
{
    try
    {
        HashMap<KEY , VALUE>::at(key);
    }
    catch (const std::exception& e)
    {
        VALUE v = {};
        HashMap<KEY , VALUE>::insert(key, v);
    }
    return HashMap<KEY , VALUE>::at(key);
}

/**
 * function checks if key exists, if not throw exception, else return reference to VALUE
 * @param key
 * @return
 */
template<class KEY, class VALUE>
VALUE& HashMap<KEY , VALUE>::at(const KEY& key)
{
    if (_table == nullptr)
    {
        throw std::exception();
    }
    VALUE& dammy = _table[0][0].second;
    if (!HashMap<KEY, VALUE>::containsKey(key))
    {
        throw std::exception(); // build an exception later
    }
    int index = HashMap<KEY , VALUE>::_getIndex(key);
    for (int i = 0; i < _table[index].size(); i++)
    {
        if (_table[index][i].first == key)
        {
            return _table[index][i].second;
        }
    }
    return dammy;
}

/**
 * checks whether two object have the same elements in the same bucket
 * @param other
 * @return
 */
template<class KEY , class VALUE>
bool HashMap<KEY , VALUE>::operator==(const HashMap &other) const
{
    if ( (_capacity != other._capacity) || (_numberOfElements != other._numberOfElements) )
    {
        return false;
    }
    bool flag = true;
    for (int i = 0 ; i < _capacity; ++i)
    {
        if (_table[i].size() != other._table[i].size())
        {
            return false;
        }
        for (int j = 0 ; j < other._table[i].size() ; ++j)
        {
            if (!checkIfPairInBucket(other._table[i][j].first, other._table[i][j].second, i))
            {
                flag = false;
            }

        }
    }
    return flag;
}


template<class KEY, class VALUE>
bool HashMap<KEY, VALUE>::checkIfPairInBucket(const KEY& key, const VALUE& value, int index) const
{
    bool flag = false;
    for (int i = 0; i < _table[index].size(); ++i)
    {
        if (_table[index][i].first == key && _table[index][i].second == value)
        {
            flag = true;
        }
    }
    return flag;
}




/**
 * checks whether two objects dont not have the same elements in the same bucket
 * @param other
 * @return
 */
template<class KEY , class VALUE>
bool HashMap<KEY , VALUE>::operator!=(const HashMap &other) const
{
    return !(other == *this);
}

/**
 * function return the number of elements in the array
 * @return
 */
template<class KEY , class VALUE>
int HashMap<KEY , VALUE>::size() const
{
    return _numberOfElements;
}

/**
 * function return the number of cells in the table
 * @return
 */
template<class KEY , class VALUE>
int HashMap<KEY , VALUE>::capacity() const
{
    return _capacity;
}

/**
 * function delete all the elements;
 */
template<class KEY , class VALUE>
void HashMap<KEY , VALUE>::clear()
{
    for (int i = 0; i < capacity(); ++i)
    {
        _table[i].clear();
    }
    _numberOfElements = 0;
}
/**
 * load factor getter
 * @return
 */
template<class KEY , class VALUE>
double HashMap<KEY , VALUE>::getLoadFactor() const
{
    return ((double)HashMap<KEY, VALUE>::_numberOfElements / ((double)HashMap<KEY, VALUE>::_capacity));
}

/**
 * checks whther object has no elements
 * @return
 */
template<class KEY , class VALUE>
bool HashMap<KEY , VALUE>::empty() const
{
    return (_numberOfElements == 0);
}

/**
 * checks bucket size
 * @param key
 * @return
 */
template<class KEY , class VALUE>
int HashMap<KEY , VALUE>::bucketSize(const KEY &key) const
{
    if (_table[HashMap<KEY , VALUE>::_getIndex(key)].size() == 0)
    {
        throw BadInputException(BUCKER_IS_EMPTY);
    }
    return _table[HashMap<KEY , VALUE>::_getIndex(key)].size();
}

/**
 * return iterator to the first key
 * @return
 */
template<class KEY , class VALUE>
const typename HashMap<KEY , VALUE>::iterator HashMap<KEY , VALUE>::begin() const
{

    typename HashMap<KEY , VALUE>::iterator i( _table, 0, _capacity);
    return i;
}

/**
 * return iterator to the first key
 * @return
 */
template<class KEY , class VALUE>
const typename HashMap<KEY , VALUE>::iterator HashMap<KEY , VALUE>::cbegin() const
{

    typename HashMap<KEY , VALUE>::iterator i( _table, 0, _capacity);
    return i;
}

/**
 * return iterator to last key(not a valid key)
 * @return
 */
template<class KEY , class VALUE>
const typename HashMap<KEY , VALUE>::iterator HashMap<KEY , VALUE>::end() const
{
    typename HashMap<KEY , VALUE>::iterator i( _table, _numberOfElements, _capacity);
    return i;
}

/**
 * return iterator to last key(not a valid key)
 * @return
 */
template<class KEY , class VALUE>
const typename HashMap<KEY , VALUE>::iterator HashMap<KEY , VALUE>::cend() const
{
    typename HashMap<KEY , VALUE>::iterator i( _table, _numberOfElements, _capacity);
    return i;
}



//template<class KEY, class VALUE>
//void HashMap<KEY, VALUE>::printHash()
//{
//    int counter = 1;
//    for (int i = 0; i < _capacity ; ++i)
//    {
//        cout << "Row " << counter << ": ";
//        for (auto pair: _table[i])
//        {
//            cout << "{ " << pair.first << " : " << pair.second << " }, ";
//        }
//        counter++;
//        cout << endl;
//    }
//    cout << endl;
//}


/**
 * default destructor
 */
template<class KEY , class VALUE>
HashMap<KEY , VALUE>::~HashMap()
{
    delete[] _table;
}

/**
 * default operator. because i used vectors no need to deal with memory
 * @param x
 * @return
 */
template<class KEY , class VALUE>
HashMap<KEY , VALUE>& HashMap<KEY , VALUE>::operator=(const HashMap &other)
{
    _capacity = other._capacity;
    _numberOfElements = other._numberOfElements;
    delete[] _table;
    _table = new bucket[_capacity];
    for (int i = 0; i < _capacity; ++i)
    {
        _table[i] = other._table[i];
    }
    _lFactor = other._lFactor;
    _UFactor = other._UFactor;
    return *this;
}


template<class KEY , class VALUE>
HashMap<KEY , VALUE>::HashMap(const HashMap &other) : _capacity(other._capacity),
                                                      _numberOfElements(other._numberOfElements) ,
                                                      _lFactor(other._lFactor), _UFactor(other._UFactor)
{
    _table = new bucket[_capacity];
    for (int i = 0; i < _capacity; ++i)
    {
        _table[i] = other._table[i];
    }
}

/**
 * move constructor
 * @param other
 */
template<class KEY , class VALUE>
HashMap<KEY , VALUE>::HashMap(HashMap && other) noexcept
{
    _capacity = other._capacity;
    _numberOfElements = other._numberOfElements;
    _table = other._table;
    other._table = nullptr;
    _lFactor = other._lFactor;
    _UFactor = other._UFactor;
}

/**
  * like swap function
  * @param first
  * @param second
  */
template<class KEY, class VALUE>
void HashMap<KEY, VALUE>::change(HashMap<KEY, VALUE> &first, HashMap<KEY, VALUE> &second)
{
    std::swap(first._capacity , second._capacity);
    std::swap(first._numberOfElements , second._numberOfElements);
    std::swap(first._lFactor , second._lFactor);
    std::swap(first._UFactor , second._UFactor);
    std::swap(first._table, second._table);
}

/**
 * move operator. because i used vectors no need to deal with memory
 * @param x
 * @return
 */
template<class KEY , class VALUE>
HashMap<KEY , VALUE>& HashMap<KEY , VALUE>::operator=(HashMap && other) noexcept
{
    change(*this, other);
    return *this;
}

template<class KEY, class VALUE>
const VALUE & HashMap<KEY, VALUE>::at(const KEY &key) const
{
    if (_table == nullptr)
    {
        throw std::exception();
    }
    return HashMap<KEY, VALUE>::at(key);
}

template<class KEY, class VALUE>
const VALUE & HashMap<KEY, VALUE>::operator[](const KEY &key) const
{
    const VALUE& dammy = _table[0][0].second;
    if (!HashMap<KEY, VALUE>::containsKey(key))
    {
        throw std::exception(); // build an exception later
    }
    int index = HashMap<KEY , VALUE>::_getIndex(key);
    for (int i = 0; i < _table[index].size(); i++)
    {
        if (_table[index][i].first == key)
        {
            return _table[index][i].second;
        }
    }
    return dammy;
}


#endif //CPPEX3_HASHMAP_HPP

