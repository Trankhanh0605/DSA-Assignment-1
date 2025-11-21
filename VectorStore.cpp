#include "VectorStore.h"


//support function

template<class T>
void merge(ArrayList<T>& list, int left, int mid, int right, bool (*compare)(const T&, const T&)) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    T* L = new T[n1];
    T* R = new T[n2];

    for (int i = 0; i < n1; i++)
        L[i] = list.get(left + i);
    for (int j = 0; j < n2; j++)
        R[j] = list.get(mid + 1 + j);

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (compare(L[i], R[j])) {
            list.set(k++, L[i++]);
        } else {
            list.set(k++, R[j++]);
        }
    }

    while (i < n1) {
        list.set(k++, L[i++]);
    }

    while (j < n2) {
        list.set(k++, R[j++]);
    }

    delete[] L;
    delete[] R;
}

template<class T>
void mergeSortArrayList(ArrayList<T>& list, int left, int right, bool (*compare)(const T&, const T&)) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortArrayList(list, left, mid, compare);
        mergeSortArrayList(list, mid + 1, right, compare);
        merge(list, left, mid, right, compare);
    }
}


// ----------------- ArrayList Implementation -----------------







template <class T>
void ArrayList<T>::ensureCapacity(int cap) {
//TODO
if (cap<=capacity) return;
int newCap=capacity*1.5;
if (newCap<cap) newCap=cap;
T* newData=new T [newCap];
for (int i=0; i<count;++i) {
    newData[i]=data[i];
}
delete[]data;
data=newData;
capacity=newCap;
}

template <class T>
ArrayList<T>::ArrayList(int initCapacity) {
    // TODO
    count = 0;
if (initCapacity < 0) {
        this->capacity=initCapacity;
        data = nullptr;
} else {
        this->capacity = initCapacity;  // Giữ nguyên giá trị truyền vào
        data = new T[capacity];
    }
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T>& other) {
    // TODO
    capacity=other.capacity;
    count=other.count;
    data=new T[capacity];
    for (int i=0; i<count; i++) {
        data[i]=other.data[i];
    }
}   

template <class T>
ArrayList<T>::~ArrayList() {
    // TODO
    delete[]data;
    data=nullptr;
    capacity=count=0;
}

// TODO: implement other methods of ArrayList

template<class T>
ArrayList<T>&  ArrayList<T>::operator=(const ArrayList<T>& other) {
    if (this==&other) return *this;
    delete[]data;
    capacity=other.capacity;
    count=other.count;
    data=new T[capacity];
    for (int i=0; i<count; ++i) {
        data[i]=other.data[i];
    }
    return *this;
}

template <class T>
void ArrayList<T> ::add(T e) {
    ensureCapacity(count+1);
    data[count]=e;
    count++;
}

template<class T>
void ArrayList<T>::add(int index, T e) {
if (index<0||index>count) {
    throw out_of_range("Index is invalid!");
}
ensureCapacity(count+1);
for (int i=count; i>index; --i) {
    data[i]=data[i-1];
}
data[index]=e;
count++;
}

template<class T>
T ArrayList<T>:: removeAt(int index) {
if (index<0||index>=count) {
    throw out_of_range("Index is invalid!");
}

T removedItem=data[index];
for (int i=index; i<count-1;++i) {
    data[i]=data[i+1];
}
count--;

return removedItem;
}

template <class T>
bool ArrayList<T>::empty() const {
if (count==0) return true;
else return false;
}

template<class T>
int ArrayList<T>::size() const {
    return count;
}

template<class T>
void ArrayList<T>:: clear() {
    delete[]data;
    count=0;
    capacity=10;
    data=new T[capacity]; 
}

template<class T>
T& ArrayList<T>:: get(int index) const {
    if (index<0||index>=count) throw out_of_range("Index is invalid!");
    return data[index];
}

template<class T>
void ArrayList<T>:: set(int index, T e) {
    if (index<0||index>=count) throw out_of_range("Index is invalid!");
    data[index]=e;
}

template<class T>
int ArrayList<T>:: indexOf(T item) const {
    for (int i=0; i<count; ++i) {
        if (data[i]==item) {
            return i;
        }
    }
    return -1;
}

template<class T>
bool ArrayList<T>:: contains(T item) const {
    for (int i=0; i<count; i++) {
        if (data[i]==item) return true;
    }
    return false;
}

