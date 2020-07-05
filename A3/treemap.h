#pragma once

#include <memory>
#include <iostream>
#include <utility>
#include <tuple>
#include <vector>

#include <cassert>

// forward declaration to resolve cross-referencing
namespace my {
    template<typename K, typename T>
    class treemap;
}

// forward declaration to resolve cross-referencing
template<typename K, typename T>
void
swap(my::treemap<K,T>& lhs, my::treemap<K,T>& rhs);

namespace my {

    /*
    * class treemap<K,T>
    * represents an associative container (dictionary) with unique keys
    * implemented by a binary search tree
    *
    */
    template<typename K, typename T>
    class treemap
    {

        protected:
            /*
            * hierarchical node structure for class treemap
            *
            */
            class node : public std::enable_shared_from_this<node>
            {
                public:
                    std::weak_ptr<node> parent_ = std::weak_ptr<node>();
                    std::shared_ptr<node> child_left_ = nullptr;
                    std::shared_ptr<node> child_right_ = nullptr;
                    // key and value represented as pair (so they can be easily passed along together)
                    std::pair<K, T> data_ = std::pair<K,T>();

                    node() = default;
                    node(const std::pair<K,T>& data) : data_(data) {}

                    std::shared_ptr<node> search(const K& key)
                    {
                        if (key == data_.first)
                        {
                            return node::shared_from_this();
                        }
                        else if (key < data_.first)
                        {
                            if (child_left_ == nullptr)
                            {
                                return nullptr; 
                            }
                            else
                            {
                                return child_left_->search(key);
                            }   
                        }
                        else
                        {
                            if (child_right_ == nullptr)
                            {
                                return nullptr;
                            }
                            else
                            {
                                return child_right_->search(key);
                            }
                        }  
                    }

                    std::pair<std::shared_ptr<node>,bool> add(const std::pair<K,T>& data, const bool& assign) 
                    {
                        
                        if (data_.first > data.first)
                        {
                            if (child_left_ == nullptr)
                            {
                                child_left_ = std::make_shared<node>(data);
                                child_left_->parent_ = node::weak_from_this();
                                return std::make_pair(child_left_, true);
                            }
                            else
                            {
                                return child_left_->add(data, assign);
                            }
                        }
                        else if (data_.first < data.first)
                        {
                            if (child_right_ == nullptr)
                            {
                                child_right_ = std::make_shared<node>(data);
                                child_right_->parent_ = node::weak_from_this();
                                return std::make_pair(child_right_, true);
                            }
                            else
                            {
                                return child_right_->add(data, assign);
                            }
                        }
                        else
                        {
                            if (assign)
                            {
                                data_ = data;
                            }
                            return std::make_pair(node::shared_from_this(), false);
                        }
                    }

                    std::shared_ptr<node> first()
                    {
                        if (child_left_ == nullptr)
                        {
                            return node::shared_from_this();
                        } else
                        {
                            return child_left_->first();
                        } 
                    }
            }; // class node

        private:
            std::shared_ptr<node> root_;
            size_t counter_;
        
        public:

            // public type aliases
            using key_type = K;
            using mapped_type = T;
            using value_type = std::pair<K, T>;

            // iterator: references a node within the tree
            class iterator 
            {

                protected:

                    // treemap is a friend, can call protected constructor
                    friend class treemap;

                    // construct iterator referencing a speciic node
                    // - only treemap shall be allowed to do so
                    iterator(const std::shared_ptr<node>& val, const std::shared_ptr<node>& root) : nodeObserver_(std::weak_ptr<node>(val)), root_(std::weak_ptr<node>(root))
                    {}

                    // non-owning reference to the actual node
                    std::weak_ptr<node> nodeObserver_;
                    std::weak_ptr<node> root_;

                public:

                    // access data of referenced map element (node)
                    value_type& operator*()
                    {
                        //nullptr check? what to return if nullptr
                        auto node_ptr = nodeObserver_.lock();
                        
                        return node_ptr->data_;
                    }
                    value_type* operator->()
                    {
                        auto node_ptr = nodeObserver_.lock();
                        return &node_ptr->data_;
                    }

