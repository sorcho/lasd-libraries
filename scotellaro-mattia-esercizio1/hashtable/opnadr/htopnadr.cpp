
namespace lasd {

/* ************************************************************************** */

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize) {
        tableSize = std::pow(2, std::ceil(log2((newSize < 16) ? 16 : newSize)));
        table = new Data[tableSize] {};
        tableFlag = new Flag[tableSize] {};
    }

        template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data>& cont) : HashTableOpnAdr(cont.Size() * 2) {
        InsertAll(cont);
    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize, const TraversableContainer<Data>& cont) : HashTableOpnAdr(newSize) {
        InsertAll(cont);
    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(MappableContainer<Data>&& cont) noexcept : HashTableOpnAdr(cont.Size() * 2) {
        InsertAll(std::move(cont));
    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize, MappableContainer<Data>&& cont) noexcept : HashTableOpnAdr(newSize) {
        InsertAll(std::move(cont));
    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr& htoa) : HashTable<Data>(htoa) {
        table = new Data[tableSize] {};
        tableFlag = new Flag[tableSize] {};
        for(ulong i = 0; i < tableSize; i++) {
            table[i] = htoa.table[i];
            tableFlag[i] = htoa.tableFlag[i];
        }
    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr&& htoa) noexcept : HashTable<Data>(std::move(htoa)) {
        std::swap(table, htoa.table);
        std::swap(tableFlag, htoa.tableFlag);
    }

    template <typename Data>
    HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr& htoa) {
        HashTable<Data>::operator=(htoa);

        delete[] table;
        delete[] tableFlag;

        table = new Data[tableSize] {};
        tableFlag = new Flag[tableSize] {};
        
        for(ulong i = 0; i < tableSize; i++) {
            table[i] = htoa.table[i];
            tableFlag[i] = htoa.tableFlag[i];
        }
        return *this;
    }

    template <typename Data>
    HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr&& htoa) noexcept {
        HashTable<Data>::operator=(std::move(htoa));
        std::swap(table, htoa.table);
        std::swap(tableFlag, htoa.tableFlag);
        return *this;
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr &htoa) const noexcept {
        if(size != htoa.Size()) {
            return false;
        }
        for(ulong i = 0; i < tableSize; i++) {
            if(tableFlag[i] == valid) {
                if(!htoa.Exists(table[i])) {
                    return false;
                }
            }
        }
        return true;
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Insert(const Data& data) {
        ulong prob_index = 0;

        if(size * 2 > tableSize) {
            Resize(tableSize * 2);
        }

        ulong index = FindEmpty(data, prob_index);

        if(tableFlag[index] != valid){
            table[index] = data;
            tableFlag[index] = valid;
            ++size;
            return !Remove(++prob_index, data); 
        }

        prob_index = 0;
        return false;
    }
        
    template <typename Data>
    bool HashTableOpnAdr<Data>::Insert(Data&& data) {
        ulong prob_index = 0;

        if(size * 2 >= tableSize) {
            Resize(tableSize * 2);
        }

        ulong index = FindEmpty(data, prob_index);

        if(tableFlag[index] != valid){
            table[index] = std::move(data);
            tableFlag[index] = valid;
            ++size;
            return !Remove(++prob_index, data); 
        }

        prob_index = 0;
        return false;
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Remove(const Data& data) {
        ulong prob_index = 0;
        return Remove(prob_index, data);
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Exists(const Data& data) const noexcept {
        ulong prob_index = 0;
        ulong index = HashKey(Hashable<Data>()(data));
        return Find(index, prob_index, data);
    }

    template <typename Data>
    void HashTableOpnAdr<Data>::Resize(const ulong newSize) {
        ulong tmptableSize = (newSize <= 16)? 16 : std::pow(2, std::ceil(log2(newSize)));

        Data* tmpTable = new Data[tmptableSize] {};
        Flag* tmpTableFlag = new Flag[tmptableSize] {}; 

        std::swap(tmptableSize, tableSize);
        std::swap(tmpTable, table);
        std::swap(tmpTableFlag, tableFlag);

        size = 0;
        for(ulong i = 0; i < tmptableSize; i++){
            if(tmpTableFlag[i] == valid) {
                Insert(tmpTable[i]);
            }
        }   
        delete[] tmpTable;
        delete[] tmpTableFlag;
    }

    template <typename Data>
    void HashTableOpnAdr<Data>::Clear() {
        for(ulong i = 0; i < tableSize; i++) {
            tableFlag[i] = dirty;
        }
        size = 0;
    }

    template <typename Data> 
    ulong HashTableOpnAdr<Data>::HashKey(const Data& key, ulong& prob_index) const noexcept {
        ulong index = HashKey(Hashable<Data>()(key));
        return (index + tableSize + ((prob_index * prob_index) + prob_index)/2) % tableSize;
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Find(ulong& index, ulong& prob_index, const Data& element) const noexcept {
        ulong tmp_index = HashKey(element, prob_index);
        ulong jumps = 0;
        do{
            if(jumps == tableSize - 1) {
                return false;
            }
            if((table[tmp_index] == element) && (tableFlag[tmp_index] == valid)) {
                index = tmp_index;
                return true;
            }
            tmp_index = HashKey(element, ++prob_index);
            jumps++;
        } while((!tableFlag[tmp_index]) == empt);
        return false;
    }

    template <typename Data>
    ulong HashTableOpnAdr<Data>::FindEmpty(const Data& element, ulong& prob_index) const noexcept {
        ulong tmp_index = HashKey(element, prob_index);
        while((tableFlag[tmp_index] == valid) && (table[tmp_index] != element)) {   
            tmp_index = HashKey(element, ++prob_index);
        }
        return tmp_index;
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Remove(ulong& prob_index, const Data& key) noexcept {
        ulong tmp_index;
        if(Find(tmp_index, prob_index, key)){
            tableFlag[tmp_index] = dirty;
            size--;
            prob_index = 0;
            if((size < tableSize / 5) && (tableSize > 16)) {
                Resize(tableSize / 2);
            }
            return true;
        }
        prob_index = 0;
        return false;
    }
/* ************************************************************************** */

}