template<class T> 
string ArrayList<T>:: toString(string (*item2str)(T&)) const {
stringstream ss;
ss<<"[";
for (int i=0; i<count; ++i) {
    if (i>0) ss<<", ";
    if (item2str!=NULL) ss<<item2str(data[i]);
    else ss<<data[i];
}
ss<<"]";
return ss.str();
}

template <class T> 
typename ArrayList<T>:: Iterator ArrayList<T>::begin()  {
    return Iterator(this, 0);
}

template <class T> 
typename ArrayList<T>:: Iterator ArrayList<T>::end()  {
    return Iterator(this, count);
}



template<class T>
void ArrayList<T>::addUnique(T item) {
    if (!contains(item)) {
        add(item);   // add là hàm thêm phần tử có sẵn trong ArrayList
    }
    // nếu đã tồn tại, không làm gì
}



// ----------------- Iterator of ArrayList Implementation -----------------
template <class T>
ArrayList<T>::Iterator::Iterator(ArrayList<T>* pList, int index) {
    // TODO
    if (index < 0 || index > pList->count) {
        throw std::out_of_range("Index is invalid!");
    }
    this->pList = pList;
    this->cursor = index;
}

// TODO: implement other methods of ArrayList::Iterator
template <class T> 
typename ArrayList<T>:: Iterator&  ArrayList<T>::Iterator::operator=(const Iterator& other) {
if (this!=&other) {
    this->cursor=other.cursor;
    this->pList=other.pList;
}
return *this;
}

template<class T>
T& ArrayList<T>::Iterator::operator*() {
if (pList==NULL||cursor<0||cursor>=pList->count) throw out_of_range("Iterator is out of range!");
return pList->data[cursor];
} 

template <class T>
bool ArrayList<T> :: Iterator :: operator!=(const Iterator& other) const {
    if ((this->pList!=other.pList) ||(this->cursor!=other.cursor)) return true;
    return false;
}

template <class T> 
typename ArrayList<T>:: Iterator& ArrayList<T>::Iterator::operator++() {
if (cursor>=pList->count) throw out_of_range("Iterator cannot advance past end!");
++cursor;
return *this; 
}

template <class T> 
typename ArrayList<T>:: Iterator ArrayList<T>::Iterator::operator++(int) {
if (cursor>=pList->count) throw out_of_range("Iterator cannot advance past end!");
Iterator temp=*this;
++cursor;
return temp;
}

template<class T> //tiền tố 
typename ArrayList<T>:: Iterator& ArrayList<T>:: Iterator::operator--() {
    if (cursor==pList->count) {cursor=pList->count-1; return *this;}
    if (cursor<=0) throw out_of_range("Iterator cannot move before begin!") ;
    else  {--cursor;};    
    return *this;
}


template <class T> //hậu tố 
typename ArrayList<T>:: Iterator ArrayList<T>:: Iterator::operator--(int) {
if (cursor == pList->count) {
        Iterator temp = *this;
        cursor = pList->count - 1;
        return temp;
    }
    if (cursor <= 0) throw out_of_range("Iterator cannot move before begin!");
    Iterator temp = *this;
    --cursor;
    return temp;
}


// ----------------- SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::SinglyLinkedList() {
    // TODO
      head=NULL;
    tail=NULL;
    count=0;
}   

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    // TODO
     clear();
}   

// TODO: implement other methods of SinglyLinkedList
template <class T>
void SinglyLinkedList<T>::add(T e) {
    Node* newNode=new Node(e);
    if (empty()) head=tail=newNode;
    else {
        tail->next=newNode;
        tail=newNode;
    }
    ++count;
}

template<class T>
void SinglyLinkedList<T>::add(int index,T e) {
if (index<0||index>count) throw out_of_range("Index is invalid!");
else if (index==count) return this->add(e);
if (index==0) {
    Node* tmp=new Node (e);
    tmp->next=this->head;
    this->head=tmp;
    this->count++;
}
else {
    Node *temp=new Node(e);
    Node *prev=this->head;
    for (int i=0; i<index-1; ++i) prev=prev->next;
    temp->next=prev->next;
    prev->next=temp;
    this->count++;
}
}

