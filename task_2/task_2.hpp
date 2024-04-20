
#include <initializer_list>
#include <iterator>
#include <memory>
#include <iostream>



template <typename T>
class ForwardList {
    
    struct Node {
        std::unique_ptr<Node> next_;
        
        T data_;
    public:    
        Node() : next_{}, data_{} {}

        Node(const T& data) : next_{}, data_{data} {}
    };

    struct FwdIter {
        Node* ptr_;
    public:
        FwdIter(Node* ptr) : ptr_(ptr) {}
        
        Node* NodeData() const { return static_cast<Node*>(ptr_); }

        T& operator*() const { return NodeData()->data_; }

        T* operator->() const { return &NodeData()->data_; }

        bool operator==(const FwdIter& rhs) const { return this->ptr_ == rhs.ptr_; }

        bool operator!=(const FwdIter& rhs) const { return this->ptr_ != rhs.ptr_; }
        
        FwdIter& operator++() {
            ptr_ = ptr_->next_.get();
            return *this; 
        }

        FwdIter& operator++(int) {
            FwdIter tmp = *this;
            ++(*this);
            return tmp.ptr_;
        }
    };
    std::unique_ptr<Node> head_;

public:
    
    explicit ForwardList() : head_(std::make_unique<Node>(nullptr)) {}

    explicit ForwardList(size_t count) : ForwardList(count, T{}) {}

    explicit ForwardList(size_t count, const T& elem) : ForwardList() {
        Node* pNode = head_.get();
        while(count != 0) {
            pNode->next_ = std::make_unique<Node>(nullptr, elem);
            pNode = pNode->next_.get();
            --count;
        }
    }

    template <typename Iter> ForwardList(Iter begin, Iter end) : ForwardList() {
            Node* pNode = head_.get();
            for (auto it = begin; it != end; ++it) {
                pNode->next_ = std::make_unique<Node>(nullptr, it);
                pNode = pNode->next_.get();
            }
        }

    ForwardList(const ForwardList& rhs) : ForwardList(rhs.begin(), rhs.end()) {}

    ForwardList(ForwardList&& rhs) = default;

    ForwardList(std::initializer_list<T> init_lst) : ForwardList(init_lst.begin(), init_lst.end()) {}

    ~ForwardList() = default;

public: 

    ForwardList& operator= (const ForwardList& rhs) {
        ForwardList tmp(rhs);
        std::swap(this->head_, tmp.head_);
        return *this;
    }

    ForwardList& operator= (ForwardList&& rhs) = default;

    ForwardList& operator= (std::initializer_list<T> init_lst) {
        *this = ForwardList(init_lst);
        return *this; 
    }

public:

    FwdIter begin() { return FwdIter(head_->next_.get()); }

    FwdIter end() { return nullptr; }
    
    FwdIter insert_after(FwdIter pos, T value) {
        Node* tmp = pos.ptr_;
        std::unique_ptr<Node> prev = std::move(tmp->next_);
        std::unique_ptr<Node> nxt = std::make_unique<Node>(std::move(prev), std::move(value));
        tmp->next_ = std::move(nxt);
        return tmp->next_.get();
    }

    FwdIter erase_after(FwdIter pos) {
        Node* tmp = pos.ptr_;
        std::unique_ptr<Node> prev = std::move(tmp->next_);
        std::unique_ptr<Node> nxt = std::move(prev->next_);
        tmp->next_ = std::move(nxt);
        return tmp->next_.get();
    }

    /*FwdIter find(T data) {
        Node* tmp = head_;
        while(tmp) {
            if(tmp->data_ == data) return ;
            tmp = tmp->next_;
        }

    }*/
    
    bool is_empty() { return head_ == nullptr; }

   /* void print() {
        if(is_empty()) return;
        auto tmp = head_;
        while (tmp) {
            std::cout << tmp->data_ << '\n';
            tmp = tmp->next_;
        }
        std::cout << '\n';
    }*/
};




