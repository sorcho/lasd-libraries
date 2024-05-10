
namespace lasd {

/* ************************************************************************** */

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize) {
        tableSize = std::pow(2, std::ceil(log2((newSize <= 16) ? 16 : newSize)));
        table = new lasd::List<Data>[tableSize] {};
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data>& cont) : HashTableClsAdr(cont.Size()) {
        InsertAll(cont);
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize, const TraversableContainer<Data>& cont) : HashTableClsAdr(newSize) {
        InsertAll(cont);
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(MappableContainer<Data>&& cont) noexcept : HashTableClsAdr(cont.Size()) {
        InsertAll(std::move(cont));
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize, MappableContainer<Data>&& cont) noexcept : HashTableClsAdr(newSize) {
        InsertAll(std::move(cont));
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data>& htca) : HashTable<Data>(htca) {
        table = new lasd::List<Data>[tableSize] {};
        std::copy(htca.table, htca.table + tableSize, table);
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data>&& htca) noexcept : HashTable<Data>(std::move(htca)) {
        std::swap(table, htca.table);
    }

    template <typename Data>
    HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& htca) {
        HashTable<Data>::operator=(htca);
        delete[] table;
        table = new lasd::List<Data>[tableSize] {};
        for(ulong i = 0; i < tableSize; i++) {
            table[i] = htca.table[i];
        }
        return *this;
    }

    template <typename Data>
    HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data>&& htca) noexcept {
        HashTable<Data>::operator=(std::move(htca));
        std::swap(table, htca.table);
        return *this;
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data>& htca) const noexcept {
        bool result = true;
        if(htca.size != size) {
            return false;
        }

        for(ulong i = 0; i < tableSize; i++){
            table[i].Traverse(
                [&htca, &result](const Data& dat){
                    if(!htca.Exists(dat)){
                        result = false;
                        return;
                    }
                }
            );
        }

        return result;
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::Insert(const Data& value) {
    bool result = false;

    ulong index = HashKey(Hashable<Data>()(value));
    result = table[index].Insert(value);

    if(result) {
        size++;
    }

    return result;
}

    template <typename Data>
    bool HashTableClsAdr<Data>::Insert(Data&& value) {
        bool result = false;

        ulong index = HashKey(Hashable<Data>()(std::move(value)));
        result = table[index].Insert(std::move(value));

        if(result) {
            size++;
        }

        return result;
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::Remove(const Data &value) {
        bool result = false;

        ulong index = HashKey(Hashable<Data>()(value));
        result = table[index].Remove(value);
        
        if(result) {
            size--;
        }

        return result;
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::Exists(const Data& value) const noexcept {
        ulong index = HashKey(Hashable<Data>()(value));

        if(table[index].Exists(value)) {
            return true;
        }

        return false;
    }

    template <typename Data>
    void HashTableClsAdr<Data>::Resize(const ulong new_size) {
        ulong newTableSize = (new_size <= 16)? 16 : std::pow(2, std::ceil(log2(new_size)));
        size = 0;
        lasd::List<Data>* newTable = new lasd::List<Data>[newTableSize] {};
        std::swap(newTable, table);
        std::swap(newTableSize, tableSize);
        for(ulong i = 0; i < newTableSize; i++){
            InsertAll(newTable[i]);
        }
        delete[] newTable;
    }

    template <typename Data>
    void HashTableClsAdr<Data>::Clear() {
        delete[] table;

        table = new lasd::List<Data>[tableSize] {};
        size = 0;
    }

/* ************************************************************************** */

}