template<class T>
T SinglyLinkedList<T>::removeAt(int index) {

if (index < 0 || index >= count) throw out_of_range("Index is invalid!");
    Node* prev = nullptr;
    Node* cur = head;
    for (int i = 0; i < index; ++i) {
        prev = cur;
        cur = cur->next;
    }
    T val = cur->data;
    if (prev == nullptr) {
        head = cur->next;
        if (count == 1) tail = nullptr; 
    } else {
        prev->next = cur->next;
        if (cur == tail) { 
            tail = prev;
        }
    }
    delete cur;
    count--;
    return val;

}

template <class T>
bool SinglyLinkedList<T>::removeItem (T item) {
    if (empty()) return false;
    if (head->data==item) {
        Node* toDelete=head;
        head=head->next;
        if (head==NULL) tail=NULL;
        delete toDelete;
        --count;
        return true; 
    }
    Node *prev=head;
    Node *cur=head->next;
    while (cur) {
        if (cur->data==item) {
            prev->next=cur->next;
            if (cur==tail) tail=prev;
            delete cur;
            --count;
            return true;
        }
        prev=cur;
        cur=cur->next;
    }
    return false;
}

template <class T>
bool SinglyLinkedList<T>::empty() const {
if (count==0) return true;
else return false;
}

template <class T>
int SinglyLinkedList<T>:: size() const {
    return count;
}

template <class T> 
void SinglyLinkedList<T>:: clear() {
Node *cur=head;
while (cur) {
    Node *nextNode=cur->next;
    delete cur;
    cur=nextNode;
}
head=tail=NULL;
count=0;
}

template <class T>
T& SinglyLinkedList<T>:: get(int index) const {
    if (index<0||index>=count) throw out_of_range("Index is invalid!");
    Node *cur=head; 
    for (int i=0; i<index; ++i) {
        cur=cur->next;
    }
    return cur->data;
}

template <class T> 
int SinglyLinkedList<T>:: indexOf(T item) const {
    Node * cur=head;
    int idx=0;
    while (cur!=nullptr) {
        if (cur->data==item) return idx;
        cur=cur->next;
        ++idx;
    }
    return -1;
}

template <class T>
bool SinglyLinkedList<T>:: contains(T item) const{
    if (indexOf(item) !=-1) return true;
    else return false;
}

template <class T>
string SinglyLinkedList<T>:: toString(string (*item2str)(T&)) const {
    stringstream ss;
    Node *cur=head;
    while (cur) {
        if (item2str) ss<<"[" <<item2str(cur->data)<<"]";
        else ss<<"["<<cur->data<<"]";
        if (cur->next) ss<<"->";
        cur=cur->next;
    }
    return ss.str();
}

template<class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>:: begin() const {
    return Iterator(head);
}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::end() const  {
    return Iterator(nullptr);
}







// ----------------- Iterator of SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::Iterator::Iterator(Node* node) {
    // TODO
    current=node;
}   

// TODO: implement other methods of SinglyLinkedList::Iterator
template<class T>
typename SinglyLinkedList<T>::Iterator&  SinglyLinkedList<T>::Iterator::operator=(const Iterator& other) {
if (current!=other.current) current=other.current;
return *this;
}

template<class T>
T& SinglyLinkedList<T>::Iterator::operator*(){
if (current==nullptr) throw out_of_range("Iterator is out of range!");
return current->data;
}

template <class T>
bool SinglyLinkedList<T>:: Iterator:: operator!=(const Iterator& other) const {
if (current!=other.current) return true;
else return false;
}

template<class T>
typename SinglyLinkedList<T>::Iterator& SinglyLinkedList<T>::Iterator::operator++() {
if (current == nullptr) throw std::out_of_range("Iterator cannot advance past end!");
current=current->next;
return *this;
}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::Iterator:: operator++(int){
if (current == nullptr) throw std::out_of_range("Iterator cannot advance past end!");
Iterator temp=*this;
++(*this);
return temp;
}


//-------------VectorRecord Constructor-----------------
VectorStore::VectorRecord::VectorRecord(int id, const string& rawText, SinglyLinkedList<float>* vector) {
this->id=id;
this->rawText=rawText;
this->vector=vector;
this->rawLength=rawText.length();  //Vĩnh Tiến dặn thêm 
}

// ----------------- VectorStore Implementation -----------------