                    // two iterators are equal if they point to the same node
                    bool operator==(const iterator& lhs) const
                    {
                        return nodeObserver_.lock() == lhs.nodeObserver_.lock();
                    }

                    bool operator!=(const iterator& lhs) const
                    {
                        return !(*this == lhs);
                    }

                    // next element in map, pre-increment
                    // note: must modify self!
                    iterator& operator++()
                    {
                        //https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html
                        auto node_ptr = nodeObserver_.lock();
                        std::shared_ptr<node> tmp;

                        if (node_ptr->child_right_ != nullptr)
                        {
                            node_ptr = node_ptr->child_right_;

                            while (node_ptr->child_left_ != nullptr)
                            {
                                node_ptr = node_ptr->child_left_;
                            }
                        }
                        else
                        {
                            tmp = node_ptr->parent_.lock();

                            while (tmp != nullptr && node_ptr == tmp->child_right_)
                            {
                                node_ptr = tmp;
                                tmp = tmp->parent_.lock();
                            }

                            node_ptr = tmp;
                        }

                        *this = iterator(node_ptr, root_.lock());
                        return *this;
                        
                    }

                    // prev element in map, pre-decrement
                    // note: must modify self!
                    iterator& operator--()
                    {
                        auto node_ptr = nodeObserver_.lock();
                        std::shared_ptr<node> tmp;

                        if (node_ptr == nullptr)
                        {
                            auto root_ptr = root_.lock();
                            node_ptr = root_ptr->child_right_;

                            while (node_ptr->child_right_ != nullptr)
                            {
                                node_ptr = node_ptr->child_right_;
                            }
                        }
                        else if (node_ptr->child_left_ != nullptr)
                        {
                            node_ptr = node_ptr->child_left_;

                            while (node_ptr->child_left_ != nullptr)
                            {
                                node_ptr = node_ptr->child_left_;
                            }
                        }
                        else
                        {
                            node_ptr = node_ptr->parent_.lock();
                        }
                        
                        
                        *this = iterator(node_ptr, root_.lock());
                        return *this;
                    }

            }; // class iterator


            // used for copy&move
            template<typename KK, typename TT>
            friend void ::swap(treemap<KK,TT>& , treemap<KK,TT>& );

            // construct empty map
            treemap();

            // move ctor
            treemap(treemap<K,T>&&);

            // deep copy ctor
            treemap(const treemap<K,T>&);

            // how often is the element contained in the map?
            // (for this type of container, can only return 0 or 1)
            size_t count(const K&) const;

            // assignment (move & copy)
            treemap<K,T>& operator=(treemap<K,T>);

            // remove/destroy all elements
            void clear();

            // random read-only access to value by key, does not modify map
            T operator[](const K& ) const;

            // random write access to value by key
            T& operator[](const K&);

            // number of elements in map (nodes in tree)
            size_t size() const;

            // iterator referencing first element (node) in map
            iterator begin();

            // iterator referencing no element (node) in map
            iterator end() const;

            // add a new element into the tree
            // returns pair, consisting of:
            // - iterator to element
            // - bool
            //   - true if element was inserted;
            //   - false if key was already in map (will not overwrite existing value)
            std::pair<iterator,bool> insert(const K&, const T&);

            // add a new element into the tree, or overwrite existing element if key already in map
            // returns:
            // - iterator to element
            // - true if element was newly created; false if existing element was overwritten
            std::pair<iterator,bool> insert_or_assign(const K&, const T&);

            // find element with specific key. returns end() if not found.
            iterator find(const K&) const;

    };

    template<typename K, typename T>
    treemap<K,T>::treemap() : root_(nullptr), counter_(0)
    {
    }

    template<typename K, typename T>
    void
    treemap<K,T>::clear()
    {
        root_ = nullptr;
        counter_ = 0;
    }

    // random read-only access to value by key
    template<typename K, typename T>
    T
    treemap<K,T>::operator[](const K& key) const
    {
        auto iter = find(key);
        return iter->second;
    }