VectorStore::VectorStore(int dimension, EmbedFn embeddingFunction) {
    // TODO
count=0;
this->dimension=dimension;
this->embeddingFunction=embeddingFunction;
nextId = 1; // Đúng là nên khởi tạo bằng 1
}

VectorStore::~VectorStore() {
    // TODO
    clear();
}

// TODO: implement other methods of VectorStore
int VectorStore::size()  const {
return count;
}

bool VectorStore::empty() const {
    if (count==0) return true;
    else return false;
}

void VectorStore:: clear() {
    for (int i=0; i<records.size(); ++i) {
        VectorRecord *rec=records.get(i);
        delete rec->vector;
        delete rec;
    }
    records.clear();
    count=0;
    nextId=1;
}

SinglyLinkedList<float>* VectorStore:: preprocessing(string rawText) {
    if (embeddingFunction == nullptr) return nullptr;  
    SinglyLinkedList<float> * vec=embeddingFunction(rawText);
    if (vec == nullptr) {
        vec = new SinglyLinkedList<float>();
        vec->add(0.0f);
        return vec;
    }
   
    if (vec->size() >dimension) {
        while (vec->size()>dimension) {
            vec->removeAt(vec->size()-1);
        }
    }
    else if (vec->size()<dimension) {
        for (int i=vec->size(); i<dimension; ++i) vec->add(0.0f);
    }
    return vec;
}

void VectorStore:: addText(string rawText) {
SinglyLinkedList<float>* vec= preprocessing (rawText);

VectorRecord *rec=new VectorRecord(this->nextId, rawText, vec);
rec->rawLength=rawText.length();
records.add(rec);
++count;
updateNextId(); //thay ++nextId bằng hàm này 
}

SinglyLinkedList<float>& VectorStore:: getVector(int index) {
if (index<0||index>=records.size()) throw out_of_range("Index is invalid!");
return *(records.get(index)->vector);
}

string VectorStore:: getRawText(int index) const {
if (index < 0 || index >= records.size()) throw out_of_range("Index is invalid!");
return records.get(index)->rawText;
}

int VectorStore:: getId(int index) const  {
    if (index < 0 || index >= records.size()) throw out_of_range("Index is invalid!");
    return records.get(index)->id;
}

bool VectorStore:: removeAt(int index) {
if (index < 0 || index >= records.size()) throw out_of_range("Index is invalid!");
VectorRecord *rec=records.get(index);
delete rec->vector;
delete rec;
records.removeAt(index);
updateNextId();
--count;
return true;
}

bool VectorStore:: updateText(int index, string newRawText) {
    if (index < 0 || index >= records.size()) throw out_of_range("Index is invalid!");
    VectorRecord *rec=records.get(index);
    delete rec->vector;
    rec->vector=preprocessing(newRawText);
    rec->rawText=newRawText;
    rec->rawLength=newRawText.length();
    return true;
}

void VectorStore:: setEmbeddingFunction(EmbedFn newEmbeddingFunction) {
embeddingFunction=newEmbeddingFunction;
}

// void VectorStore:: forEach(void (*action)(SinglyLinkedList<float>&, int, string&)) {
// int size=records.size();
// for (int i=0; i<size; ++i) {
//     VectorRecord *rec=records.get(i);
//     action(*(rec->vector),rec->id,rec->rawText);
// }
// }

//đoạn là chỗ ngồi debug 

void VectorStore::forEach (void (*action)(SinglyLinkedList<float>&, int , string& )) {
    int n = records.size();
    for (int i = 0; i < n; ++i) {
        VectorRecord* rec = records.get(i);
        // int rawLength = rec->rawText.length(); //hoặc size() (bỏ chỗ này vào constructor luôn)
        action(*(rec->vector), rec->rawLength, rec->rawText);
    }
}

double VectorStore::cosineSimilarity( const SinglyLinkedList<float>& v1, const SinglyLinkedList<float>& v2) const {
double cos;
double dot=0; 
double normA=0;
double normB=0;
auto it1=v1.begin();
auto it2=v2.begin();
while ((it1!=v1.end()) && (it2!=v2.end())) {
    double a=*it1;
    double b=*it2;
    dot+=a*b;
    normA+=a*a;
    normB+=b*b;
    ++it1; 
    ++it2;
}
if ((normA==0)||(normB==0)) return 0.0;
else cos=dot/(sqrt(normA)*sqrt(normB));
return cos;
}
 
double VectorStore:: l1Distance( const SinglyLinkedList<float>& v1, const  SinglyLinkedList<float>& v2) const { //khoang cach manhattan
double result=0.0 ;
auto it1=v1.begin();
auto it2=v2.begin();
while ((it1!=v1.end()) && (it2!=v2.end())) {
    result+=fabs(*it1-*it2);
    ++it1;
    ++it2;
}
return result;
}

double VectorStore:: l2Distance( const SinglyLinkedList<float>& v1, const SinglyLinkedList<float>& v2) const {
double result;
double temp;
double d=0.0; 
auto it1=v1.begin();
auto it2=v2.begin();
while ((it1!=v1.end()) && (it2!=v2.end())) {
    temp=*it1-*it2;
    d+=temp*temp;
    ++it1;
    ++it2;
}
result=sqrt(d);
return result;
}

int VectorStore::findNearest( const SinglyLinkedList<float>& query, const string& metric) const {
    
    if (empty()) return -1;

    int idxBest = -1;
    double bestVal = 0.0;
    int n = records.size();

    for (int i = 0; i < n; ++i) {
        double val;
        if (metric == "cosine") {
            val = cosineSimilarity(query, *(records.get(i)->vector));
        } else if (metric == "euclidean") {
            val = l2Distance(query, *(records.get(i)->vector));
        } else if (metric == "manhattan") {
            val = l1Distance(query, *(records.get(i)->vector));
        } else {
            throw invalid_metric();
        }

        if (idxBest == -1) {
            // first element initializes best
            bestVal = val;
            idxBest = i;
            continue;
        }

        if (metric == "cosine") {
            if (val > bestVal + EPSILON) {
                bestVal = val;
                idxBest = i;
            } else if (fabs(val - bestVal) <= EPSILON && i < idxBest) {
                // tie: choose smaller index
                idxBest = i;
            }
        } else { // euclidean / manhattan -> smaller is better
            if (val < bestVal - EPSILON) {
                bestVal = val;
                idxBest = i;
            } else if (fabs(val - bestVal) <= EPSILON && i < idxBest) {
                idxBest = i;
            }
        }
    }

    return idxBest;

}

int* VectorStore:: topKNearest(const SinglyLinkedList<float>& query, int k, const string& metric) const {
int n = records.size();
if (!(metric == "cosine" || metric == "euclidean" || metric == "manhattan")) throw invalid_metric();
if (k <= 0 || k > n) throw invalid_k_value();


using Pair = pair<int,double>; // index, score
ArrayList<Pair> vals;
for (int i = 0; i < n; ++i) {
    double s = 0;
    if (metric == "cosine") s = cosineSimilarity(query, *(records.get(i)->vector));
    else if (metric == "euclidean") s = l2Distance(query, *(records.get(i)->vector));
    else if (metric == "manhattan") s = l1Distance(query, *(records.get(i)->vector));
    vals.add(Pair(i,s));
    }
if (metric=="cosine") mergeSortArrayList<Pair>(vals, 0, vals.size() - 1, compareCosine);
else mergeSortArrayList<Pair>(vals, 0, vals.size() - 1, compareDistance);
int *res=new int [k];
for (int i=0; i<k; ++i) {
    res[i]=vals.get(i).first;
}
return res;
}

void VectorStore:: updateNextId () {
    int maxId = -1;
    for (int i = 0; i < records.size(); ++i) {
        int id = records.get(i)->id; 
        // nếu record là pointer, dùng get(i)->id, nếu object dùng get(i).id
        if (id > maxId) maxId = id;
    }
    nextId = (maxId >= 0) ? (maxId + 1) : 1;
}


// Explicit template instantiation for char, string, int, double, float, and Point

template class ArrayList<char>;
template class ArrayList<string>;
template class ArrayList<int>;
template class ArrayList<double>;
template class ArrayList<float>;
template class ArrayList<Point>;

template class SinglyLinkedList<char>;
template class SinglyLinkedList<string>;
template class SinglyLinkedList<int>;
template class SinglyLinkedList<double>;
template class SinglyLinkedList<float>;
template class SinglyLinkedList<Point>;