    // random write access to value by key
    template<typename K, typename T>
    T&
    treemap<K,T>::operator[](const K& key)
    {
        auto iter = find(key);
        if (iter.nodeObserver_.lock() == nullptr)
        {
            auto insertion = insert(key, T());
            return insertion.first->second;
        }
        else
        {
            return iter->second;
        }
    }

    // number of elements in map (nodes in tree)
    template<typename K, typename T>
    size_t
    treemap<K,T>::size() const
    {
        return counter_;
    }

    // move ctor
    template<typename K, typename T>
    treemap<K,T>::treemap(treemap<K,T>&&)
    {
        /* todo */ 
    }

    // deep copy ctor
    template<typename K, typename T>
    treemap<K,T>::treemap(const treemap<K,T>& val) : root_(val.root_), counter_(val.counter_) 
    {
        /* todo */ 
    }

    // assignment (move & copy)
    template<typename K, typename T>
    treemap<K,T>& 
    treemap<K,T>::operator=(treemap<K,T>)
    {
        /* todo, use copy&swap */ 
        return *this;
    }


    // iterator referencing first element (node) in map
    template<typename K, typename T>
    typename treemap<K,T>::iterator
    treemap<K,T>::begin()
    {
        if (root_ == nullptr)
        {
            return iterator(nullptr, nullptr);
        }
        else
        {
            return iterator(root_->first(), root_);
        }
    }

    // iterator referencing no element (node) in map
    template<typename K, typename T>
    typename treemap<K,T>::iterator
    treemap<K,T>::end() const
    {
        /* todo */ return iterator(nullptr, root_);
    }

    // add a new element into the tree
    // returns:
    // - iterator to element
    // - true if element was inserted; false if key was already in map
    template<typename K, typename T>
    std::pair<typename treemap<K,T>::iterator,bool>
    treemap<K,T>::insert(const K& key, const T& val)
    {
        if (root_ == nullptr)
        {
            root_ = std::make_shared<node>(std::make_pair(key, val));
            counter_++;
            return std::make_pair(iterator(root_, root_), true);     
        }
        else
        {
            std::pair<std::shared_ptr<node>, bool> insertion = root_->add(std::make_pair(key, val), false);
            if (insertion.second == true)
            {
                counter_++;
            }
            
            return std::make_pair(iterator(insertion.first, root_), insertion.second);
        }
    }

    // add a new element into the tree, or overwrite existing element if key already in map
    // returns:
    // - iterator to element
    // - true if element was newly created; false if existing element was overwritten
    template<typename K, typename T>
    std::pair<typename treemap<K,T>::iterator,bool>
    treemap<K,T>::insert_or_assign(const K& key, const T& val)
    {
        if (root_ == nullptr)
        {
            root_ = std::make_shared<node>(std::make_pair(key, val));
            counter_++;
            return std::make_pair(iterator(root_, root_), true);
        }
        else
        {
            std::pair<std::shared_ptr<node>, bool> insertion = root_->add(std::make_pair(key, val), true);
            if (insertion.second == true)
            {
                counter_++;
            }
            return std::make_pair(iterator(insertion.first, root_), insertion.second);   
        }
    }

    // find element with specific key. returns end() if not found.
    template<typename K, typename T>
    typename treemap<K,T>::iterator
    treemap<K,T>::find(const K& key) const
    {
        if (root_ != nullptr)
        {
            return iterator(root_->search(key), root_);
        }
        else
        {
            return iterator(nullptr, root_);
        }
    }

    // how often is the element contained in the map?
    template<typename K, typename T>
    size_t
    treemap<K,T>::count(const K& val) const
    {
        if (root_ != nullptr && root_->search(val) != nullptr)
        {
            return 1;
        }
        
        return 0;
    }

} // namespace my

// swap is overloaded in global namespace
// see https://stackoverflow.com/questions/11562/how-to-overload-stdswap
// (answer by Attention Mozza314)
template<typename K, typename T>
void
swap(my::treemap<K,T>&, my::treemap<K,T>&)
{
}

